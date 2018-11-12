#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "heap.h"
#include "manager.h"
#define MEM 1024
manager m; //declaring data structure
int i = 0; //for initialization
size_t memalloc = 0; //amount of memory allocated
void *p;
/*when run first time it executes the condition of initialization
 *In further steps it checks for available size and allocates memory accordingly
*/
void *smalloc(size_t size) {
	void *q;
	if(size == 0)
		return NULL;
	size = (size - 1) / 4 * 4 + 4;  // optional (allocating size in multiples of 4)
	if(i == 0) {
		initialize();
		i++;
	}
	if(size > 0)
		q = assign(size);
	return q;
}
void *scalloc(size_t nmemb, size_t size) {
	size_t totalsize = nmemb * size;
	p = smalloc(totalsize);
	memset(p, 0, totalsize);
	return p;
}
void *srealloc(void *ptr, size_t size) {
	void *p;
	size_t currsize;
	currsize = sizeofptr(&m, ptr);
	if(size == 0 && ptr != NULL) {
		sfree(ptr);
		return ptr;
	}
	else if(currsize > size)
		return ptr;
	else if(ptr == NULL || currsize == 0)
		ptr = smalloc(size);
	else {
		p = smalloc(size);
		memcpy(p, ptr, currsize);
		remov(&m, ptr);
	}
	return p;
}
void sfree(void *ptr) {
	if(ptr == NULL) {
		return;
	}
	remov(&m, ptr);
	ptr = NULL;
	if(m.blkfreed == memalloc) {
		sbrk(0 - memalloc);
		i = 0;
	}
}
/*It initializes new chunk of memory when program is called first time.
*/
void initialize() {
	void *q;
	manageit(&m, MEM);
	p = sbrk(0);
	if(p == (void *) -1) {
		fprintf(stderr,"Error no memory");		
		exit(0);
	}
	p = sbrk(MEM);
	memalloc = MEM;
	if(p == (void *) -1) {
		fprintf(stderr,"Error no memory");		
		exit(0);
	}
	q = sbrk(0);
	if(q == (void *) -1) {
		fprintf(stderr,"Error no memory\n");		
		exit(0);
	}
	newbuddy(&m, p, 0, MEM);
}
/*It first finds out a location suitable for a given pointer from either freed chunk or in use chunk or if memory required exceeds 
*available memory it intializes a new chunk using sbrk which meets the requirement.
*/
void* assign(size_t size) {
	int multiple, num, pos;
	void *tmp;
	if((num = buddyavail(&m, size))) {
		if(num > 0) {
			pos = currposition(&m, num);
			p = allocate(&m, num, size);
			tmp = (void *)((char *)p + pos);
			insert(&m, size, tmp, p, num);
		}
		else {
			p = allocate(&m, num, size);
		}
	}
	else{
		multiple = 1;
		while(multiple * MEM < size)
			multiple++;
		p = sbrk(multiple * MEM);
		if(p == (void *) -1) {
			fprintf(stderr, "Error no memory\n");		
			exit(0);
		}
		tmp = sbrk(0);
		if(tmp == (void *) -1) {
			fprintf(stderr, "Error no memory\n");		
			exit(0);
		}
		memalloc = memalloc + multiple * MEM;
		newbuddy(&m, p, size, multiple * MEM);
		tmp = p;	
	}
	return tmp;
}
