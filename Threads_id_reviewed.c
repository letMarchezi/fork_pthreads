#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THR 40000


void* f_thread(void *v) {
  int thr_id = *(int*) v;
  int r;
  
  printf("id: %d\n", thr_id);
  return NULL; 
} 

int main() {
  pthread_t thr[MAX_THR];
  int i, *p_id;

  for(int i=0; i<MAX_THR; i++){
    p_id = (int*) malloc(sizeof(int));
    *p_id = i;
    pthread_create(&thr[i], NULL, f_thread, (void*) p_id);
  }
  

  for (i = 0; i < MAX_THR; i++) 
    pthread_join(thr[i], NULL); 
    pthread_exit(NULL); 

  
  return 0;
}
