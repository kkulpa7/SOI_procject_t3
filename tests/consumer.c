#include "functions.h"

int main(int argc, char *argv[]){
	FILE *log, *buf, *fullLog;
	int k = atoi(argv[1]);
	int n = atoi(argv[2]);
	int a = atoi(argv[3]);
	int b = atoi(argv[4]);
	int id = atoi(argv[5]);
	int i, take_count, taken, count, num_blocked, temp;
	char file_name[50] = "consumer";
	srand(time(NULL) + id);
 
	sem_init(MUTEX, 1);
	sem_init(PRODUCER_STOP, 0);
	sem_init(CONSUMER_STOP, 0);
	
	strcat(file_name, argv[5]);
	strcat(file_name, ".txt");
	log = fopen(file_name, "w");
	fprintf(log, "[%s] Consumer %d start.\n", current_time(), id);
	
	for(i = 0; i < n; ++i) {
		taken = 0;
		take_count = uniform_distribution(a,b);
		while(taken == 0) {
			sem_down(MUTEX);
			buf = fopen(BUFFER_FILE, "r");
			count = get_count(buf);
			fclose(buf);
			if(count < take_count) {
				fullLog = fopen(FULL_LOG_FILE, "a");
				fprintf(fullLog,"[%s] Consumer %d don't get %d products. Magazine: %d/%d\n", current_time(), id, take_count, count, k);
				fclose(fullLog);
				fprintf(log, "[%s] Don't get %d products.\n", current_time(), take_count);
				sem_up(MUTEX);
				sem_down(CONSUMER_STOP);
				sem_up(MUTEX);
			} else {
				buf = fopen(BUFFER_FILE, "w");
				count = set_count(buf, count - take_count);
				fclose(buf);
				taken = 1;
				fullLog=fopen(FULL_LOG_FILE, "a");
				fprintf(fullLog,"[%s] Consumer %d took %d products. Magazine: %d/%d\n", current_time(), id, take_count, count, k);
				fclose(fullLog);
				fprintf(log, "[%s] Took %d products.\n", current_time(), take_count);
				sem_status(PRODUCER_STOP, &temp, &num_blocked);
				num_blocked ? sem_up(PRODUCER_STOP) : sem_up(MUTEX);
			}
			sleep(2); 
		}
	}
	fullLog = fopen(FULL_LOG_FILE, "a");
	fprintf(fullLog,"[%s] Consumer %d finish.\n", current_time(), id);
	fclose(fullLog);
	fclose(log);
}

