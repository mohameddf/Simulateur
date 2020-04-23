#ifndef H_MENUGUI
#define H_MENUGUI

#include "MenuState.h"
#include "MainGState.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

class MenuState;

class MenuGui: public QWidget{
    Q_OBJECT
  private:
    MenuState* menu;
    QVBoxLayout* mainlayout;
    QPushButton* newgame;
    QPushButton* charger;
    QPushButton* libre;
    QPushButton* quit;
    QPushButton* entr;
  public:
    MenuGui(MenuState* state);
    ~MenuGui();

  public slots:
     void GenerateFromFile();
     void GenerateRandom();
     void GenerateFree();

};

#endif
