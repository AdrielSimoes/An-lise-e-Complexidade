#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

//Y= Quantidade de itens//
#define y 3
#define peso 10

	int mat[y][2],matgula[y][2],matdina[y+1][peso+1]={ { 0 } }, vetvald[y]={0}, aux=0,mg=0, totalpesog=0, totalvalorg=0, totalpesod=0, max1=y, max2=peso;

int main(){
	int i,j;
	int pesoaux=peso;
	
	printf("Digite o valor e peso de cada item: \n");
	
	//recebe os valores na matriz, onde coluna 1 recebe todos os valor e coluna 2 todos os pesos
	for(i=0;i<y;i++){
	printf("Valor:");
	scanf("%i", &mat[i][1]);
	printf("Peso:");	
	scanf("%i", &mat[i][2]);
	}
	
	//ordena a matriz em ordem crescente em relação ao peso
	for(i=0;i<y;i++){
		for(j=i+1;j<y;j++){
			if(mat[i][2]>mat[j][2]){
				aux=mat[i][1];
				mat[i][1]=mat[j][1];
				mat[j][1]=aux;
				
				aux=mat[i][2];
				mat[i][2]=mat[j][2];
				mat[j][2]=aux;
			}
		}
	}
	
	//Metodo guloso, coloca a maior quantidade possivel sem se preocupar com a solução perfeita, apenas o mais proximo disso
	
	for(i=0;i<y;i++){
		if(mat[i][2]<=pesoaux ){
			mg++;
			pesoaux=pesoaux-mat[i][2];
			matgula[i][1]=mat[i][1];
			totalvalorg=totalvalorg+matgula[i][1];
			matgula[i][2]=mat[i][2];
			totalpesog=totalpesog+matgula[i][2];
		}	
	}
	
	
	//Metodo dinamico, coloca os melhores valores possiveis, dividando o problema principal em menores
	
	for(i=1;i<y+1;i++){ //linha
		for(j=1;j<peso+1;j++){ //coluna
			if(j>=mat[i-1][2]){ //se o peso atual for maior que o peso que o usuario forneceu
				matdina[i][j]=mat[i-1][1];  // essa posição recebe o valor correspondente ao peso
				aux=j-mat[i-1][2];                       //auxiliar recebe a divisão do peso atual pelo peso fornecido
				matdina[i][j]=matdina[i][j]+matdina[i-1][aux];  //matriz dinamica recebe ela mesma mais a coluna dada pela divisão, na linha superior
			}
			if(matdina[i][j]<matdina[i-1][j]){   // se o valor atual for menos que o valor da mesma coluna na linha superior
					matdina[i][j]=matdina[i-1][j];   //então mantem o valor da linha superior
			}
		}
	}
	
	//Calcula e organiza as respostas com base na tabela gerada pelas linhas a cima	

	do{
	if(matdina[max1][max2] != matdina[max1-1][max2]){
		totalpesod=totalpesod+mat[max1-1][2];
		vetvald[max1]=mat[max1-1][1];
		max2=max2-mat[max1-1][2];
		max1--;
		}
	
	}while( matdina[max1][max2]>0 );
	
	
	
	//exibe a matriz
	printf("\nNumeros Recebidos:");
	printf("\nV - P\n");
	for(i=0;i<y;i++){
	printf("%i - %i\n",mat[i][1],mat[i][2]);
	}
	//exibe mochila gulosa
	printf("\n Mochila por metodo Guloso: \n");
	printf("O valor total da mochila e: %i \n", totalvalorg );
	printf("O peso total da mochila e: %i \n", totalpesog);
	printf("Os itens selecionados foram: \n");
	for(i=0;i<mg;i++){
		printf("%i - %i \n",matgula[i][1] ,matgula[i][2]);
	}
	
	
	//exibe mochila Dinamica
	printf("\n Mochila por metodo Dinamico: \n");
	printf("O valor total da mochila e: %i \n", matdina[y][peso] );
	printf("O peso total da mochila e: %i \n", totalpesod );
	printf("Os itens selecionados sao: \n" );
	for(i=0;i<=y;i++){
		if(vetvald[i] > 0){
		printf("%i \n",vetvald[i]);
		}
	}
	
	
	getch();
}
