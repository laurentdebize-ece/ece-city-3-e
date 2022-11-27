#include "Graphe.h"
#include <stdio.h>
#include <stdlib.h>

pSommet *Graph_CreateArc(pSommet *sommet, int s1, int s2) {

    pArc Newarc = (pArc) malloc(sizeof(struct Arc));
    Newarc->arc_suivant = NULL;
    Newarc->sommet1 = s1 + 1;
    Newarc->sommet2 = s2 + 1;

    if (sommet[s1]->arc == NULL) {
        sommet[s1]->arc = Newarc;
        return sommet;
    }
    else {
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant)
            temp = temp->arc_suivant;

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

void Graph_PrintSucesseurs(pSommet *sommet, int num) {
    printf(" sommet1 %d :\n", num);

    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("%d ", arc->sommet1);
        arc = arc->arc_suivant;
    }
}

void Graph_Print(Graphe *graphe) {
    printf("Graphe\n");


    printf("Ordre = %d\n", graphe->ordre);

    printf("Listes D'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        Graph_PrintSucesseurs(graphe->pSommet, i);
        printf("\n");
    }
}


// creer le graphe
void Graphe_AllocGraphe(ECECITY* ececity) {

    ececity->graphe = (Graphe *) malloc(sizeof(Graphe));
    ececity->graphe->pSommet = (pSommet *) malloc(sizeof(struct Sommet));

    ececity->graphe->ordre = 0;
    ececity->graphe->taille = 0;
}


void Graphe_ReallocGraphe(ECECITY* ececity,int typeBatiment) {

    ececity->graphe->pSommet = (pSommet*) realloc(ececity->graphe->pSommet, (ececity->graphe->ordre) * sizeof(pSommet));

    ececity->graphe->pSommet[ececity->graphe->ordre - 1] = (pSommet) malloc(sizeof(struct Sommet));
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->id = ececity->graphe->ordre;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->ligneTab = ececity->souris.ligneSouris;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->colonneTab = ececity->souris.colonneSouris;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->couleur = UNEXPLORED;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->numCC = ececity->graphe->ordre - 1;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->type = ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->numType = ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->arc = NULL;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->type = typeBatiment;
    ececity->graphe->pSommet[ececity->graphe->ordre - 1]->nbArcs = 0;

}



void buildGraphe(ECECITY* ececity,int typeBatiment) {

    if(ececity->graphe != NULL){
        if(ececity->graphe->ordre > 0) {
            Graphe_ReallocGraphe(ececity,typeBatiment);
        }
        for (int sommet1 = 0; sommet1 < ececity->graphe->ordre; ++sommet1) {
            for (int sommet2 = 0; sommet2 < ececity->graphe->ordre; ++sommet2) {
                if(sommet1 != sommet2){
                    if(proximiteSommet(ececity,ececity->graphe->pSommet[sommet1], ececity->graphe->pSommet[sommet2]) == true
                       && arcExiste(ececity->graphe->pSommet[sommet1], ececity->graphe->pSommet[sommet2]) == false
                       && arcExiste(ececity->graphe->pSommet[sommet2], ececity->graphe->pSommet[sommet1]) == false){
                        ececity->graphe->pSommet = Graph_CreateArc(ececity->graphe->pSommet, ececity->graphe->pSommet[sommet1]->id - 1, ececity->graphe->pSommet[sommet2]->id - 1);
                        ececity->graphe->pSommet = Graph_CreateArc(ececity->graphe->pSommet, ececity->graphe->pSommet[sommet2]->id - 1, ececity->graphe->pSommet[sommet1]->id - 1);
                        ececity->graphe->taille++;
                        ececity->graphe->pSommet[sommet1]->nbArcs++;
                        ececity->graphe->pSommet[sommet2]->nbArcs++;
                    }
                }
            }
        }
    }


}

//arcExiste(ececity->graphe->pSommet[i], ececity->graphe->pSommet[sommet]
bool arcExiste(pSommet sommet1, pSommet sommet2) {
    pArc arc = sommet1->arc;

    while (arc != NULL) {
        if(arc->sommet2 == sommet2->id){
            return true;
        }
        arc = arc->arc_suivant;
    }

    return false;
}

bool proximiteSommet(ECECITY* ececity,pSommet sommet1, pSommet sommet2) {
    if(sommet1->type == ROUTE && sommet2->type == ROUTE){
        if (sommet1->ligneTab == sommet2->ligneTab) {
            if (sommet1->colonneTab == sommet2->colonneTab + 1 || sommet1->colonneTab == sommet2->colonneTab - 1) {
                return true;
            }
        }
        else if (sommet1->colonneTab == sommet2->colonneTab) {
            if (sommet1->ligneTab == sommet2->ligneTab + 1 || sommet1->ligneTab == sommet2->ligneTab - 1) {
                return true;
            }
        }
    }
    else if((sommet1->type == ROUTE || sommet2->type == ROUTE ) && sommet1->type != sommet2->type){
        if(sommet1->type == ROUTE){
            switch (sommet2->type){
                case TerrainVague:
                    if((sommet1->ligneTab >= sommet2->ligneTab - 1 && sommet1->ligneTab <= sommet2->ligneTab + ececity->formatBatiment.nblignesMaison)
                       && (sommet1->colonneTab <= sommet2->colonneTab - 1 && sommet1->colonneTab >= sommet2->colonneTab + ececity->formatBatiment.nbcolonnesMaison)
                       && !(sommet1->colonneTab == sommet2->colonneTab - 1 && sommet1->ligneTab == sommet2->ligneTab - 1)
                       && !(sommet1->colonneTab == sommet2->colonneTab - 1 && sommet1->ligneTab == sommet2->ligneTab + ececity->formatBatiment.nblignesMaison)
                       && !(sommet1->colonneTab == sommet2->colonneTab + ececity->formatBatiment.nbcolonnesMaison && sommet1->ligneTab == sommet2->ligneTab - 1)
                       && !(sommet1->colonneTab == sommet2->colonneTab + ececity->formatBatiment.nbcolonnesMaison && sommet1->ligneTab == sommet2->ligneTab + ececity->formatBatiment.nblignesMaison)
                       ){
                        return true;
                    }
                    break;
                case CHATEAUDEAU:
                    if((sommet1->ligneTab >= sommet2->ligneTab - 1 && sommet1->ligneTab <= sommet2->ligneTab + ececity->formatBatiment.nblignesChateaux)
                       && (sommet1->colonneTab <= sommet2->colonneTab - 1 && sommet1->colonneTab >= sommet2->colonneTab + ececity->formatBatiment.nbcolonnesChateaux)
                      && !(sommet1->colonneTab == sommet2->colonneTab - 1 && sommet1->ligneTab == sommet2->ligneTab - 1)
                      && !(sommet1->colonneTab == sommet2->colonneTab - 1 && sommet1->ligneTab == sommet2->ligneTab + ececity->formatBatiment.nblignesChateaux)
                      && !(sommet1->colonneTab == sommet2->colonneTab + ececity->formatBatiment.nbcolonnesChateaux && sommet1->ligneTab == sommet2->ligneTab - 1)
                      && !(sommet1->colonneTab == sommet2->colonneTab + ececity->formatBatiment.nbcolonnesChateaux && sommet1->ligneTab == sommet2->ligneTab + ececity->formatBatiment.nblignesChateaux)
                       ){
                        return true;
                    }
                    break;
                case CENTRALE:
                    if((sommet1->ligneTab >= sommet2->ligneTab - 1 && sommet1->ligneTab <= sommet2->ligneTab + ececity->formatBatiment.nblignesCentrales)
                       && (sommet1->colonneTab <= sommet2->colonneTab - 1 && sommet1->colonneTab >= sommet2->colonneTab + ececity->formatBatiment.nbcolonnesCentrales)
                      && !(sommet1->colonneTab == sommet2->colonneTab - 1 && sommet1->ligneTab == sommet2->ligneTab - 1)
                      && !(sommet1->colonneTab == sommet2->colonneTab - 1 && sommet1->ligneTab == sommet2->ligneTab + ececity->formatBatiment.nblignesCentrales)
                      && !(sommet1->colonneTab == sommet2->colonneTab + ececity->formatBatiment.nbcolonnesCentrales && sommet1->ligneTab == sommet2->ligneTab - 1)
                      && !(sommet1->colonneTab == sommet2->colonneTab + ececity->formatBatiment.nbcolonnesCentrales && sommet1->ligneTab == sommet2->ligneTab + ececity->formatBatiment.nblignesCentrales)
                       ){
                        return true;
                    }
                    break;
                default:
                    break;
            }
        }
        else if(sommet2->type == ROUTE){
            switch (sommet1->type){
                case TerrainVague:
                    if((sommet2->ligneTab >= sommet1->ligneTab - 1 && sommet2->ligneTab <= sommet1->ligneTab + ececity->formatBatiment.nblignesMaison)
                    && (sommet2->colonneTab >= sommet1->colonneTab - 1 && sommet2->colonneTab <= sommet1->colonneTab + ececity->formatBatiment.nbcolonnesMaison)
                   && !(sommet2->colonneTab == sommet1->colonneTab - 1 && sommet2->ligneTab == sommet1->ligneTab - 1)
                   && !(sommet2->colonneTab == sommet1->colonneTab - 1 && sommet2->ligneTab == sommet1->ligneTab + ececity->formatBatiment.nblignesMaison)
                   && !(sommet2->colonneTab == sommet1->colonneTab + ececity->formatBatiment.nbcolonnesMaison && sommet2->ligneTab == sommet1->ligneTab - 1)
                   && !(sommet2->colonneTab == sommet1->colonneTab + ececity->formatBatiment.nbcolonnesMaison && sommet2->ligneTab == sommet1->ligneTab + ececity->formatBatiment.nblignesMaison)
                    ){
                        return true;
                    }
                    break;
                case CHATEAUDEAU:
                    if((sommet2->ligneTab >= sommet1->ligneTab - 1 && sommet2->ligneTab <= sommet1->ligneTab + ececity->formatBatiment.nblignesChateaux)
                       && (sommet2->colonneTab >= sommet1->colonneTab - 1 && sommet2->colonneTab <= sommet1->colonneTab + ececity->formatBatiment.nbcolonnesChateaux)
                      && !(sommet2->colonneTab == sommet1->colonneTab - 1 && sommet2->ligneTab == sommet1->ligneTab - 1)
                      && !(sommet2->colonneTab == sommet1->colonneTab - 1 && sommet2->ligneTab == sommet1->ligneTab + ececity->formatBatiment.nblignesChateaux)
                      && !(sommet2->colonneTab == sommet1->colonneTab + ececity->formatBatiment.nbcolonnesChateaux && sommet2->ligneTab == sommet1->ligneTab - 1)
                      && !(sommet2->colonneTab == sommet1->colonneTab + ececity->formatBatiment.nbcolonnesChateaux && sommet2->ligneTab == sommet1->ligneTab + ececity->formatBatiment.nblignesChateaux)
                       ){
                        return true;
                    }
                    break;
                case CENTRALE:
                    if((sommet2->ligneTab >= sommet1->ligneTab - 1 && sommet2->ligneTab <= sommet1->ligneTab + ececity->formatBatiment.nblignesCentrales)
                       && (sommet2->colonneTab >= sommet1->colonneTab - 1 && sommet2->colonneTab <= sommet1->colonneTab + ececity->formatBatiment.nbcolonnesCentrales)
                      && !(sommet2->colonneTab == sommet1->colonneTab - 1 && sommet2->ligneTab == sommet1->ligneTab - 1)
                      && !(sommet2->colonneTab == sommet1->colonneTab - 1 && sommet2->ligneTab == sommet1->ligneTab + ececity->formatBatiment.nblignesCentrales)
                      && !(sommet2->colonneTab == sommet1->colonneTab + ececity->formatBatiment.nbcolonnesCentrales && sommet2->ligneTab == sommet1->ligneTab - 1)
                      && !(sommet2->colonneTab == sommet1->colonneTab + ececity->formatBatiment.nbcolonnesCentrales && sommet2->ligneTab == sommet1->ligneTab + ececity->formatBatiment.nblignesCentrales)
                       ){
                        return true;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return false;
}



void Graphe_PrintPathsRecursive(Graphe *graphe, pSommet sommetActuel) {
    if (sommetActuel->predecesseur == NULL) {
        printf("%d", sommetActuel->id);
        return;
    } else {
        printf("%d <-- ", sommetActuel->id);
        Graphe_PrintPathsRecursive(graphe, sommetActuel->predecesseur);
    }
}

void Graphe_PrintPaths(Graphe *graphe, int sommetActuel) {
    for (int i = 0; i < graphe->ordre; ++i) {
        if (i == sommetActuel)
            continue;

        if (!graphe->pSommet[i]->predecesseur)
            continue;

        Graphe_PrintPathsRecursive(graphe, graphe->pSommet[i]);
        printf("\n\r");
    }
}


void Graphe_DisplayArcs(Graphe* graphe) {
    if(graphe != NULL && graphe->taille){
        for (int i = 0; i < graphe->ordre; ++i) {
            pArc arc = graphe->pSommet[i]->arc;
            printf("%d",arc->sommet1);
            while (arc != NULL) {
                printf(" --->%d",arc->sommet2);
                arc = arc->arc_suivant;
            }
            printf("\n");
        }
    }
}

void Graphe_DisplaySommet(Graphe* graphe) {
    if(graphe != NULL){
        for (int i = 0; i < graphe->ordre; ++i) {
            printf(" sommet %d: type: %d case[%d][%d]\n",graphe->pSommet[i]->id, graphe->pSommet[i]->type,graphe->pSommet[i]->colonneTab,graphe->pSommet[i]->ligneTab);
        }
    }
}
