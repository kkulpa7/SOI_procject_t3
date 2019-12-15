#include <lib.h>
#include "type.h"
#include <unistd.h>
#include <stdio.h>

int sem_init(int sem_num, int value) {
	message m;
	m.m1_i1 = sem_num;
	m.m1_i2 = value;
	return _syscall(MM, SEM_INIT, &m);
}

int sem_down(int sem_num) {
	message m;
	m.m1_i1 = sem_num;
	m.m1_i2 = getpid();
	return _syscall(MM, SEM_DOWN, &m);
}

int sem_up(int sem_num) {
	message m;
	m.m1_i1 = sem_num;
	return _syscall(MM, SEM_UP, &m);
}

int sem_status(int sem_num, int *value, int *num_blocked) {
	message m;
	m.m1_i1 = sem_num;
	*value = _syscall(MM, SEM_STATUS, &m);
	m.m1_i1 = sem_num;
	*num_blocked = _syscall(MM, SEM_STATUS_BLOCKED, &m);
	return 0;
}
