#include "processus.h"
#include <queue>
using namespace std;

#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

template<typename T>
using File = std::queue<T>;
namespace TP {



    class Ordonnanceur {
    public:
        // Algorithme Premier Arrivé, Premier Servi (FCFS)
        static File<Processus> fcfs(queue<Processus> f_entree, int& temps);

        // Algorithme Plus Court d'abord (SJF)
        static File<Processus> fjs(queue<Processus> f_entree, int& temps);

        // Algorithme Round Robin (RR)
        static File<Processus> round_robin(queue<Processus> f_entree, int quantum, int& temps);

        // Algorithme d'ordonnancement par priorité
        static File<Processus> priorite(queue<Processus> f_entree, int& temps);

        // Algorithme d'ordonnancement à files d'attente multiniveaux
        static File<Processus> multiniveaux(queue<Processus> f_entree, int quantum, int& temps);

        void verifieInvariant() const;
    };

} // namespace TP

#endif // ORDONNANCEUR_H
