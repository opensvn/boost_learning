#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

using namespace std;

int main()
{
    boost::interprocess::shared_memory_object::remove("Highscore");
    boost::interprocess::managed_shared_memory managed_shm(
        boost::interprocess::open_or_create, "Highscore", 1024);

    typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
    typedef boost::interprocess::basic_string<char, char_traits<char>, CharAllocator> bstring;
    bstring *bs = managed_shm.find_or_construct<bstring>("BString")("Hello!", managed_shm.get_segment_manager());
    bs->insert(5, ", world");
    cout << *bs << endl;

    int *i = managed_shm.construct<int>("Integer")[10](99);
//    cout << *i << endl;
    string *s = managed_shm.construct<string>("String")("Hello, world");
//    cout << *s <<endl;

    pair<int *, size_t> p = managed_shm.find<int>("Integer");
    if (p.first)
    {
//        for (int i = 0; i < 10; ++i, ++p.first)
//            cout << *p.first << endl;
//        cout << p.second <<endl;
    }
    pair<string *, size_t> q = managed_shm.find<string>("String");
    if (q.first)
    {
//        cout << *q.first << endl;
//        cout << q.second << endl;
    }

    managed_shm.destroy<int>("Integer");
    managed_shm.destroy<string>("String");

    q = managed_shm.find<string>("String");
    if (q.first)
    {
        cout << *q.first << endl;
    }

    return 0;
}
