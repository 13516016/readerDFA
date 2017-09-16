#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>



#define maxKol 100
#define maxBar 100
#define maxStr 100
#define ACCEPTED "ACCEPTED"
#define REJECTED "REJECTED"
#define INVALID "INVALID INPUT"


typedef struct {
  int nKolom;
  int nBaris;
  int nFinalState;
  char tab[maxBar][maxKol][maxStr];
  char finalTab[maxKol][maxStr];

} TransTab;

typedef struct {
  int nInputs;
  char tab[maxBar][maxStr];
} Inputs;

typedef struct {
  int nState;
  char * status;
  char tab[maxBar][maxStr];
} SessionState;

void openFile (FILE **f){
  char filename[1000];
  printf("input file name: ");scanf("%s",&filename );

  *f = fopen(filename,"r");

}

void readTransTable(TransTab *T, FILE * f){
  // TODO : make matriks from inputs
  int i=0; //row
  int j=0;
  int count=0; //column
  char buf[1000];
  bool loadFail=false;

  //EXPECT INPUT
  fscanf(f,"%s",buf);
  if (strcmp(buf,"NUMBER_OF_INPUT")==0){
    fscanf(f,"%s",buf);
    strtol(buf,NULL,10);
    (*T).nKolom = (int) strtol(buf,NULL,10);
  }
  else {
    loadFail = true;
  }

// EXPECT STATE
  fscanf(f,"%s",buf);
  if (strcmp(buf,"NUMBER_OF_STATE")==0){
    fscanf(f,"%s",buf);
    strtol(buf,NULL,10);
    (*T).nBaris = (int) strtol(buf,NULL,10);
  }
  else {
    loadFail = true;
  }

//EXPECT DFATABLE
  fscanf(f,"%s",buf);
  if (strcmp(buf,"DFA_TABLE")==0){
  for (i = 0; i<= (*T).nBaris; i++){
    for (j = 0; j<=  (*T).nKolom; j++ ){
          fscanf(f,"%s",buf);
          strcpy((*T).tab[i][j],buf);
        }
    }
  }
  else{
    loadFail = true;
  }

  fscanf(f,"%s",buf);
  if (strcmp(buf,"NUMBER_OF_FINAL_STATE")==0){
    fscanf(f,"%s",buf);
    strtol(buf,NULL,10);
    (*T).nFinalState = (int) strtol(buf,NULL,10);
  }
  else {
    loadFail = true;
  }

  fscanf(f,"%s",buf);
  if (strcmp(buf,"FINAL_STATE")==0){
    for (i = 0; i < (*T).nFinalState; i++) {
      fscanf(f,"%s",buf);
      strcpy((*T).finalTab[i],buf);
    }
  }
  else {
    loadFail = true;
  }

  if (loadFail==true){
    printf("Invalid file format\n");
    exit(0);
  }

}
	int main()
	{
    int i;
    int j;
    FILE *f;
    TransTab T;
    openFile(&f);
    readTransTable(&T,f);
    for (i = 0; i <= (T).nBaris; i++) {
      for (j = 0; j <= (T).nKolom; j++) {
        printf("%s", (T).tab[i][j]);
      }
      printf("\n");
     }
	}
