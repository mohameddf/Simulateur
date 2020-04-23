#include "../../include/utils/xmlparser.h"


xmlparser::xmlparser(){

}

xmlparser::xmlparser(QString filepath){
    file = new QFile(filepath);
    if(!(file->open(QIODevice::ReadOnly))){
         QMessageBox::warning(this, "Erreur à l'ouverture du document XML",
                              "Le document XML n'a pas pu être ouvert.");
    }
    dom = new QDomDocument();
    QString errorStr;
    int errorLine;
    int errorColumn;
    //Récuperation des éléments du fichiers XML
    if (!dom->setContent(file, false, &errorStr, &errorLine, &errorColumn))
        QMessageBox::warning(this, "Erreur DOM XML",
                             "Le document XML n'a pas pu être parser.");
    }

xmlparser::~xmlparser(){
    file->close();
    delete file;
}

void xmlparser::parseXmlFile(){
      int tab[7];
      int i = 0;
      QDomElement docElem = dom->documentElement();//Simulateur
      sys = new Systeme(docElem.attributeNode("capacite").value().toDouble(),
                        docElem.attributeNode("consomation").value().toDouble(),
                        docElem.attributeNode("duree").value().toInt(),
                        docElem.attributeNode("tempsactuel").value().toInt());

      QDomNode n = docElem.firstChild();//Pannes
      QDomNode nn = n.firstChild(); //Panne

/*
 *     std::cout << "DEBUG: " << docElem.nodeName().toStdString() << std::endl;
 *     std::cout << "DEBUG: " <<n.nodeName().toStdString() << std::endl;
 *     std::cout << "DEBUG: " <<docElem.attributeNode("consomation").value().toStdString() << std::endl;
 *     std::cout << "DEBUG: " <<docElem.attributeNode("duree").value().toStdString() << std::endl;
 *     std::cout << "DEBUG: " <<docElem.attributeNode("capacite").value().toStdString() << std::endl;
*/
      while (!nn.isNull()) {
          QDomNode panelem = nn.firstChild();
          i = 2;
           while(!panelem.isNull()){
/*
 *     std::cout << nn.toElement().attribute("id", "").toInt() << std::endl;
 *     std::cout << panelem.toElement().tagName().toStdString() << std::endl;
 *     std::cout << panelem.toElement().text().toStdString() << std::endl <<"*********" << std::endl;
*/
               tab[0] = nn.toElement().attribute("id", "").toInt();
               tab[1] = nn.toElement().attribute("idparent", "").toInt();
               tab[i] = panelem.toElement().text().toInt();
               i++;
               panelem = panelem.nextSibling();
             }

           pannes.push_back(new panne(tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6]));

          nn = nn.nextSibling();
      }
     /*for (int z= 0; z < 7; z++) {
            std::cout << tab[z] << std::endl;
        }

*/
}

panne* xmlparser::GetRandomPannes(int nb, int duree){
    return new panne(nb, duree);
}


QVector<panne*> * xmlparser::sortedPannes(QVector<panne*> * p){
    auto sortRule = [] (panne* p1, panne* p2)-> bool{
        return p1->duree > p2->duree;
    };

    std::sort(p->begin(), p->end(), sortRule);

    return p;
    }
void xmlparser::WriteinXmlFile(QFile* file, Systeme* sys, QVector<panne*> pannes){
    if(!file->open(QIODevice::WriteOnly))
    {
        file->close();
        //QMessageBox::warning(this,"Erreur","Impossible d'écrire dans le document XML");
        return;
    }
     //Création de la balise simulation
     QDomDocument document;
     QDomElement sim = document.createElement("Simulateur");
     sim.setAttribute("tempsactuel", sys->tempsactuel);
     sim.setAttribute("duree", sys->duree);
     sim.setAttribute("capacite", sys->GetCapacity());
     sim.setAttribute("consomation", sys->conso_mot);
     document.appendChild(sim);
     //Creation de la balise panne
     QDomElement ps = document.createElement("Pannes");
     sim.appendChild(ps);
     for(int i = 0; i < pannes.size(); i++){
      QDomElement panne = document.createElement("Panne");
      panne.setAttribute("idparent", pannes[i]->parent);
      panne.setAttribute("id", pannes[i]->id);
      ps.appendChild(panne);
      QDomElement piece = document.createElement("Piece");
      QDomElement nbPiece = document.createElement("nbPiece");
      QDomElement Note = document.createElement("Note");
      QDomElement Temps = document.createElement("Temps");
      QDomElement Passe = document.createElement("Passe");

      QDomText text = document.createTextNode(QString::number(pannes[i]->piece));
      piece.appendChild(text);
      panne.appendChild(piece);
       //---------------------------//
       text = document.createTextNode(QString::number(pannes[i]->idobjet));
       nbPiece.appendChild(text);
       panne.appendChild(nbPiece);
       //---------------------------//
       text = document.createTextNode(QString::number(pannes[i]->note));
       Note.appendChild(text);
       panne.appendChild(Note);
       //-----------------------------//
       text = document.createTextNode(QString::number(pannes[i]->duree));
       Temps.appendChild(text);
       panne.appendChild(Temps);
       //-----------------------------//
       text = document.createTextNode(QString::number(pannes[i]->isdone));
       Passe.appendChild(text);
       panne.appendChild(Passe);
       //-----------------------------//
     }

     QTextStream stream(file);
     stream << document.toString();
       file->close();
       return;
}
