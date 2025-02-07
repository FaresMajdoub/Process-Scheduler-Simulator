#include "processus.h"
#include "ContratException.h"

/**
 * @brief Constructeur de la classe Processus.
 * @param pid Identifiant du processus.
 * @param arrivee Temps d'arrivée du processus.
 * @param duree Durée d'exécution du processus.
 * @param priorite Priorité du processus.
 * @param type Type du processus.
 * \pre arrivee >= 0 (le temps d'arrivée doit être non-négatif)
 * \pre duree > 0 (la durée doit être positive)
 * \pre priorite >= 0 (la priorité doit être non-négative)
 * \post m_pid == pid
 * \post m_arrivee == arrivee
 * \post m_duree == duree
 * \post m_priorite == priorite
 * \post m_type == type
 */
Processus::Processus(const string& pid, int arrivee, int duree, int priorite, TypeProcessus type)
    : m_pid(pid), m_arrivee(arrivee), m_duree(duree), m_restant(duree),
      m_attente(0), m_fin(0), m_priorite(priorite), m_type(type) {

    PRECONDITION(arrivee >= 0);
    PRECONDITION(duree > 0);
    PRECONDITION(priorite >= 0);

    POSTCONDITION(m_pid == pid);
    POSTCONDITION(m_arrivee == arrivee);
    POSTCONDITION(m_duree == duree);
    POSTCONDITION(m_priorite == priorite);
    POSTCONDITION(m_type == type);

    INVARIANTS();
}

//Accesseurs

/**
 * @brief Retourne l'identifiant du processus.
 * \return L'identifiant du processus.
 */
string Processus::getPid() const {
    return m_pid;
}

/**
 * @brief Retourne le temps d'arrivée du processus.
 * \return Le temps d'arrivée du processus.
 */
int Processus::getArrivee() const {
    return m_arrivee;
}

/**
 * @brief Retourne la durée du processus.
 * \return La durée du processus.
 */
int Processus::getDuree() const {
    return m_duree;
}

/**
 * @brief Retourne le temps restant du processus.
 * \return Le temps restant à exécuter du processus.
 */
int Processus::getRestant() const {
    return m_restant;
}

/**
 * @brief Retourne le temps d'attente du processus.
 * \return Le temps d'attente cumulé du processus.
 */
int Processus::getAttente() const {
    return m_attente;
}

/**
 * @brief Retourne le temps de fin du processus.
 * \return Le temps auquel le processus est terminé.
 */
int Processus::getFin() const {
    return m_fin;
}

/**
 * @brief Retourne la priorité du processus.
 * \return La priorité du processus.
 */
int Processus::getPriorite() const {
    return m_priorite;
}

/**
 * @brief Retourne le type du processus.
 * \return Le type du processus.
 */
TypeProcessus Processus::getType() const {
    return m_type;
}

// Mutateurs

/**
 * @brief Définit le temps restant du processus.
 * @param restant Temps restant à définir.
 * \pre restant >= 0 (le temps restant doit être non-négatif)
 * \post m_restant == restant
 */
void Processus::setRestant(int restant) {
    PRECONDITION(restant >= 0);
    m_restant = restant;
    POSTCONDITION(m_restant == restant);
    INVARIANTS();
}

/**
 * @brief Définit le temps d'attente du processus.
 * @param attente Temps d'attente à définir.
 * \pre attente >= 0 (le temps d'attente doit être non-négatif)
 * \post m_attente == attente
 */
void Processus::setAttente(int attente) {
    PRECONDITION(attente >= 0);
    m_attente = attente;
    POSTCONDITION(m_attente == attente);
    INVARIANTS();
}

/**
 * @brief Définit le temps de fin du processus.
 * @param fin Temps de fin à définir.
 * \pre fin >= 0 (le temps de fin doit être non-négatif)
 * \post m_fin == fin
 */
void Processus::setFin(int fin) {
    PRECONDITION(fin >= 0);
    m_fin = fin;
    POSTCONDITION(m_fin == fin);
    INVARIANTS();
}

/**
 * @brief Définit la priorité du processus.
 * @param priorite Priorité à définir.
 * \pre priorite >= 0 (la priorité doit être non-négative)
 * \post m_priorite == priorite
 */
void Processus::setPriorite(int priorite) {
    PRECONDITION(priorite >= 0);
    m_priorite = priorite;
    POSTCONDITION(m_priorite == priorite);
    INVARIANTS();
}

/**
 * @brief Surcharge de l'opérateur < pour comparer les priorités des processus.
 * @param autre Autre processus à comparer.
 * @return true si la priorité du processus actuel est inférieure à celle de l'autre processus.
 */
bool Processus::operator<(const Processus& autre) const {
    return m_priorite < autre.m_priorite;
}

/**
 * @brief Surcharge de l'opérateur == pour comparer les identifiants des processus.
 * @param autre Autre processus à comparer.
 * @return true si les identifiants des deux processus sont égaux.
 */
bool Processus::operator==(const Processus& autre) const {
    return m_pid == autre.m_pid;
}

/**
 * \brief Vérifie les invariants de la classe Processus.
 */
void Processus::verifieInvariant() const {
    INVARIANT(m_arrivee >= 0);
    INVARIANT(m_duree > 0);
    INVARIANT(m_restant >= 0);
    INVARIANT(m_attente >= 0);
    INVARIANT(m_fin >= 0);
    INVARIANT(m_priorite >= 0);
}
