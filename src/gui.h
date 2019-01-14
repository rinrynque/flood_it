#pragma once

#include <ncurses.h>
#include <ctype.h>

#include "utils.h"
#include "board.h"

/**
 * \struct FIgui
 * \brief la structure accueillant les fenêtres du moteur
 */
typedef struct
{
    WINDOW* headerwin; /*!< Fenetre d'affichage du header */
    WINDOW* boardwin; /*!< Fenetre d'affichage du plateau */
    WINDOW* choicewin; /*!< Fenetre d'affichage du choix */
    WINDOW* messagewin; /*!< Fenetre d'affichage du message */
} FIgui;

void FIg_initncurses();
void FIg_initcolorpairs();
void FIg_drawheader(WINDOW* win);
void FIg_drawgrid(WINDOW* win, FIboard* board);
void FIg_drawchoice(WINDOW* win, int choice, int trials);
void FIg_endGUI();

void FIg_drawbox(WINDOW* win, int l, int c, int h, int w);
