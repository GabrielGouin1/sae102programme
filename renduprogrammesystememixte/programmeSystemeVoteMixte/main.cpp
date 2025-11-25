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

// Le systeme de vote mixte étant composé à la fois d'un vote majoritaire et d'un vote proportionnel
// On a 120 votant et on considère qu'une "circonscription" est constitué de 5 votants consécutif donc 24 "points"/"siège" sont attribué par vote majoritaire et 24 par vote proportionnel.

void votemajoritaire(vector <double>& compteurPointsMajoritaire, const vector<participant>& vParticipant){
    int nombreGroupe = 24;// nombre de groupe
    for(int indiceGroupe = 0; indiceGroupe < nombreGroupe; indiceGroupe +=1){
        vector<int> compteurVoteGroupe(4,0); //compteur de votes pour le groupe dont c'est l'itération$
        // on compte alors les votes eds différents participants du groupe
        for (int indicParticipant = 0; indicParticipant < 5; indicParticipant+=1) {
            int vote = vParticipant[indiceGroupe*5 + indicParticipant].glacePref -1; //L'indice de la glace pour lequel le participant vote
            compteurVoteGroupe[vote] +=1; //On ajoute 1 à la glace pour lequel le participant à voté
        }

        // ON cherche vérifier si il y a des égalité et à les gérer dans le cas échéant
        bool egalité = false;
        int cptWhile = 0;
        int indiceEgalité;
        while (egalité == false && cptWhile < 3) { //On cherche toutes les égalités existantes dans le groupe
            for(int indiceGlace= cptWhile ; indiceGlace <4; indiceGlace +=1){
                if (cptWhile != indiceGlace){
                    if (compteurVoteGroupe[cptWhile] == compteurVoteGroupe[indiceGlace]){ // Si 2 fruit on le même nombre de vote alors on casse la boucle et change la variable egalité à true pour signifier qu'il y en a une
                        egalité = true;
                        indiceEgalité = indiceGlace;
                        break;
                    }
                }
            }
            cptWhile +=1;
        }

        if(egalité == true){
            int voteMax =0;
            for (int indiceGlace =0; indiceGlace < 4; indiceGlace +=1){ //On cherche la plus grand nombre de vote récolté par une glace
                if (voteMax < compteurVoteGroupe[indiceGlace]){
                    voteMax = compteurVoteGroupe[indiceGlace];
                }
            }
            if(compteurVoteGroupe[cptWhile-1] == voteMax){ //On vérifie que ce nombre correspond bien au nombre de voix de nos égalités afgin d'être sûr qu'il n'y a pas d'autres fruit ayant récolté plus de voix
                compteurPointsMajoritaire[cptWhile-1] +=0.5;
                compteurPointsMajoritaire[indiceEgalité] +=0.5;

            } else { // Dans le cas ou il y a un nombre ayant récolté plus de voix que les fruit concerné par nos égalité alors l'égalité ne nous intéresse plus
                egalité = false;
            }
        }

        if(egalité == false){
            int vainqueurGroupe = 0; //cette valeur contiendra l'indice de la glace ayant remporté le vote dans ce groupe
            for (int indiceGlace =1; indiceGlace < 4; indiceGlace +=1){
                if (compteurVoteGroupe[vainqueurGroupe] < compteurVoteGroupe[indiceGlace]){
                    vainqueurGroupe = indiceGlace;
                }
            }
            compteurPointsMajoritaire[vainqueurGroupe] +=1; //On ajoute 1 point pour la glace ayant gagné cete élection dans le compteur global.
        }
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
    vector<double> compteurPointsMajoritaire(4, 0.0);
    votemajoritaire(compteurPointsMajoritaire, vParticipant);

    //Votes proportionnels
    vector<int> compteurPointsProportionnel(4,0);
    for (const participant & part : vParticipant){
        compteurPointsProportionnel[part.glacePref-1] += 1;
    }

    vector<double> compteurPointsFinals(4, 0);

    //On réuni les 2 compteur pour obtenir un combinant les votes
    for (unsigned i = 0; i < 4; i+=1) {
        compteurPointsFinals[i] = compteurPointsMajoritaire[i] + (compteurPointsProportionnel[i] / 120.0) * 24; // On donne le même poid(24points) à chaque groupe pour le compteur final et on le calcul pour chaque glace
    }

    // variable qui contiendra l'indice du fruit vainqueur
    int locFruitGagnant = 0;

    // On cherche le fruit ayant remporté l'élection
    for (unsigned i = 1; i <4; i+=1){
        if (compteurPointsFinals[locFruitGagnant] < compteurPointsFinals[i]){ //Si jamais la variable qui contiendra l'indice du fruit vainqueur(le plus grand actuellement) ne l'est pas alors l'indice est remplacé par celui de l'itération actuel de la boucle
            locFruitGagnant = i;
        }
    }

    cout << "Le vainqueur est: " << vGlacePref[locFruitGagnant] << endl;

    /* debug */
    // affichVectString (vGlacePref);
}


