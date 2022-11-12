#ifndef PROJETINFO_ECECITY_H
#define PROJETINFO_ECECITY_H

#include "raylib.h"

#define TIMENOW (ececity->time.timer.hoursCounter*3600 + ececity->time.timer.minutesCounter*60 + ececity->time.timer.secondsCounter)
#define MAP_TILE_SIZE 20
#define NB_COLONNES 45
#define NB_LIGNES 35
#define SIZEBOARDX 1024
#define SIZEBOARDY 768
#define MAX_OBJET 300




#define MouseOnBoard (GetMousePosition().x > (float)(1920-SIZEBOARDX)/2  && GetMousePosition().x < (float)(NB_COLONNES)*MAP_TILE_SIZE+(float)(1920-SIZEBOARDX)/2 && GetMousePosition().y > (float)(1065-SIZEBOARDY)/2 && GetMousePosition().y < (float)(NB_LIGNES)*MAP_TILE_SIZE+(float)(1065-SIZEBOARDY)/2)? 1 : 0

typedef enum {
    MENU,
    Jeu,
    END,
    NB_PROCESS,
} GameProcess;

typedef enum {
    NADA,
    START,
    QUIT,
    CHARGER,
    CREDITS,
} MenuProcess;

typedef enum {
    NONE,
    CONSTRUCTIONROUTE,
    CONSTRUCTIONMAISON,
    CONSTRUCTIONCHATEAUDEAU,
    CONSTRUCTIONCENTRALE,
    GAMEPAUSE,
    GAMEOVER,
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
}typeCase;

typedef enum {
    IMAGEACCUEIL,
    IMAGEJEU,
    IMAGEROUTE,
    NB_IMAGES,
}NomImage;

typedef enum {
    MusiqueAccueil,
    ClicSouris,
    NB_MUSIQUE
}NomMusique;

typedef enum{
    BOUTON_STARTGAME,
    BOUTON_EXITGAMEAccueil,
    BOUTON_CHARGER,
    BOUTON_Credits,
    NB_BOUTON_MENU,
}NomBoutonMenu;

typedef enum{
    BOUTON_ROUTE,
    BOUTON_MAISON,
    BOUTON_CHATEAUDEAU,
    BOUTON_CENTRALE,
    PAUSE,
    EXITGAME,
    NB_BOUTON_JEU,
}NomBoutonJeu;

typedef enum{
    REJOUER,
    SAUVEGARDE,
    QUITTER,
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
        "PAUSE\0",
        "EXIT\0",
};

static const char *boutonFinText[] = {
        "REJOUER\0",
        "SAUVEGARDER\0",
        "QUITTER\0",
};




typedef struct{
    Rectangle positionCase;
    int type;// 0-vide 1-terrain vague/ruine 3-cabane 4- maison 5- immeuble 6- Gratte ciel 7- chateau d'eau 8- centrale electrique
    bool libre;
    bool proximiteRoute;
    int numeroConnexeEau;
    int numeroConnexeElec;
    int numeroType;
    int centraleAssignee;
    int chateauAssignee;
    int capaciteInitiale;
    int capaciteRestante;//capacité restante centrale/chateau
    int capaciteHabEnCours;// capacité de remplissage d'une habitation
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
    int compteurCabanes;
    int compteurMaisons;
    int compteurImmeubles;
    int compteurGratteCiel;
    int compteurChateaux;
    int compteurCentrales;
}Compteur;

typedef struct{
    int prixTerrainVague;
    int prixRoute;
    int Impots;
    int centralePrix;
    int chateauPrix;
}Prix;

typedef struct{
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
    Color fontColor;
}Write;

typedef struct {
    bool IsCodeRunning;
    bool IsGameBreak;
    int currentProcess;
    int currentMenuProcess;
    int currentJeuProcess;
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
void Charger(ECECITY* ececity);
void Gameplay(ECECITY* ececity);
int calculRoute( ECECITY *ececity, int typeCalcul, Case  tabCentraleElec[MAX_OBJET], Case tabChateauDeau[MAX_OBJET]);
void ajouteCelluleRoute(Case matrice[NB_COLONNES][NB_LIGNES], int colonne, int ligne, int numRoute, int typeCalcul,    Case  tabCentraleElec[MAX_OBJET], Case tabChateauDeau[MAX_OBJET]);
void rechercheHabitationRoute(int listeMaison[MAX_OBJET], int numRoute, Case matrice[NB_COLONNES][NB_LIGNES], int typeCalcul);
void calculDistributionElec(Case matrice[NB_COLONNES][NB_LIGNES], Case  tabCentraleElec[MAX_OBJET], Case tabHabitation[MAX_OBJET], int nbMaxRoute, Compteur c);
void pause(ECECITY* ececity);
void defineTypeCase(ECECITY* ececity);
void defineCurrentJeuProcess(ECECITY* ececity);
bool proximiteRoute(ECECITY* ececity, int typeBatiment);
bool construire(ECECITY* ececity);

#endif //PROJETINFO_ECECITY_H
