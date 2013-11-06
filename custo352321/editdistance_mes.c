#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6

#define CPY 0
#define REP 1
#define DEL 2
#define INS 3
#define TWD 4
#define KILL 5

#define INF (1<<30)

#define TIMES 20

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
	TCell** table;
	table = (TCell**)malloc((m+1)*sizeof(TCell*));
	for (i = 0; i<=m; i++)
		table[i] = (TCell*)malloc((n+1)*sizeof(TCell));


	//casos base
    	for(i = 1; i <= m; i++){
        	table[i][0].v = i*c[DEL];
		table[i][0].prev = DEL;  // Indicativo de fim de lista
	}
	for(j = 1; j <= n; j++){
        	table[0][j].v = j*c[INS];
		table[0][j].prev = INS;  // Indicativo de fim de lista
	}

	table[0][0].v = 0;
	table[0][0].prev = -1;

	//outros casos
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			//verifica se 'e possivel realizar a copia
		        int copy = (x[i-1] == y[j-1]);              ///i ou j?
			//verifica se 'e possivel realizar o twiddle
			int twd = (i > 1 && j > 1) && (x[i-1] == y[j-2] && x[i-2] == y[j-1]);
			//calcula o custo de cada operacao
			costs[INS] = c[INS] + table[i][j-1].v;
			costs[DEL] = c[DEL] + table[i-1][j].v;
			costs[REP] = c[REP] + table[i-1][j-1].v;
			costs[CPY] = copy? c[CPY] + table[i-1][j-1].v : INF;
			costs[TWD] = twd? c[TWD] + table[i-2][j-2].v : INF;
			costs[KILL] = INF;
			//pega a operacao com menor custo
			int action;
			action = min(costs,SIZE);
			table[i][j].v = costs[action];
			table[i][j].prev = action;
		}
	}
	//procura um ponto onde o kill pode ser feito
	int killIndex = 1;

	for(i=1;i<m;i++)
	  if(table[i][n].v < table[killIndex][n].v) 
			killIndex = i;

	//verifica se a realizacao do kill compensa de fato
	int killFlag = 0;
	int k = m; // linha
	int l = n; // coluna
	if((c[KILL] + table[killIndex][n].v) < table[m][n].v){
		table[m][n].v =  c[KILL] + table[killIndex][n].v;
		table[m][n].prev = table[killIndex][n].prev;
		k = killIndex;
		killFlag = 1;
	}
	
	// Preenche seq com a sequencia inversa das operacoes
	seq[0] = killFlag? KILL : -1;	
	for(i=killFlag; table[k][l].prev != -1; i++){ 
	  seq[i] = table[k][l].prev;

	  switch(table[k][l].prev){
	  case CPY:
	  case REP: k--; l--; break;
	  case DEL: k--; break;
	  case INS: l--; break;
	  case TWD: k-=2; l-=2; break;
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
	int i;
	scanf("%d %d %d %d %d %d", &cost[CPY],&cost[REP],&cost[DEL],&cost[INS],&cost[TWD],&cost[KILL]);
	
	int c;
	for(i=0; i<TIMES; i++){
	  c = editDistance(x,y,cost,seq);
	}

	printf("%d\n",c);

	for(i=0; seq[i] >= 0; i++){}
	i--;

	int a,b;
	for(a=b=0; i >=0; i--){
	  //printf("%d %d ", a+1, b+1);
	  switch(seq[i]){

	  case CPY:
	    //	    printf("Copy %c\n", x[a]);
	    a++; b++;
	    break;

	  case REP:
	    //printf("Replace %c\n", y[b]);
	    a++; b++;
	    break;

	  case DEL:
	    //printf("Delete _\n");
	    a++;
	    break;	    
	  
	  case INS:
	    //printf("Insert %c\n", y[b]);
	    b++;
	    break;
	  
	  case TWD:
	    //printf("Twiddle %c%c \n", x[a], x[a+1]);
	    a+=2;
	    b+=2;
	    break;
	  
	  case KILL:
	    //printf("Kill *\n");
	    break;
	  }
	}
	

	//	free(x);
	//free(y);
	//free(seq);

	return 0;
	
}
