#include "gui.h"

/**
 * \fn void FIg_initncurses()
 * \brief Appelle les fonctions d'initialisation d'une console ncurse
 */
void FIg_initncurses()
{
    // Initialisation de ncurses
    initscr();
    if(has_colors() == FALSE)
	{	endwin();
		printf("Votre terminal n'affiche pas les couleurs.\nLancez le programme sans interface graphique\n");
		exit(1);
	}
	start_color();	
	
    //cbreak();
    noecho();
    raw();
    //halfdelay(10);
    keypad(stdscr, TRUE);
    curs_set(0);
}
/**
 * \fn void FIg_initcolorpairs()
 * \brief Initialise les paires de couleur utilisées par l'affichage
 */
void FIg_initcolorpairs()
{
    init_pair(1, COLOR_BLUE, COLOR_YELLOW); /* 'B' */
    init_pair(2, COLOR_GREEN, COLOR_MAGENTA); /* 'V' */
    init_pair(3, COLOR_RED, COLOR_CYAN); /* 'R' */
    init_pair(4, COLOR_YELLOW, COLOR_BLUE); /* 'J' */
    init_pair(5, COLOR_MAGENTA, COLOR_GREEN); /* 'M' */
    init_pair(6, COLOR_CYAN, COLOR_RED); /* 'G' */
    
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);
    init_pair(9, COLOR_BLACK, COLOR_RED);
    
    init_pair(11, COLOR_BLUE, COLOR_BLUE); /* 'B' */
    init_pair(12, COLOR_GREEN, COLOR_GREEN); /* 'V' */
    init_pair(13, COLOR_RED, COLOR_RED); /* 'R' */
    init_pair(14, COLOR_YELLOW, COLOR_YELLOW); /* 'J' */
    init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA); /* 'M' */
    init_pair(16, COLOR_CYAN, COLOR_CYAN); /* 'G' */
}

/**
 * \fn void FIg_drawgrid(WINDOW* win, FIboard* board)
 * \brief Dessine la grille de jeu
 * 
 * \param win Fenêtre ncurse
 * \param board Plateau de jeu
 */
void FIg_drawgrid(WINDOW* win, FIboard* board)
{
    wclear(win);
    wattrset(win,A_NORMAL|A_BOLD|COLOR_PAIR(7));
    wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_LTEE, ACS_PLUS, ACS_LLCORNER, ACS_BTEE);
    wattrset(win,A_NORMAL);
    
    int i, j;
    for (i=0; i<board->size; i=i+1)
    {
        for (j=0; j<board->size; j=j+1) 
        {
           wattrset(win,A_REVERSE
                   |COLOR_PAIR(
                               board->colors[i][j]+10
                               )
                  );
           mvwaddch(win, 1 + i, 1 + j*2, ' ');
           mvwaddch(win, 1 + i, 1 + j*2+1, ' ');
        }
    }
    wattrset(win,A_NORMAL);
}

/**
 * \fn void FIg_drawheader(WINDOW* win)
 * \brief Dessine le 'header' de notre affichage en jeu
 * 
 * \param win Une fenêtre ncurse
 */
void FIg_drawheader(WINDOW* win)
{
    wclear(win);
    wattrset(win,A_NORMAL|COLOR_PAIR(7)|A_BOLD);
    wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    wattrset(win,A_NORMAL|COLOR_PAIR(8)|A_BOLD);
    mvwprintw(win,1,2, "P.N.L : FLOOD IT !");
    wattrset(win,A_NORMAL);
}

/**
 * \fn void FIg_drawchoice(WINDOW* win, int choice, int trials)
 * \brief Dessine la partie de sélection de couleur
 * 
 * \param win Fenêtre ncurse
 * \param choice choix surligné
 * \param trials nombre d'essais restants
 */
void FIg_drawchoice(WINDOW* win, int choice, int trials)
{
    wclear(win);
    
    /*Dessin de bordure*/
    wattrset(win,A_NORMAL|COLOR_PAIR(7)|A_BOLD);
    wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    
    /*Dessin de la palette de choix*/
    wattrset(win,A_NORMAL|COLOR_PAIR(8)|A_BOLD);
    int i;
    for(i = 1; i <= 6; i++)
    {
       wattrset(win, A_REVERSE | COLOR_PAIR(i));
       mvwaddch(win, 2, (i-1)*3+2, colorchar(i));
       waddch(win, ' ');
    }
    /*On entoure le choix courant */
    wattrset(win,A_NORMAL|COLOR_PAIR(7));
    FIg_drawbox(win, 1, choice*3+1,1,2);
    
    /* On affiche le nombre de coups restants */
    wattrset(win,A_NORMAL|A_BOLD|COLOR_PAIR(7));
    mvwprintw(win, 4,2, "Restants : %i", trials);
    
    wattrset(win,A_NORMAL);
}

/**
 * \fn void FIg_drawbox(WINDOW* win, int l, int c, int h, int w)
 * \brief Dessine une boite
 * 
 * \param win Fenêtre ncurse
 * \param l ligne
 * \param c colonne
 * \param h hauteur
 * \param w largeur
 */
void FIg_drawbox(WINDOW* win, int l, int c, int h, int w)
{
    int i;
    for(i = 0; i < h; i++)
    {
       mvwaddch(win, l+1+i, c, ACS_VLINE);
       mvwaddch(win, l+1+i, c+1+w, ACS_VLINE);
    }
    for(i = 0; i < w; i++)
    {
       mvwaddch(win, l, c+1+i, ACS_HLINE);
       mvwaddch(win, l+1+h, c+1+i, ACS_HLINE);
    }
    
   mvwaddch(win, l, c, ACS_ULCORNER);
   mvwaddch(win, l, c+1+w, ACS_URCORNER);
   mvwaddch(win, l+1+h, c, ACS_LLCORNER);
   mvwaddch(win, l+1+h, c+1+w, ACS_LRCORNER);
   wattrset(win,A_NORMAL);
   
}

/**
 * \fn void FIg_endGUI()
 * \brief Termine l'interface graphique
 */
void FIg_endGUI()
{
    endwin();
}
