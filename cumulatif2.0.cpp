/**
 *  @date : 22 octobre 2024
 *  @author : Alain Casali et groupe 2 G1
 *  @Brief : vote 2 tour de la SAE 1.02 de 25/26
**/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief litUneString
 * @return la chaine lue sauf si :
 * (1) on une boulette sur l'entrée
 * (2) on trouve un commentaire sur l'entrée
 * le commentaire est matérialisé par la chaine "//"
 */


string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}


int litUnEntier (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

struct participant {
    string nom;
    string prenom;
    int glacePref;
    vector<unsigned> vGlacePoint; // --------------- vecteur ajouté pour le nb de points
};

bool compare2part (const participant & p1, const participant & p2){
    return p1.prenom < p2.prenom;
}

void affichVectString (const vector<string> & v){
    for (const string & val : v)
        cout << val << '\t';
    cout << endl;
}

void affichVectParticipants (const vector<participant> & vPart){
    for (const participant & part : vPart){
        cout << part.nom << endl;
        cout << part.prenom << endl;
        cout << part.glacePref << endl;
    }
}

//--------------------------CODE MODIFIE-------------------------------------
//On a ajouté au struct un vecteur qui compte le nb de pts par glace

// on va detecter les glaces preférées des votants tout en virant les commentaires
void enregistrePart (vector<participant> & vPart){
    for (unsigned i (0); i < 116; ++i){
        string nom (litUneString());
        string prenom  (litUneString());
        int numGlace (litUnEntier());
        for (unsigned j(0); j < 4; j = j + 1){
            participant.vGlacePoint.push_back(litUnEntier()); // On lit sur le fichier d'entrée combien de points ont les glaces
        }
        vPart.push_back(participant{nom, prenom, numGlace,vGlacePoint});
        //cout << nom << endl << prenom << endl << numGlace << endl << "NUMERO :" << i << endl;
    }
}

int main()
{
    /* on vote sur 4 glaces */
    vector<string> vGlacePref;
    for (unsigned i=0; i < 4; i=i+1)
        vGlacePref.push_back(litUneString());
    //affichVectString(vGlacePref);

    //On lit les datas du clavier, et on les stocke :
    vector<participant> vParticipant;
    enregistrePart(vParticipant);

    //------Vote majoritaire en deux tours :

    //Votes du premier tour
    vector<int> vCompteur (4,0); //4 glaces
    for (const participant & participant : vParticipant){ //boucle qui passe pour chaque participants du vecteur
        vCompteur[participant.glacePref-1] += 1; // rajoute 1 pour le num de la glace qui est entre 1 et 4 donc on enleve 1
    }
    //cout << "Compteur Choco : " << vCompteur[0] << "   Compteur pour Fraises : " << vCompteur[1] << "   Compteur pour Banane : " << vCompteur[2] << "   Compteur pour Mangue : " << vCompteur[3] << endl;

    //On annonce le résultat final :
    if (vCompteur2[0] > vCompteur2[1])
        cout << "la glace élue est : " << vGlacePref[max1] << endl;
    else if (vCompteur2[1] > vCompteur2[0])
        cout << "la glace élue est : " << vGlacePref[max2] << endl;
    else
        cout << "Egalité entre les deux glaces en tête" << endl;
    }
    return 0;
}
