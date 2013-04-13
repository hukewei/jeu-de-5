#include "console.h"

const char* console_exception::what() const throw(){
	return info.c_str();
}



console::console(){
	hScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hScreenBuffer == INVALID_HANDLE_VALUE) {
		throw console_exception("Can't get screen handle");
	}
	GetConsoleScreenBufferInfo (hScreenBuffer, &screenInfo);
	clear();
}

console::~console(){
	// restore l'état initial de la console (couleur,...)
	SetConsoleTextAttribute(hScreenBuffer, screenInfo.wAttributes);

}

void console::set_title(const string& s) {
	string str(s.begin(),s.end());
	SetConsoleTitle(str.c_str());
}

void console::set_pen_color(color c) {
	switch(c) {
	case default_color:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case red:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case green:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
		break;
	case blue:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
		break;
	case yellow:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case white:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case black:
		SetConsoleTextAttribute(hScreenBuffer, 0);
		break;
	case dark_red:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED);
		break;
	case dark_green:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN);
		break;
	case dark_blue:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_BLUE);
		break;
	case dark_yellow:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED   | FOREGROUND_GREEN );
		break;
	default:
		throw console_exception("Unknown color in set_cursor_color");
	}
}

void console::set_cursor_position(unsigned int x, unsigned int y) {
	COORD p;
	p.X=x;
	p.Y=y;
	SetConsoleCursorPosition(hScreenBuffer, p);
}

void console::clear() {
	system("CLS");
}

bool console::set_dimensions(unsigned int w, unsigned int h) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD  coordMax;
	coordMax = GetLargestConsoleWindowSize(hScreenBuffer);
	if (h > coordMax.Y) h = coordMax.Y;
	if (w > coordMax.X) w = coordMax.X;
	if (!GetConsoleScreenBufferInfo(hScreenBuffer, &info)) return FALSE;
	/* - hauteur - */
	info.srWindow.Left = 0;        
	info.srWindow.Right = info.dwSize.X - 1;               
	info.srWindow.Top = 0;
	info.srWindow.Bottom = h - 1;         
 
	if (h < info.dwSize.Y){
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow)) return FALSE;
		info.dwSize.Y = h;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize)) return FALSE;
	}else if (h > info.dwSize.Y){
		info.dwSize.Y = h;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize)) return FALSE;
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow))
			return FALSE;
	}
	if (!GetConsoleScreenBufferInfo(hScreenBuffer, &info)) return FALSE;
 
	/* --- largeur - */
	info.srWindow.Left = 0;        
	info.srWindow.Right = w - 1;
	info.srWindow.Top = 0;
	info.srWindow.Bottom = info.dwSize.Y - 1;              
	if (w < info.dwSize.X){
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow)) return FALSE;
		info.dwSize.X = w;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize))
		return FALSE;
	}else if (w > info.dwSize.X){
		info.dwSize.X = w; 
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize)) return FALSE;
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow))
		return FALSE;
	}
	return TRUE;
}




void console::put_char(char c, unsigned int x, unsigned int y){ 
	// écrit le caractère c en (x,y)
	set_cursor_position(x,y);
	std::cout<<c;
}

void console::clear(unsigned int x, unsigned int y){
	set_cursor_position(x,y);
	std::cout<<' ';
}

void console::put_string(const string& s, unsigned int x, unsigned int y){ 
	// écrit la chaine de caractères s en (x,y),(x+1,y),(x+2,y)...(x+s.length()-1)
	set_cursor_position(x,y);
	std::cout<<s;
}
