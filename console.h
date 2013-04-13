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
    void set_title(const string& s); // change le titre de la barre de la fen�tre de la console
    bool set_dimensions(unsigned int width, unsigned int height); // change les dimensions de la console
    void set_cursor_position(unsigned int x, unsigned int y);
    void set_pen_color(color c); // change la couleur de l'�criture
	void clear(unsigned int x, unsigned int y); // efface le caract�re (x,y) de l'�cran
    void clear(); // efface tous les caract�res ?l'�cran
	void put_char(char c, unsigned int x, unsigned int y); // �crit le caract�re c en (x,y)
	void put_string(const string& s, unsigned int x, unsigned int y); // �crit la chaine de caract�res s en (x,y),(x+1,y),(x+2,y)...(x+s.length()-1)
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