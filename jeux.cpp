#include "jeux.h"
jeux::jeux(){
    int m = 7;
    int n = 6;    
    int o = 4;        
    plateau = new int* [m];           //
    player1 = new int**[m];
    player2 = new int**[m];
   for(int i = 0 ; i < m ; i++)
 {
  plateau[i] = new int[n];
  player1[i] = new int*[n];
  player2[i] = new int*[n];
    for (int j = 0;j < n;j++)
       {
        plateau[i][j]=0;
        player1[i][j] = new int[o];
        player2[i][j] = new int[o];
        for (int k=0;k<o;k++)
        {
            player1[i][j][k]=0;
            player2[i][j][k]=0;
            }
       }
 }
}
jeux::~jeux(){  //il y a des erreurs pour le destructeur, mais je ne sais pas ou sont ils.
   /* int m = 7;
    int n = 6;                    
    for (int i=0;i<m;i++)
     {
      delete[] plateau[m];
        for (int j=0;j<n;j++)
        {
            delete [] player1[i][j];
            delete [] player2[i][j];
        }
        delete [] player1[i];
        delete [] player2[i];
    } 
    delete[] plateau;
    delete [] player1;
    delete [] player2;    */
   }    

void jeux::randon_play(int m){
	//jouer par harsard,m represent de numero d'etape.
     int first;
     for(int t=0;t<2*m;t++){ 
     srand(time(NULL));
     first=rand()%8+1;
	 //first=3;
     ajouter_pion(first,t%2+1);
     }
}

 void jeux::menu(){
	 //imprimer le resultat de match.
    system("cls");
    set_pen_color(red);
    put_string("Choisisez un mode:", 10, 1);
    set_pen_color(white);
    put_string("1-Jouer avec ordinateur", 5, 3);
    put_string("2-Jouer entre deux personnes", 5, 4);
    put_string("3-Jouer simule par ordinateur", 5, 5);
    put_string("4-Exit", 5, 6);
    put_string("Choisisez:", 5, 7);

      }
      
  int jeux::choix_color(){
	  //demander l'utilisateur pour choisir un couleur
      int co;
       put_string("Votre couleur,jaune ou rouge?", 3, 0);
       put_string("1 = jaune,2 = rouge", 3, 2);
       put_string("Votre choix(1/2):", 3, 4);
      cin>>co;  
      while(co<1||co>2){   
          put_string("Error, retapez!(1/2)£º",3, 4);
          cin>>co;  
          }
      return co;
      }
      
      int jeux::choix_ordre(){
		  //demander l'utilisateur pour choisir jouer avant ou apres
          int fo;
           put_string("Vous voulez jouer avant ou pas?", 3, 0);
       put_string("1 = avant,2 = apres", 3, 2);
       put_string("Votre choix(1/2):", 3, 4);
      cin>>fo;   
      while(fo<1||fo>2){   
         put_string("Error, retapez!(1/2)£º",3, 4);
          cin>>fo;            
          }  
          return fo;
          }

  bool jeux::ajouter_pion(int x, int color){
       if(!is_full(x)){                    //on n'ajoute un pion que le colonne n'est pas plein.
         int j=get_top(x);                 //obtenir le haut du colonne
       plateau[x-1][j]=color;              //ajouter un pion.
	   for(int k=0;k<=3;k++){              //set le manuel d'echec
		   player1[x-1][j][k]=-10;
		   player2[x-1][j][k]=-10;
	   }
       return TRUE;
                      }
       else return FALSE;
       }
       

       
  bool jeux::is_full(int x){           //verifier si le colonne x est plein x~(1..7)
       if (plateau[x-1][5]!=0)
       return TRUE;
       else return FALSE;
       
       }
       
  int jeux::get_top(int x){
	  //retour le haut du colonne datif, s'il est vide, retour 0.
      int j=5;
       while((j>=0)&&(plateau[x-1][j]==0))
       j--;
         return ++j;
      }
       
  int jeux::get_one_possible(int x,int y,int color){
	  //calculer des pion datif
            int count1=0,count2=0,i=1,max=0;
            //calculer le pion en linge horizontal 
            while(((x-i>=0)&&(plateau[x-i][y]==color)))
            {count1+=1;
            i++;} 
			max=count1;
            i=1; 
             while(((x+i<=6)&&plateau[x+i][y]==color))
            {count2+=1;
            i++;} 
			if (max<count2)
				max=count2;
			if (color==1)
            player1[x][y][0]=get_degree(count1,count2,x,y);
			else player2[x][y][0]=get_degree(count1,count2,x,y);
            count1=0;
			count2=0;
            i=1;
            //calculer le pion en linge vertical 
            while(((y-i>=0)&&plateau[x][y-i]==color))
            {count2+=1; 
            i++;}
            i=1;
            if (max<count2)
				max=count2;
            if (color==1)
            player1[x][y][1]=get_degree(count1,count2,x,y);
			else player2[x][y][1]=get_degree(count1,count2,x,y);
            count2=0;
			
            i=1;
           //calculer le pion en linge oblique gauche 
            while(((x-i>=0)&&(y+i<=5)&&plateau[x-i][y+i]==color))
            {count1+=1; 
            i++;}
			if (max<count1)
				max=count1;
            i=1;
            while(((x+i<=6)&&(y-i>=0)&&plateau[x+i][y-i]==color))
            {count2+=1; 
            i++;}
			if (max<count2)
				max=count2;
            if (color==1)
            player1[x][y][2]=get_degree(count1,count2,x,y);
			else player2[x][y][2]=get_degree(count1,count2,x,y);
            count1=0;
			count2=0;
            i=1;
            //calculer le pion en linge oblique droite 
            while(((x+i<=6)&&(y+i<=5)&&plateau[x+i][y+i]==color))
            {count1+=1; 
            i++;}
			if (max<count1)
				max=count1;
            i=1;
            while(((x-i>=0)&&(y-i>=0)&&plateau[x-i][y-i]==color))
            {count2+=1; 
            i++;}
			if (max<count2)
				max=count2;
            if (color==1)
            player1[x][y][3]=get_degree(count1,count2,x,y);
			else player2[x][y][3]=get_degree(count1,count2,x,y);
			return max;
            }
       
       
       
   int jeux::get_degree(int a,int b,int i,int j){
	   //estimer des risques
             int degree = 0;
            if(a<b){
                    int temp=a;
                    a=b;
                    b=temp;
                    }
            if((a==0)&&(b==0)) degree=0;
            if((a==1)&&(b==0)) {
            if (((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1)))
                degree=1;
                else degree=0;     }           
            if((a==1)&&(b==1))  {
              if (((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1)))
                degree=20;
               else degree=5; }
            if((a==2)&&(b==0))  {
            if (((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1)))
                degree=5;
            else degree=0; }
            if((a==2)&&(b==1)) {
              if (((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1)))
              degree=100;
              else
              degree = 0;}
              
            if((a==2)&&(b==2)){
              if (((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1)))
               degree=100;
              else
               degree = 0;}
            if(a==3){
              if (((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1)))
               degree=100;
              else
               degree = 0;}
            return degree;
           }
           
       
 void jeux::possible(int color){
      int i,j;
      for(j=5;j>=0;j--)
         for(i=0;i<=6;i++){
         if(plateau[i][j]==0)
         get_one_possible(i,j,color);
          }
      } 

 int jeux::get_pion(int color,int & max){
      int i,j,k,t=0,temp=1,top;
	  int player[7][6][4];
	  int max_i=0;
	  max=0;
	  if(color==1)
		  for(i=0;i<=6;i++)
			  for(j=0;j<=5;j++)
				  for(k=0;k<=3;k++)
                    player[i][j][k]=player1[i][j][k];
			if(color==2){ for(i=0;i<=6;i++)
			               for(j=0;j<=5;j++)
				             for(k=0;k<=3;k++)
                               player[i][j][k]=player2[i][j][k];
                         }
         while(is_full(temp)) 
           temp++;
           top=get_top(temp);
           max_i=temp-1;
	  for(k=0;k<=3;k++)
	    max+=player[max_i][top][k];
      for(i=0;i<=6;i++)
         for(j=0;j<=5;j++){
			 for(k=0;k<=3;k++)
	        	 t+=player[i][j][k];
	        	 if ((plateau[i][j]==0)&&(t>=max)&&((j==0)||(plateau[i][j-1]!=0))&&(!is_full(i+1))){
				 max=t;
				 max_i=i;
				 t=0;
                 }
		      }
        return max_i;
 }

 int jeux::status()
	 //juger la fin du jeu£¬si le jaune a gagne, retour 1, 
	 //si le rouge a gagne, retour 2, si le match est nul, retour 3, si le match est en progres, retour 0 
 {
	 int count=0;
	 for(int i=0;i<=6;i++)
		 {for(int j=0;j<=5;j++)
	       {if ((plateau[i][j]==1)&&(get_one_possible(i,j,1)==3))
		     return 1;
		   else if ((plateau[i][j]==2)&&(get_one_possible(i,j,2)==3))
			   return 2;
	        }
	 if(is_full(i+1))
		 count+=1;
	 }
	 if (count==7)
		 return 3;
	 else return 0;
 }


 void jeux::auto_play(int color){
	 //jouer par AI
   int i,j,max1,max2;
   possible(1);
   possible(2);
	 if(color==1){
	  
      i=get_pion(1,max1);
      j=get_pion(2,max2);
      if (max1>=100)   //si on ajoute un pion dans ce colonne, on peut gagner tout de suite.
      ajouter_pion(i+1,1);
	  
      else if((max2>=max1)||(max2>=100))ajouter_pion(j+1,1); //si on n'ajoute pas un pion dans ce colonne, on peut pert tout de suite.
        else  ajouter_pion(i+1,1);
		
      }
	 else {
      i=get_pion(2,max1);
      j=get_pion(1,max2);
      if (max1>=100)
      ajouter_pion(i+1,2);
      else if((max2>=max1)||(max2>=100)) ajouter_pion(j+1,2);
        else ajouter_pion(i+1,2);

      }
	 
	 }
 
 
 
 void jeux::result(int sta){
	 //imprimer le resultat de match.
      if(sta==1)
     {set_pen_color(yellow);
	cout<<"Le jaune a gagne!"<<endl; }
      if(sta==2)
      {set_pen_color(red);
     cout<<"Le rouge a gagne!"<<endl; }
     if(sta==3)
      { set_pen_color(green);
     cout<<"Match nul, dommage !"<<endl; } 
      }


  void jeux::print()
//renouveler l'ecran 
{ 
       int i,j,k,t;
	   char c1 = 178;
	   char c2 = 254;
       system("cls");
       set_pen_color(blue);
    for (k=0;k<=36;k++)
         cout<<c1;
    for (j=5;j>=0;j--){
        for(t=0;t<2;t++){
         for ( i=0;i<=6;i++)
     {
           
      set_pen_color(blue);
    if(plateau[i][j]==0)
    cout<<c1<<c1<<"   ";
    if(plateau[i][j]==1)
      {set_pen_color(blue);
         cout<<c1<<c1;
      set_pen_color(yellow);
      cout<<c2<<c2<<c2; }
      if(plateau[i][j]==2)
     {set_pen_color(blue);
             cout<<c1<<c1;
      set_pen_color(red);
     cout<<c2<<c2<<c2; }
    }
    set_pen_color(blue);
    cout<<c1<<c1;
    }
    for (k=0;k<=36;k++)
    cout<<c1;
    
    
    
}
 cout<<"   1    2    3    4    5    6    7";  //imprimer le numero des colonnes
 set_pen_color(green);
 set_cursor_position(0,20);
 for (k=0;k<=36;k++)                                       //imprimer deux bornes.
    cout<<c1;
 set_cursor_position(0,25);
 for (k=0;k<=36;k++)
    cout<<c1;
     set_cursor_position(0,21);
 
 
}

