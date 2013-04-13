#if !defined(CONSOLE)
#define CONSOLE


#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

enum color {default_color, blue, yellow, red, green, white, black, dark_blue, dark_yellow, dark_red, dark_green}; 

class console{
public:
	console();
	~console();
    void set_title(const string& s); // change le titre de la barre de la fenêtre de la console
    bool set_dimensions(unsigned int width, unsigned int height); // change les dimensions de la console
    void set_cursor_position(unsigned int x, unsigned int y);
    void set_pen_color(color c); // change la couleur de l'écriture
	void clear(unsigned int x, unsigned int y); // efface le caractère (x,y) de l'écran
    void clear(); // efface tous les caractères ?l'écran
	void put_char(char c, unsigned int x, unsigned int y); // écrit le caractère c en (x,y)
	void put_string(const string& s, unsigned int x, unsigned int y); // écrit la chaine de caractères s en (x,y),(x+1,y),(x+2,y)...(x+s.length()-1)
private:
	HANDLE hScreenBuffer;
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
};


class console_exception{
	string info;
public:
	console_exception(const string& s):info(s){}
	virtual const char* what() const throw();
};

#endif