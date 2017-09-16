#include<stdio.h>
#include <stdbool.h>


#define maxKol 100
#define maxBar 100
#define maxStr 100


typedef struct {
  int nKolom;
  int nBaris;
  char tab[maxBar][maxKol][maxStr];
} transTab;

typedef struct {
  char tab[maxBar][maxKol][maxStr];
} inputs;

void createTransTable (transTab *T){
  printf("input row: "); scanf("%d",&(*T).nBaris );
  printf("input column: "); scanf("%d",&(*T).nKolom );
}

void readTransTable(transTab *T){
  // TODO : make matriks from inputs
  int i; //row
  int j; //column

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

void readInputs()

int main(){
  transTab T;

  createTransTable(&T);
  readTransTable(&T);
  writeTransTable(T); printf("\n");

}
