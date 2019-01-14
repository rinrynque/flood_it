/**
 * \file argparse.h
 * \brief Définit le parsing des arguments du programme en utilisant Argp : http://www.gnu.org/software/libc/manual/html_node/Argp.html (regarder l'exemple 3)
 */
 
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"

#define ARG_NUM 0  /*!< Nombre d'arguments attendus (non utilisés pour éviter des warnings) */


/**
 * \struct s_args 
 * \brief structure utilisée par le parseur d'option parse_opt
 */
typedef struct
{
  unsigned int ncurses; /*!< Booléen pour savoir si ncurses est utilisé*/
  unsigned int size; /*!< Taille du plateau voulue*/
  unsigned int trials; /*!< Nombre d'essais accordés*/
  char* input_file; /*!< Chemin vers un fichier pour charger la carte*/
} s_args;

int parse_opt(s_args* arguments, int argc, char** argv);
s_args FI_argp(int argc, char** argv);
