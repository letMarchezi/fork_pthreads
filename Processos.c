#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_MAX 70000

/* Integrantes:
 * Augusto Luchesi Matos - 740871
 * Ingrid Lira dos Santos - 790888
 * João Otavio Martini Korczovei - 790913
 * Leticia Bossatto Marchezi - 791003
 * Pratica 1 - Teste de criacao de processos e threads
 * Data: 09/09/2021
*/

/* Questao 1 
 * Com a execução dos códigos processos.c e threads.c os resultados foram de 14756 processos e
 * 32751 threads aproximadamente. Entretanto, ao executar o comando (ulimit -u) obtem-se que
 * a quantidade máxima de processos por usuário é de 23144, já com o comando cat /proc/sys/kernel/threads-max
 * obtem-se o número máximo de threads de 46289.  
 */

/* Questao 2
 * O gargalo para criação de processos foi falta de recursos (se aproximando do limite de criação de processos
 * por usuário, considerando que existem processos externos executando simultaneamente), já no caso das threads
 * o problema foi erro na alocação de memória, isto é, o sistema operacional não teve seu limite atingido,
 * porém o hardware não foi capaz de fornecer recurso suficiente. 
 * Tais erros foram obtidos a partir do comando perror, o qual captura a variavel "errno" e apresenta uma mensagem
 * no terminal condizente com a causa do erro.
 */

/* Questao 3
 * Observou-se usando clock_gettime que o tempo de criação de 1000 processos foi em torno de 0.005142 enquanto 
 * o tempo de 1000 threads foi 0.002271, ou seja, as threads foram criadas na metade do tempo utilizado pelos processos.
 */

/*
 * Questao 4 
 * O programa foi testado usando o comando ulimit para reduzir o numero máximo de processos permitidos
 * e com isso verificou-se que ao configurar um número menor o resultado foi uma quantidade menor de processos criados.
 * Nesse caso, ao alterar o limite no sistema para 10000 processos por usuário, foram criados 9340 processos.
 * Na tentativa de aumentar o número de processos permitidos por um usuário atraves do comando
 * ulimit não foi observada alteraçao da criação de processos no programa.
 * Vale ressaltar que o comando ulimit não é uma configuração permanente, isto é, altera o limite de processos 
 * apenas no ambiente em que é executado. Ao reiniciar a sessão, os limites são reestabelecidos para um padrão.
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