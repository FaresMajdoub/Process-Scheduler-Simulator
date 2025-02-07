# Process-Scheduler-Simulator

## 📌 Description
Simulation d'ordonnancement de processus implémentant plusieurs algorithmes :  
- **FCFS (First Come First Served)**  
- **SJF (Shortest Job First)**  
- **Round Robin (RR)**  
- **Ordonnancement par Priorité**  
- **Ordonnancement Multiniveau**  

## 🏗️ Structure du projet
```
📂 **src/** - Fichiers sources  
  ├── `Processus.h` / `Processus.cpp` (Gestion des processus)  
  ├── `Ordonnanceur.h` / `Ordonnanceur.cpp` (Algorithmes)  
  ├── `simulateur.cpp` (Programme principal)  
  ├── `scenarios/` (Fichiers de tests)  
  └── `CMakeLists.txt` (Compilation)  
```


## 📊 Exemples
### ⚡ FCFS
```plaintext
P1 (24ms) → P2 (3ms) → P3 (3ms)
Temps d'attente moyen : 17ms
```
### ⚡ Round Robin (Quantum = 4ms)
```plaintext
P1 (4ms) → P2 (3ms) → P3 (3ms) → P1 (20ms)
Temps d'attente moyen : 4.25ms
```

## ✍️ Auteurs
**Fares Majdoub** - Université Laval, GLO-2100/IFT-2008  

## 📜 Licence
Sous licence **MIT**.
