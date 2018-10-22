#include "manager.h"
#include <limits.h>
void manageit(manager *m, int mem) {
	int j;
	m->currpos = 0;
	m->available = mem;
	m->i = 0;
	for(j = 0; j < SIZE; j++) {
		m->u[j].p = NULL;
		m->u[j].start = m->u[j].size = m->u[j].status = 0 ;
	}
}
int insert(manager *m, int size, void *p) {
	m->u[m->i].start = m->currpos;
	m->u[m->i].size = size;
	m->u[m->i].status = 1;
	m->u[m->i++].p = p;
	m->available = m->available - size;
	m->currpos = m->currpos + size;
	return m->available;
}
int find(manager *m, void *p) {
	int count = 0, flag = 0;
	while(m->u[count].p != NULL) {
		if(p == m->u[count].p) {
			flag = 1;
			break;
		}
		count++;
	}
	if(flag == 0)
		return INT_MIN;
	return count;
}
int remove(manager *m, void *p) {
	int num;
	num = find(m, p);
	if(num == INT_MIN)
		return m->available;
	m->available = m->available + m->u[num].size;
	while(m->u[num + 1].p != NULL) {
		u[num] = u[num + 1];
		num++;
	}
	m->i--;
	return m->available;
}
int modify(manager *m, int size, void *p) {
	int num;
	num = find(m, p);
	if(num == INT_MIN)
		return m->available;
	m->available = m->available - m->u[num].size + size;
	m->u[num].size = size;
	return m->available;
}
