#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4

#define CPY 0
#define REP 1
#define DEL 2
#define INS 3

#define INF (1<<30)

typedef struct {
  int v;  // Valor
  int prev;
} TCell;


//Retorna o indice da menor posicao do vetor 

int min(int a[], int size) {
  int i, min;
  min = 0;
  for(i = 1; i < size; i++)
    {
      if (a[i] < a[min]) 
	min = i;
			
    }
  return min;
}

int editDistance(char *x, char *y, int *c, int* seq) {
  //indices
  int i, j;

  //tamanho da tabela de armazenamento dos custos
  int m = strlen(x);
  int n = strlen(y);

  //vetor auxiliar para calcular o custo de cada operacao
  int costs[SIZE];

  //tabela para armazenar os custos de edicao
  TCell **table;
  table = (TCell**)malloc((m+1)*sizeof(TCell*));
  for (i = 0; i<=m; i++)
    table[i] = (TCell*)malloc((n+1)*sizeof(TCell));

  //casos base
  for(i = 1; i <= m; i++){
    table[i][0].v = i*c[DEL];
    table[i][0].prev = DEL;
  }
  for(j = 1; j <= n; j++){
    table[0][j].v = j*c[INS];
    table[0][j].prev = INS;
  }

  table[0][0].v = 0;
  table[0][0].prev = -1;

  //outros casos
  for(i = 1; i <= m; i++){
    for(j = 1; j <= n; j++){
      //verifica se 'e possivel realizar a copia
      int copy = (x[i-1] == y[j-1]);              ///i ou j?
      //calcula o custo de cada operacao
      costs[INS] = c[INS] + table[i][j-1].v;
      costs[DEL] = c[DEL] + table[i-1][j].v;
      costs[REP] = c[REP] + table[i-1][j-1].v;
      costs[CPY] = copy? c[CPY] + table[i-1][j-1].v : INF;
      //pega a operacao com menor custo
      int action;
      action = min(costs,SIZE);
      table[i][j].v = costs[action];
      table[i][j].prev = action;
    }
  }
  
  int k = m;
  int l = n;
  // Preenche seq com a sequencia inversa das operacoes
  for(i=0; table[k][l].prev != -1; i++){ 
    seq[i] = table[k][l].prev;

    switch(table[k][l].prev){
    case CPY:
    case REP: k--; l--; break;
    case DEL: k--; break;
    case INS: l--; break;
    }
  }
  seq[i] = -1;

  //salva o resultado para dar o free na tabela
  int result = table[m][n].v;

  for (i = 0; i<=m; i++) 
    {free(table[i]);} 
  free(table); 

  return result;
	
}

int main(void) {
  int m, n;
  scanf("%d %d",&m,&n);
	
  char *x, *y;
  int *seq;
  if (m <= 0 || n <= 0){
    printf("Tamanho invalido\n");
    return 0;
  }

  x = (char*)malloc(sizeof(char)*m);
  y = (char*)malloc(sizeof(char)*n);
  seq = (int*)malloc(sizeof(int)*(m+n+2));
	
  scanf("%s",x);
  scanf("%s",y);

  int cost[SIZE];
  cost[CPY] = -1;  // STRINGS BATEM
  cost[REP] = 1;   // Caracteres diferentes
  cost[DEL] = 2;   // Por espaco em Y
  cost[INS] = 2;   // Por espaco em X
	
  int i;
  int c = editDistance(x,y,cost,seq);

  printf("%d\n",-c);

  for(i=0; seq[i] >= 0; i++){}
  i--;


  int j = i;
  int a;
  for(a=0; i >=0; i--){
    switch(seq[i]){
    case CPY:
    case REP:
    case DEL:
      printf("%c", x[a]);
      a++;
      break;

    case INS:
      printf(" ");
      break; 
    }
  }
  
  puts("");

  i = j;
  for(a=0; i >=0; i--){
    switch(seq[i]){
    case CPY:
    case REP:
    case INS:
      printf("%c", y[a]);
      a++;
      break;
	  
    case DEL:
      printf(" ");
      break; 
    }
  }

  puts("");
  i = j;
  for(a=0; i >=0; i--){
    switch(seq[i]){
    case CPY:
      printf("+"); 
      break;
    case REP:
      printf("-"); 
      break;
    case DEL:
    case INS:
      printf("*"); 
      break;	  
    }
  }
	

  //	free(x);
  //free(y);
  //free(seq);

  return 0;
	
}
