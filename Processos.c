#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_MAX 70000

/* Integrantes:
 * Augusto Luchesi Matos
 * Ingrid Lira dos Santos 
 * João Otavio Martini Korczovei 
 * Leticia Bossatto Marchezi 
 * Pratica 1 - Teste de criacao de processos e threads
 * Data: 09/09/2021
*/



void createProcess(){
    struct timespec comeco, fim;	
	int child[NUM_MAX];
    int i, j, stop = 0, count = 0;
	float tempo_total; 

	clock_gettime(CLOCK_REALTIME, &comeco);	

    for(i=0; i<NUM_MAX && !stop; i++){
        child[i]=fork();
        if(count==1000){
			clock_gettime(CLOCK_REALTIME, &fim);                        
		    tempo_total = (fim.tv_sec + fim.tv_nsec / 10e9) - (comeco.tv_sec + comeco.tv_nsec / 10e9);
		}
		if(child[i]<0){  
            for(j=0; j<i;j++){
                kill(child[j],SIGTERM);
            }
            perror("Erro ao criar processos");
            printf("Quantidade de processos criados: %d\n",count);
		    printf("Tempo para criacao de 1000 processos: %f\n",tempo_total);
	        exit(0);
        }
        if(!child[i]){
            stop = 1;
        }
        count++;
    }
       	
    if(i<NUM_MAX){
        exit(0);     
    }

    for(i=0; i<NUM_MAX; i++){
        wait(NULL);
    }
        
    printf("\n\nTodos os processos terminaram\n");
    printf("Quantidade total de processos: %d \n", count);

}
	
int main(){
	createProcess();
	return 0;
}
