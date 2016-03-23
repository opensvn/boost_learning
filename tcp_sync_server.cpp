#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
//    boost::asio::ip::address addr;
//    addr = addr.from_string("127.0.0.1");
//    assert(addr.is_v4());
//    cout << addr.to_string() << endl;
//    boost::asio::ip::tcp::endpoint ep(addr, 6688);
//    assert(ep.address() == addr);
//    assert(ep.port() == 6688);
//    addr = addr.from_string("ab::12:34:56");
//    assert(addr.is_v6());
//    cout << addr.to_string() << endl;

    try
    {
        cout << "server start." << endl;
        boost::asio::io_service ios;
        boost::asio::ip::tcp::acceptor acceptor(ios,
                                                boost::asio::ip::tcp::endpoint(
                                                                               boost::asio::ip::tcp::v4(), 6688));

        cout << acceptor.local_endpoint().address() << endl;

        while (true)
        {
            boost::asio::ip::tcp::socket sock(ios);
            acceptor.accept(sock);

            cout << "client:";
            cout << sock.remote_endpoint().address() << endl;

            sock.write_some(boost::asio::buffer("hello asio"));
        }
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
