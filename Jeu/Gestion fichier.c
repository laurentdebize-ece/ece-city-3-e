#include "../include/ECECity.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/gestion fichier.h"
// cree un fichier grille à 0
int initFichierGrille(char* nomFichier){
    FILE * ifs = fopen(nomFichier,"w");
    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    for (int j = 0; j < NBLIGNE; j++) {
        for (int i = 0; i < NBCOLONNE; i++) {
            fprintf(ifs,"|");
            fprintf(ifs, "%2d", i);
            fprintf(ifs, "%3d", j);
            fprintf(ifs, "%3d", 0);
            fprintf(ifs,"%3d", 0);
        }
        fprintf(ifs,"\n");
    }
    fclose(ifs);
}

//ecrit la matrice dans un fichier
int ecritureFichierGrille(char* nomFichier,ECECITY ececity){
    FILE * ifs = fopen(nomFichier,"w");
    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    for (int j = 0; j < NBLIGNE; j++) {
        for (int i = 0; i < NBCOLONNE; i++) {
            fprintf(ifs,"|");
            fprintf(ifs, "%2d", i);
            fprintf(ifs, "%3d", j);
            fprintf(ifs, "%3d", ececity.tabCase[i][j].type);
            fprintf(ifs,"%3d", ececity.tabCase[i][j].numeroType);

        }
        fprintf(ifs,"\n");
    }
    fclose(ifs);
}

//fct de lecture du fichier qui contient la grille
int lectureFichierGrille(char * nomFichier, ECECITY ececity)
{

    FILE * ifs = fopen(nomFichier,"r");//ouverture


    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int col, ligne, type, num;
    for (int h = 0; h < NBLIGNE; h++) {//lecture de chaque lignes et colonnes
        for (int t = 0; t < NBCOLONNE; t++) {
            fscanf(ifs,"|%2d%3d%3d%3d",&col, &ligne,&type, &num);
            ececity.tabCase[col][ligne].type = type;
            ececity.tabCase[col][ligne].numeroType = num;

        }
        fscanf(ifs,"\n");
    }
    fclose(ifs);//fermeture
    return 0;
}

