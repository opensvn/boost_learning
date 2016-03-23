#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost::asio;

class server
{
private:
    io_service &ios;
    ip::tcp::acceptor acceptor;
    typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
public:
    server(io_service& io):
        ios(io), acceptor(ios, ip::tcp::endpoint(ip::tcp::v4(), 6688))
    {
        start();
    }

    void start()
    {
        sock_pt sock(new ip::tcp::socket(ios));
        acceptor.async_accept(*sock,
                              boost::bind(&server::accept_handler, this,
                                          placeholders::error, sock));
    }

    void accept_handler(const boost::system::error_code &ec, sock_pt sock)
    {
        if (ec)
            return;
        cout << "client:";
        cout << sock->remote_endpoint().address() << endl;
        sock->async_write_some(buffer("hello asio"),
                               boost::bind(&server::write_handler, this, placeholders::error));
        start();
    }

    void write_handler(const boost::system::error_code&)
    {
        cout << "send msg complete." << endl;
    }
};

int main()
{
    try
    {
        cout << "server start." << endl;
        io_service ios;
        server s(ios);
        ios.run();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
