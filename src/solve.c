
/**
 * \file solve.c
 * \brief Implémentation des fonctions relatives au solveur
 */
 
 #include "solve.h"


/**
 * \fn FIs_solve(FIboard board, FIsolution solution, FIsolution* bestSol, int depth)
 * \brief Recherche d'un tableau séquence de caractère solution de la grille
 * 
 * \param board solution bestSol depth Une grille de jeu, la solution en cours, la meilleure solution stockée, la longueur de la solution courante
 */
 
void FIs_solve(FIboard g, FIsolution solution, FIsolution* bestSol, int depth) {
    if (solution.len > bestSol->len)
    {
        return;
    }
    
    int i, j;
    FIboard tmp;
    FIboard g2;
    
    for (j=1; j<=6; j++) 
    {
        i = (j+depth)%6 +1;
        FIsolution newSol = solution;
        
        newSol.seq[solution.len]=colorchar(i);
        newSol.len++;
        
        FIb_copy(&g,&g2);
        
        tmp = FIb_connectedcomp(&g2, 0, 0);
        FIb_colorcomp (&g2,&tmp,colorchar(i));
        FIb_destroy(&tmp);
        
        if (FIb_win(g2))
        {
            if (newSol.len<bestSol->len) 
            {
                *bestSol = newSol;
            }
            FIb_destroy(&g2);
            return;
            //printf("%s",newSol.seq);
            //FIb_display(&g2);
            //exit(0);
        }else 
        {
            //printf("longueur %i : %s \n",newSol.len,newSol.seq);
            FIs_solve(g2, newSol, bestSol, depth+1);
            FIb_destroy(&g2);
        }
    }
}
