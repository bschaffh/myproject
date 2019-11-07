#include <stdlib.h>
#include <stdio.h>
#include "road.h"
#include "town.h"

struct road * createRoad (struct town * U, struct town * V) {
  struct road * R = (struct road *)calloc(1, sizeof(struct road));

  R->U = U;
  R->V = V;

  return R;
}

void freeRoad ( struct road * R ) {
  free(R);
}

struct town * getURoad(struct road * R) {
  return R->U;
}

void setURoad ( struct road * R, struct town * T ) {
  R->U = T;
}

struct town * getVRoad(struct road * R) {
  return R->V;
}

void setVRoad ( struct road * R, struct town * T ) {
  R->V = T;
}

void viewRoad ( struct road * R ) {
  printf("(%s, %s)\n", R->U->name, R->V->name);
}

struct list * getRoadListFromFile(char * filename){
  struct list * L = new();
  FILE* ptrFile = NULL;
  ptrFile = fopen(filename, "r");

  if (ptrFile != NULL){
    int n;
    fscanf(ptrFile, "%d", &n);

    for (int i = 0; i < n; i++){
      char * name1 = (char*)calloc(NAME_LENGTH, sizeof(char));
      char * name2 = (char*)calloc(NAME_LENGTH, sizeof(char));

      fscanf(ptrFile, "( %s , %s )", name1, name2);

      struct road * R = createRoad(createTown(name1), createTown(name2));
      cons(L, R);
    }
  }
  else{
    printf("ERREUR ! Fichier introuvable !\n");
  }

  return L;
}
