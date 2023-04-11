#include <stdio.h>
#include <stdlib.h>


void affiche_aide (void) {
    printf("Ce programme fait une simulation du jeu de la vie pour un tableau 2D de taille N*M et pour K itérations\n");
    printf("Ce programme prend 3 paramètres : int N, int M, int K\n");
}

void recup_param (int argc, char **argv, int *N, int *M, int *K) {
    if (argc == 4) {
        *N = atoi(argv[1]);
        *M = atoi(argv[2]);
        *K = atoi(argv[3]);
    }
    else {
        affiche_aide();
    }
}

int ** alloc (int N, int M) {
    int i;
    int **tab = NULL;

    tab = malloc(N*sizeof(int *));
    for (i=0; i<N; i++) {
        tab[i] = malloc(M*sizeof(int));
    }

    return tab;
}

void desalloc (int **tab, int N) {
    int i;
    for (i=0; i<N; i++) {
        free(tab[i]);
    }
    free(tab);
}

int ** init_tab (int N, int M) {
    int **tab = alloc(N, M);

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            tab[i][j] = rand() % 2;
        }
    }

    return tab;
}

void affichage(int **tab, int N, int M) {
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
    printf(" \n");
}


int main(int argc, char **argv){
    int N;
    int M;
    int K;
    recup_param(argc, argv, &N, &M, &K);
    int **tab = init_tab(N, M);

    affichage(tab, N, M);

    desalloc(tab, N);
    return 0;
}
