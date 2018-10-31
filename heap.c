#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "heap.h"
#include "manager.h"
#define MEM 1024
manager m;
int i = 0;
size_t memalloc = 0;
void *smalloc(size_t size) {
	void *p, *q;
	int pos;
	if(size == 0)
		return NULL;
	size = (size - 1) / 4 * 4 + 4;
	if(i == 0) {
		manageit(&m, MEM);
		p = sbrk(MEM);
		memalloc = MEM;
		if(p == (void *) -1)
			return NULL;
		i++;
	}
	q = fralloc(&m, size);
	if(q)
		return q;
	if(i == 1 && mfull(&m, size)) {
		p = sbrk(2 * memalloc);
		if(p == (void *) -1)
			return NULL;
		modify(&m, 2 * memalloc);
		memalloc = memalloc + 2 * memalloc;
	}
	p = sbrk(0);
	pos = currposition(&m);
	q = (void *)((char *)p + pos); 
	insert(&m, size, q);
	return q;
}
void *scalloc(size_t nmemb, size_t size) {
	size_t totalsize = nmemb * size;
	void *p;
	p = smalloc(totalsize);
	memset(p, 0, totalsize);
	return p;
}
void *srealloc(void *ptr, size_t size) {
	void *p;
	size_t currsize;
	if(size == 0 && ptr != NULL) {
		sfree(ptr);
		return ptr;
	}
	else if(ptr == NULL || (find(&m, ptr) < 0))
		ptr = smalloc(size);
	else {
		currsize = sizeofptr(&m, ptr);
		p = smalloc(size);
		memcpy(p, ptr, currsize);
		remov(&m, ptr);
	}
	return p;
}
void sfree(void *ptr) {
	int avail;
	if(ptr == NULL) {
		return;
	}
	avail = remov(&m, ptr);
	if(avail == memalloc) {
		sbrk(0 - memalloc);
		i = 0;
	}
}
