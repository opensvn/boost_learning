#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
    cout << "UDP server start!" << endl;
    io_service ios;

    ip::udp::socket sock(ios, ip::udp::endpoint(ip::udp::v4(), 6699));

    while (true)
    {
        char buf[1];
        ip::udp::endpoint ep;

        boost::system::error_code ec;
        sock.receive_from(buffer(buf), ep, 0, ec);

        if (ec && ec != error::message_size)
            throw boost::system::system_error(ec);

        cout << "send to " << ep.address() << endl;
        sock.send_to(buffer("hello asio udp"), ep);
    }
    return 0;
}
