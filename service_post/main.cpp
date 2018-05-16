#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace std;
//using namespace boost::asio;
//io_service service;
//void func(int i) {
//    cout << "Thread ID: " << boost::this_thread::get_id() << " ";
//    std::cout << "func called, i= " << i << std::endl;
//}
//void worker_thread() {
//    service.run();
//}
//int main(int argc, char* argv[]) {
//    for (int i = 0; i < 10; ++i)
//        service.post(boost::bind(func, i));
//    boost::thread_group threads;
//    for (int i = 0; i < 3; ++i)
//        threads.create_thread(worker_thread);
//    // wait for all threads to be created
//    boost::this_thread::sleep(boost::posix_time::millisec(500));
//    threads.join_all();
//}
using namespace boost::asio;
io_service service;
//void func(int i) {
//    std::cout << "func called, i= " << i << "/"
//    << boost::this_thread::get_id() << std::endl;
//}
//void worker_thread() {
//    service.run();
//}
//int main(int argc, char* argv[])
//{
//    io_service::strand strand_one(service), strand_two(service);
//    for ( int i = 0; i < 5; ++i)
//        service.post(strand_one.wrap( boost::bind(func, i)));
//    for ( int i = 5; i < 10; ++i)
//        service.post(strand_two.wrap( boost::bind(func, i)));
//    boost::thread_group threads;
//    for ( int i = 0; i < 3; ++i)
//        threads.create_thread(worker_thread);
//    // wait for all threads to be created
//    boost::this_thread::sleep( boost::posix_time::millisec(500));
//    threads.join_all();
//}
//void func(int i) {
//    std::cout << "func called, i= " << i << std::endl;
//}
//void run_dispatch_and_post() {
//    for ( int i = 0; i < 10; i += 2) {
//        service.dispatch(boost::bind(func, i));
//        service.post(boost::bind(func, i + 1));
//    }
//}
//int main(int argc, char* argv[]) {
//    service.post(run_dispatch_and_post);
//    service.run();
//}
//void dispatched_func_1() {
//    std::cout << "dispatched 1" << std::endl;
//}
//void dispatched_func_2() {
//    std::cout << "dispatched 2" << std::endl;
//}
//void test(boost::function<void()> func) {
//    std::cout << "test" << std::endl;
//    service.dispatch(dispatched_func_1);
//    func();
//}
//void service_run() {
//    service.run();
//}
//int main(int argc, char* argv[]) {
//    test(service.wrap(dispatched_func_2));
//    boost::thread th(service_run);
//    boost::this_thread::sleep( boost::posix_time::millisec(500));
//    th.join();
//}
struct connection : boost::enable_shared_from_this<connection> {
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<connection> ptr;
    connection() : sock_(service), started_(true) {}
    void start(ip::tcp::endpoint ep) {
        sock_.async_connect(ep,
                            boost::bind(&connection::on_connect, shared_from_this(),
                                        _1));
    }
    void stop() {
        if ( !started_) return;
        started_ = false;
        sock_.close();
    }
    bool started() { return started_; }
private:
    void on_connect(const error_code & err) {
        // here you decide what to do with the connection: read or write
        if (!err) do_read();
        else stop();
    }
    void on_read(const error_code & err, size_t bytes) {
        if (!started()) return;
        std::string msg(read_buffer_, bytes);
        if (msg == "can_login") do_write("access_data");
        else if (msg.find("data ") == 0) process_data(msg);
        else if (msg == "login_fail") stop();
    }
    void on_write(const error_code & err, size_t bytes) {
        do_read();
    }
    void do_read() {
        sock_.async_read_some(buffer(read_buffer_),
                              boost::bind(&connection::on_read, shared_from_this(),
                                          _1, _2));
    }
    void do_write(const std::string & msg) {
        if ( !started() ) return;
        // note: in case you want to send several messages before
        // doing another async_read, you'll need several write buffers!
        std::copy(msg.begin(), msg.end(), write_buffer_);
        sock_.async_write_some(buffer(write_buffer_, msg.size()),
                               boost::bind(&connection::on_write, shared_from_this(),
                                           _1, _2));
    }
    void process_data(const std::string & msg) {
        // process what comes from server, and then perform another write
    }
private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
};
int main(int argc, char* argv[]) {
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"),
                          8001);
    connection::ptr(new connection)->start(ep);
}