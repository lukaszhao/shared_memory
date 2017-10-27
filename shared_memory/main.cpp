#include <iostream>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>



using namespace std;


void create_shared_memory() {

    using namespace boost::interprocess;

    //Create a shared memory object.
    shared_memory_object shm (create_only, "MySharedMemory", read_write);

    //Set size
    shm.truncate(1000);

    //Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    //Write all the memory to same value
    std::memset(region.get_address(), '2', region.get_size());

    while(true) {}
}


int main()
{
    cout << "Create shared memory..." << endl;
    create_shared_memory();
    return 0;
}
