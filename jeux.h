#include<iostream>
#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include "console.h"
#include <time.h>

using namespace std;

class jeux: public console{
   private:
     int **plateau;
     int ***player1,***player2;
   private:
    int get_top(int x);//retour le haut du colonne datif, s'il est vide, retour 0.
    void possible(int color);//calculer des pions de tous les colonne et l'ecrire dans le player[]
    int get_one_possible(int x,int y,int color);//calculer des pion datif
    int get_degree(int a, int b,int i,int j);//estimer des risques
    int get_pion(int color,int & max );//retour le numero de colonne qui est le plus possible pour gagner  ~(1..7)

    public:
    jeux();
	~jeux(); 
    bool is_full(int x);//verifier si le colonne datif est plein, si oui, retour TRUE.
    void print();//renouveler l'ecran 
    bool ajouter_pion(int x,int color);//ajouter un pion dans le colonne datif, s'il est plein retour FALSE, d'autre retour TRUE 
    int status();//juger la fin du jeu£¬si le jaune a gagne, retour 1, si le rouge a gagne, retour 2, si le match est nul, retour 3, si le match est en progres, retour 0 
	void auto_play(int color);//jouer par AI
	void result(int sta);//imprimer le resultat de match.
	void menu();//imprimer le resultat de match.
	void randon_play(int m);//jouer par harsard,m represent de numero d'etape.
	int choix_color();//demander l'utilisateur pour choisir un couleur
	int choix_ordre();//demander l'utilisateur pour choisir jouer avant ou apres
    
};
