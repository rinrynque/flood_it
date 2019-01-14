/**
 * \file board.h
 * \brief Header de board, contient la définition du plateau de jeu
 * \author Laure BEDU
 */

#pragma once

#define H_BOARD_H
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "cpile.h"

/**
 * \struct FIboard
 * \brief Implémentation de la structure de plateau de jeu, avec une taille propre, et des couleurs pour chaque case 
 * \author Laure BEDU
 */
typedef struct
{
  int size; /*!< Taille du plateau */
  int** colors;  /*!< Tableau contenant les couleurs */
 } FIboard;

/**
 * \struct pixel
 * \brief Implémentation de la structure de pixel, avec des coordonnées et une couleur
 * \author Vianney TOUCHARD
 */
typedef struct
{
	int i;  /*!< Colonne du pixel */
	int j;  /*!< Ligne du pixel */
	int color;  /*!< Couleur du pixel */
} pixel;

FIboard FIb_new(int n);

void FIb_alloc(FIboard* board);
void FIb_init(FIboard* board);
void FIb_copy(FIboard* b1, FIboard* b2);
void FIb_display(FIboard* board);
void FIb_destroy(FIboard* board);

int FIb_loadfromfile(FIboard* board, char* filename);

FIboard FIb_connectedcomp(FIboard* board, int init_row, int init_column);
int FIb_colorcomp(FIboard* board, FIboard* comp, int c);
void FIb_color (FIboard* board , int i, int j, int color);
int FIb_win (FIboard board);

pixel* pix_new(int i, int j, int color);
