#include <iostream>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>


using namespace std;

void read_shared_memory() {

    using namespace boost::interprocess;

    //Open already created shared memory object.
    shared_memory_object shm (open_only, "MySharedMemory", read_only);

    //Map the whole shared memory in this process
    mapped_region region(shm, read_only);

    //Check that memory was initialized to 1
    char *mem = static_cast<char*>(region.get_address());

    cout << "region.get_size() = " << region.get_size() << endl;

    for(std::size_t i = 0; i < region.get_size(); ++i) {
        cout << "*mem++ = " << *mem++ << endl;
    }

    char yesOrNo = 'n';
    cout << "End (y): "; cin >> yesOrNo;

}

void destroy_shared_memory() {
    cout << "Destroy shared memory...\n";
    using namespace boost::interprocess;
    shared_memory_object::remove("MySharedMemory");
}

int main()
{
    cout << "Reading shared memory...\n" << endl;
    read_shared_memory();
    destroy_shared_memory();
    return 0;
}
