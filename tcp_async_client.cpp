#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost::asio;

class client
{
private:
    io_service &ios;
    ip::tcp::endpoint ep;
    typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
    int count;
public:
    client(io_service &io):
        ios(io), ep(ip::address::from_string("127.0.0.1"), 6688), count(0)
    {
        start();
    }

    void start()
    {
        if (count >= 10)
            return;
        ++count;
        sock_pt sock(new ip::tcp::socket(ios));
        sock->async_connect(ep,
                            boost::bind(&client::conn_handler, this, placeholders::error, sock));
    }

    void conn_handler(const boost::system::error_code &ec, sock_pt sock)
    {
        if (ec)
            return;
        cout << "receive from " << sock->remote_endpoint().address();
        boost::shared_ptr<vector<char> > buf(new vector<char>(100, 0));
        sock->async_read_some(buffer(*buf),
                              boost::bind(&client::read_handler, this, placeholders::error, buf));
        start();
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
    try
    {
        io_service ios;
        client c(ios);
        ios.run();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
