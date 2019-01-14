/**
 * \file cpile.h
 * \brief Header de cpile, contient la définition de cpile
 * \author Vianney TOUCHARD
 */
 
#pragma once

/**
 * \struct cpile 
 * \brief Une pile acceptant des pointeurs vers n'importe quoi
 */
struct cpile
{
	void* elt; /*!< Pointeur vers une variable quelconque */
	struct cpile* prec; /*!< Pointeur vers l'élément précédent */
};
typedef struct cpile cpile;

void cp_push(cpile**, void*);
void* cp_pop(cpile**);
void* cp_peak(cpile**);
