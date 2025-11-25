//----Modification----
/**
 * @date 21/11/2025
 */
//--------------------------CODE MODIFIE-------------------------------------

// on va detecter les glaces preférées des votants tout en virant les commentaires
void enregistrePart (vector<participant> & vPart){
    for (unsigned i (0); i < 116; ++i){
        string nom (litUneString());
        string prenom  (litUneString());
        int numGlace (litUnEntier());
        //cout << nom << endl << prenom << endl << numGlace << endl << "NUMERO :" << i << endl;
        vPart.push_back(participant{nom, prenom, numGlace});
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

    //Cas de la majorité absolue qui fait une simple vérification sur la moitié du nb de participants
    bool majoriteAbsolue (false);
    for (unsigned i=0; i < vCompteur.size(); i=i+1){
        if (vCompteur[i] > vParticipant.size()/2){
            majoriteAbsolue = true;
            cout << "la glace élue est : " << vGlacePref[i] << endl;
        }
    }

    //Cas sans majorité absolue
    if (!majoriteAbsolue){
        //Les deux glaces en tete seront definies par max1 et max2
        int max1 = 0;
        int max2 = 0;
        for (unsigned i=1; i < 4; i=i+1){
            if (vCompteur[i] > vCompteur[max1]){//On trouve le max1
                max2 = max1;//Si il est trouvé, le max1 précédent devient max2
                max1 = i;
            }
            else if (vCompteur[i] > vCompteur[max2]){//On verifie si max2 peut etre plus petit que max1 mais plus grand que le max2 actuel
                max2 = i;
            }
        }

        //On prends les votes du second tour
        vector<participant> vParticipant2;
        enregistrePart(vParticipant2);

        //On refait un comptage
        vector<int> vCompteur2 (4,0);
        for (const participant & part : vParticipant2){ //boucle qui passe pour chaque participants du vecteur
            vCompteur2[part.glacePref-1] += 1; // rajoute 1 pour le num de la glace qui est entre 1 et 4 donc on enleve 1
        }

        //cout << "Compteur " << vGlacePref[max1] << " : " << vCompteur2[0] << endl << "Compteur " << vGlacePref[max2] << " : " << vCompteur2[1] << endl;

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


    return 0;
}
