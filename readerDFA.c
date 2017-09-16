#include<stdio.h>
#include <stdbool.h>


#define maxKol 100
#define maxBar 100
#define maxStr 100


typedef struct {
  int nKolom;
  int nBaris;
  char tab[maxBar][maxKol][maxStr];
  char finalState[maxKol][maxStr];

} transTab;

typedef struct {
  int nInputs;
  char tab[maxBar][maxStr];
} inputs;

void readTransTable(transTab *T){
  // TODO : make matriks from inputs
  int i; //row
  int j; //column
  printf("input row: "); scanf("%d",&(*T).nBaris );
  printf("input column: "); scanf("%d",&(*T).nKolom );

  for (i = 0; i<= (*T).nBaris; i++){
    for (j = 0; j<=  (*T).nKolom; j++ ){
          scanf("%s",&(*T).tab[i][j]);
        }
    }
}

void writeTransTable(transTab T){
  // TODO : make matriks from inputs
  int i; //row
  int j; //column

  for (i = 0; i<= (T).nBaris; i++){
    for (j = 0; j<= (T).nKolom; j++ ){
        //Skip the 0,0 index.
        printf("%s",(T).tab[i][j]);
        if (j!=(T).nKolom){
          printf(" ");
        }
      }
      printf("\n" );
    }
}

void readInputs(inputs * IN){
  int i;

  printf("number of inputs : ");scanf("%d",&(*IN).nInputs);

  for (i = 0; i<(*IN).nInputs;i++){
    scanf("%s",&(*IN).tab[i]);
  }

}

void writeInputs(inputs IN){
  int i;

  for (i = 0; i<(IN).nInputs;i++){
    printf("%s",(IN).tab[i]);
    if (i!=(IN).nInputs){
      printf(" ");
    }

  }

}

int main(){
//variables
  transTab T;
  inputs IN;

  readTransTable(&T);
  writeTransTable(T); printf("\n");
  readInputs(&IN);
  writeInputs(IN); printf("\n");
}
