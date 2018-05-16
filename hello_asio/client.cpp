//
// Created by root on 16-4-11.
//

#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::asio;
using boost::bind;

class Client
{
public:
    Client(io_service &ios, std::string host, int port):
            sock(ios), ep(ip::address::from_string(host), port),
            sig(ios)
    {
        send_str = "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOQPRSTUVWXYZ"
                   "0123456789!@#$%^&*()-_+=\\|`~;:'\"<>,./?";
        sig.add(SIGINT);
        sig.add(SIGTERM);
        sig.async_wait(bind(&Client::sig_handle, this));
        is_connected = false;
        sock.async_connect(ep, bind(&Client::handle_connect, this,
                                    placeholders::error));
    }

private:
    void handle_connect(const boost::system::error_code &ec)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        if (!ec)
        {
            is_connected = true;
            shuffle_string();
            cout << send_str << endl;
            async_write(sock, buffer(send_str),
                        bind(&Client::handle_write, this, placeholders::error));
        }
        else
        {
            std::cout << "connect error!" << ec.message() << std::endl;
            sock.close();
        }
    }

    void handle_write(const boost::system::error_code &ec)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        if (!is_connected) return;

        if (!ec)
        {
            async_read(sock, buffer(read_buf, send_str.size()),
                       bind(&Client::handle_read, this, placeholders::error));
        }
        else
        {
            sock.close();
        }
    }

    void handle_read(const boost::system::error_code &ec)
    {
        cout << __PRETTY_FUNCTION__ << endl;

        if (!is_connected) return;

        if (!ec)
        {
            cout << read_buf << endl;
            boost::this_thread::sleep(boost::posix_time::millisec(1000));
            shuffle_string();
            async_write(sock, buffer(send_str),
                        bind(&Client::handle_write, this, placeholders::error));
        }
        else
        {
            sock.close();
        }
    }

    void sig_handle()
    {
        cout << __PRETTY_FUNCTION__ << endl;
        is_connected = false;
        sock.close();
    }

    void shuffle_string()
    {
        random_shuffle(send_str.begin(), send_str.end());
    }

private:
    std::string send_str;

    ip::tcp::socket sock;
    ip::tcp::endpoint ep;
    signal_set sig;
    bool is_connected;
    enum {max_len = 1024};
    char read_buf[max_len];
};

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: client host port" << endl;
        return -1;
    }

    io_service ios;

    Client c(ios, argv[1], atoi(argv[2]));

    ios.run();

    return 0;
}
