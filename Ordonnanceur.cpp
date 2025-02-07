#include "ordonnanceur.h"
#include "ContratException.h"
#include <iostream>
#include <list>
#include <map>

/**
 * @brief ordonnanceur utilisant la méthode First Come First Served (FCFS).
 * @param f_entree file des processus à ordonnancer.
 * @param temps temps actuel de la simulation.
 * @return file des processus ordonnancés.
 */
File<Processus> TP::Ordonnanceur::fcfs(queue<Processus> f_entree, int& temps) {
    PRECONDITION(temps >= 0); // le temps ne peut pas être négatif

    queue<Processus> result; // file résultat
    while (!f_entree.empty()) {
        Processus p = f_entree.front(); // récupérer le premier processus
        f_entree.pop(); // retirer le processus
        p.setAttente(temps - p.getArrivee()); // calculer le temps d'attente
        POSTCONDITION(p.getAttente() >= 0); // le temps d'attente ne peut pas être négatif
        temps += p.getDuree(); // mettre à jour le temps global
        result.push(p); // ajouter le processus dans la file résultat
    }

    POSTCONDITION(!result.empty());
    return result;
}

/**
 * @brief ordonnanceur utilisant la méthode Shortest Job First (SJF).
 * @param f_entree file des processus à ordonnancer.
 * @param temps temps actuel de la simulation.
 * @return file des processus ordonnancés.
 */
File<Processus> TP::Ordonnanceur::fjs(queue<Processus> f_entree, int& temps) {
    PRECONDITION(temps >= 0);
    // transférer les processus dans une liste pour faciliter le tri
    list<Processus> liste_processus;
    while (!f_entree.empty()) {
        liste_processus.push_back(f_entree.front());
        f_entree.pop();
    }

    // trier d'abord par temps d'arrivée puis par durée
    liste_processus.sort([](const Processus& a, const Processus& b) {
        if (a.getArrivee() == b.getArrivee()) {
            if (a.getDuree() == b.getDuree()) {
                return a.getPid() < b.getPid(); // si les durées sont égales, priorité au pid
            }
            return a.getDuree() < b.getDuree(); // priorité à la plus courte durée
        }
        return a.getArrivee() < b.getArrivee(); // priorité au processus arrivé en premier
    });

    queue<Processus> result;
    list<Processus> file_attente; // processus disponibles à traiter, arrivés à l'instant actuel

    auto it = liste_processus.begin();
    while (it != liste_processus.end() || !file_attente.empty()) {
        // ajouter les processus disponibles à l'instant `temps`
        while (it != liste_processus.end() && it->getArrivee() <= temps) {
            file_attente.push_back(*it);
            it = liste_processus.erase(it);
        }

        // si la file d'attente est vide, avancer dans le temps au prochain processus
        if (file_attente.empty()) {
            temps = it->getArrivee(); // avancer le temps au prochain processus
            file_attente.push_back(*it);
            it = liste_processus.erase(it);
        }

        // trier les processus dans la file d'attente par durée
        file_attente.sort([](const Processus& a, const Processus& b) {
            if (a.getDuree() == b.getDuree()) {
                return a.getPid() < b.getPid(); // priorité au pid si égalité de durée
            }
            return a.getDuree() < b.getDuree(); // priorité à la plus courte durée
        });

        // prendre le premier processus de la file d'attente
        Processus p = file_attente.front();
        file_attente.pop_front();

        // calculer le temps d'attente et mettre à jour le temps
        p.setAttente(temps - p.getArrivee());
        POSTCONDITION(p.getAttente() >= 0);
        temps += p.getDuree();
        result.push(p);
    }

    POSTCONDITION(!result.empty());
    return result;
}

/**
 * @brief ordonnanceur utilisant la méthode Round Robin.
 * @param f_entree file des processus à ordonnancer.
 * @param quantum quantum de temps pour chaque processus.
 * @param temps temps actuel de la simulation.
 * @return file des processus ordonnancés.
 */
File<Processus> TP::Ordonnanceur::round_robin(queue<Processus> f_entree, int quantum, int& temps) {
    PRECONDITION(quantum > 0); // le quantum doit être positif
    PRECONDITION(temps >= 0);  // le temps ne peut pas être négatif

    queue<Processus> result;   // file des processus terminés
    map<string, int> temps_execution; // stocker le temps d'exécution total de chaque processus
    queue<Processus> attente_file; // file temporaire pour les processus en attente

    // initialiser la map avec un temps d'exécution de 0 pour chaque processus
    queue<Processus> copie_file = f_entree;
    while (!copie_file.empty()) {
        Processus p = copie_file.front();
        copie_file.pop();
        temps_execution[p.getPid()] = 0;
    }

    while (!f_entree.empty() || !attente_file.empty()) {
        // ajouter les processus arrivés dans la file d'attente
        while (!f_entree.empty() && f_entree.front().getArrivee() <= temps) {
            attente_file.push(f_entree.front());
            f_entree.pop();
        }

        if (!attente_file.empty()) {
            Processus p = attente_file.front();
            attente_file.pop();

            if (p.getRestant() > quantum) {
                // exécution partielle du processus (quantum non terminé)
                p.setAttente(max(temps - p.getArrivee() - temps_execution[p.getPid()], 0));
                temps_execution[p.getPid()] += quantum;
                temps += quantum;
                p.setRestant(p.getRestant() - quantum);
                attente_file.push(p); // réinsérer dans la file d'attente
            } else {
                // exécution complète du processus
                p.setAttente(max(temps - p.getArrivee() - temps_execution[p.getPid()], 0));
                temps_execution[p.getPid()] += p.getRestant();
                temps += p.getRestant();
                p.setRestant(0); // processus terminé
                result.push(p);  // ajouter à la file des résultats
            }
        } else {
            // avancer le temps si aucun processus n'est prêt à être exécuté
            if (!f_entree.empty()) {
                temps = f_entree.front().getArrivee();
            }
        }
    }

    POSTCONDITION(!result.empty());
    return result;
}

/**
 * @brief ordonnanceur utilisant la méthode par priorité.
 * @param f_entree file des processus à ordonnancer.
 * @param temps temps actuel de la simulation.
 * @return file des processus ordonnancés.
 */
File<Processus> TP::Ordonnanceur::priorite(queue<Processus> f_entree, int& temps) {
    PRECONDITION(temps >= 0); // le temps ne peut pas être négatif

    list<Processus> liste_processus;  // utiliser une liste pour trier facilement
    while (!f_entree.empty()) {
        liste_processus.push_back(f_entree.front());
        f_entree.pop();
    }

    // trier les processus par priorité décroissante
    liste_processus.sort([](const Processus& a, const Processus& b) {
        return a.getPriorite() > b.getPriorite();
    });

    queue<Processus> result;
    for (auto& p : liste_processus) {
        p.setAttente(temps - p.getArrivee()); // calculer le temps d'attente
        POSTCONDITION(p.getAttente() >= 0);
        temps += p.getDuree(); // mettre à jour le temps global
        result.push(p); // ajouter à la file résultat
    }

    POSTCONDITION(!result.empty());
    return result;
}

/**
 * @brief ordonnanceur utilisant la méthode par file multiniveaux.
 * @param f_entree file des processus à ordonnancer.
 * @param quantum quantum de temps pour les processus interactifs.
 * @param temps temps actuel de la simulation.
 * @return file des processus ordonnancés.
 */
File<Processus> TP::Ordonnanceur::multiniveaux(queue<Processus> f_entree, int quantum, int& temps) {
    PRECONDITION(quantum > 0); // le quantum doit être positif
    PRECONDITION(temps >= 0);  // le temps ne peut pas être négatif

    list<Processus> systeme, interactif, batch, utilisateur;

    // séparer les processus en différentes catégories
    while (!f_entree.empty()) {
        Processus p = f_entree.front();
        f_entree.pop();
        switch (p.getType()) {
            case SYSTEME:
                systeme.push_back(p);
                break;
            case INTERACTIF:
                interactif.push_back(p);
                break;
            case BATCH:
                batch.push_back(p);
                break;
            case UTILISATEUR:
                utilisateur.push_back(p);
                break;
        }
    }

    // file de résultat
    queue<Processus> result;

    // traiter les processus système (priorité décroissante)
    systeme.sort([](const Processus& a, const Processus& b) {
        return a.getPriorite() > b.getPriorite();
    });

    for (auto& p : systeme) {
        p.setAttente(temps - p.getArrivee());
        temps += p.getDuree(); // mettre à jour le temps après chaque exécution
        POSTCONDITION(p.getAttente() >= 0);
        result.push(p);
    }

    // traiter les processus interactifs avec Round Robin
    queue<Processus> file_interactif;
    for (auto& p : interactif) {
        file_interactif.push(p);
    }

    while (!file_interactif.empty()) {
        Processus p = file_interactif.front();
        file_interactif.pop();

        // calcul du temps d'attente
        if (p.getRestant() > quantum) {
            if (temps > p.getArrivee()) {
                p.setAttente(max(temps - p.getArrivee() - (p.getDuree() - p.getRestant()), 0));
            }
            temps += quantum;  // avancer le temps par quantum
            p.setRestant(p.getRestant() - quantum);  // réduire le temps restant du processus
            file_interactif.push(p);  // réinsérer dans la file pour le prochain tour
        } else {
            if (temps > p.getArrivee()) {
                p.setAttente(max(temps - p.getArrivee() - (p.getDuree() - p.getRestant()), 0));
            }
            temps += p.getRestant();
            p.setRestant(0);  // processus terminé
            result.push(p);
        }
    }

    // traiter les processus batch et utilisateur (priorité décroissante)
    batch.sort([](const Processus& a, const Processus& b) {
        return a.getPriorite() > b.getPriorite();
    });

    for (auto& p : batch) {
        p.setAttente(temps - p.getArrivee());  // calculer le temps d'attente
        temps += p.getDuree();  // avancer le temps après chaque exécution
        POSTCONDITION(p.getAttente() >= 0);
        result.push(p);
    }

    utilisateur.sort([](const Processus& a, const Processus& b) {
        return a.getPriorite() > b.getPriorite();
    });

    for (auto& p : utilisateur) {
        p.setAttente(temps - p.getArrivee());  // calculer le temps d'attente
        temps += p.getDuree();  // avancer le temps après chaque exécution
        POSTCONDITION(p.getAttente() >= 0);
        result.push(p);
    }

    POSTCONDITION(!result.empty());
    return result;
}
