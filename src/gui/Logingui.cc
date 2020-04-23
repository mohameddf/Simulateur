#include "../../include/gui/Logingui.h"


Logingui::Logingui(Loginstate* st): QWidget(){
    //Faire le lien entre le gui et son etat
    this->state = st;
    //Configuration de la fenetre
    this->setStyleSheet("background-color:white;");
    this->setWindowIcon(QIcon("../../assets/simulator.png"));
    this->setFixedSize(QSize(500, 250));
    this->setCursor(QCursor());
    //Creation des widgets
    mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    buttonlayout = new QHBoxLayout();
    connect = new  QPushButton("Connect");
    connect->setStyleSheet("background-color : green; color:white; font-weight:bold;");
    quit = new QPushButton("Quit");
    quit->setStyleSheet("background-color : red; color:white;font-weight:bold;");
    logo = new QLabel();
    logo->setPixmap(QPixmap("../../assets/simulator.png"));
    logo->setAlignment(Qt::AlignHCenter);
    //Creation du fomulaire
    form = new QFormLayout();
    login = new QLineEdit();
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    form->addRow("Login", login);
    form->addRow("Password", password);
    //Creation du layout H de bouttons
    buttonlayout->addWidget(connect);
    buttonlayout->addWidget(quit);
    //Configuration du layout principal (Un label + Un form+ un layout h de bouton)
    mainlayout->addWidget(logo);
    mainlayout->addLayout(form);
    mainlayout->addLayout(buttonlayout);

    //Connection du bouton quitter à l'action correspondante
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(connect, SIGNAL(clicked()), this, SLOT(checkcred()));

}

Logingui::~Logingui(){
    delete mainlayout;
    delete buttonlayout;
    delete connect;
    delete quit;
    delete form;
    delete login;
    delete password;
    delete logo;

}


bool Logingui::checkcred(){
   QString login = this->getLogin()->text();
   QString password = this->getPassword()->text();
    if(!login.isEmpty() && !password.isEmpty()){
       if(state->isUser(login, password)){
            // std::cout << "Mot de passe validé" << std::endl;

           MenuState * menu = new MenuState();
           state->GetManager()->SetLogin(login);
           state->free();
           state->GetManager()->PopState();
           state->GetManager()->PushState(menu);
           state->GetManager()->GetCurrentState()->update();
 

        return true;
        }else{
          //  std::cout << "Retour à l'état de connexion" << std::endl;
           QMessageBox::warning(this, "Erreur d'accès à la base de donnée", "Le pilote n'existe pas.");
          return false;
        }
        QMessageBox::warning(this, "Erreur d'accès à la base de donnée", "Le pilote n'existe pas.");
       return false;
    }
     QMessageBox::warning(this, "Erreur d'accès à la base de donnée", "Le pilote n'existe pas.");
    return false;
 }


