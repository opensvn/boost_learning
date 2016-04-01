#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace std;

void handler(const boost::system::error_code &ec)
{
    cout << "5s." << endl;
}

void handler1(const boost::system::error_code &ec)
{
    cout << "6s." << endl;
}

void handler2(const boost::system::error_code &ec)
{
    cout << "10s." << endl;
}

boost::asio::io_service io_service;
boost::asio::io_service io_service1;
boost::asio::io_service io_service2;

void run()
{
    io_service.run();
}

void run1()
{
    io_service1.run();
}

void run2()
{
    io_service2.run();
}

int main()
{
    boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(5));
    timer.async_wait(handler);

    boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(6));
    timer1.async_wait(handler1);

    boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(10));
    timer2.async_wait(handler2);

    io_service.run();
    boost::thread thread1(run1);
    boost::thread thread2(run2);

    thread1.join();
    thread2.join();

    return 0;
}
