#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<time.h>
#include<sys/syscall.h>

typedef struct {
  int start;
  int end;
  int order;
  char substr[12001];
  char text[12001];
  int count;
  int *index;
  pid_t tid;
}thdata;


void* search_substring(void *arg){
  thdata *data = (thdata *)arg;
  pid_t tid = syscall(SYS_gettid);
  data -> tid = tid;
  time_t thread_start_time = time(NULL);
  char *thread_start_time_string = ctime(&thread_start_time);
  printf("[Main] work thread %d: %d\n", data -> order, tid);
  printf("[Tid = %d] %s", tid, thread_start_time_string);
  
  int length = strlen(data -> substr);
  char search_context[8];
  char search_string[length + 1];
  //int index[12001];
  strncpy(search_context, &data -> text[data -> start], 8);
  printf("[Tid = %d] Search %s at %d %s\n", tid, data -> substr, data -> start, search_context);
  for(int i = data -> start; i <= data -> end - length + 1; i++){
    strncpy(search_string, &data -> text[i], length);
    search_string[length] = '\0';
    if(strcmp(search_string, data -> substr) == 0){
      data -> index[data -> count] = i;
      data -> count++;
      }
    }
    
}


int main(int argc, char *argv[])
{
  char S[12001];     //text string
  char K[12001];     //key string
  int n;             //number of threads

  time_t main_start_time = time(NULL);
  char *main_start_time_string = ctime(&main_start_time);
  printf("[Main] %s", main_start_time_string);

  //Open the file
  FILE *file = fopen(argv[1], "r");
  if(file == NULL){
    fprintf(stderr, "Error opening file: %s\n", argv[1]);
    exit(1);
  }

  //Read the text string
  if(fgets(S, sizeof(S), file) == NULL){
    fprintf(stderr, "Error reading target string from the file: %s\n", argv[1]);
    exit(1);
  }
  
  //Read the number of threads
  char threadNum[10];
  if(fgets(threadNum, sizeof(threadNum), file) == NULL){
    fprintf(stderr, "Error reading thread numbers from the file: %s\n", argv[1]);
    exit(1);
  }
  n = atoi(threadNum);
  if(n < 2 || n > 6){
    fprintf(stderr, "Error: threads should be between two and six");
    exit(1);
  }

  pthread_t threads[n];  //thread variables
  thdata thread_data[n]; // thread data array

  //Read the key string
  if(fgets(K, sizeof(K), file) == NULL){
    fprintf(stderr, "Error reading key string from the file: %s\n", argv[1]);
    exit(1);
  }

  int section = strlen(S) / n;
  for(int i = 0; i < n; i++){
    thread_data[i].index = malloc(sizeof(int) * 12001);  // allocate memory for index array
    thread_data[i].count = 0;
    thread_data[i].start = i * section;
    //thread_data[i].end = (i + 1) * section + strlen(K) - 1;
    thread_data[i].order = i + 1;
    strcpy(thread_data[i].text, S);
    if(i == n - 1)
      thread_data[i].end = strlen(S);
    else
      thread_data[i].end = (i + 1) * section + strlen(K) - 1;
    
    //strncpy(thread_data[i].text, &S[thread_data[i].start], thread_data[i].end - thread_data[i].start);
    
    strcpy(thread_data[i].substr, K);
    pthread_create(&threads[i], NULL, search_substring, (void *)&thread_data[i]);
    
  }

  for(int i = 0; i < n; i++){
    pthread_join(threads[i], NULL);
    time_t thread_end_time = time(NULL);
    char *thread_end_time_string = ctime(&thread_end_time);
    printf("[Tid = %d] %s", thread_data[i].tid, thread_end_time_string);
  }
    
  printf("[Main] %s ", K);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < thread_data[i].count; j++){
      printf("%d ", thread_data[i].index[j]);
    }
  }
  time_t main_end_time = time(NULL);
  char *main_end_time_string = ctime(&main_end_time);
  printf("\n[Main] %s", main_end_time_string);
  
  exit(0);
}