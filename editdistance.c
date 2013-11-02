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

int editDistance(char *x, char *y, int *c) {


	//indices
	int i, j;


	//tamanho da tabela de armazenamento dos custos
	int m = strlen(x);
	int n = strlen(y);

	//vetor auxiliar para calcular o custo de cada operacao
	int costs[SIZE];


	//tabela para armazenar os custos de edicao
	int **table;
	table = (int**)malloc((m+1)*sizeof(int*));
	for (i = 0; i<=m; i++)
		table[i] = (int*)malloc((n+1)*sizeof(int));

	//casos base
    	for(i = 1; i <= m; i++)
        	table[i][0] = i*c[DEL];
	for(j = 1; j <= n; j++)
        	table[0][j] = j*c[INS];

	//outros casos
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			//verifica se 'e possivel realizar a copia
			int copy = (x[i-1] == y[i-1]);
			//verifica se 'e possivel realizar o twiddle
			int twd = (i > 1 && j > 1) && (x[i-1] == y[j-2] && x[i-2] == y[j-1]);
			//calcula o custo de cada operacao
			costs[INS] = c[INS] + table[i][j-1];
			costs[DEL] = c[DEL] + table[i-1][j];
			costs[REP] = c[REP] + table[i-1][j-1];
			costs[CPY] = copy? c[CPY] + table[i-1][j-1] : INF;
			costs[TWD] = twd? c[TWD] + table[i-2][j-2] : INF;
			costs[KILL] = INF;
			//pega a operacao com menor custo
			int action;
			action = min(costs,SIZE);
			table[i][j] = costs[action];
						
		}
	}
	//procura um ponto onde o kill pode ser feito
	int killIndex = 1;

	for(i=1;i<m;i++)
		if(table[i][n] < table[killIndex][n]) 
			killIndex = i;
	//verifica se a realizacao do kill compensa de fato
	if((c[KILL] + table[killIndex][n]) < table[m][n])
		table[m][n] =  c[KILL] + table[killIndex][n];	

	//salva o resultado para dar o free na tabela
	int result = table[m][n];

	for (i = 0; i<=m; i++)
		{free(table[i]);}
	free(table);

	return result;
	
}

int main(void) {

	int m, n;
	scanf("%d %d",&m,&n);
	
	char *x, *y;
	if (m <= 0 && n <= 0)
	{
		printf("Tamanho invalido\n");
		return 0;
	}

	x = (char*)malloc(sizeof(char)*m);
	y = (char*)malloc(sizeof(char)*n);
	scanf("%s",x);
	scanf("%s",y);

	int cost[SIZE];
	int i;
	scanf("%d %d %d %d %d %d",&cost[CPY],&cost[REP],&cost[DEL],&cost[INS],&cost[TWD],&cost[KILL]);

	int c = editDistance(x,y,cost);
	printf("%d\n",c);
	return 0;
}
