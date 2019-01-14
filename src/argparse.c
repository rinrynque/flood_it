#include "argparse.h"

int parse_opt(s_args* arguments, int argc, char** argv)
{
  int key;
  key = getopt (argc, argv, "gcs:n:l:");
  switch (key)
    {
    case 'c': case 'g':
      arguments->ncurses = 1;
      break;
    case 'l':
      strcpy(arguments->input_file, (optarg!=NULL?optarg : ""));
      break;
    case 's':
      arguments->size = (optarg!=NULL ? atoi(optarg) : 0);
      break;
    case 'n':
      arguments->trials = (optarg!=NULL ? atoi(optarg) : 0);
      break;
    case '?':
    printf("P.N.L : FLOOD IT ! -- INONDER LES JOLIES COULEURS\n \
            Utilisation :\n \
            -g, -c : affichage graphique\n \
            -s INT : taille du plateau\n \
            -n INT : nombre d'essais\n \
            -l FICHIER : Charger depuis un fichier (deboguage)\n");
            exit(0);
      break;
    default:
      return 0;
      break;
    }
    return 1;
}

/**
 * \fn int FI_argp(int argc, char** argv)
 * \brief Parsing d'arguments ligne de commande
 * 
 * \param argc argc
 * \param argv argv
 * \return s_args une structure contenant les options interprétées
 */
s_args FI_argp(int argc, char** argv)
{
	s_args arguments;
	arguments.size = 0;
  arguments.ncurses = 0;
  arguments.trials = 0;
  arguments.input_file="";
  
  while (parse_opt(&arguments, argc,argv));
  if(!arguments.ncurses)
	{
    char c = '\0';
    while('y'!=c && 'n' !=c)
    {
      printf("Voulez-vous lancer floodit en mode graphique (y/n)?\n\
(<-/-> ou caracteres pour sélectionner la couleur):");
      c = prompt_char();
    }
    if(c == 'y')
    {
      arguments.ncurses = 1;
    }
	}
  
	return arguments;
}
