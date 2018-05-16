#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using namespace std;

class Server: public boost::enable_shared_from_this<Server>
{
public:
    typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;

    Server(io_service &ios, const ip::tcp::endpoint &ep):
            ios_(ios), acceptor_(ios, ep)
    {
        start_accept();
    }

private:
    void start_accept()
    {
        new_connection.reset(new ip::tcp::socket(ios_));
        acceptor_.async_accept(*new_connection,
                               bind(&Server::handle_accept, this,
                                   placeholders::error));
    }

    void handle_accept(const boost::system::error_code &ec)
    {
        if (!ec)
        {
            async_read(*new_connection, buffer(read_buf),
                bind(&Server::handle_read, shared_from_this(),
                    placeholders::error));
        }
        start_accept();
    }

    void handle_read(const boost::system::error_code &ec)
    {
        if (!ec)
        {
            async_write(*new_connection, buffer(read_buf),
                bind(&Server::handle_write, shared_from_this(),
                    placeholders::error));
            cout << read_buf << endl;
        }
    }

    void handle_write(const boost::system::error_code &ec)
    {
        ;
    }

private:
    sock_ptr new_connection;
    io_service &ios_;
    ip::tcp::acceptor acceptor_;
    enum {max_len=1024};
    char read_buf[max_len];
    char write_buf[max_len];
};

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: server port" << endl;
        return -1;
    }

    try
    {
        io_service ios;
        ip::tcp::endpoint ep(ip::tcp::v4(), atoi(argv[1]));
        Server s(ios, ep);

        ios.run();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}