#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <lib.h>
#include <minix/semaphore.h>

#define FULL_LOG_FILE "fulllog.txt"
#define BUFFER_FILE "buffer.txt"
#define MUTEX 0
#define PRODUCER_STOP 1
#define CONSUMER_STOP 2

int get_count(FILE *buffer) {
	int value = 0;
	fscanf(buffer, "%d", &value);
	return value;
}

int set_count(FILE *buffer,int value) {
	fprintf(buffer, "%d", value);
	return value;
}

int uniform_distribution(int a, int b) {
	return a + rand() % (b - a + 1);
}

char* current_time(void) {
	time_t mytime = time(NULL);
  char * time_str = ctime(&mytime);
  time_str[strlen(time_str)-1] = '\0';
	return time_str;
}
