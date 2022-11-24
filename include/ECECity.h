#ifndef ECE_CITY_3_E_H_INCLUDED
#define ECE_CITY_3_E_H_INCLUDED

#include "raylib.h"

#define MouseOnIso (GetMousePosition().y >= ((ececity->infoIso.coeffDirecteur * GetMousePosition().x) + ececity->infoIso.ligne) && GetMousePosition().y >= - (ececity->infoIso.coeffDirecteur * GetMousePosition().x) + ececity->infoIso.colonnemax && GetMousePosition().y <= - (ececity->infoIso.coeffDirecteur * GetMousePosition().x) + ececity->infoIso.colonne && GetMousePosition().y <= (ececity->infoIso.coeffDirecteur * GetMousePosition().x) + ececity->infoIso.lignemax) ? 1 : 0


#define TIMENOW (ececity->time.timer.hoursCounter*3600 + ececity->time.timer.minutesCounter*60 + ececity->time.timer.secondsCounter)
#define MAP_TILE_SIZE 20
#define NB_COLONNES 45
#define NB_LIGNES 35
#define SIZEBOARDX 900
#define SIZEBOARDY 700
#define MAX_OBJET 300
#define CAPACENTRALE 5000
#define CAPAEAU 5000
#define SOLDEBANQUE 500000
#define PRIXIMPOT 10

typedef enum{
    COMMUNISTE,
    CAPITALISTE,
    NB_TYPE,
}ModeJeu;

typedef enum{
    NIVEAU0,
    NIVEAU1,
    NIVEAU2,
}NiveauJeu;

typedef enum {
    MENU,
    ChoixMode,
    Jeu,
    END,
    NB_PROCESS,
} GameProcess;

typedef enum {
    CREDITS,
    CHARGER,
    NIVEAU0,
    NIVEAU1,
    NIVEAU2,
    CONSTRUCTIONROUTE,
    CONSTRUCTIONMAISON,
    CONSTRUCTIONCHATEAUDEAU,
    CONSTRUCTIONCENTRALE,
    STARTGAME,
    GAMEPAUSE,
    GAMEOVER,
    SAUVEGARDE,
    NONE,
} JeuProcess;

typedef enum{
    VIDE,
    ROUTE,
    TerrainVague,
    CABANE,
    MAISON,
    IMMEUBLE,
    GRATTE_CIEL,
    CHATEAUDEAU,
    CENTRALE,
    RUINE,
}typeCase;

typedef enum{
    OUEST,
    EST,
    NORD,
    SUD,
    NB_CARDINAL,
}Cardinal;

typedef enum {
    IMAGEACCUEIL,
    IMAGEJEU,
    IMAGECLOCK,
    IMAGEARGENT,
    IMAGEPOPULATION,
    IMAGECHOIXJEU,
    IMAGEROUTE,
    IMAGECHATEAUEAU,
    IMAGECENTRALEELEC,
    NB_IMAGES,
}NomImage;

typedef enum {
    MusiqueAccueil,
    ClicSouris,
    NB_MUSIQUE
}NomMusique;

typedef enum{
    BOUTON_STARTGAME,
    BOUTON_EXIT_MENU,
    BOUTON_CHARGER,
    BOUTON_CREDITS,
    NB_BOUTON_MENU,
}NomBoutonMenu;

typedef enum {
    Bouton_Communiste,
    Bouton_Capitaliste,
    EXITChoix,
    NB_BOUTON_ChoixJeu,

}NomBoutonChoixModeJeu;

typedef enum{
    BOUTON_ROUTE,
    BOUTON_MAISON,
    BOUTON_CHATEAUDEAU,
    BOUTON_CENTRALE,
    BOUTON_PAUSE,
    BOUTON_EXIT_JEU,
    BOUTON_NIVEAU_0,
    BOUTON_NIVEAU_1,
    BOUTON_NIVEAU_2,
    NB_BOUTON_JEU,
}NomBoutonJeu;

typedef enum{
    BOUTON_REJOUER,
    BOUTON_SAUVEGARDE,
    BOUTON_EXIT_FIN,
    NB_BOUTON_FIN,
}NomBoutonFin;

static const char *boutonMenuText[] = {
        "START GAME\0",
        "EXIT GAME\0",
        "CHARGER\0",
        "CREDITS\0",
};

static const char *boutonJeuText[] = {
        "ROUTE\0",
        "TerrainVague\0",
        "CHATEAUDEAU\0",
        "CENTRALE\0",
        "BOUTON_PAUSE\0",
        "EXIT\0",
        "NIVEAU 0\0",
        "NIVEAU -1\0",
        "NIVEAU -2\0",
};

static const char *boutonChoixJeu[] = {
        "COMMUNISME\0",
        "CAPITALISME\0",
        "BACK TO MENU\0",
};

static const char *boutonFinText[] = {
        "REJOUER\0",
        "SAUVEGARDER\0",
        "QUITTER\0",
};


typedef struct{
   Vector2 debut;
   Vector2 fin;
   float coeffDirecteur;
   float ligne;
   float colonne;
   float lignemax;
   float colonnemax;
}Isometric;

typedef struct{
    Rectangle positionCase;
    Vector2 cardinal[NB_CARDINAL];
    int type;
    bool libre;
    bool proximiteRoute;
    int numeroConnexeEau;
    int numeroConnexeElec;
    int numeroType;
    int capaciteInitiale;
    int capaciteRestante;//capacité restante centrale/chateau
    int capaciteHabElecEnCours;// capacité de remplissage d'une habitation en elec
    int capaciteHabEauEnCours;// capacité de remplissage d'une habitation en eau
    int distance;
    int timerSeconds;
} Case;


enum SommetCouleur {
    UNEXPLORED,
    EXPLORING,
    EXPLORED
};

struct Arc
{
    int sommet1;
    int sommet2;
    struct Arc* arc_suivant;
};
typedef struct Arc* pArc;

struct Sommet
{
    struct Arc* arc;
    int id;
    int type;
    struct Sommet *predecesseur;
    struct Sommet *suivant;
    int numCC;
    int colonneTab;
    int ligneTab;
    enum SommetCouleur couleur;
};

typedef struct Sommet* pSommet;


typedef struct Graphe
{
    int taille;
    int ordre;
    pSommet* pSommet;
} Graphe;

typedef struct{
    int temporel;
    int nbHabitantsTotal;
    int CapaciteEau;
    int CapaciteCentrale;
    int soldeBanque;
    int nbRoutes;
    int compteurMaisons;
    int compteurChateaux;
    int compteurCentrales;
    int timerImpots;
}Compteur;

typedef struct {
    int typeJeu;//1- si communisme 2- si capitalisme
    int typeCalcul;// 1 eau, 2 elec.
}ElementSauvegarde;

typedef struct{
    int prixTerrainVague;
    int prixRoute;
    int prixImpots;
    int centralePrix;
    int chateauPrix;
}Prix;

typedef struct{
    int terrainVague;
    int Cabane;
    int Maison;
    int Immeuble;
    int Gratte_ciel;
}NB_habitants;

typedef struct {
    int nblignesRoute;
    int nblignesMaison;
    int nblignesCentrales;
    int nblignesChateaux;
    int nbcolonnesRoute;
    int nbcolonnesMaison;
    int nbcolonnesCentrales;
    int nbcolonnesChateaux;
}FormatBatiment;

typedef struct{
    int width;
    int height;
    int FPS;
    int flags;
}Display;

typedef struct{
    Image Image;
    Texture2D TextureImage;
    Rectangle format;
}Images;

typedef struct{
    Music music;
    float pan;
    float pitch;
    float volume;
}Musique;

typedef struct{
    int secondsCounter;
    int minutesCounter;
    int hoursCounter;
}Timer;

typedef struct{
    int framesCounter;
    int seconds;
    int timeDebut;
    int constructionTime;
    Timer timer;
}Time;

typedef struct{
    int ligneSouris;
    int colonneSouris;
    Vector2 position;
}Souris;

typedef struct{
    Rectangle recBouton;
    const char* nom;
}Bouton;

typedef struct{
    Font font;
    int fontSize;
    Vector2 positions;
    Color fontColor;
}Write;

typedef struct {
    bool IsCodeRunning;
    bool IsGameBreak;
    int currentProcess;
    int currentMenuProcess;
    int currentJeuProcess;
    int currentChoixJeuProcess;
    ElementSauvegarde jeu;
    Isometric infoIso;
    Graphe* graphe;
    Case tabCase[NB_COLONNES][NB_LIGNES];
    Case* tabHabitations;
    Case* tabChateauEau;
    Case* tabCentrale;
    Compteur compteur;
    Prix prix;
    NB_habitants nbHabitants;
    FormatBatiment formatBatiment;
    Images tabImage[NB_IMAGES];
    Musique tabMusic[NB_MUSIQUE];
    Bouton tabBouton[NB_PROCESS][NB_BOUTON_JEU];
    Display display;
    Time time;
    Souris souris;
    Write write;
}ECECITY;

void MainBoucle(ECECITY* ececity);
void Menu(ECECITY* ececity);
void ChoixModeJeu(ECECITY* ececity);
void Charger(ECECITY* ececity);
void JEU(ECECITY* ececity);
void Gameplay(ECECITY* ececity);
int calculRoute( ECECITY* ececity, int typeCalcul);
void ajouteCelluleRoute(ECECITY* ececity, int colonne, int ligne, int numRoute, int typeCalcul);
void rechercheHabitationRoute(int listeMaison[MAX_OBJET], int numRoute, Case matrice[NB_COLONNES][NB_LIGNES], int typeCalcul);
// void calculDistributionElec_old(Case matrice[NB_COLONNES][NB_LIGNES], Case  tabCentraleElec[MAX_OBJET], Case tabHabitation[MAX_OBJET], int nbMaxRoute, Compteur c);
int calculDistance(Case caseSource, Case caseCible, int numRoute, Case matrice[NB_COLONNES][NB_LIGNES] );
int sousCalcDistance(int colonne, int ligne, Case caseCible, int numRoute, int distanceEnCours, Case matrice[NB_COLONNES][NB_LIGNES]);
void calculDistributionEau(ECECITY* ececity, int nbMaxRoute, Compteur c);
void calculDistributionElec(ECECITY* ececity, int nbMaxRoute, Compteur c);
void calculCommunisme ( ECECITY* ececity, int maisonTraitee, Compteur c);
void calculCapitalisme (ECECITY* ececity, int maisonTraitee, Compteur c);
void evolutionConstruction( ECECITY* ececity, int maisonTraitee, Compteur c);
void pause(ECECITY* ececity);
void defineTypeCase(ECECITY* ececity);
void defineCurrentJeuProcess(ECECITY* ececity);
bool proximiteRoute(ECECITY* ececity, int typeBatiment);
bool construire(ECECITY* ececity);
void calculTimerHabitations(ECECITY* ececity);
void calculHabitant(ECECITY* ececity);
void CalculImpotChaqueMois(ECECITY* ececity);

#endif //ECE_CITY_3_E_H_INCLUDED
