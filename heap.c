#include <unistd.h>
#include "heap.h"
#include "manager.h"
#define MEM 512
manager m;
int i = 0;
void *smalloc(size_t size) {
	void *p, *q;
	int mem, pos;
	size = (size - 1) / 4 * 4 + 4;
	if(i == 0) {
		manageit(&m, MEM);
		p = sbrk(MEM);
		if(p == (void *) -1)
			return NULL;
		i++;
	}
	p = sbrk(0);
	pos = currposition(&m);
	q = p[pos];
	mem = insert(&m, size, q);
	return q;
}
void *scalloc(size_t nmemb, size_t size) {
	int j = 0; 
	size_t totalsize = nmemb * size;
	void *p;
	p = smalloc(totalsize);
	/*while(j < totalsize) {
		p[j] = 0;
		++j;
	}*/
	return p;
}
void *srealloc(void *ptr, size_t size) {
	int avail;
	void *p;
	p = sbrk(0);
	avail = modify(&m, size, p, ptr);
	return ptr;
}
void sfree(void *ptr) {
	int avail;
	avail = remov(&m, ptr);
	if(avail == MEM) {
		sbrk(0 - MEM);
		i = 0;
	}
}
