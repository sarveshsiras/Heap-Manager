#include "manager.h"
/*
*It initializes a new list(data structure) which is further used to store allocated and freed memory.
*Data structure is an array of structures it basically keeps record of pointers position and and size of memory allocated.
*/
void manageit(manager *m, unsigned int mem) {
	int a, b;
	m->available[0] = mem;
	m->bi = 0;
	m->j = 0;
	m->blkfreed = 0;
	for(a = 0; a < BLOCK; a++) {
		m->currpos[a] = 0;
		m->i[a] = 0;
		for(b = 0; b < SIZE; b++) {
			m->u[a][b].p = m->u[a][b].ref = NULL;
			m->u[a][b].start = m->u[a][b].size = 0;
		}
	}
	for(b = 0; b < SIZE; b++) {
		m->f[b].p = m->f[b].ref = NULL;
		m->f[b].start = m->f[b].size = m->f[b].blkno = 0;
	}
}
/*It checks if the record is full*/
int mfull(manager *m, int a) {
	return (m->bi < BLOCK && m->j < BLOCK && m->i[a] < SIZE);
}
/*It returns size of a specific pointer from the record if it exists*/
int sizeofptr(manager *m, void *p) {
	int x, y;
	size_t size;
	find(m, p, &x, &y);
	if(x == -1 || y == -1) {
		return 0;
	}
	size = m->u[x][y].size;
	return size;
}
/*It inserts data like pointer location, size, pointer allocated, reference wrt to which pointer is allocated.
*Its job is to insert this data in a specific block in which pointer memory is allocated.
*/
void insert(manager *m, unsigned int size, void *p, void *ref, int b) {
	m->u[b][m->i[b]].start = m->currpos[b];
	m->u[b][m->i[b]].size = size;
	m->u[b][m->i[b]].p = p;
	m->u[b][m->i[b]].ref = ref;
	m->available[b]= m->available[b] - size;
	m->currpos[b] = m->currpos[b] + size;
	m->i[b]++;
}
/*It finds the pointer location if it exist in the record.
*/
void find(manager *m, void *p, int *a, int *b) {
	int flag = 0, x, y;
	for(x = 0; x < m->bi; x++) {
		for(y = 0; m->u[x][y].p != NULL; y++) {
			if(p == m->u[x][y].p) {
				*a = x;
				*b = y;
				flag = 1;
				break;
			}
		}
	}
	if(flag == 0) {
		*a = -1;
		*b = -1;
		return;
	}
}
/*It removes the data wrt a pointer from the record which is to be freed*/
void remov(manager *m, void *p) {
	int x, y;
	find(m, p, &x, &y);
	if(x == -1 || y == -1) {
		printf("No record\n");
		return;
	}
	finsert(m, m->u[x][y], x);
	m->blkfreed = m->blkfreed + m->u[x][y].size;
	while(y < m->i[x] - 1) {
		m->u[x][y] = m->u[x][y + 1];
		y++;
	}
	m->i[x]--;
}
/*It inserts the freed block into an array which remembers the size, location and block.
*It also sorts the memory in ascending order so as to allocate a best suited block of memory.
*/
void finsert(manager *m, node u, int x) {
	int a, b, c;
	fnode tmp;
	m->f[m->j].start = u.start;
	m->f[m->j].size = u.size;
	m->f[m->j].p = u.p;
	m->f[m->j].ref = u.ref;
	m->f[m->j].blkno = x;
	if(m->j > 1) {
		c = m->j;
		for(a = 0; a < c - 1; a++)
			for(b = 0; b < c - 1 - a; b++)
				if(m->f[b].size > m->f[b + 1].size) {
					tmp = m->f[b];
					m->f[b] = m->f[b + 1];
					m->f[b + 1] = tmp;
				}
	}
}
/*It allocates a freed block of memory to a new memory requirement.
*/
void* fralloc(manager *m, unsigned int size, int a) {
	void *ptr;
	if(!m->j)
	return NULL;
	ptr = m->f[a].p;
	insert(m, size, ptr, m->f[a].ref, m->f[a].blkno);
	while(a < m->j -1) {
		m->f[a] = m->f[a + 1];
		a++;
	}
	m->j--;
	return ptr;
}
/*If the size of available chunk is less than new memory a new block is initialized with greater memory so as to meet memory requirement.
*/
void newbuddy(manager *m, void *p, size_t size, size_t tsize) {
	if(size == 0) {
		m->u[0][0].ref = p;
		m->available[0] = tsize;
		m->bi++;
	}
	else {
		m->u[m->bi][0].ref = m->u[m->bi][0].p = p;
		m->available[m->bi] = tsize - size;
		m->u[m->bi][0].start = 0;
		m->u[m->bi][0].size = size;
		m->currpos[m->bi] = size;
		m->i[m->bi]++;
		m->bi++;
	}
}
/*It returns the block no. to for required memory.
*It returns -ve number is memory is available in freed chunk.
*It returns +ve number is memory is available in current use chunk.
*/
int buddyavail(manager *m, size_t size) {
	int a;
	if(m->j) {
		for(a = 0; a < m->j; a++)
			if(m->f[a].size >= size){
				m->blkfreed = m->blkfreed - m->f[a].size;
				return -a;
			}
	}
	if(m->bi) {
		for(a = 0; a < m->bi; a++)
			if(m->available[a] >= size)
				return a;
	}
	return 0;
}
/*It returns the current position of lock memory for further allocation.
*/
int currposition(manager *m, int blk) {
	return m->currpos[blk];
}
/*It returns pointer best suitable for asked memory from either freed block or current block in use.
*If negative location is received pointer is allocated from freed chunk.
*If postive location is received pointer is allocated from current block in use. 
*/
void* allocate(manager *m, int blk, size_t size) {
	void *ptr;
	if(!mfull(m, blk)) {
		printf("No memory left\n");
		exit(0);
	}
	if(blk < 0) {
		blk = -blk;
		ptr = fralloc(m, blk, size);
	}
	else {
		ptr = m->u[blk][m->i[blk]].ref;
	}
	return ptr;
}
