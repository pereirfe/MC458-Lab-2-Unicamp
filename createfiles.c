#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 6

#define CPY 3
#define REP 5
#define DEL 2
#define INS 3
#define TWD 2
#define KILL 1
#define SIZEDICT 500000
#define P(x) printf("----- PONTO %d", (x))

int main(void) {
  int size;
  int c_flag = 1;
  int tx, ty;
  char x[5001];
  char y[5001];
  FILE* words, *fp;
  char* dict[SIZEDICT];
  int index = 0;
  char* pos;
  char buf[5001];
  int i;
  char namef[500];
  int t, rd;
  char str[] = "words.txt";

  P(0);
  srand(time(0));

  words = fopen(str, "r");  // <<< testar em outro lugar
  if( words == NULL) puts("CANT OPEN WORDS!\n");

 
  for(index = 0; index < SIZEDICT; index++){
    if((pos = fgets( buf, 5001, words)) == NULL) break; 
     
    for(i=0; buf[i] != '\0'; i++){
      if(buf[i] == '\n'){
	buf[i] = '\0';
	break;
      }
      if(buf[i]=='\''){
	buf[i] = buf[i+1];
	buf[i+1] = '\0';
	break;
      }


    }

   
      
    dict[index] = strdup(buf); /* (char*)malloc(sizeof(char)*i); */
    if( dict[index] == NULL ){
      puts("ERRO MALLOC!");
      exit(1);
    }
    if(index%1000 == 0)printf("lido index %d: %s\n", index, dict[index]);

  }

  fclose(words);
  P(2);
  printf("EI?!");
  fflush(stdout);

  for(size=50; size<=5000; size+=50){
    for(t=0; t<5; t++){
      tx = 1 + rand()%(size-1);
      ty = size - tx;
    
      do{
	rd = rand();
	rd =rd%index;
	strcat(x, dict[rd]);
      }while(strlen(x) < tx);
      x[tx] = '\0';

      do{
	rd = rand()%index;
	strcat(y, dict[rd]);
      }while(strlen(y) < ty);
      y[ty] = '\0';
      
      
      sprintf(namef, "ins.%d.%d.%d.txt", size, c_flag, t);
      //printf("namef %s\n", namef);
      /* usleep(10000); */
      fp = fopen(namef, "w");
      fprintf(fp, "%d %d\n%s\n%s\n%d %d %d %d %d %d\n", tx, ty, x, y, CPY, REP, DEL, 
	      INS, TWD, KILL);
      fclose(fp);
    }
  }

  /* for(i=0; i<SIZEDICT; i++){ */
  /*   free(dict[i]); */
  /* } */
    
  return 0;
	
}
