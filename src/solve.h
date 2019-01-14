/**
 * \file solve.h
 * \brief Header de solve, contient la définition de FIsolution
 */
 
#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "board.h"

/**
 * \struct FIsolution
 * \brief Un tableau contenant la séquence de couleurs solution de la grille
 */
typedef struct
{
	char seq[100]; /*!< tableau de caractères */
	int len; /*!< Longueur de la séquence (nombre de coups) */
} FIsolution;

void FIs_display(FIsolution* solution);

void FIs_solve(FIboard board, FIsolution solution, FIsolution* bestSol, int depth);
FIsolution* FIs_newSol(FIsolution solution, char c);
