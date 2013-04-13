#include <iostream>
#include <time.h>
#include "jeux.h"
int main()
{ 

int w=0,k,p=1;
    
    jeux screen;                                   //creer un objet pour controler le screen.
    screen.set_dimensions(37,27);
    screen.set_title("Puissance 4       beta v0.2");
    
while (p!=4){
    
    screen.menu();                                 //imprimer le menu du match
    cin>>p;
    system("cls");
    if(p==1){   
        
      jeux game;    //creer un objet pour jouer  
      int co,fo;
      co=screen.choix_color();   //demander la couleur de pion
      system("cls");
      fo=screen.choix_ordre();   //demander l'ordre du jeu              
      game.print();               //imprimer l'echiquie
      color col_play,col_auto;
      int colnum_play,colnum_auto;
      if (co==2) {col_play=red; col_auto = yellow;colnum_play = 2;colnum_auto = 1;}
      else {col_play=yellow; col_auto = red;colnum_play = 1;colnum_auto = 2;}                       
      while(game.status()==0)
     {  
        if(fo ==1){
        screen.set_pen_color(col_play);
        if (col_play == yellow)
        cout<<"Joueur jaune"<<endl<<"Choisisez la colonne(1~7):"; 
        else cout<<"Joueur rouge"<<endl<<"Choisisez la colonne(1~7):"; 
        cin>>k;
        while(((k<=0)||(k>7))||game.is_full(k)){   //verifier si le colonne est plein ou le numero est surpasse hors de port¨¦
          cout<<"Error, retapez(1~7):"; 
          cin>>k; }  //while        
        game.ajouter_pion(k,colnum_play);                    //jouer aux echecs dans le colonne k.
        game.print();                              //renouveler l'ecran
        if(game.status()==0){                      //verifier si le joueur a gagne ou pas.
          game.auto_play(colnum_auto);                       // 
          game.print();
         }//if
         }
         else{
          game.auto_play(colnum_auto);                       // 
          game.print(); 
          if(game.status()==0){  
               screen.set_pen_color(col_play);
        if (col_play == yellow)
        cout<<"Joueur jaune"<<endl<<"Choisisez la colonne(1~7):"; 
        else cout<<"Joueur rouge"<<endl<<"Choisisez la colonne(1~7):"; 
        cin>>k;
        while(((k<=0)||(k>7))||game.is_full(k)){   //verifier si le colonne est plein ou le numero est surpasse hors de port¨¦
          cout<<"Error, retapez!(1~7):"; 
          cin>>k; }  //while        
        game.ajouter_pion(k,colnum_play);                    //jouer aux echecs dans le colonne k.
        game.print();                                          
                                 }
              }
  	 }//while
     game.result(game.status());                  //imprimer le resultat
   }

   if(p==2){                                      //jouer entre deux personnes
     jeux game;
     game.print();
     while(game.status()==0)
      {   
        screen.set_pen_color(yellow);
        cout<<"Joueur jaune"<<endl<<"Choisisez la colonne(1~7):"; 
        cin>>k;
        while(((k<=0)||(k>7))||game.is_full(k)){
          cout<<"Error, retapez!(1~7):"; 
          cin>>k;     
        }     
        game.ajouter_pion(k,1);
        game.print();
        if(game.status()==0){  
           screen.set_pen_color(red);
           cout<<"Joueur rouge"<<endl<<"Choisisez la colonne(1~7):"; 
           cin>>k;
           while(((k<=0)||(k>7))||game.is_full(k)){
              cout<<"Error, retapez!(1~7):"; 
              cin>>k;     
           }     
           game.ajouter_pion(k,2);
           game.print(); 
        }    //if  
      }//while
      game.result(game.status());
   }
   if(p==3){
      jeux game;
      game.randon_play(3);
      while(game.status()==0){
        game.auto_play(1);
        if(game.status()==0){
           game.auto_play(2);
        }//if 
      }//while
      game.print();
      game.result(game.status());
   }//if
   system("pause");        // une pose
} //while	
	return 0;               // 
}



