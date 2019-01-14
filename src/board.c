/**
 * \file board.c
 * \brief Implémentation des fonctions relatives au tableau de jeu
 * \author Laure BEDU, Vianney TOUCHARD
 */
 
 #include "board.h"

/**
 * \fn FIboard FIb_new(int n)
 * \brief Allocation de la mémoire pour la grille de jeu 
 * 
 * \param n Entier non-nul, taille du plateau
 * \return res Plateau avec des cases vides
 */

FIboard FIb_new(int n)
{
  FIboard res;
  res.size = n;
  FIb_alloc(&res);
  return res;
}

/**
 * \fn void FIb_alloc(FIboard* board)
 * \brief Allocation de la memoire pour la taille de la grille de jeu
 * 
 * \param board pointeur vers un plateau
 * \return rien
 */
void FIb_alloc(FIboard* board)
{
  board->colors = (int**) calloc (board->size,sizeof(int*));
  int i;
  for (i=0; i<board->size; i=i+1)
  {
    board->colors[i]= (int*) calloc (board->size,sizeof(int));
  }
}

/**
 * \fn void FIb_init(FIboard* board)
 * \brief Procdure d'initialisation de la grille de jeu, avec des couleurs alatoires
 * 
 * \param board Un pointeur vers un plateau avec la memoire alloue pour chaque case
 * \return rien
 */

void FIb_init(FIboard* board){
  int i, j;
  for (i=0; i<board->size; i=i+1) {
    for (j=0; j<board->size; j=j+1) {
      board->colors[i][j]=color_aleat();
    }
  }
}

/**
 * \fn void FIb_copy(FIboard* b1, FIboard* b2)
 * \brief Procdure de copie d'un board dans un autre
 * 
 * \param b1 b2 2 pointeurs vers un tableau de jeu
 */

void FIb_copy(FIboard* b1, FIboard* b2) {
  b2->size = b1->size;
  FIb_alloc(b2);
  int i,j;
  for (i=0; i<b1->size; i=i+1) {
    for (j=0; j<b1->size; j=j+1) {
      b2->colors[i][j]= b1->colors[i][j];
    }
  }
}

/**
 * \fn void FIb_display(FIboard* board)
 * \brief Procdure d'affichage de la grille de jeu
 * 
 * \param board Un pointeur vers un tableau de jeu
 * \return rien
 */

void FIb_display(FIboard* board)
{
  int i, j; 
  printf("Cote : %d\n==\n", board->size);
  for (i=0; i<board->size; i=i+1)
  {
    printf("|");
    for (j=0; j<board->size; j=j+1) 
    {
      printf("%c", colorchar(board->colors[i][j]));
    }
    printf("|\n");
  }
  printf("==\n");
}

/**
 * \fn void FIb_destroy(FIboard* board)
 * \brief Procdure de libration de memoire de la matrice
 * 
 * \param board un pointeur vers plateau de jeu avec de la memoire alloue
 * \return rien
 */

void FIb_destroy(FIboard* board){
  int i;
  for (i=0; i<board->size; i=i+1) {
    free(board->colors[i]);
  }
  free(board->colors);
  board->size = 0;
}

/**
 * \fn int FIb_loadfromfile(FIboard* board, char* filename)
 * \brief Chargement d'un plateau de jeu depuis un fichier
 * 
 * \param board filename Un pointeur vers le plateau de jeu
 * \param filename le nom du fichier à charger
 * \return un code d'erreur à 0 si tout s'est bien passé
 */
int FIb_loadfromfile(FIboard* board, char* filename)
{
  FILE* texte = NULL;
  texte = fopen(filename, "r");
  if (texte == NULL) 
  {
    int errnum = errno;
    perror("Erreur ");
    fprintf(stderr, "Erreur a l ouverture de %s : %s\n", filename, strerror( errnum ));
    return 1;
  }
  
  char c = '\0';
  int i = 0;
  int j = 0;
  int n = 0;
  /* On compte le nombre de caractères sur la première ligne pour savoir la taille du plateau */
  while( c!='\n' )
  {
    n++;
    if( EOF == (c = fgetc(texte)) ) /* On lit le caractère dans c, et on vérifie si on arrive à EOF */
    {
      fprintf(stderr, "Erreur : %s n'est pas une carte valide", filename);
      return 1;
    }
  }
  board->size = n-1;
  FIb_alloc(board);
  
  c='\0';
  rewind(texte);
  
  while( j < n &&  c != EOF)
  {
    c = fgetc(texte);
    if (c == '\n')
    {
      j++;
      i = 0;
    }
    else
    {
      FIb_color(board, j, i, c);
      i++;
    }
  }
  
  fclose(texte);
  return 0;
}

/**
 * \fn FIboard FIb_connectedcomp(FIboard* board)
 * \brief Reconnaissance de la composante 4-connexe incluant la case d'origine (ligne init_row, colone init_column)
 * 
 * \param board Un pointeur vers le plateau de jeu
 * \return Plateau masque contenant des 'C' aux pixels de la composante connexe
 */
 
FIboard FIb_connectedcomp(FIboard* board, int init_row, int init_column)
{
  /* Implémentation de l'algorithme de remplissage par diffusion https://fr.wikipedia.org/wiki/Algorithme_de_remplissage_par_diffusion */
	cpile* P = NULL;
	
	/* On veut faire un pot de peinture sur le pixel en haut à gauche */
	int colcible = board->colors[init_row][init_column];
	
	/* On crée un plateau qui contiendra seulement des '\0' ou des 'C' qui représente la composante connexe à colorer*/
	FIboard conn_comp = FIb_new(board->size);
	
	/*Dans tous les cas, on colorie le pixel en haut à gauche*/
	cp_push(&P, pix_new(init_row,init_column, -1));
	
	int it = 0;
	while(P != NULL)
	{
	  it++;
	  
	  /* On dépile un pixel */
		pixel* n = (pixel*)(cp_pop(&P));
		
		/* On ajoute le pixel à la composante connexe */
		conn_comp.colors[n->i][n->j] = -1;
		
		/* Pour chaque direction, on va regarder si le pixel est de la couleur qu'on veut remplacer
		et si il n'a pas déjà été ajouté à la composante connexe */
		/* Si c'est le cas, on l'ajoute à la pile */
		/*Nord*/
		if(n->i > 0 && board->colors[n->i - 1][n->j] == colcible 
		&& conn_comp.colors[n->i - 1][n->j] != -1)
		{
			cp_push(&P, pix_new(n->i - 1, n->j, 0));
		}
		/*Sud*/
		if(n->i < board->size-1 && board->colors[n->i + 1][n->j] == colcible
		&& conn_comp.colors[n->i + 1][n->j] != -1)
		{
			cp_push(&P, pix_new(n->i + 1, n->j, -1));
		}
		/*Est*/
		if(n->j < board->size-1 && board->colors[n->i][n->j+1] == colcible
		&& conn_comp.colors[n->i][n->j+1] != -1)
		{
			cp_push(&P, pix_new(n->i, n->j+1, -1));
		}
		/*Ouest*/
		if(n->j > 0 && board->colors[n->i][n->j - 1] == colcible
		&& conn_comp.colors[n->i][n->j - 1] != -1)
		{
			cp_push(&P, pix_new(n->i, n->j - 1, -1));
		}
		free(n);
	}
	return conn_comp;
}
	
/**
 * \fn void FIb_colorcomp(FIboard* board, FIboard* comp, char c)
 * \brief Coloriage d'un board suivant un masque de pixels
 * 
 * \param board Un pointeur vers le plateau de jeu
 * \param comp un plateau servant de masque avec 'C' aux pixels à colorier
 * \param c la couleur avec laquelle colorier
 */
int FIb_colorcomp(FIboard* board, FIboard* comp, int c)
{
  int count = 0;
  assert(board->size == comp->size);
  int i, j;
  for (i=0; i<board->size; i=i+1)
  {
    for (j=0; j<board->size; j=j+1) 
    {
      if (-1 == comp->colors[i][j])
      {
        FIb_color(board, i, j, c);
        count++;
      }
    }
  }
  return count;
}

/**
 * \fn FIb_color (FIboard* board, int i, int j, char color)
 * \brief Colorie le pixel en la couleur passée en paramètre
 * 
 * \param board un pointeur vers le plateau à colorier
 * \param i la colonne du pixel à colorier
 * \param j la ligne du pixel à colorier
 * \param color la couleur avec laquelle colorier
 * \return rien
 */
 
void FIb_color (FIboard* board , int i, int j, int color) {
  if(i >= 0 && j >= 0 && i<board->size && j<board->size)
  {
    board->colors[i][j]=color;
  }
}

/**
 * \fn FIb_win (FIboard board)
 * \brief Vérifie la présence d'une même couleur sur toute la grille
 * 
 * \param board La grille sur laquelle on travaille
 * \return int 1 si la grille est d'une même couleur, 0 sinon
 */
 int FIb_win (FIboard board) 
 {
   int i,j;
   int c = board.colors[0][0];
   for (i=0; i<board.size; i=i+1) {
       for (j=0; j<board.size; j=j+1) {
           if (board.colors[i][j]!=c) { return 0;}
       }
   }
   return 1;
 }

/**
 * \fn pix_new(int i, int j, char color)
 * \brief Allocation de la mmoire pour un pixel
 * 

 * \param i la colonne du pixel à colorier
 * \param j la ligne du pixel à colorier
 * \param color la couleur avec laquelle colorier
 * \return p Un pointeur vers le pixel dont la mémoire a été allouée
 */

pixel* pix_new(int i, int j, int color)
{
	pixel* p = malloc(sizeof(pixel));
	p->i = i;
	p->j = j;
	p->color = color;
	return p;
}
