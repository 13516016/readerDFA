#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>



#define maxKol 50
#define maxBar 50
#define maxStr 50
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

void writeTransTable(TransTab T){
  // TODO : make matriks from inputs
  int i; //row
  int j; //column


  for (i = 0; i<= (T).nBaris; i++){
    for (j = 0; j<= (T).nKolom; j++ ){
        if (i==0 && j==0){
          printf("_");
        }
        else {
          printf("%s",(T).tab[i][j]);
        }
        if (j!=(T).nKolom){
          printf(" | ");
        }
      }

      printf("\n" );
    }

    printf("FINAL STATES\n");
    for (i=0; i<(T).nFinalState;i++){
        printf("%s", (T).finalTab[i]);
      if(i!= (T).nFinalState-1){
        printf(" ");
      }
    }


}

void readInputs(Inputs * IN){
  int i;

  printf("number of inputs : ");scanf("%d",&(*IN).nInputs);

  for (i = 0; i<(*IN).nInputs;i++){
    scanf("%s",&(*IN).tab[i]);
  }

}

void writeInputs(Inputs IN){
  int i;

  for (i = 0; i<(IN).nInputs;i++){
    printf("%s",(IN).tab[i]);
    if (i!=(IN).nInputs){
      printf(" ");
    }

  }

}

char * transFunction(char * input, char * currentState, TransTab T){
    int i;
    int inputIdx = -1;
    int stateIdx = -1;
    char * state;

    for (i = 0; i <= (T).nKolom; i++) {
        if (strcmp(input,(T).tab[0][i])==0){
          inputIdx = i;
        }
    }

    for (i = 0; i<= (T).nBaris;i++){
      if (strcmp(currentState,(T).tab[i][0])==0){
        stateIdx = i;
      }
    }

    if (inputIdx != -1 && stateIdx != -1){
      state = (T).tab[stateIdx][inputIdx];
    }
    else {
      state = INVALID;
    }

    return state;
}

void simulateDFA(Inputs IN, TransTab T, SessionState * S){
  int nIn=0;
  int i;
  int j;
  char * currentState = (T).tab[1][0];
  (*S).status = INVALID;

  strcpy((*S).tab[nIn],currentState);
  while (nIn<=(IN).nInputs){
    currentState = transFunction((IN).tab[nIn],currentState,T);
    nIn++;
    strcpy((*S).tab[nIn],currentState);
  }

  (*S).nState = nIn;


  if (strcmp((*S).tab[nIn-1],INVALID)!=0){
    for (i = 0; i < (*S).nState; i++) {
      if (strcmp((T).finalTab[i],(*S).tab[nIn-1])==0) {
        (*S).status = ACCEPTED;
        break;
      }
      else {
        (*S).status = REJECTED;
      }
    }
  }

}

void writeSessionState(SessionState S){
  int i;

  if (strcmp((S).status,REJECTED)==0){
    printf("%s",REJECTED);
  }
  else if (strcmp((S).status,INVALID)==0){
    printf("%s", INVALID);
  }

  else {
    printf("%s",ACCEPTED);
    printf("\n" );
      for (i = 0; i < (S).nState; i++) {
        printf("%s",(S).tab[i]);
        if (i!= (S).nState-1){
          printf(" --> ");
      }
    }
  }

}


int main(){
  //variables
  FILE * f;
  TransTab T;
  Inputs IN;
  SessionState S;

  openFile(&f);
  readTransTable(&T,f);printf("\n");
  writeTransTable(T);
  printf("\n");
  printf("\n");

  readInputs(&IN);printf("\n");

  simulateDFA(IN,T,&S);
  writeSessionState(S);printf("\n" );

}
