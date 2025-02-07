#include <string>
using namespace std;

// processus.h
#ifndef PROCESSUS_H
#define PROCESSUS_H

// enum pour le multiniveaux
enum TypeProcessus {
    SYSTEME,
    INTERACTIF,
    BATCH,
    UTILISATEUR
};

class Processus {

private:
    string m_pid;  // identifiant pour l'affichage du résultat
    int m_arrivee;      // instant d'arrivée du processus dans le système
    int m_duree;        // durée d'exécution initiale du processus
    int m_restant;      // temps restant à exécuter
    int m_attente;      // temps d'attente cumulé
    int m_fin;          // temps à la préhémption pour l'algorithme de tourniquet
    int m_priorite;     // priorité du processus
    TypeProcessus m_type; // type du processus pour multiniveaux

public:
    // Constructeur
    Processus(const string& pid, int arrivee, int duree, int priorite, TypeProcessus type);

    void verifieInvariant() const;

    // Accesseurs
    string getPid() const;
    int getArrivee() const;
    int getDuree() const;
    int getRestant() const;
    int getAttente() const;
    int getFin() const;
    int getPriorite() const;
    TypeProcessus getType() const;

    // Mutateurs
    void setRestant(int restant);
    void setAttente(int attente);
    void setFin(int fin);
    void setPriorite(int priorite);

    // Surcharge des opérateurs
    bool operator<(const Processus& autre) const; // Compare deux processus en fonction de leur priorite
    bool operator==(const Processus& autre) const; // Pour identifier un processus par son pid
};

#endif // PROCESSUS_H