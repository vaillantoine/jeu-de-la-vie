#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> /* pour la fonction clock */


void affiche_aide (void) {
    /*Affiche la description du programme et ses entrées*/
    printf("Ce programme fait une simulation du jeu de la vie pour un tableau 2D de taille N*M et pour K itérations\n");
    printf("Ce programme prend 3 paramètres : int N, int M, int K\n");
    exit(1);
}

void recup_param (int argc, char **argv, int *N, int *M, int *K) {
    /*Récupère les paramètres d'entrée du main*/
    if (argc == 4) {
        *N = atoi(argv[1]);
        *M = atoi(argv[2]);
        *K = atoi(argv[3]);
    }
    else {
        affiche_aide(); //Si mauvais nombre de paramètres : affichage de l'aide dans le terminal
    }
}

int ** alloc (int N, int M) {
    /*Alloue la mémoire à un tableau de taille N*M*/
    int i;
    int **tab = NULL;

    tab = malloc(N*sizeof(int *));
    for (i=0; i<N; i++) {
        tab[i] = malloc(M*sizeof(int));
    }

    return tab;
}

void desalloc (int **tab, int N) {
    /*Libère la mémoire d'un tableau de taille N*_*/
    int i;
    for (i=0; i<N; i++) {
        free(tab[i]);
    }
    free(tab);
}

int ** init_tab (int N, int M) {
    /*Crée, alloue la mémoire et initialise les valeurs d'un tableau N*M*/
    int **tab = alloc(N, M);

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            tab[i][j] = rand() % 2; //Initialisation des valeurs (0 ou 1) de manière aléatoire
        }
    }

    return tab;
}

void affichage(int **tab, int N, int M) {
    /*Affiche de manière stylisée le contenu d'un tableau de booléens de taille N*M*/
    int i,j;

printf(" ");
    for (j=0; j<M; j++) {
        printf("-");
    }
    printf(" \n");
    for (i=0; i<N; i++) {
        printf("|");
        for (j=0; j<M; j++) {
            if (tab[i][j]) {
                printf("o");
            }
            else {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf(" ");
    for (j=0; j<M; j++) {
        printf("-");
    }
    printf("\n");
}

int sum_alentours (int alentours[3][3]) {
    /*Somme les valeurs d'un tableau 3*3*/
    int sum = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            sum += alentours[i][j];
        }
    }

    return sum;
}

int cell_next(int alentours[3][3]) {
    /*détermine la valeur de la cellule en fonction de ses voisines*/
    int nb_vivant = sum_alentours(alentours);
    if (alentours[1][1]) { //si la cellule est vivante

        return (nb_vivant == 3 || nb_vivant == 4);
    }
    else { //si la cellule est morte
        return (nb_vivant == 3);
    }
}

int ** calculsuivant(int **tab, int N, int M) {
    /*Détermine le tableau à l'itération suivante*/
    int **tab_next = alloc(N, M);
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {   //pour chaque case de tab
            int alentours[3][3];
            for (int k=0; k<3; k++) {
                for (int l=0; l<3; l++) {   //on extrait un tableau des cases voisines
                    if (i-1+k == -1 || i-1+k ==N || j-1+l == -1 || j-1+l == M) {
                        alentours[k][l] = 0;    //on met 0 si le vopisin n'existe pas
                    }
                    else {
                        alentours[k][l] = tab[i-1+k][j-1+l];
                    }
                }
            }
            tab_next[i][j] = cell_next (alentours);
        }
    }

    return tab_next;
}


int main(int argc, char **argv){
    int N;
    int M;
    int K;
    recup_param(argc, argv, &N, &M, &K);
    srand(clock());
    int **tab = init_tab(N, M);

    system("clear");
    affichage(tab, N, M);   //affichage de l'état initial

    for (int i=0; i<K; i++) {
        int **tab_next = calculsuivant(tab, N, M);
        desalloc(tab, N);
        tab = tab_next;
        usleep(100000);
        system("clear");
        affichage(tab, N, M);   //afichage de l'état actuel
    }

    desalloc(tab, N);    //on n'oublie pas de désallouer tab
    return 0;
}
