#include "functions.h"

int main(int argc, char *argv[]){
	FILE *log, *buf, *fullLog;
	int k = atoi(argv[1]);
	int n = atoi(argv[2]);
	int a = atoi(argv[3]);
	int b = atoi(argv[4]);
	int id = atoi(argv[5]);
	int i, produce_count, inserted, count, num_blocked, temp;
	char file_name[50] = "producer";
	srand(time(NULL) + id);

	sem_init(MUTEX, 1);
	sem_init(CONSUMER_STOP, 0);
	sem_init(PRODUCER_STOP, 0);
	
	strcat(file_name, argv[5]);
	strcat(file_name, ".txt");
	log = fopen(file_name, "w");
	fprintf(log, "[%s] Producer %d start.\n", current_time(), id);
	
	for(i = 0; i < n; ++i){
		produce_count = uniform_distribution(a,b);
		inserted = 0;
		while(inserted == 0){
			sem_down(MUTEX);
			buf = fopen(BUFFER_FILE, "r");
			count = get_count(buf);
			fclose(buf);
			if(k - count < produce_count){
				fullLog=fopen(FULL_LOG_FILE, "a");
				fprintf(fullLog,"[%s] Producer %d waits with %d products. Magazine: %d/%d\n", current_time(), id, produce_count, count, k);
				fclose(fullLog);
				fprintf(log, "[%s] Wait with %d products.\n", current_time(), produce_count);
				sem_up(MUTEX);
				sem_down(PRODUCER_STOP);
				sem_up(MUTEX);
			} else {
				buf = fopen(BUFFER_FILE, "w");
				count = set_count(buf, count + produce_count);
				fclose(buf);				
				inserted = 1;
				fullLog = fopen(FULL_LOG_FILE, "a");
				fprintf(fullLog,"[%s] Producer %d inserts %d products. Magazine: %d/%d\n", current_time(), id, produce_count, count, k);
				fclose(fullLog);
				fprintf(log, "[%s] Instert %d products.\n", current_time(), produce_count);
				sem_status(CONSUMER_STOP, &temp, &num_blocked);
				num_blocked ? sem_up(CONSUMER_STOP) : sem_up(MUTEX);
			}
			sleep(2);
		}
	}
	
	fullLog = fopen(FULL_LOG_FILE, "a");
	fprintf(fullLog,"[%s] Producer %d finish.\n", current_time(), id);
	fclose(fullLog);
	fclose(log);
}

