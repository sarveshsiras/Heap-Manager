/*These are prototypes like normal dynamic memory allocators.*/
void *smalloc(size_t size);
void *scalloc(size_t nmemb, size_t size);
void *srealloc(void *ptr, size_t size);
void sfree(void *ptr);
void initialize(); //It initializes a new chunk of memory using sbrk
void* assign(size_t size);//It assignes a particular pointer to the memory obtained using sbrk.
