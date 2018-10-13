#include "manager.h"
int manageit(manager *m) {
	int j;
	m->currpos = 0;
	m->available = 4096;
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

}
int modify(manager *m, int size, void *p) {

}
