# B-CPP-500-STG-5-1-babel-jean-baptiste.roesch

<!-- GETTING STARTED -->
## Pour commencer

EPITECH Project Babel 2021

### Les prérequis.

Une fois conan installé:
* conan
  ```sh
  mkdir build
  cd build
  conan install ..
  ```
Une fois CMAKE, gcc installés.
* création des binaires
  ```sh
  cmake ..
  ``` 
<!-- USAGE EXAMPLES -->
## Usage

* Utilisation du client
  ```sh
  make
  ./bin/babel_client
  ``` 
* Utilisation du serveur
  ```sh
  make
  ./bin/babel_server {PORT}
  ``` 

## PROTOCOLE BINAIRE TCP

### Légende tableau:
S = std::string; </br>
I = integer;
### Protocole:
| CODE| COMPORTEMENT | ARGUMENTS |
| :------------ |:---------------:|:-----:|
|       |
|      |
|      |
| `1XX`    | `Requetes au serveur`  |  |
|      |
|      |
|      |
| 100    | Se connecter  | [S: username, S: password] |
| 101    | Créer un compte  | [S: username, S: password] |
| 102    | Ajouter un ami  | [S: friendName, S: UserName] |
| 104    | Récuperer liste d'ami  | [S: UserName] |
| 105    | Démarre l'appel | [I: IdToCall] |
| 106    | Arreter l'appel actuel  | [ / ] |
| 107    | Propose un appel à un ami | [I: IdToCall] |
| 108    | Arrêter la demande d'appel | [I: IdToCall] |
|       |
|      |
|      |
| `2XX`    | `Réponses positive serveur`  |  |
|       |
|      |
|      |
| 200    | Compte bien crée  | / |
| 201    | Bien connecté  | / |
| 203    | Ami bien ajouté  | liste d'ami [{I:id, S:name}, {I:id, S:name}] |
| 204    | Liste d'amis  | liste d'ami [{I:id, S:name}, {I:id, S:name}] |
| 205    | Appel bien crée  | [I: PortRead, I: PortWrite, S:ipOther] |
| 206    | Appel terminé | / |
| 207    | Demande d'appel reçue | / |
|       |
|      |
|      |
| `4XX`    | `Réponses négatives serveur`  |  |
|       |
|      |
|      |
| 402    | Mauvais compte / MDP  | / |
| 403    | Compte déjà existant  | / |
| 404    | Utilisateur non trouvé  | / |
| 405    | Déjà amis  | / |
| 406    | Utilisteur indisponible | / |
|      |
|      |
|      |
| `3XX`    | `Evenements serveur`  |  |
|      |
|      |
|      |
| 302    | Cet utilisateur vous appelle  | [S: userName, I: userId] |
| 303    | Fin de la demande d'appel | / |
