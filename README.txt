Title: HEAP MANAGER
Name: Sarvesh Prashant Siras
MIS ID: 111708059
Description :
I have created my own set of functions like smalloc, scalloc, srealloc and sfree instead of predefined functions like malloc, calloc, realloc and free. I have allocated dynamic memory using the system call sbrk. This dynamic memory received should be managed by keeping the record. There are several ways, I have used buddy type memory allocator in which a big chunk of memory is received from the system and it is further broken and allocated as per the need. To keep the record of memory allocated at which point of what size I have implemented a list type data structure which uses array of structures to store the record of memory allocated and freed. Also I have tried to reuse the previously freed memory from the buddy(memory chunk).
