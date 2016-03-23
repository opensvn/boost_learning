#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

void resolv_connect(ip::tcp::socket &sock,
                    const char *name, int port)
{
    ip::tcp::resolver rlv(sock.get_io_service());
    ip::tcp::resolver::query qry(name, boost::lexical_cast<string>(port));

    ip::tcp::resolver::iterator iter = rlv.resolve(qry);
    ip::tcp::resolver::iterator end;
    boost::system::error_code ec = error::host_not_found;

    for (; ec && iter != end; ++iter)
    {
        sock.close();
        sock.connect(*iter, ec);
    }
    if (ec)
    {
        cout << "can't connect." << endl;
        throw boost::system::system_error(ec);
    }
    cout << "connect success." << endl;
    cout << sock.remote_endpoint().address() << endl;
}

int main()
{
    try
    {
        io_service ios;
        ip::tcp::socket sock(ios);
        resolv_connect(sock, "www.boost.org", 80);
        ios.run();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
