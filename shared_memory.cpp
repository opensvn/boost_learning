#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;

int main()
{
    boost::interprocess::shared_memory_object shdmem(
            boost::interprocess::open_or_create,
            "Highscore",
            boost::interprocess::read_write);
    shdmem.truncate(1024);

    boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write);
    cout << hex << region.get_address() << endl;
    cout << dec << region.get_size() << endl;
    int *i1 = static_cast<int *>(region.get_address());
    *i1 = 99;
    char *p = static_cast<char *>(region.get_address()) + 4;
    strcpy(p, "Hello, shared_memory.");

    boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only);
    cout << hex << region2.get_address() << endl;
    cout << dec << region2.get_size() << endl;
    int *i2 = static_cast<int *>(region2.get_address());
    cout << *i2 << endl;
    char *q = static_cast<char *>(region2.get_address()) + 4;
    cout << q << endl;

//    cout << shdmem.get_name() << endl;
//    boost::interprocess::offset_t size;
//    if (shdmem.get_size(size))
//        cout << size << endl;
    bool removed = boost::interprocess::shared_memory_object::remove("Highscore");
    cout << removed << endl;

    return 0;
}
