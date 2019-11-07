#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "town.h"
#include "road.h"

struct list * new () {
  struct list * L = (struct list *)calloc(1, sizeof(struct list));

  L->numelm = 0;
  L->head = NULL;
  L->tail = NULL;

  return L;
}

bool isempty ( struct list *L ) {
  return (L->numelm == 0 && L->head == NULL && L->tail == NULL);
}

void dellist ( struct list * L, void (*ptrF) () ) {
  struct elmlist * iterator = L->head;

  if ( ptrF == NULL ) { // ne supprime pas les données
    while(iterator) {
      struct elmlist* next = iterator->suc;
      free( iterator );
      iterator = next;
    }
  }
  else { // suppression complète
    while(iterator) {
      struct elmlist* next = iterator->suc;
      (*ptrF) (iterator->data);
      free( iterator );
      iterator = next;
    }
  }
  free(L);
}

void viewlist ( struct list *L, void (*ptrF) () ) {
  struct elmlist * deb = L->head;

  while(deb){
    void * d = deb->data;
    (*ptrF) (d);
    deb = deb->suc;
  }
}

void cons ( struct list * L, void * data ) {
  struct elmlist * E = (struct elmlist *) calloc( 1, sizeof(struct elmlist));

  E->data = data;
  E->pred = NULL;
  E->suc = L->head;
  
  if (!(isempty(L))){//si la liste est vide, head pointe sur rien donc L->head->pred n'existe pas (d'où la condition)
    L->head->pred = E;
  }
  else{//si la liste était vide, on fait pointer tail sur E
    L->tail = E;
  }
  L->head = E;

  L->numelm += 1;
}

void insert_after(struct list * L, void * data, struct elmlist * ptrelm) {
  struct elmlist * E = (struct elmlist *) calloc( 1, sizeof(struct elmlist));

  if(ptrelm == NULL){
    cons(L, data);
  }
  else{
    struct elmlist* iterator = L->head;
    while(iterator != ptrelm){//on avance dans la liste jusqu'à trouver le bon endroit où insérer
      iterator = iterator ->suc;
    }
    E->data = data;
    E->suc = iterator->suc;
    E->pred = iterator;
    iterator->suc = E;

    if (E->suc){//si E n'est pas rajouté à la fin de la liste(car si ajouté en fin, E->suc point sur NULL donc E->suc->pred donne SegFault car inexistant)
      E->suc->pred = E;
    }
    else{//alors E est mis en fin de liste (ptrelm = L->tail)
      L->tail = E;
    }
    
    L->numelm +=1;
  }
}

void insert_ordered ( struct list * L, void * data, struct town * departure) {
 if( L->head == NULL) {
  cons(L, data);
 } else {
    struct elmlist * iterator = L->head;

    if( departure == NULL) { // C'est la liste des villes
      char * TownName = getTownName(data);//on récupère le nom de la ville à insérer (pour le comparer)
      char * iteratorName = getTownName(iterator->data);

      while(iterator && (strcmp(iteratorName, TownName) < 0)){//on se déplace jusqu'à trouver le  bon endroit où insérer, soit iterator
        iterator = iterator->suc;
        if(iterator)//condition nécessaire car si iterator est arrivé à NULL, iterator->data segfault
          iteratorName = getTownName(iterator->data);
      }
    } 
    else { // C'est une liste d'ajacence, une liste de routes (on regarde d'abord si U ou V de data est departure, puis dans chaque cas on regarde si U ou V de iterator est departure pour comparer avec l'autre ville)
      struct town * Udata = getURoad(data);//ville U de la route data
      struct town * Vdata = getVRoad(data);//ville V de la route data

      if (departure == Udata){// Si U de data est departure, on regarde alors V de data pour savoir où insérer data 

        while(iterator){// On parcourt la liste de routes 
          struct town * UIterator = getURoad(iterator->data);
          struct town * VIterator = getVRoad(iterator->data);

          if( UIterator == departure ){//2 choix possibles, soit U de la route à comparer est la ville departure, donc on compare avec V de la route, soit l'inverse (ville V de la route est le departure)
            if (strcmp(VIterator->name, Vdata->name) < 0) 
              iterator = iterator->suc;
            else 
              break;
          } 
          else{// Donc si V de iterator est departure
            if (strcmp(UIterator->name, Vdata->name) < 0)
              iterator = iterator->suc;
            else
              break;
          }
        }
      }
      else{// C'est donc V de data (Vdata) qui sert de departure, et il faut utiliser U de data pour savoir où l'insérer
        while(iterator){// On parcourt la liste de routes 
          struct town * UIterator = getURoad(iterator->data);
          struct town * VIterator = getVRoad(iterator->data);

          if (UIterator == departure){///U de iterator est departure, donc on utilise V de iterator pour comparer
            if (strcmp(VIterator->name, Udata->name) < 0)
              iterator = iterator->suc;
            else
              break;
          }
          else{// C'est donc V de iterator qui est departure, on utilise U de iterator pour comparer
            if (strcmp(UIterator->name, Udata->name) < 0)
              iterator = iterator->suc;
            else
              break;
          }
        }
      }
    }
    
    if ( iterator == NULL) { // Ajout en queue
      insert_after(L, data, L->tail);
    } else if ( iterator == L->head ) { // Ajout en Tête
      cons(L, data);
    } else {
        insert_after(L, data, iterator->pred);//iterator nous dit l'elmlist suivant, donc on insère avant celui là
    }
  }
}
