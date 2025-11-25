/**
 *  @date : 21 novembre 2025
 *  @author : Gabriel Gouin
 *  @Brief : une prmière réponse à la SAE 1.02 de 24/25
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

// Le systeme de vote mixte étant composé à la fois d'un vote majoritaire et d'un vote proportionnel on va dire que les 2 votes auront le même poid, 50/50.
// On a 120 votant et on considère qu'une "circonscription" est constitué de 5 votants consécutif donc 24 points sont attribué par vote majoritaire et 24 par vote proportionnel.


void votemajoritaire(const vector<participant>& vParticipant,
                     const vector<string>& vGlacePref,
                     vector<int>& pointsMajoritaires) {

    int nbGroupes = 24 ;// nombre de groupe( a modifier)

    for (int groupe = 0; groupe < nbGroupes; groupe += 1) {
        vector<int> voteGroupe(4, 0); // Compteur de votes pour le groupe actuel
        // On compte les votes des defferents participants du groupe
        for (int i = 0; i < 5; i+= 1) {
            int locParticipant = groupe * 5 + i;
            int vote = vParticipant[locParticipant].glacePref - 1;
            voteGroupe[vote] += 1;
        }
        // ON cherche le vainqueur en cas d'égalité le point est attribué au premier.
        int gagnantGroupe = 0;
        int maxVotes = voteGroupe[0];
        for (int glace = 1; glace < 4; glace +=1) {
            if (voteGroupe[glace] > maxVotes) {
                maxVotes = voteGroupe[glace];
                gagnantGroupe = glace;
            }
        }
        pointsMajoritaires[gagnantGroupe] += 1;
    }
}

int main()
{

    /* on vote sur 4 glaces */
    vector<string> vGlacePref;
    for (unsigned i (0); i < 4; ++i)
        vGlacePref.push_back(litUneString());
    //On lit les datas du clavier, et on les stocke
    vector<participant> vParticipant;

    for (unsigned i (0); i < 120; ++i){
        string nom (litUneString());
        string prenom  (litUneString());
        int numGlace (litUnEntier());
        // cout << nom << endl << prenom << endl << numGlace << endl;
        vParticipant.push_back(participant{nom, prenom, numGlace});
            //  vJoueur[numEquipe-1].push_back(joueur {nom, prenom, numEquipe});
    }

    // vote majoritaire
    vector<int> pointsMajoritaires(4, 0);
    votemajoritaire(vParticipant, vGlacePref, pointsMajoritaires);

    //Votes proporionnel
    vector<int> voteproportionnel(4,0); //4 glaces
    for (const participant & part : vParticipant){
        voteproportionnel[part.glacePref-1] += 1;
    }

    vector<double> scoresFinaux(4, 0.0);


    int locFuitGagnant = 0;

    // On donne le même poid à chaque groupe pour le score final
    for (unsigned i = 0; i < 4; i+=1) {
        // On équilibre les groupes
        double scoreMajoritaire = (pointsMajoritaires[i]) ;
        double scoreProportionnel = (voteproportionnel[i] / 120.0) * 24;
        scoresFinaux[i] = scoreMajoritaire + scoreProportionnel;

        for (unsigned i = 1; i <4; i+=1){
            if (scoresFinaux[locFuitGagnant] < scoresFinaux[i]){
                locFuitGagnant = i;
            }
        }
    }

    cout << "Le vainqueur est: " << vGlacePref[locFuitGagnant] << endl;

    /* debug */
    // affichVectString (vGlacePref);
}


