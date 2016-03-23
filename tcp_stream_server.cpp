#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
    io_service ios;

    ip::tcp::endpoint ep(ip::tcp::v4(), 6688);
    ip::tcp::acceptor acceptor(ios, ep);

    while (true)
    {
        ip::tcp::iostream tcp_stream;
        acceptor.accept(*tcp_stream.rdbuf());
        tcp_stream << "hello tcp stream.";
    }

    return 0;
}
