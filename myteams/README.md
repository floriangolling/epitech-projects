#  myTeams

Recréation d'un serveur teams et d'un client permettant la connexion et la communication avec le serveur.

## Installation

Prérequis:  gcc / clang / make
```bash
make
```

## Usage

```bash
./myteams_server 8080 => Lancement du serveur sur le port 8080 et l ip localhost("127.0.0.1")
./myteams_cli 127.0.0.1 8080 => Connexion d un client sur le serveur crée sur le port 8080 et sur l ip "127.0.0.1"
```

## Réponses du serveur.

| CODE| COMPORTEMENT | EXAMPLE DE COMMANDE |FORMAT DE REPONSE | STATUS | CONNEXION NECESSAIRE | 
| :------------ |:---------------:| -----:|:----------:|-----:|-----:|
| 220    | Client connecté | /login "user"|220 name id| OK| NON|
| 221      |Client déconnecté |   /logout |221  name id | OK| OUI|
| 222 | Réception de tout les utilisateurs | /users | 222 ;name;id;status | OK| OUI|
| 223    | Renvoi de le messages d'aide | /help |223 help | OK| OUI|
| 224      | Réception d'un messages d'un utilisateur       |  /send "user_id"|224 ;id;message | OK| NON|
| 225 | Réception de tout les messages d'un utilisateur       | /messages "user_id"|225 ;id;message;time | OK| OUI|
| 226    | Team bien créée (pour le créateur) | /create "name" "desc"| 226 id name status | OK| OUI|
| 227      | Evènement de création d'une team (tout le monde)        |/create "name" "desc"|227 ;id;name;desc | OK| OUI|
| 228 | Abonnement à une team réussi|/subscribe "team_id"|228 ;id;teamid | OK| OUI|
| 229    | Désabonnement à une team réussi |/unsubscribe "team_id"| 229 ;id;teamid | OK| OUI|
| 230      | Un client autre que vous s'est connecté       | /login "user"| 230 id name | OK| OUI|
| 231 | Un client autre que vous s'est déconnecté        |  /logout |231 id name | OK| OUI|
| 234    |Evènement de Channel crée (pour les utilisateurs abonnés à celui-ci) | /create "name" "desc"| 234 ;id;name;desc | OK| OUI|
| 235      | Evènement de Thread crée (pour les utilisateurs abonnés à celui-ci) | /create "name" "desc"|235 ;id;userid;time;title;body |OK| OUI|
| 236 | Evènement de réponse créée (pour les utilisateurs abonnés à celui-ci) | /create "reply"|236 ;teamid;threadid;userid;body | OK| OUI|
| 237    | Création du Channel réussie (pour le créateur)| /create "name" "desc" |237 ;id;name;desc | KO| OUI|
| 238      | Création du Thread réussie (pour le créateur)|/create "name" "desc"|238 ;id;userid;time;title;body | KO| OUI|
| 239 | Création de la réponse réussie (pour le créateur) | /create "reply"|239 ;teamid;threadid;userid;body | KO| OUI|
| 400| Commande non connue | /?| 400 | KO| NON|
| 404 | Utilisateur non connu | /user "userid"|404| KO| OUI|
| 501 | Message trop long | /create "reply"| 501 Too long body | KO| NON|
| 502 | ID non connu | /user "id"| 502 id| KO| OUI|
| 503 | Pas assez d'arguments | /create| 503 | KO| OUI|
| 504 | Pas autorisé (doit être connecté) | /create "reply"| 504 | KO| NON|
| 506 | Existe déjà | /create "name" "desc"| 506 | KO| OUI|
| 507 | ID de team non connu | /subscribe "id"| 507 ID | KO| OUI|
| 508| Déjà abonné | /subscribe "id"| 508 | KO| OUI|
| 509 | Pas abonné | /create "reply"| 509 | KO| OUI|
| 510 | ID de Channel non connu | /create "reply"| 510 id | KO| OUI|
| 511 | ID de Thread non connu | /create "reply"| 511 id | KO| OUI|

EXEMPLE DE CONNEXION:

```bash
 /login "florian"
```
