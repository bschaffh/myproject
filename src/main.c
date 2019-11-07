#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "road.h"
#include "list.h"
#include "town.h"

void printInteger ( int * i ) {
printf( "%d ", (*i) );
}

int main() {
  graph G = readmap ();

  viewmap ( G );

  freeGraph ( G );

// ------------------------------------------------------------------------------------------------------------------- */

/*int a = 10; int b  = 11; int c = 12; int d = 13; int e = 221;
  
void *ptra = &a; void *ptrb = &b; void *ptrc = &c; void *ptrd = &d; void *ptre = &e;

struct list * L = new();

void (*ptrPrintI) (int *);
ptrPrintI = printInteger;

cons(L, ptrd);
cons(L, ptrc);
cons(L, ptrb);
cons(L, ptra);

viewlist(L, ptrPrintI);

insert_after(L, ptre, NULL);

printf("\n");
viewlist(L, ptrPrintI);

dellist(L, NULL);*/

// ------------------------------------------------------------------------------------------------------------------- */

/*struct list * L = new();

struct town * villeA = createTown("C");
struct town * villeB = createTown("F");
struct town * villeD = createTown("L");
struct town * villeC = createTown("B");

L = getTownListFromFile("data/town.txt");

void (*ptrPrintTown) (struct town * T);
ptrPrintTown = viewTown;

viewlist(L, ptrPrintTown);
printf("---------------------------------------\n");

insert_ordered(L, villeC, NULL);
viewlist(L, ptrPrintTown);

freeTown(L->head->data);*/

// ------------------------------------------------------------------------------------------------------------------- */

/*struct list * L = new();

struct town * villeA = createTown("NewYork");
struct town * villeB = createTown("Paris");
struct town * villeC = createTown("SanFrancisco");
struct town * villeD = createTown("I");
struct town * villeP = createTown("LosAngeles");

struct road * RAB = createRoad(villeA, villeB);
struct road * RAC = createRoad(villeA, villeC);
struct road * RBC = createRoad(villeA, villeD);

struct road * RTP = createRoad(villeA, villeP);


void (*ptrPrintR) (struct road * R);
ptrPrintR = viewRoad;

insert_ordered(L, RTP, villeA);
insert_ordered(L, RAB, villeA);
insert_ordered(L, RAC, villeC);

viewlist(L, ptrPrintR);*/

// ------------------------------------------------------------------------------------------------------------------- */ 

return EXIT_SUCCESS;
}

