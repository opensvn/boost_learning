#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        ip::tcp::iostream tcp_stream("localhost", "6688");
        string str;
        getline(tcp_stream, str);
        cout << str << endl;
    }
    return 0;
}
