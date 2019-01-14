/**
 * \file comp.h
 * \brief Header de comp, contient les structures pour voir le tableau comme un graphe
 */
 
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "board.h"
#include "solve.h"

/**
 * \struct FIsolution2
 * \brief Structure d'une solution : seq la séquence d'entier solution (correspondance avec couleurs) et len sa longueur
 */
typedef struct
{
	int seq[100]; /*!< tableau de caractères */
	int len; /*!< Longueur de la séquence (nombre de coups) */
} FIsolution2;

void FIs2_display(FIsolution2* solution);

/**
 * \struct FIcomp
 * \brief Structure d'une composante connexe : weigth le nombre de case dedans, color sa couleur,
 * et link un tableau avec les id des composantes liées.
 */
typedef struct
{
	int id;
	int weight; /* nombre de cases colorées */
	int color; 
	int links[100]; /* Liens avec les autres composantes */
	int nlinks; /* nombre de liens */
} FIcomp;



void FIc_solveOpti(FIcomp* board, FIsolution2 solution, FIsolution2* bestSol, int depth);
int FIc_nthBestChoice(FIcomp* gboard, int n);
void FIc_colorComps(FIcomp* gboard, int c);
int FIc_win(FIcomp* gboard);

FIcomp* FIc_compBoard(FIboard* board);
void FIc_linksComp(FIboard* board, FIcomp* comps);
int* FIc_bestChoices(FIcomp* g);

void FIc_dispComp(FIcomp comp);
void FIc_addLink(FIcomp* comp, int id);
void FIc_clearLinks(FIcomp* comp);
void FIc_remLink(FIcomp* comp, int id);
int FIc_isLinked(FIcomp* comp, int id);

