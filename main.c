#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 1<<30;
#define CSIZE 100

typedef enum e{ CPY=0, REP=1, DEL=2, INS=3, TWD=4, KLL=5} EOp;

typedef struct {
  int cost;
  int i, j;
} TCell;

int main(void){
  char x[] = "ABACATE";               // só teste
  char y[] = "AAABCATE";              // só teste
  char z[100];
  int costs[6] = {3, 5, 2, 3, 2, 1};  // só teste

  int k,l,q;
  TCell m[6][CSIZE];
  TCell aux[6];
  int cost;
  int n = strlen(y);
  int i, j = 0;  // i => indice de x; j => indice de y
  
  m[0][CPY].i = m[0][CPY].j = 1;
  m[0][CPY].cost = INF;
  if( x[i] == y[j] ){
    m[0][CPY].cost = costs[CPY];      
  }

  m[0][REP].i = m[0][REP].j = 1;
  m[0][REP] = costs[REP];

  m[0][DEL].i = 1;
  m[0][DEL].j = 0;
  m[0][DEL] = costs[DEL];

  m[0][INS].i = 0;
  m[0][INS].j = 1;
  m[0][INS] = costs[INS];

  m[0][TWD].i = m[0][TWD].j = 2;
  m[0][TWD].cost = INF;
  if( x[0] == y[1] && x[1] == y[0] ){
    m[0][TWD].cost = costs[TWD];
  }    
    
    
  for( k = 1; k < n; k++ ){
    
    // Preenche aux;
    for( q = 0; q < 6; q++){
      op( q, x, y, m[q][k-1].i, m[q][k-1].j, &aux, costs );
    }

    for( l = 0; l < 6; l++){

      // analisar com o custo da proxima operacao


    }
  }
}


void op(int p, char* x, char* y, int i, int j, TCell* ct, int* costs){
  switch(p){
  case CPY:
    ct[CPY].i = i+1;
    ct[CPY].j = j+1;
    ct[CPY].cost = INF;
    if( x[i] == y[j] ){
      ct[CPY].cost = costs[CPY];      
    }
    break;

  case REP:
    ct[REP].i = i+1;
    ct[REP].j = j+1;
    ct[REP] = costs[REP];
    break;

  case DEL:
    ct[DEL].i = i+1;
    ct[DEL] = costs[DEL];
    break;

  case INS:
    ct[INS].j = j+1;
    ct[INS] = costs[INS];
    break;

  case TWD:
    ct[TWD].i += 2;
    ct[TWD].j += 2;
    ct[TWD].cost = INF;
    if( x[i] == y[i+1] && x[i+1] == y[i] ){   //// p?!?!?!?!?!
      ct[TWD].cost = costs[TWD];
    }
    break; 
  }    
} 


