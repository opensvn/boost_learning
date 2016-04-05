#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using namespace std;

void print(boost::system::error_code&)
{
    cout << "expired!" << endl;
}

int main()
{
    io_service ios;
    deadline_timer t(ios, boost::posix_time::seconds(2));
//    cout << t.expires_at() << endl;
//    t.wait();
//    cout << "hello asio" << endl;

    boost::system::error_code ec;
    t.async_wait(boost::bind(print, ec));
    cout << "it show before t expired." << endl;
    ios.run();

    return 0;
}
