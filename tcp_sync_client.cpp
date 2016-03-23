#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;

class a_timer
{
private:
    int count, count_max;
    boost::function<void()> f;
    boost::asio::deadline_timer t;
public:
    template <typename F>
    a_timer(boost::asio::io_service &ios, int x, F func):
        f(func), count_max(x), count(0),
        t(ios, boost::posix_time::millisec(500))
    {
        t.async_wait(boost::bind(&a_timer::call_func, this,
                                 boost::asio::placeholders::error));
    }
    void call_func(const boost::system::error_code&)
    {
        if (count >= count_max)
            return;
        ++count;
        f();
        t.expires_at(t.expires_at() + boost::posix_time::millisec(500));
        t.async_wait(boost::bind(&a_timer::call_func, this,
                                 boost::asio::placeholders::error));
    }
};

void client(boost::asio::io_service &ios)
{
    try
    {
        cout << "client start." << endl;

        boost::asio::ip::tcp::socket sock(ios);
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 6688);

        sock.connect(ep);
        vector<char> str(100, 0);
        sock.read_some(boost::asio::buffer(str));

        cout << "receive from " << sock.remote_endpoint().address();
        cout << " " << &str[0] << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}

int main()
{
    boost::asio::io_service ios;
    a_timer at(ios, 5, boost::bind(client, boost::ref(ios)));
    ios.run();
    return 0;
}
