#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "road.h"
#include "town.h"

graph readmap() {
  FILE * fd;
  char fname[20];

  printf(" file name of the map : ");
  scanf("%s", fname);
  if((fd = fopen(fname, "rt")) == NULL) {
    fprintf(stderr, "Error while opening %s\n", fname);
    exit(EXIT_FAILURE);
  }
  int nb;

  // Construction de la liste des villes
  //  qui sont les sommets du graphe
  graph G = new (); 

  fscanf(fd, " %d", &nb);
  for ( int i = 0; i < nb; i++ ) {
    char txtbuf[BUFSIZ];
    int buflen;

    fscanf(fd, " %s", txtbuf);
    buflen = strlen(txtbuf) + 1;
    char * name = (char *) calloc(buflen, sizeof(char));
    strcpy(name, txtbuf);
    struct town * T = createTown(name);
    insert_ordered(G, T, NULL);
    free(name);
  }

  // Construction de la liste des routes
  //  dont les villes sont des références
  //  aux villes enregistrées auparavant
  // Les routes sont les arêtes du graphe
  struct list * edges = new ();

  fscanf ( fd, " %d", &nb );
  for ( int i = 0; i < nb; i++ ) {
    char T1[20], T2[20];
    fscanf ( fd, " ( %s , %s )", T1, T2 );

    struct elmlist * iterator = G->head;
    while (strcmp(getTownName(iterator->data),T1) != 0) {//on avance dans G jusqu'à trouver une référence à la première ville
      iterator = iterator->suc;
    }
    if ( iterator == NULL ) exit ( EXIT_FAILURE );

    struct town * u = iterator->data;

    iterator = G->head;
    while (strcmp(getTownName(iterator->data), T2) != 0) {
      iterator = iterator->suc;
    }
    if ( iterator == NULL ) exit ( EXIT_FAILURE );

    struct town * v = iterator->data;

    struct road * R = createRoad(u, v);

    cons ( edges, R ); // un simple ajout en tête
  }

  // Construction des listes d'adjacences
  //  en parcourant la liste de routes
  for(struct elmlist * roads = edges->head; roads; roads = roads->suc) {
    struct town * u = getURoad(roads->data);
    struct town * v = getVRoad(roads->data);

    if( u == NULL || v == NULL) exit ( EXIT_FAILURE );

    insert_ordered(u->alist, roads->data, u); // insertion ordonnée de ville de départ u
    insert_ordered(v->alist, roads->data, v); // insertion ordonnée de ville de départ v
  }

  // Libérer la liste des arêtes mais pas les routes
  dellist ( edges, NULL );

  fclose ( fd );
  return G;
}
  
void viewmap ( graph G ) {
  int nb = G->numelm;
  printf("\t\t+++++%d villes+++++\n", nb);
  struct elmlist * iterator = G->head;

  while(iterator){
    viewTown(iterator->data);

    iterator = iterator->suc;
  }
}

void freeGraph ( graph  ptrG ) {
  /** TODO 
   * Il faut malgré tout supprimer les villes ET les routes.
   * 
   * Faites attention que les routes ne sont référencées que par
   * les listes d'adjacence des villes.
   * 
   * Vous devez parcourir les villes (le graphe G)
   *  Pour chaque ville V, parcourez sa liste d'adjance
   *    (liste des routes auxquelles V est connexe)
   *    Pour chaque route R de la liste d'adjacence,
   *      vous devez déréférencer (NUll) la ville V
   *      Si les deux villes U et V de R sont déréférencées
   *      Alors vous pouvez supprimer la route R
   */

  struct elmlist * iterator = ptrG->head;
  
  while (iterator){
    struct town * V = ((struct town*)iterator->data);
    struct elmlist * iteratorRoad = V->alist->head;

    while (iteratorRoad){//on parcourt la liste de routes pour chaque chaque ville
      struct road * R = ((struct road*)iteratorRoad->data); //la route à prendre en compte
      if (getURoad(R) == (iterator->data)){//si la ville est dans U
        setURoad(R, NULL);
      }
      else if(getVRoad(R) == (iterator->data)){//si la ville est dans V
        setVRoad(R, NULL);
      }
      if (getURoad(R) == NULL && getVRoad(R) == NULL){//si U et V sont à nuls, on supprime R
        free(R);
      }
      iteratorRoad = iteratorRoad->suc;
    }
    iterator = iterator->suc;
  }

  void (*ptrFreeT) (struct town * T);//
  ptrFreeT = freeTown;
  dellist(ptrG, ptrFreeT);// Lorsque l'on a fini de supprimer toutes les routes, on supprime le graphe et ses données, soit des routes
}