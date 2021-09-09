#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define NUM_MAX 30000

int main(){
        int child[NUM_MAX];
        int errsv;
        int count = 0, i, j;
        int status;
        int pause=0;

        for(i=0; i<NUM_MAX && !pause; i++){
                child[i]=fork();
                if(child[i]<0){
                  
                        for(j=0; j<i;j++){
                                kill(child[j],SIGTERM);
                        }
                        printf("Ultimo processo: %d\n",count);
                        perror("Erro: \n");
                        exit(0);
                }
                if(!child[i]){
                  pause = 1;
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

        return 0;
}

/* Questao 2
 *
 *
 *
 */

/*
 * Questao 4 
 * O comando foi testado usando o comando ulimit para reduzir o numero maximo de processos permitidos
 * e com isso verificou-se que ao configurar um numero menor de processos por usuario o programa
 * executou uma quantidade menor(aquela definida atraves do comando).
 * Na tentativa de aumentar o numero de processos permitidos por um usuario atraves do comando 
 * ulimit nao foi observada alteraçao da criacao de processos no programa.
 *
 *
 */ 

