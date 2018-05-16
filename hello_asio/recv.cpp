#include <iostream>
#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>

#include "flag.hpp"

using namespace boost::asio;
using namespace std;

static const std::string s = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOQPRSTUVWXYZ"
        "0123456789!@#$%^&*()-_+=\\|`~;:'\"<>,./?";

class Connection: public boost::enable_shared_from_this<Connection>,
                  private boost::noncopyable
{
public:
    Connection(io_service &ios): socket(ios), writtenMB(0), readMB(0) {}

    ~Connection()
    {
        std::cout << remoteIP << ":" << remotePort << " Written: "
                  << writtenMB << " Read: " << readMB << std::endl;
    }

    void start()
    {
        remoteIP = socket.remote_endpoint().address().to_string();
        remotePort = socket.remote_endpoint().port();

        startRead();
    }

    ip::tcp::socket &getSocket()
    {
        return socket;
    }

private:
    void startRead()
    {
        boost::asio::async_read(socket, buffer(read_buf, max_len),
                                boost::bind(&Connection::onRead,
                                            shared_from_this(),
                                            placeholders::error));
    }

    void onRead(const boost::system::error_code &ec)
    {
        if (ec)
        {
            std::cout << "onRead: " << ec.message() << std::endl;
            return;
        }

        readMB += 1;

        startRead();
    }

private:
    ip::tcp::socket socket;
    enum {max_len = 1024 * 64}; // 1MB
    char read_buf[max_len];

    size_t writtenMB;
    size_t readMB;

    std::string remoteIP;
    int remotePort;
};

class Server
{
public:
    typedef boost::shared_ptr<Connection> ConnectionPtr;

    Server(io_service &ios, const ip::tcp::endpoint &ep):
        ios_(ios), acceptor_(ios, ep)
    {
    }

    void startAccept()
    {
        new_connection.reset(new Connection(ios_));
        acceptor_.async_accept(new_connection->getSocket(),
                               boost::bind(&Server::onAccept, this,
                                           new_connection, placeholders::error));
    }

private:
    void onAccept(ConnectionPtr connection, const boost::system::error_code &ec)
    {
        if (!ec)
        {
            connection->start();
        }

        startAccept();
    }

private:
    ConnectionPtr new_connection;
    io_service &ios_;
    ip::tcp::acceptor acceptor_;
};

ip::tcp::endpoint makeEndpoint(const std::string& ip, int port)
{
    if (ip.empty())
        return ip::tcp::endpoint(ip::tcp::v4(), port);
    else
        return ip::tcp::endpoint(ip::address::from_string(ip), port);
}

int main(int argc, const char *argv[])
{
    Flag flag;
    flag.addOption("h", "", "listening ip");
    flag.addOption("p", "10001", "listening port");

    if (!flag.parse(argc, argv))
    {
        std::cout << flag.help() << std::endl;
        return -1;
    }

    std::string ip;
    int port;

    flag.getString("h", ip);
    flag.getInt("p", port);

    try
    {
        io_service ios;

        Server server(ios, makeEndpoint(ip, port));
        server.startAccept();

        ios.run();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
