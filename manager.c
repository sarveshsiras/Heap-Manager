#include "manager.h"
#include <limits.h>
void manageit(manager *m, int mem) {
	int j;
	m->currpos = 0;
	m->available = mem;
	m->i = 0;
	for(j = 0; j < SIZE; j++) {
		m->n[j].p = NULL;
		m->n[j].start = m->n[j].size = m->n[j].status = 0 ;
	}
}
int insert(manager *m, int size, void *p) {
	m->n[m->i].start = m->currpos;
	m->n[m->i].size = size;
	m->n[m->i].status = 1;
	m->n[m->i++].p = p;
	m->available = m->available - size;
	m->currpos = m->currpos + size;
	return m->available;
}
int remove(manager *m, void *p) {
	int num;
	num = find(m, p);
	if(num == INT_MIN)
		return m->available;
	m->available = m->available + m->n[num].size;
	while(m->n[num + 1].p != NULL) {
		n[num] = n[num + 1];
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
	m->available = m->available - m->n[num].size + size;
	m->n[num].size = size;
	return m->available;
}
int find(manager *m, void *p) {
	int count = 0, flag = 0;
	while(m->n[count].p != NULL) {
		if(p == m->n[count].p) {
			flag = 1;
			break;
		}
		count++;
	}
	if(flag == 0)
		return INT_MIN;
	return count;
}
