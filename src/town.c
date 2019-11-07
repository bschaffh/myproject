#include <stdio.h>
#include <stdlib.h>
#include "town.h"
#include "road.h"

struct town * createTown(char * name) {
  struct town * T = (struct town *)calloc(1, sizeof(struct town));

  T->name = (char *)calloc(NAME_LENGTH, sizeof(char));
  strcpy(T->name, name);

  T->alist = new();
  
  return T;
}

void freeTown ( struct town * T ) {
  if (T){
    free(T->name);
    dellist(T->alist, NULL);
    free(T);
  }
}

char * getTownName(struct town * T) {
  return T->name;
}

struct list * getAList(struct town * T) {
  return T->alist;
}

void viewTown (struct town * T) {
  struct elmlist * iterator = T->alist->head;

  printf("\t%s connected to : \n", getTownName(T));

  while(iterator){
    struct town * roadU = getURoad(iterator->data);
    struct town * roadV = getVRoad(iterator->data);

    if(roadU == T)//si il faut afficher U ou V de la route pointée par iterator
      printf("\t\t%s\n", roadV->name);
    else
      printf("\t\t%s\n", roadU->name);

    iterator = iterator->suc;
  }
}

void printTownName ( struct town * T ) {
  printf("%s", T->name);
}

struct list * getTownListFromFile(char * filename){
  struct list * L = new();
  FILE* ptrFile = NULL;
  ptrFile = fopen(filename, "r");

  if (ptrFile != NULL){
    int nb;
    fscanf(ptrFile, " %d", &nb);

    for ( int i = 0; i < nb; i++ ) {
      char txtbuf[BUFSIZ];
      int buflen;

      fscanf(ptrFile, " %s", txtbuf);
      buflen = strlen(txtbuf) + 1;
      char * name = (char *) calloc(buflen, sizeof(char));
      strcpy(name, txtbuf);

      struct town * T = createTown(name);

      insert_ordered(L, T, NULL);
    }
    fclose(ptrFile);
  }
  else{
    printf("ERREUR ! Fichier introuvable !\n");
  }

  return L;
}