#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 6

#define SIZEDICT 70000
#define P(x) printf("----- PONTO %d", (x))

int main(void) {
  int size;
  int tx, ty;
  char x[5001];
  char y[5001];
  FILE* words, *fp;
  char dict[SIZEDICT];
  int index = 0;
  char* pos;
  char buf[5001];
  int i;
  char namef[500];
  int t, rd;
  char str[] = "DNA.txt";

  P(0);
  srand(time(0));

  words = fopen(str, "r");  // <<< testar em outro lugar
  if( words == NULL) puts("CANT OPEN WORDS!\n");

  fscanf(words, "%s", dict);   
      
  fclose(words);

  printf("EI?!");

  for(size=50; size<=5000; size+=50){
    for(t=0; t<5; t++){
      tx = 1 + rand()%(size-1);
      ty = size - tx;

      int stx = rand()%(SIZEDICT-tx);
      strncpy(x, &dict[stx], tx);

      int sty = rand()%(SIZEDICT-ty);
      strncpy(y, &dict[sty], ty);
      
      sprintf(namef, "ins.dna.%d.%d.txt", size, t);
      fp = fopen(namef, "w");
      fprintf(fp, "%d %d\n%s\n%s\n", tx, ty, x, y);
      fclose(fp);
    }
  }

  /* for(i=0; i<SIZEDICT; i++){ */
  /*   free(dict[i]); */
  /* } */
    
  return 0;
	
}
