#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

void time_expired(boost::system::error_code &ec, serial_port *sp)
{
    cout << "time_expired" << endl;
    sp->close();
}

void read_handler(boost::system::error_code &ec)
{
    cout << ec.message() << endl;
}

int main()
{
    io_service ios;
    serial_port sp(ios, "COM1");

    sp.set_option(serial_port::baud_rate(9600));
    sp.set_option(serial_port::flow_control(serial_port::flow_control::none));
    sp.set_option(serial_port::parity(serial_port::parity::none));
    sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
    sp.set_option(serial_port::character_size(8));

    size_t len = sp.write_some(buffer("hello serial"));
    cout << len << endl;

    vector<char> v(100);
    sp.async_read_some(buffer(v), boost::bind(read_handler, placeholders::error));
    deadline_timer t(ios, boost::posix_time::seconds(2));
    t.async_wait(boost::bind(time_expired, placeholders::error, &sp));

    ios.run();

    return 0;
}
