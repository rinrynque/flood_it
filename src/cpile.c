/**
 * \file board.c
 * \brief Implémentation des fonctions relatives à la manipulation de piles
 * \author Vianney TOUCHARD
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "cpile.h"

/**
 * \fn void cp_push(cpile** p, void* e)
 * \brief Procdure d'empilement d'un élément sur une pile
 * 
 * \param p Un double pointeur vers une structure cpile (pour pouvoir changer le dessus)
 * \param e Pointeur vers un élément à ajouter sur la pile
 */
void cp_push(cpile** p, void* e)
{
	cpile* np = malloc(sizeof(cpile));
	if(!np) exit(EXIT_FAILURE);     /* Si l'allocation a échouée. */
	np->elt = e;
	np->prec = (cpile*) *p;
	*p = np;       /* Le pointeur pointe sur la nouvelle pile. */
}

/**
 * \fn void cp_pop(cpile** p)
 * \brief Procdure de dépilement d'un élément sur une pile
 * 
 * \param p Un double pointeur vers une structure cpile (pour pouvoir changer le dessus)
 * \return Un pointeur vers l'élément qui était placé sur la pile (à free si nécessaire)
 */
void* cp_pop(cpile** p)
{ 
	void* Val;
	cpile* tmp;
	if(!*p) return NULL;     /* Retourne NULL si la pile est vide. */
	tmp = (*p)->prec;
	Val = (*p)->elt;
	free(*p);
	*p = tmp;       /* Le pointeur pointe sur le dernier élément. */
	return Val;     /* Retourne la valeur soutirée de la pile. */
}

/**
 * \fn void cp_peak(cpile** p)
 * \brief Procdure de peak de la pile
 * 
 * \param p Un double pointeur vers une structure cpile (parce que c'est ce qui a été utilisé partout)
 * \return Un pointeur vers l'élément qui était placé sur la pile (à free si nécessaire)
 */
void* cp_peak(cpile** p)
{
    return (*p)->elt;
}
