#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THR 40000


void* f_thread(void *v) {
  int thr_id = *(int*) v;
  return (void*) thr_id;
}

int main() {
  pthread_t thr[MAX_THR];
  int *p_id, count=0, result;
  int i;

  for(i=0; i<MAX_THR; i++){
    p_id = (int*) malloc(sizeof(int));
    *p_id = i;
    if(pthread_create(&thr[i], NULL, f_thread, (void*) p_id)==0)
      count++;
      
  }
  printf("Threads successfully created: %d\n", count);
  for (i = 0; i < count; i++) {
    pthread_join(thr[i], NULL); 
  }
  pthread_exit(NULL); 
  
  return 0;
}
