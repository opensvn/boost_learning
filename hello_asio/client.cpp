#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include "flag.hpp"

using namespace std;
using namespace boost::asio;

static const std::string s = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOQPRSTUVWXYZ"
        "0123456789!@#$%^&*()-_+=\\|`~;:'\"<>,./?";

class Client
{
public:
    Client(io_service &ios, std::string host, int port):
            socket(ios), ep(ip::address::from_string(host), port),
            sig(ios), writtenMB(0), readMB(0)
    {
        sendStr.reserve(max_len);

        for (std::string::size_type i = 0; i != sendStr.capacity(); ++i)
        {
            sendStr.push_back(s[i%s.size()]);
        }

        sig.add(SIGINT);
        sig.add(SIGTERM);
        sig.async_wait(bind(&Client::onSignal, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::signal_number));

        memset(read_buf, 0, sizeof(read_buf));
//        srand(time(0));
    }

    ~Client()
    {
        std::cout << IP << ":" << port << " Written: "
                  << writtenMB * max_len << " Read: " << readMB * max_len << std::endl;
    }

    void startConnect()
    {
        socket.async_connect(ep, bind(&Client::onConnected, this,
                                      placeholders::error));
    }

private:
    void onConnected(const boost::system::error_code &ec)
    {
        if (ec)
        {
            std::cout << "onConnected: " << ec.message() << std::endl;
            close();
            return;
        }

        IP = socket.local_endpoint().address().to_string();
        port = socket.local_endpoint().port();

        startWrite();
    }

    void startWrite()
    {
//        shuffle_string(); // 打乱字符串
        async_write(socket, buffer(sendStr),
                    bind(&Client::onWrite, this, placeholders::error));
    }

    void onWrite(const boost::system::error_code &ec)
    {
        if (ec)
        {
            std::cout << "onWrite: " << ec.message() << std::endl;
            return;
        }

        writtenMB += 1;

        startRead();
    }

    void startRead()
    {
        async_read(socket, buffer(read_buf, max_len),
                   bind(&Client::onRead, this, placeholders::error));
    }

    void onRead(const boost::system::error_code &ec)
    {
        if (ec)
        {
            std::cout << "onRead: " << ec.message() << std::endl;
            return;
        }

        readMB += 1;

        std::cout << string(read_buf, read_buf + max_len) << std::endl;

        usleep(10);
        startWrite();
    }

    void onSignal(const boost::system::error_code& ec, int signal)
    {
        if (ec)
        {
            std::cout << "onSignal: " << ec.message() << std::endl;
            return;
        }

        close();
    }

    void shuffle_string()
    {
        random_shuffle(sendStr.begin(), sendStr.end());
    }

    void close()
    {
        socket.close();
    }

private:
    std::string sendStr;

    ip::tcp::socket socket;
    ip::tcp::endpoint ep;
    signal_set sig;

    enum {max_len = 1024};
    char read_buf[max_len];

    size_t writtenMB;
    size_t readMB;

    std::string IP;
    int port;
};

int main(int argc, const char *argv[])
{
    Flag flag;

    flag.addOption("h", "127.0.0.1", "server address");
    flag.addOption("p", "10001", "server port");
    flag.addOption("c", "1", "number of client to run");

    if (!flag.parse(argc, argv))
    {
        std::cout << flag.help() << std::endl;
        return -1;
    }

    std::string host;
    int port;
    int clientNum;

    flag.getString("h", host);
    flag.getInt("p", port);
    flag.getInt("c", clientNum);

    io_service ios;

    std::list<boost::shared_ptr<Client> > clients;
    boost::thread_group threads;

    for (int i = 0; i < clientNum; ++i)
    {
        boost::shared_ptr<Client> c(new Client(ios, host, port));
        clients.push_back(c);
        c->startConnect();
    }

    int coreNum = boost::thread::hardware_concurrency();
    for (int i = 0; i < coreNum; ++i)
    {
        threads.create_thread(boost::bind(&boost::asio::io_service::run, &ios));
    }

    threads.join_all();

    return 0;
}
