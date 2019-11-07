#ifndef _LIST_
#define _LIST_
/**
 * @brief
 * Liste générique homogène doublement chaînée
 * 
 * @note
 * Du fait de l'inclusion de "town.h" par "list.h"
 * et de l'inclusion "list.h" par "town.h",
 * il est nécessaire de rappeler dans le fichier "list.h"
 * que la structure town est déclarée par ailleurs.
 */
struct town;
#include <stdbool.h>
#include "town.h"

/**
 * @brief
 * Un élément de liste contient
 * (+) Une donnée (data)
 * (+) Une référence (suc) à l'élément suivant
 * (+) Une référence (pred) à l'élément précédent
 */
struct elmlist {
  void * data;
  struct elmlist * suc, * pred;
};

/**
 * La liste est une structure contenant
 * (+) Une référence (head) sur son premier élément,
 * (+) Une référence (tail) sur son dernier élement et
 * (+) Le nombre d'éléments
 */
struct list {
  struct elmlist * head, * tail;
  int numelm;
};

/**
 * @brief
 * Construire une liste vide
 */
struct list * new ();

/**
 * @brief
 * Vérifier si la liste L est vide
 */
bool isempty ( struct list * L );

/**
 * @brief
 * Deux possibilités de supprimer la liste L :
 * (+) Si le pointeur de fonction (ptrF) est indéfini (NULL)
 *     Alors les données (data) référencées par les élements
 *     de la liste L ne sont pas supprimées ;
 * (+) Si le pointeur de fonction (ptrF) est défini
 *     Alors ce pointeur de fonction (ptrF) référence la fonction
 *     devant servir à supprimer les données (data) référencées par
 *     les éléments de la liste L.
 */
void dellist ( struct list * L, void (*ptrF) () );

/**
 * @brief
 * Ajouter en tête de la liste L un élément de donnée data
 */
void cons ( struct list * L, void * data );

/**
 * @brief
 * Afficher les éléments de la liste.
 * Chaque élément est affiché grâce au pointeur de fonction ptrF
 */
void viewlist ( struct list * L, void (*ptrF) () );

/**
 * @brief
 * Insérer un élément de liste de donnée data dans la liste L
 * après le pointeur d'élément ptrelm
 * 
 * Note.
 *    le pointeur d'élément ptrelm désigne obligatoirement
 *    un élément de la liste L.
 */
void insert_after ( struct list * L, void * data, struct elmlist * ptrelm );

/**
 * @brief
 * Deux possibilités de liste générique homogène :
 * (+) Si L est une liste de villes
 *     Alors l'ordre est donné par les noms des villes
 *     et il est nullement besoin d'indiquer une ville de départ (departure)
 *     Dans ce cas la ville de départ (departure) ne doti pas être
 *     référencée (NULL)
 * (+) Si L est une liste de routes
 *     Alors c'est la liste d'adjacence de la ville de départ (departure)
 *     et l'ordre est donné par les noms des villes reliées à cette ville
 *     de départ (departure)
 */
void insert_ordered ( struct list * L, void * data, struct town * departure );

#endif // _LIST_
