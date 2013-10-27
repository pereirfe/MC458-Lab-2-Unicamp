#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define COPY 3
#define REPL 5 
#define DEL  2
#define INSR 3
#define TWID 2
#define KILL 1


int main(void){
  char x[] = "ABACATE";
  char y[] = "AAABCATE";
  char z[100];

  int n;
  int i,j,k;
  int m[100][100];
  int aux;
  int cost;

  n = strlen(x) + strlen(y);



  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      
      if(i < 2){
	m[j+i][j+i] = instr(x,y,i,j);
      } else {
	cost = MAX_INT;
	for(k=0; k<i; k++){
	  aux = m[j][i] + m[j+i][j] ; //
	  if( aux < cost ){ cost = aux; }
	}
	m[j+i][j+i] = cost;
      }
    }
  }
}


int instr( char* x, char* y, int i, int j){
  int v[6];
  
  v[0] = v[1] = v[2] = v[3] = v[4] = v[5] = MAX_INT;
  
  if( (i-j) == 1 ){
    if( x[i] == y[j] && x[j] == x[i] ){
      v[0] = TWID;
    }
  } 

  v[1] = COPY;  // Sempre pode ser executada
  v[2] = REPL;
  
  if( x[i] == y[i+1] ){  /// VERIFICAR FIM...)
    v[3] = KILL;
  }

  

  // insert
  // kill
}

