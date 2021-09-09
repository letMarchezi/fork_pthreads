#include <pthread.h>
#include <errno.h>
#include <stdio.h>


#define NUM_MAX 30000
void *routine(void *arg){
	return NULL;
}
  
void createThreads(){
	struct timespec comeco, fim;
	pthread_t threads;
        int id;
        int count=0;
	float tempo_total; 
        clock_gettime(CLOCK_REALTIME, &comeco);

        while (1){
		if(count==1000){
                        clock_gettime(CLOCK_REALTIME, &fim);                        
                        tempo_total =  (fim.tv_sec + fim.tv_nsec / 10e9) - (comeco.tv_sec + comeco.tv_nsec / 10e9); 
                }	
		id = pthread_create(&threads, NULL, routine, NULL);

                if(id!=0){
                         perror("Erro ao criar a thread");
			 break;
                 }
                 count++;
  
         }
	printf("Quantidade de Threads criadas: %d\n",count);
	printf("Tempo para criacao de 1000 threads: %f\n",tempo_total);


}
int main(){
	createThreads();
	return 0;
}
