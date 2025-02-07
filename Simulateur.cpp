#include "processus.h"
#include "ordonnanceur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <filesystem>
using namespace std;

/**
 * @brief fonction pour charger les processus à partir d'un fichier
 *
 * cette fonction lit un fichier texte contenant des processus et les stocke dans une file.
 *
 * @param fileName le nom du fichier à partir duquel charger les processus
 * @param file_processus la file où les processus seront stockés
 *
 * @return true si le chargement est réussi, false sinon
 */
bool chargerProcessus(const string& fileName, queue<Processus>& file_processus) {
    ifstream fichier(fileName);

    // vérifier si le fichier a été ouvert avec succès
    if (!fichier) {
        cerr << "erreur : impossible d'ouvrir le fichier " << fileName << "." << endl;
        cerr << "chemin courant : " << filesystem::current_path() << endl;
        return false;
    }

    string ligne;  // variable pour lire le fichier ligne par ligne
    while (getline(fichier, ligne)) {
        istringstream iss(ligne);  // découper la ligne
        string pid;
        int arrivee, duree, restant, priorite, type;

        // lire et créer le processus s'il y a suffisamment de données
        if (iss >> pid >> arrivee >> duree >> restant >> priorite >> type) {
            auto typeEnum = static_cast<TypeProcessus>(type - 1); // conversion en type énuméré
            file_processus.emplace(pid, arrivee, duree, priorite, typeEnum);  // création d'un nouveau processus
        } else {
            cerr << "erreur : impossible de lire la ligne : " << ligne << endl;
        }
    }
    fichier.close();

    // afficher les processus chargés (sans toucher la file principale)
    cout << "chargement des processus depuis " << fileName << " :\n";
    queue<Processus> temp = file_processus;
    while (!temp.empty()) {
        Processus p = temp.front();
        temp.pop();  // retirer l'élément pour lire le suivant
        cout << p.getPid() << " arrivee : " << p.getArrivee() << " Duree : " << p.getDuree()
             << " temps d'attente : " << p.getAttente() << " Priorite : " << p.getPriorite()
             << " Type : " << (p.getType() + 1) << endl;
    }
    cout << "fin chargement\n";

    return true;
}

/**
 * @brief fonction principale
 *
 * cette fonction exécute différentes simulations d'algorithmes d'ordonnancement de processus :
 * fcfs, sjf, round robin, priorité et à files multiniveaux. les résultats sont affichés dans la console.
 *
 * @return 0 si l'exécution se fait correctement, 1 sinon
 */
int main() {
    queue<Processus> file_processus;
    int temps = 0;

    string cheminFichier = "Test.txt";


    // simulation FCFS
    if (!chargerProcessus(cheminFichier, file_processus)) {
        return 1;
    }

    cout << "\nsimulation FCFS resultat: \n";
    queue<Processus> fcfs_result = TP::Ordonnanceur::fcfs(file_processus, temps);
    double temps_attente_total = 0;
    int n = fcfs_result.size();
    while (!fcfs_result.empty()) {
        Processus p = fcfs_result.front();
        fcfs_result.pop();
        cout << p.getPid() << " arrivee : " << p.getArrivee() << " Duree : " << p.getDuree()
             << " temps d'attente : " << p.getAttente() << " Priorite : " << p.getPriorite()
             << " Type : " << (p.getType() + 1) << endl;
        temps_attente_total += p.getAttente();
    }
    if (n > 0) {
        cout << "temps d'attente moyen : " << temps_attente_total / n << "\n";
    }

    // réinitialisation du temps pour les autres simulations
    temps = 0;

    // simulation SJF (fjs)
    cout << "\nsimulation SJF (FJS) resultat: \n";
    queue<Processus> sjf_result = TP::Ordonnanceur::fjs(file_processus, temps);
    temps_attente_total = 0;
    n = sjf_result.size();
    while (!sjf_result.empty()) {
        Processus p = sjf_result.front();
        sjf_result.pop();
        cout << p.getPid() << " arrivee : " << p.getArrivee() << " Duree : " << p.getDuree()
             << " temps d'attente : " << p.getAttente() << " Priorite : " << p.getPriorite()
             << " Type : " << (p.getType() + 1) << endl;
        temps_attente_total += p.getAttente();
    }
    if (n > 0) {
        cout << "temps d'attente moyen : " << temps_attente_total / n << "\n";
    }

    // simulation Round Robin
    temps = 0;
    int quantum = 4;
    cout << "\nsimulation Round Robin resultat: \n";
    queue<Processus> rr_result = TP::Ordonnanceur::round_robin(file_processus, quantum, temps);
    temps_attente_total = 0;
    n = rr_result.size();
    while (!rr_result.empty()) {
        Processus p = rr_result.front();
        rr_result.pop();
        cout << p.getPid() << " arrivee : " << p.getArrivee() << " Duree : " << p.getDuree()
             << " temps d'attente : " << p.getAttente() << " Priorite : " << p.getPriorite()
             << " Type : " << (p.getType() + 1) << endl;
        temps_attente_total += p.getAttente();
    }
    if (n > 0) {
        cout << "temps d'attente moyen : " << temps_attente_total / n << "\n";
    }

    // simulation avec Priorité
    file_processus = queue<Processus>(); // réinitialisation de la file des processus
    if (!chargerProcessus("TestPriorite.txt", file_processus)) {
        return 1;
    }
    temps = 0;
    cout << "\nsimulation avec Priorite resultat: \n";
    queue<Processus> priorite_result = TP::Ordonnanceur::priorite(file_processus, temps);
    temps_attente_total = 0;
    n = priorite_result.size();
    while (!priorite_result.empty()) {
        Processus p = priorite_result.front();
        priorite_result.pop();
        cout << p.getPid() << " arrivee : " << p.getArrivee() << " Duree : " << p.getDuree()
             << " temps d'attente : " << p.getAttente() << " Priorite : " << p.getPriorite()
             << " Type : " << (p.getType() + 1) << endl;
        temps_attente_total += p.getAttente();
    }
    if (n > 0) {
        cout << "temps d'attente moyen : " << temps_attente_total / n << "\n";
    }

    // simulation à files multiniveaux
    file_processus = queue<Processus>(); // réinitialisation de la file des processus
    if (!chargerProcessus("TestMultiniveaux.txt", file_processus)) {
        return 1;
    }
    temps = 0;

    cout << "\nsimulation Multiniveaux resultat: \n";
    queue<Processus> multiniveaux_result = TP::Ordonnanceur::multiniveaux(file_processus, quantum, temps);
    temps_attente_total = 0;
    n = multiniveaux_result.size();
    while (!multiniveaux_result.empty()) {
        Processus p = multiniveaux_result.front();
        multiniveaux_result.pop();
        cout << p.getPid() << " arrivee : " << p.getArrivee() << " Duree : " << p.getDuree()
             << " temps d'attente : " << p.getAttente() << " Priorite : " << p.getPriorite()
             << " Type : " << (p.getType() + 1) << endl;
        temps_attente_total += p.getAttente();
    }
    if (n > 0) {
        cout << "temps d'attente moyen : " << temps_attente_total / n << "\n";
    }

    cout << "fin du programme\n";
    return 0;
}
