 #include "../../include/states/Loginstate.h"


Loginstate::Loginstate(){
    gui = new Logingui(this);
    init();
}

Loginstate::~Loginstate(){
    free();
    delete gui;
}

void Loginstate::init(){
	//Accéde à la base de donnée
    int code  = sqlite3_open("../../simulateur.db", &db);
    //Debug
    //std::cout <<"Code retour Sqlite3 open" <<  code << std::endl;
   // std::cout <<"Init: " << db << std::endl;
    if(code != SQLITE_OK){
        std::cerr << "Erreur Sqlite3 :" << sqlite3_errmsg(db) << std::endl;
        std::cerr << "Impossible d'acceder à la base de donnée, fermeture duprogramme" << std::endl;
        free();
        exit(1);
    }
}

void Loginstate::free(){
    gui->hide();
    sqlite3_close(db);
}

void Loginstate::update(){
  //std::cout << "Updating Login state" << std::endl;
    display();

}

void Loginstate::display(){
    gui->show();
}

bool Loginstate::isUser(QString login, QString password){
    sqlite3_stmt* resultat;
    QString sql = "SELECT * FROM Pilotes WHERE Login = '"+ login +"' AND Password = '"+ password +"' ;";
    //Debug
    // std::cout << sql.toStdString() << std::endl;
    //std::cout << db << std::endl;
    int coderetour = sqlite3_prepare_v2(db, sql.toStdString().data(), -1, &resultat,0);
    //Debug
    //std::cout <<"Code retour sqlite3 prepare:  " << coderetour << std::endl;
    //std::cout <<"Accès à la base de donnée: " << this->db << std::endl;
    if(!coderetour){
        if (coderetour == SQLITE_OK || coderetour == SQLITE_ROW){
             coderetour = sqlite3_step(resultat);
             if(coderetour == SQLITE_ROW || coderetour == SQLITE_OK){
                 sqlite3_finalize(resultat);
                 return true;
              }else{
                 sqlite3_finalize(resultat);
                 //sqlite3_close(db);
                 std::cerr << "sqlite3 step error :" <<  sqlite3_errmsg(db)<< std::endl;
                 return false;
             }
        }else{
            sqlite3_finalize(resultat);
            //sqlite3_close(db);
            std::cerr <<"sqlite" <<  sqlite3_errmsg(db)<< std::endl;
            return false;
        }
      }else{
        sqlite3_finalize(resultat);
        sqlite3_close(db);
        std::cerr <<"Les informations saisies ne sont pas valables: " <<  sqlite3_errmsg(db)<< std::endl;
        return false;
    }

   return false;

}
