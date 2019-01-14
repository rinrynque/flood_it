```
██████╗ ███╗   ██╗██╗                ███████╗██╗      ██████╗  ██████╗ ██████╗     ██╗████████╗
██╔══██╗████╗  ██║██║         ██╗    ██╔════╝██║     ██╔═══██╗██╔═══██╗██╔══██╗    ██║╚══██╔══╝
██████╔╝██╔██╗ ██║██║         ╚═╝    █████╗  ██║     ██║   ██║██║   ██║██║  ██║    ██║   ██║   
██╔═══╝ ██║╚██╗██║██║         ██╗    ██╔══╝  ██║     ██║   ██║██║   ██║██║  ██║    ██║   ██║   
██║     ██║ ╚████║███████╗    ╚═╝    ██║     ███████╗╚██████╔╝╚██████╔╝██████╔╝    ██║   ██║   
╚═╝     ╚═╝  ╚═══╝╚══════╝           ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═════╝     ╚═╝   ╚═╝   
```
``INSTALLATION``
Pour compiler, se placer à la racine et faire ```make```

Les commandes disponibles sont :
```make FloodIt```
```make Tests```
```make doxygen```
ainsi que l'option ```clean```.

Il y a deux exécutables, situés dans ```./bin/```

L'exécutable ```Tests``` lance les tests unitaires, écrits dans ```Cunit/main.c```
L'exécutable ```FloodIt``` lance une démo d'utilisation des fonctions du lot, écrite dans ```src/main.c```

Le code source du projet (sans les tests unitaires) se trouve dans le dossier ```src/```

Pour générer la documentation avec doxygen, exécuter la commande ```doxygen``` à la racine (ou ```make doxygen```). 
La documentation se trouve alors dans le dossier ```Doxygen/```


``UTILISATION``
Au lancement de la boucle de jeu, tapez au clavier les entiers demandés : celui représentant la taille de la grille,
puis le nombre de coups maximum.

Il est également possible de spécifier ces parametres en ligne de commande, utilisez ```-?``` pour plus d'informations.
L'utilisation de ```-g``` permet d'activer l'interface graphique (utilisant ncurses);

Le choix de la couleur suivante se fait en tapant au clavier sur le charactère correspondant parmis ```BVGRMJ```.

Pour quitter la partie en cours, appuyer sur la touche ```q```.
Bon jeu ! 


``SOLVEUR``

Au début de la partie, le solveur vous donne une combinaison gagnante optimale,
et donc la longueur de coups minimale requise pour gagner. 

Libre à vous de défier l'algorithme !

``Attention :`` Une taille de grille supérieure à 5 demande beaucoup de mémoire/temps pour le solveur,
nous vous conseillons d'éviter d'excéder cette taille.