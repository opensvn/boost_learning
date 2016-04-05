#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost::asio;

class a_timer
{
private:
    int count, count_max;
    boost::function<void()> f;
    boost::asio::deadline_timer t;
public:
    template<typename F>
    a_timer(io_service &ios, int x, F func) :
            t(ios, boost::posix_time::millisec(500)), count_max(x), count(0),
            f(func)
    {
        t.async_wait(boost::bind(&a_timer::wait_handler, this,
                                 placeholders::error));
    }

    void wait_handler(const boost::system::error_code &)
    {
        if (count >= count_max)
            return;
        ++count;
        f();
        t.expires_at(t.expires_at() + boost::posix_time::millisec(500));
        t.async_wait(boost::bind(&a_timer::wait_handler, this,
                                 placeholders::error));
    }
};

class client
{
private:
    a_timer timer;
public:
    typedef boost::shared_ptr<ip::tcp::socket> sock_pt;

    client(io_service &ios, int x) :
            timer(ios, x, boost::bind(&client::connect_handler, this, boost::ref(ios)))
    {
    }

    void connect_handler(io_service &ios)
    {
        sock_pt p(new ip::tcp::socket(ios));
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 6688);

        p->async_connect(ep, boost::bind(&client::conn_handler, this, placeholders::error, p));
    }

//    void read_handler(sock_pt p)
//    {
//        boost::shared_ptr<vector<char> > buf(new vector<char>(100, 0));
//        p->async_read_some(buffer(buf), boost::bind(&client::void_handler, this, buf));
//    }
//
//    void void_handler(boost::shared_ptr<vector<char> > buf)
//    {
//        cout << &(*buf)[0] << endl;
//    }
    void conn_handler(const boost::system::error_code &ec, sock_pt sock)
    {
        if (ec)
            return;
        cout << "receive from " << sock->remote_endpoint().address();
        boost::shared_ptr<vector<char> > buf(new vector<char>(100, 0));
        sock->async_read_some(buffer(*buf),
                              boost::bind(&client::read_handler, this, placeholders::error, buf));
    }

    void read_handler(const boost::system::error_code &ec,
                      boost::shared_ptr<vector<char> > buf)
    {
        if (ec)
            return;
        cout << " " << &(*buf)[0] << endl;
    }
};

int main()
{
    io_service ios;
    client c(ios, 10);
    ios.run();
    return 0;
}
