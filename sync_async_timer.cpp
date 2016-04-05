#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void timer_sync()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.wait();
    cout << __func__ << endl;
}

void print(const boost::system::error_code &ec)
{
    cout << "timer_async" << endl;
}

void timer_async()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.async_wait(print);
    io.run();
}

void print(const boost::system::error_code &,
           boost::asio::deadline_timer *t, int *count)
{
    if (*count < 5)
    {
        cout << *count << endl;
        ++*count;
        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
    }
}

void timer_async2()
{
    boost::asio::io_service io;
    int count = 0;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.async_wait(boost::bind(print,
                             boost::asio::placeholders::error, &t, &count));
    cout << __func__ << endl;
    io.run();
    cout << "Final count is " << count << endl;
}

class Printer
{
public:
    Printer(boost::asio::io_service &io) :
            timer_(io, boost::posix_time::seconds(1)),
            count_(0)
    {
        cout << __func__ << endl;
        timer_.async_wait(boost::bind(&Printer::print, this));
    }

    ~Printer()
    {
        cout << "Final count is " << count_ << endl;
    }

    void print()
    {
        if (count_ < 5)
        {
            cout << count_ << endl;
            ++count_;

            timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&Printer::print, this));
        }
    }

private:
    boost::asio::deadline_timer timer_;
    int count_;
};

void timer_async_class()
{
    boost::asio::io_service io;
    Printer p(io);
    io.run();
}

int main()
{
    timer_sync();
    timer_async();
    timer_async2();
    timer_async_class();
    return 0;
}
