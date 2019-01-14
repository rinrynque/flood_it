/**
 * \file comp.c
 * \brief Implémentation des fonctions relatives à la structure de comp, solveur optimisé
 */
 
 #include "comp.h"

/**
 * \fn FIc_solveOpti(FIcomp * g, FIsolution2 solution, FIsolution2* bestSol, int depth)
 * \brief Recherche d'un tableau séquence de caractère solution de la grille(optimisé à l'aide du graphe des composantes connexes de la grille)
 * \param g solution bestSol depth Le graphe des composantes connexes de la grille de jeu, la solution en cours, la meilleure solution stockée, la longueur de la solution courante
 */

void FIc_solveOpti(FIcomp* g, FIsolution2 solution, FIsolution2* bestSol, int depth) 
{
    if (0 != bestSol->seq[0] || solution.len > bestSol->len)
    {
        return;
    }
    
    int i,j;
    FIcomp* g2 = (FIcomp*) malloc(255*sizeof(FIcomp));
    int* colors = FIc_bestChoices(g);
    
    for (j=0; j<colors[0]; j++) 
    {
        //i = (j+depth)%6+1;
        i= colors[j+1];
        FIsolution2 newSol = solution;
        
        newSol.seq[solution.len]=i;
        newSol.len++;
        
        memcpy(g2, g, 255*sizeof(FIcomp));
        FIc_colorComps(g2, i);
        
        if (FIc_win(g2))
        {
            if (newSol.len<bestSol->len) 
            {
                printf("\nnouvelle sol :  ");
                FIs2_display(bestSol);
                printf(" -> ");
                FIs2_display(&newSol);
                *bestSol = newSol;
            }
            free(g2);
            free(colors);
            return;
        }else 
        {
            //printf("longueur %i : %s \n",newSol.len,newSol.seq);
            FIc_solveOpti(g2, newSol, bestSol, depth+1);
        }
    }
    free(g2);
    free(colors);
    
}


/**
 * \fn FIc_bestChoices(FIcomp * gboard)
 * \brief Recherche des meilleurs choix de couleur à faire sur la donnée du graphe des composantes connexes de la grille de jeu
 * \param gboard Le graphe des composantes connexes du graphe sur lequel on travaille
 */
int* FIc_bestChoices(FIcomp* gboard)
{
    intPair weighs[6] = {{0}};
    int i; /* On crée des couples d'entiers avec la couleur et son poids */
    for (i=0;i<6;i++)
    {
        weighs[i].a = i+1;
        weighs[i].b = 0;
    }
    
    for (i=0; i < gboard[0].nlinks; i++)
    {
        int linkedId = gboard[0].links[i] - 1; // Pour chaque composante connectée à la première
        weighs[gboard[linkedId].color-1].b += gboard[linkedId].weight;
    }

    qsort(weighs, 6, sizeof(intPair), cmp_func);

    int* choices = (int*) calloc(7,sizeof(int));
    
    for (i=0;i<6;i++)
    {
        choices[i+1] = weighs[i].a;
        if(weighs[i].b == 0)
        {
            choices[0] = i;
            break;
        }
    }
    
    return choices;
}


/**
 * \fn FIc_colorComps(FIcomp* gboard, int c)
 * \brief Mise à jour des liens des composantes connexes du tableau passé en paramètre, et de la couleur de celles-ci, enfonction de la couleur passée en paramètre
 * \param gboard c tableau de composantes connexes et couleur de colorisation c
 */
void FIc_colorComps(FIcomp* gboard, int c)
{
    FIcomp* oldgboard = (FIcomp*) malloc(255*sizeof(FIcomp));
    memcpy(oldgboard, gboard, 255*sizeof(FIcomp));
    int i;
    
    gboard[0].color = c;
    
    for (i=0; i < oldgboard[0].nlinks; i++)
    {
        int linkedId = oldgboard[0].links[i]-1; // Pour chaque composante connectée à la première
        
        if(oldgboard[linkedId].color==c)
        {
            gboard[linkedId].id = -1; /* On 'détruit' la composante qui était reliée à la première et de la même couleur*/
            int j;
            for (j=0; j<oldgboard[linkedId].nlinks; j++) //On va rajouter tous les liens de la composante connectée
            {
                FIc_addLink(&(gboard[0]), oldgboard[linkedId].links[j]);
            }
        }
    }
    i=0;
    while(gboard[i].id != 0)
    {
        if(-1==gboard[i].id)
        {
            FIc_remLink(&(gboard[0]), i+1); /* On enlève le lien */
        }
        i++;
    }
    
    free(oldgboard);
}


/**
 * \fn FIc_win(FIcomp * gboard)
 * \brief Vérification si le tableau de composante connexes passé en paramètre amène à une victoire
 * \param gboard Le tableau des composantes connexes de la grille de jeu
 */
int FIc_win(FIcomp* gboard)
{
    int i;
    int c = gboard[0].color;
    for(i=1; i<255; i++)
    {
        if(gboard[i].id == 0)
        {
            return 1;
        }
        if(gboard[i].id != -1 && gboard[i].color != c)
        {
            return 0;
        }
    }
    return 1;
}

/*
FLAP FLAP L'HELICOBIDE ARRIVE POUR RESOUDRE LE FLOODIT

---------------+---------------
          ___ /^^[___              _
         /|^+----+   |#___________//
       ( -+ |____|   _______-----+/
        ==_________--'            \
          ~_|___|__ -wh 
          
*/

/**
 * \fn FIc_compBoard(FIcomp * board)
 * \brief  Construction du tableau/graphe des composantes connexes du board passé en paramètre (détermination des couleurs, liens, poids et id de chaque comp)
 * \param board Pointeur vers le board de jeu
 */
FIcomp* FIc_compBoard(FIboard* board) {
    int n = board->size;
    FIboard comp;
    
    comp.size = board->size;
    
    FIb_alloc(&comp);
    
    int i,j;
    int maxid = 0; 

    FIcomp* comps = (FIcomp*) calloc (255,sizeof(FIcomp));
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(comp.colors[i][j] == 0)
            {
                maxid++;
                
                /* On colorie dans notre comps */
                FIboard temp;
                
                temp = FIb_connectedcomp(board, i, j);
                comps[maxid-1].weight = FIb_colorcomp(&comp, &temp, maxid);
                FIb_destroy(&temp);
			    
                comps[maxid-1].id = maxid;
                comps[maxid-1].color = board->colors[i][j];
            }
        }
    }
    
    
    FIc_linksComp(&comp, comps);
    FIb_destroy(&comp);
   /** Les lignes qui suivent permettent d'afficher en liste toutes
    * les composantes connexes du plateau
    **/
    /*
    printf("\nCote : %d\n==\n", board->size);
    for (i=0; i<comp.size; i=i+1)
    {
        printf("|");
        for (j=0; j<comp.size; j=j+1) 
        {
          printf("%3i|", comp.colors[i][j]);
        }
        printf("\n");
    }
    printf("==\n");
    printf("On a trouvé %i composantes\n", maxid);
    i=0;
    while(comps[i].id != 0)
    {
        FIc_dispComp(comps[i]);
        i++;
    }*/
    return comps;
}


/**
 * \fn FIc_linksComp(FIboard* board, FIcomp* comps)
 * \brief Recherche des liens existant entre les composantes passées en paramètre sur la donnée du board de jeu
 * \param board comps Le board de jeu et la liste de composantes connexes associées (liens non encore renseignés)
 */
void FIc_linksComp(FIboard* board, FIcomp* comps)
{
    int i,j;
    for (i=0; i < board->size; i++)
    {
        for (j=0; j < board->size; j++)
        {
            int colorij = board->colors[i][j];
            if (i < board->size-1 && colorij != board->colors[i+1][j]) /* On regarde si on est dans une composante différente en dessous de la case */
            {
                int coloripj = board->colors[i+1][j];
                FIc_addLink(&(comps[colorij-1]), coloripj); /* On relie les 2 composantes dans le graphe */
                FIc_addLink(&(comps[coloripj-1]), colorij);
            }
            if (j < board->size-1 && board->colors[i][j] != board->colors[i][j+1])
            {
                int colorijp = board->colors[i][j+1];
                FIc_addLink(&(comps[colorij-1]), colorijp); /* On relie les 2 composantes dans le graphe */
                FIc_addLink(&(comps[colorijp-1]), colorij);
            }
        }
    }
}


/**
 * \fn FIc_dispComp(FIcomp comp)
 * \brief Fonction d'affichage d'une composante connexe (id, poids, couleur et liens)
 * \param comp la composante à afficher
 */
void FIc_dispComp(FIcomp comp)
{
    printf("--\n[%i](%i, %c)\n(%i)->", comp.id, comp.weight, colorchar(comp.color), comp.nlinks);
    int i = 0;
    for(i=0; i < comp.nlinks;i++)
    {
        printf("%i,", comp.links[i]);
    }
    printf("\n");
}


/**
 * \fn FIc_isLinked(FIcomp* comp, int id)
 * \brief Vérification si la composante passée en paramètre est liée à la composante dont l'id est passé en paramètre
 * \param comp id La composante 1 et l'id de la composante 2 pour lesquelles on veut vérifier l'existence d'un lien
 */
 int FIc_isLinked(FIcomp* comp, int id)
{
    int i;
    for(i=0; i<comp->nlinks;i++)
    {
        if(comp->links[i] == id)
        {
            return 1;   
        }
    }
    return 0;
}


/**
 * \fn FIc_clearLinks(FIcomp* comp)
 * \brief Efface le nb liens de la composante 
 * \param comp pointeur vers la composante
 */
void FIc_clearLinks(FIcomp* comp)
{
    comp->nlinks = 0;
}


/**
 * \fn FIc_remLink(FIcomp * comp, int id)
 * \brief Suppression du lien id dans la composante comp
 * \param comp id Un pointeur vers la composante et id l'id de la composante pour laquelle on veut supprimer le lien
 */
void FIc_remLink(FIcomp* comp, int id)
{
    int i;
    int offset = 0;
    int links[100] = {0};
    int n= comp->nlinks;
    
    for(i=0; i<comp->nlinks;i++)
    {
        while(comp->links[offset] == id)
        {
            offset++;
            n--;
        }
        links[i] = comp->links[offset];
        offset++;
    }
    memcpy(&(comp->links), &links, 100*sizeof(int));
    comp->nlinks = n;
}


/**
 * \fn FIc_addLink(FIcomp * comp, int i)
 * \brief Ajout du lien à comp, avec la composante d'id id
 * \param comp id La composante pour laquelle on veut ajouter le lien avec une autre composante d'id id
 */
void FIc_addLink(FIcomp* comp, int id)
{
    if (id == comp->id || FIc_isLinked(comp, id))
    {
        return;
    }
    comp->links[comp->nlinks]=id;
    comp->nlinks++;
}


/**
 * \fn FIs2_display(FIsolution2* solution)
 * \brief Affichage de la séquence solution solution
 * \param solution la séquence solution à afficher
 */
 void FIs2_display(FIsolution2* solution)
{
    int i;
    for (i=0; i<solution->len;i++)
    {
        printf("%c", colorchar(solution->seq[i]));
    }
    printf("\n");
}