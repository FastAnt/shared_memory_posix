#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MEM_SIZE 1048576
#define KEY_SNAME "/test.shm"

class nullPtrErr{};

void* alloc_memory(size_t size)
{
	try
	{
		void *ptr = nullptr;
		int shm_fd;  // shared memory file descriptor
		shm_fd = shm_open(KEY_SNAME, O_CREAT | O_RDWR, 0644);
		ftruncate(shm_fd, MEM_SIZE);
		ptr = mmap(0, MEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if (ptr == MAP_FAILED) 
			throw nullPtrErr();
		return ptr;
	}
	catch(nullPtrErr)
	{
		std::cout << "ptr shit" << std::endl;
		return nullptr;
	}
	catch(...)
	{
		std::cout << "some shit" << std::endl;
	}

}
int main(int argc, char **argv)
{
	char *ptr = (char *)alloc_memory(MEM_SIZE);
	if (ptr){
		memset(ptr, 42, MEM_SIZE);
	}
	else
		std::cout << "" << std::endl;
	pause();
	return 0;
}
