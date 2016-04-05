#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

void conn_handler(const boost::system::error_code&)
{

}

void time_expired(const boost::system::error_code&,
                  ip::tcp::socket *sock)
{
    cout << "time expired" << endl;
    sock->close();
}

int main()
{
    try
    {
        io_service ios;
        ip::tcp::socket sock(ios);
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 6688);

        sock.async_connect(ep, &conn_handler);
        deadline_timer t(ios, boost::posix_time::seconds(5));
        t.async_wait(bind(time_expired, placeholders::error, &sock));

        ios.run();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
