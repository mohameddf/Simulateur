#ifndef H_LOGINSTATE
#define H_LOGINSTATE 

#include <sqlite3.h>
#include <iostream>
#include <cstring>
#include <QWidget>

#include "State.h"
#include "../gui/Logingui.h"

class State;
class Logingui;

class Loginstate : public State{

private:
    sqlite3* db;
	//Informations récupérés depuis la base de donnée
	char* Login;
	char* Password;	
	//Ajouter le GUI
    Logingui* gui;

public:
	Loginstate();
    ~Loginstate();
    void init();
	void free();
	void update();
    void display();

    bool isUser(QString, QString);

    Logingui* getGui() const {return gui;}
};

#endif
