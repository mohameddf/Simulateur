#ifndef H_LOGINGUI
#define H_LOGINGUI

#include <iostream>
#include <string>
#include <cstring>
#include <QObject>
#include <QCursor>
#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QMessageBox>
#include <QTime>

#include "../states/Loginstate.h"
#include "../states/MenuState.h"

class MenuState;
class Loginstate;


class Logingui : public QWidget{
    Q_OBJECT
private:

      Loginstate* state;
      QVBoxLayout* mainlayout;
      QHBoxLayout* buttonlayout;
      QLabel* logo;
      QLabel* name;
      QPushButton* connect;
      QPushButton* quit;
      QFormLayout* form;
      QLineEdit* login;
      QLineEdit* password;
public slots:
    bool checkcred();
public:
    Logingui(Loginstate* st);
    ~Logingui();
    //Getters
    QVBoxLayout* getMainLayout() const {return this->mainlayout;}
    QHBoxLayout* getButtonLayout() const {return this->buttonlayout;}
    QLabel* getLogo() const {return this->logo;}
    QPushButton* getConnectButton() const { return this->connect;}
    QPushButton* getQuitButton() const { return this->quit;}
    QFormLayout* getFrom() const {return this->form;}
    QLineEdit* getLogin() const {return this->login;}
    QLineEdit* getPassword() const {return this->password;}
};

#endif
