#ifndef _ROAD_H_
#define _ROAD_H_

#include "list.h"

/** TYPE ABSTRAIT
 * Cette structure décrit une route
 * par les deux villes U et V qu'elle relie.
 */
struct road {
  struct town * U, * V; // indices of towns in graph->towns
  // double km;
  // and all the stuff you want/need
};

// Créer une route qui relie les villes u et v données
struct road * createRoad(struct town * u, struct town * v);

// Libérer une route référencée par ptrR
void freeRoad ( struct road * R );

// Consulter la ville U de la route R donnée
struct town * getURoad(struct road * R);

// Modifier la référence U
void setURoad ( struct road * R, struct town * T );

// Consulter la ville V de la route R donnée
struct town * getVRoad(struct road * R);

// Modifier la référence V
void setVRoad ( struct road * R, struct town * T );

// Afficher le nom de deux villes que la route (R) connecte
void viewRoad ( struct road * R );

// Créer une liste de routes à partir d'un fichier filename
struct list * getRoadListFromFile(char * filename);

#endif // _ROAD_H_