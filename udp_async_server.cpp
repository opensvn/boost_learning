#include <iostream>
#include <ctime>
#include <string>
#include <boost/array.hpp>
#include <boost/shared_array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using boost::asio::ip::udp;

string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server(boost::asio::io_service &io_service) :
            socket_(io_service, udp::endpoint(udp::v4(), 13))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::bind(&udp_server::handle_receive, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code &error, size_t)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            boost::shared_ptr<string> message(
                    new string(make_daytime_string()));

            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                                  boost::bind(&udp_server::handle_send, this, message,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<string>, const boost::system::error_code &,
                     size_t)
    { }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};

int main()
{
    try
    {
        boost::asio::io_service io_service;
        udp_server service(io_service);
        io_service.run();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
