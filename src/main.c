#include "floodit.h"

int main(int argc, char** argv)
{
	printf("> Flood It\n");
	
	printf("> Parsing des arguments\n");
	s_args arguments = FI_argp(argc, argv);
	
	FIengine engine;
	
	printf("> Initialisation du moteur\n");
	FIe_init(&engine, arguments);

	if(!arguments.ncurses)
	{
		printf("> Initialisation de la résolution\n");
		FIsolution2 initSol = {{0}, 0};
		FIsolution2 bestSol = {{0}, 25};
		
		printf("> Determination des composantes connexes\n");
		FIcomp* cboard = FIc_compBoard(&(engine.board));
		FIb_display(&(engine.board));
		
		printf("> Resolution\n");
		FIc_solveOpti(cboard, initSol, &bestSol, 0);
		free(cboard);
		
		printf("Solution de len %i:\n", bestSol.len);
		FIs2_display(&bestSol);
	}
	
	printf("> Boucle principale (q pour quitter)\n");
	FIe_start_loop(&engine);
	printf("> Destruction du moteur\n");
	FIe_destroy(&engine);
	
	//printf("> Initialisation de la carte à partir de resources/map.txt\n");
	//FIb_loadfromfile(&(engine.board), "resources/map.txt");
	//printf("> Destruction du moteur\n");
	//FIe_destroy(&engine);
	return 0;
}
