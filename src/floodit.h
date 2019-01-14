/**
 * \file floodit.h
 * \brief header de floodit, définition du deroulement du jeu
 * \author Vianney TOUCHARD
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "utils.h"
#include "argparse.h"
#include "gui.h"
#include "solve.h"
#include "comp.h"

#define F_NCURSES 1 /*!< Flag pour l'utilisation de ncurses*/

/**
 * \struct FIengine
 * \brief Implémentation de la structure de engine, qui comprend le board et les options de jeu
 * \author Vianney TOUCHARD
 */
typedef struct
{
    FIboard board; /*!< plateau de jeu*/
    int trials; /*!< nombre de coups restants*/
    unsigned int options; /*!< les options sont representes par les flags*/
    FIgui gui; /*!< La structure d'interface*/
} FIengine;

int FIe_init(FIengine* engine, s_args arguments);
void FIe_initGUI(FIengine* engine);
int FIe_start_loop(FIengine* engine);
void FIe_ndraw(FIengine* engine, int continuer);
void FIe_nrefresh(FIengine* engine);
int FIe_mainloop(FIengine* engine);
char FIe_guiloop(FIengine* engine);
int FIe_destroy(FIengine* engine);
void FIe_endscreen(FIengine* engine, int continuer);
