#include<stdio.h>
#include <stdbool.h>
#include <string.h>


#define maxKol 100
#define maxBar 100
#define maxStr 100
#define ACCEPTED "ACCEPTED"
#define REJECTED "REJECTED"
#define INVALID "#INVALID#"


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

void readTransTable(TransTab *T){
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
  printf("number of final states : ");scanf("%d",&(*T).nFinalState);
  for (i = 0; i < (*T).nFinalState; i++) {
    scanf("%s",&(*T).finalTab[i]);
  }

}

void writeTransTable(TransTab T){
  // TODO : make matriks from inputs
  int i; //row
  int j; //column


  for (i = 0; i<= (T).nBaris; i++){
    for (j = 0; j<= (T).nKolom; j++ ){
        printf("%s",(T).tab[i][j]);
        if (j!=(T).nKolom){
          printf(" ");
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
  while ((nIn<=(IN).nInputs) && (strcmp(currentState,INVALID)!=0) ){
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
  }
  printf("\n" );
    for (i = 0; i < (S).nState; i++) {
      printf("%s",(S).tab[i]);
      if (i!= (S).nState-1){
        printf(" --> ");
    }

  }

}


int main(){
  TransTab T;
  Inputs IN;
  SessionState S;
  //variables

  readTransTable(&T);printf("\n");
  writeTransTable(T); printf("\n");
  readInputs(&IN);printf("\n");
  writeInputs(IN); printf("\n");
  simulateDFA(IN,T,&S);
  writeSessionState(S);printf("\n" );

  // printf("%s\n",transFunction((IN).tab[0],(T).tab[0][1],T));
}
