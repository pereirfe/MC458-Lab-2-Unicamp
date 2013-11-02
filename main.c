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
  TCell* prev;
  int end;
} TCell;

int main(void){
  char x[] = "ABACATE";               // só teste
  char y[] = "AAABCATE";              // só teste
  char z[100];
  int costs[6] = {3, 5, 2, 3, 2, 1};  // só teste

  int k,l,q;
  TCell m[5][CSIZE];
  TCell aux[5];
  int cost;
  int n = strlen(y);
  int i, j = 0;  // i => indice de x; j => indice de y
  

  // Inicializacao
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
  
  m[0][CPY].prev = m[0][REP].prev = m[0][DEL].prev = m[0][INS].prev = m[0][TWD].prev = NULL; 
  
    
  for( k = 1; k < n; k++ ){ // Coluna (passo)
    for( l = 0; l < 5; l++){ // operacao
      
      // Preenche aux;
      for( q = 0; q < 6; q++){  
	op( l, x, y, &m[q][k-1], aux, costs );   // O que varia: OP anterior
      }

      // min aux
      m[l][k] = min(aux);
    }
  }
  
  /// QUANDO TERMINAR?


}


TCell min_cell(TCell ct[]){
  TCell min;
  int i;

  min = ct[0]; 
  for(i=1; i<6; i++){
    if( ct[i].cost < min.cost || (ct[i].cost == min.cost && ct[i].i > min.i)){
      min = ct[i];
    }
  }
  
  return min;
}



void op(int p, int pop, char* x, char* y, TCell* o, TCell* ct, int* costs){
  //pop  -> previous operation: posicao de ct; (ligado a "o")

  ct[pop].prev = o;
  switch(p){  // Decisao sobre a operacao a ser executada agora
  case CPY:
    ct[pop].i = o->i+1;
    ct[pop].j = o->j+1;
    ct[pop].cost = INF;
    if( x[o->i] == y[o->j] ){
      ct[pop].cost = costs[CPY] + o->cost;      
    }
    break;

  case REP:
    ct[pop].i = o->i+1;
    ct[pop].j = o->j+1;
    ct[pop] = costs[REP] + o->cost;
    break;

  case DEL:
    ct[pop].i = o->i+1;
    ct[pop] = costs[DEL] + o->cost;
    break;

  case INS:
    ct[pop].j = o->j+1;
    ct[pop] = costs[INS] + o->cost;
    break;

  case TWD:
    ct[pop].i += 2;
    ct[pop].j += 2;
    ct[pop].cost = INF;
    if( x[o->i] == y[o->i+1] && x[o->i+1] == y[o->i] ){
      ct[pop].cost = costs[TWD] + o->cost;
    }
    break; 
  }    

  

} 


