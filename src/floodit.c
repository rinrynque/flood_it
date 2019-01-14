/**
 * \file floodit.c
 * \brief Implémentation des fonctions relatives au déroulement du jeu
 * \author Vianney TOUCHARD
 */

#include "floodit.h"


/**
 * \fn int FIe_init(FIengine* engine, int argc, char** argv)
 * \brief Initialisation de la grille de jeu (mémoire, valeurs aléatoires)
 * 
 * \param engine Un pointeur vers un engine (tableau de jeu + options)
 * \param argc argc
 * \param argv argv
 * \return int Un entier
 */
int FIe_init(FIengine* engine, s_args arguments)
{
	srand(time(NULL));
	engine->options = 0;
	
	printf("Arguments :\nSize : %i\nNcurses : %i\nEssais : %i\nFichier : %s\n",
			arguments.size,
			arguments.ncurses,
			arguments.trials,
			arguments.input_file);
	
	engine->trials = arguments.trials;
	if(arguments.size)
	{
		engine->board.size = arguments.size;
	}
	else
	{
		int n = 0;
		printf("Choisissez la taille de la grille de jeu :");
		n = prompt_int();
		if (n<=0) {
		    printf("Vous devez choisir un entier strictement positif");
		}
		engine->board.size = n;
	}
	
	
	if(strcmp(arguments.input_file, ""))
	{
		FIb_loadfromfile(&(engine->board), arguments.input_file);
	}
	else
	{
		FIb_alloc(&(engine->board));
		FIb_init(&(engine->board));
	}
	
	if(arguments.ncurses)
	{
		engine->options |= F_NCURSES; /* On active l'option graphique*/
		FIe_initGUI(engine);
	}
	
	return 1;
}

/**
 * \fn void FIe_initGUI(FIengine* engine)
 * \brief Initialise de l'interface graphique
 * 
 * \param engine Un pointeur vers un engine (tableau de jeu + options)
 */
void FIe_initGUI(FIengine* engine)
{
	FIg_initncurses();
    FIg_initcolorpairs();
    int n = engine->board.size;
    engine->gui.boardwin = newwin(n + 2 , n*2 + 2, 3, 1);
    engine->gui.headerwin = newwin(3, n*2 + 2, 1, 1);
    engine->gui.choicewin = newwin(n + 2, 5*4+2, 3, n*2+2);
    engine->gui.messagewin = newwin(4, 20, 2, 4);
}

/**
 * \fn int FIe_start_loop(FIengine* engine)
 * \brief Initialisation de la taille de la grille et nombre de coups autorisés
 * 
 * \param engine Un pointeur vers un engine
 * \return int Un entier
 */
 int FIe_start_loop(FIengine* engine) {
 	
    if(engine->trials != 0)
    {
    	
    }
    else if(engine->options & F_NCURSES)
    {
    	engine->trials = 50;
    }
    else
    {
    	while (engine->trials<=0) {
			printf("Choisissez votre nombre de coups autorisé :");
			engine->trials = prompt_int();
			if (engine->trials<=0) {
			    printf("Vous devez choisir un nombre de coup strictement positif");
			}
    	}
	}

	FIe_mainloop(engine);
	return 0;
 }
 
/**
 * \fn int FIe_mainloop(FIengine* engine)
 * \brief Boucle de jeu
 * 
 * \param engine Un pointeur vers un engine
 */
int FIe_mainloop(FIengine* engine)
{
	int continuer = 0;
	char c = ' ';

	while(!continuer)
	{
		if(engine->options & F_NCURSES)
		{
			c = FIe_guiloop(engine);
		}
		else
		{
			FIb_display(&(engine->board));
			printf("Nombre de coups restants : %i\n", engine->trials);
			do
			{
				printf("Choisissez une couleur.\n");
				c = prompt_char();
				c = toupper(c);
			}
			while( !strchr("QBVGRMJ", c));
		}
		
		if (c != 'Q')
		{
			FIboard comp;
			comp = FIb_connectedcomp(&(engine->board),0,0);
			FIb_colorcomp(&(engine->board), &comp, colorpair(c));
			FIb_destroy(&comp);
			if(engine->trials > 0)
			{
				engine->trials--;
			}
		}
		

		
		if (c == 'q' || c=='Q')
		{
		    continuer = 3;
		    
		    if (engine->trials==0) {
				continuer=2;
			}
		}
		
		if (FIb_win(engine->board)) {
			continuer=1;
		}
	}
	
	FIe_endscreen(engine, continuer);
	return 0;
}

/**
 * \fn void FIe_endscreen(FIengine* engine, int continuer)
 * \brief Affiche le message de fin
 * 
 * \param engine Un pointeur vers un engine
 * \param continuer un entier indiquant le dénouement du jeu
 */
void FIe_endscreen(FIengine* engine, int continuer)
{
	const char* endcomment[] = {"Vous avez gagne !\n TRO FOR !\n",
						   	   "Vous avez perdu !\n",
						   	   "Au revoir !\n Reviens vite !\n"	};
	if(engine->options & F_NCURSES)
	{
		
		FIe_ndraw(engine, 1);
    	wattrset(engine->gui.messagewin,COLOR_PAIR(8)|A_BOLD);
		mvwprintw(engine->gui.messagewin,
				  1,
				  1,
				  "%s",endcomment[continuer-1]);
    	wborder(engine->gui.messagewin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		FIe_nrefresh(engine);
		wrefresh(engine->gui.messagewin);
		getch();
	}
	else
	{
		printf("%s", endcomment[continuer-1]);
	}
}

/**
 * \fn void FIe_ndraw(FIengine* engine, int choice)
 * \brief Dessine le jeu
 * 
 * \param engine Un pointeur vers un engine
 * \param choice un entier indiquant le choix surligné
 */
void FIe_ndraw(FIengine* engine, int choice)
{
	FIg_drawheader(engine->gui.headerwin);
	FIg_drawchoice(engine->gui.choicewin, choice, engine->trials);
	FIg_drawgrid(engine->gui.boardwin, &(engine->board));
}

/**
 * \fn void FIe_nrefresh(FIengine* engine)
 * \brief Rafraîchit l'affichage du jeu
 * 
 * \param engine Un pointeur vers un engine
 */
void FIe_nrefresh(FIengine* engine)
{
	wrefresh(engine->gui.headerwin);
	wrefresh(engine->gui.choicewin);
	wrefresh(engine->gui.boardwin);
}

/**
 * \fn char FIe_guiloop(FIengine* engine)
 * \brief Boucle demandant l'action au joueur, pour l'affichage graphique
 * 
 * \param engine Un pointeur vers un engine
 */
char FIe_guiloop(FIengine* engine)
{
	
    int c = ERR;
    int choice = 0;
    
    do
    {
		FIe_ndraw(engine, choice);
		FIe_nrefresh(engine);
        c = getch();
        
        if (c==KEY_LEFT)
        {
        	choice--;
        }
        else if(c==KEY_RIGHT)
        {
        	choice++;
        }
        else if(c=='\n')
        {
        	c = colorchar(choice+1);
        }
        else
        {
        	c = toupper(c);
        }
        
        choice = positive_modulo(choice, 6);
        
    } while(!strchr("QBVGRMJ", c));
	
	return c;
}

/**
 * \fn int FIe_destroy(FIengine* engine)
 * \brief Libération de la mémoire du plateau de jeu/options
 * 
 * \param engine Un pointeur vers un engine (tableau de jeu + options)
 * \return int Un entier
 */
int FIe_destroy(FIengine* engine)
{
	FIb_destroy(&(engine->board));
	if(engine->options & F_NCURSES)
	{
		FIg_endGUI();
	}
	return 1;
}

