/**
 * \file utils.c
 * \brief Implémentation des fonctions relatives à la jouabilité du logiciel, et diverses
 * \author Laure BEDU, Vianney TOUCHARD
 */
 
 #include "utils.h"

/**
 * \fn compare_int(const int a, const int b)
 * \brief Fonction de comparaison de 2 entiers
 * 
 * \return int -1 si a < b, 1 sinon
 */
int compare_int(const int a , const int b) {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    }
    return 0;
}

/**
 * \fn char cmp_func (const void *a, const void* b)
 * \brief Fonction de comparaison de variables (utilisé dans comp.c avec qsort)
 * 
 * \return c -1 si a < b, 1 sinon
 */
int cmp_func(const void *a, const void *b) {
    const intPair *num1 = (intPair *)a;
    const intPair *num2 = (intPair *)b;

    return compare_int(num2->b, num1->b);
}

/**
 * \fn char char_aleat ()
 * \brief Fonction de renvoi aléatoire de char, parmis les couleurs proposées
 * 
 * \return c Un char parmis R,J,B,V,O,P
 */
char char_aleat ()
{
  int rando = (rand()%6) +1;
  return colorchar(rando);
}

int color_aleat()
{
    return (rand()%6) +1;
}

/**
 * \fn void clean_stdin()
 * \brief Fonction de nettoyage du flux stdin
 * 
 * \return rien
 */
int clean_stdin()
{
    scanf ("%*[^\n]"); /* Regex vidant tous les caractères avant un \n*/
    getchar (); /* Vide le \n */
    return 1;
}

/**
 * \fn char prompt_char()
 * \brief Fonction de récupération du charactère saisi par l'utilisateur
 * 
 * \return c Un char parmis R,J,B,V,O,P (saisi par l'utilisateur)
 */
char prompt_char()
{
    char buffer[2];
    scanf ("%1s", buffer);
    clean_stdin();
    return buffer[0];
}

/**
 * \fn char prompt_int()
 * \brief Fonction de récupération de l'entier saisi par l'utilisateur
 * 
 * \return i Un entier
 */
int prompt_int()
{
    int n=0;
    char c;
    do {
        printf("\n:");
    }
    while (((scanf("%d%c",&n,&c)!=2 || c!='\n') && clean_stdin()) || n<1);
    /* On boucle sur la demande tant que l'utilisateur n'a pas rentré une saisie correcte (correspondante à l'expression du scanf) */
    return n;
}

/**
 * \fn int colorpair(char c)
 * \brief Renvoie le numéro de la paire de couleurs (ncurses) associée au caractère envoyé
 * 
 * \return un entier
 */
int colorpair(char c)
{
  return (c == 'B' ? 1 : (
          c == 'V' ? 2 : (
          c == 'R' ? 3 : (
          c == 'J' ? 4 : (
          c == 'M' ? 5 : (
          c == 'G' ? 6 : (
            -1 )))))));
}

/**
 * \fn int colorchar(int i)
 * \brief Renvoie le caractère de couleur associée à l'entier envoyé (désignant une paire de couleur ncurses)
 * 
 * \return un caractère
 */
char colorchar(int i)
{
  return ( i == 1 ? 'B' : (
           i == 2 ? 'V' : (
           i == 3 ? 'R' : (
           i == 4 ? 'J' : (
           i == 5 ? 'M' : (
           i == 6 ? 'G' : (
    'L' )))))));
}

/**
 * \fn int positive_modulo(int i, int n)
 * \brief Modulo positif
 * \param i i
 * \param n n
 * \return le modulo mathématique i mod n
 */
int positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

