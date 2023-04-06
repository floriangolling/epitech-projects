# DASHBOARD EPITECH

Création d'un dashboard utilisant de multiples API pour avoir des informations en temps réel sous nos yeux.

## Installation

Prérequis: - Avoir docker d'installé.
           - Avoir créer un fichier .env à la racine avec les valeurs valides (voir suite)
1. `sudo docker-compose build` Création des containers avec leur dépendences.
1. `sudo docker-compose up` Lancer le serveur.

## Environnement

DB: Base de données

| Nom | Description | Type | Valeur par défaut |
|:----|:------------|:-----|:------------------|
| <span style="color: #FF5500; text-decoration: underline;">***BASE DE DONNEE***</span> | | | | 
| **POSTGRES_PASSWORD** | Mot de passe de la DB | `string` | 'postgres' | 
| **POSTGRES_USER** | Utilisateur de la DB | `string` | 'postgres' | 
| **POSTGRES_SCHEMA** | Nom de la DB | `string` | 'postgres' | 
| **POSTGRES_HOST** | Host de la DB | `string` | 'postgres' | 
| **POSTGRES_PORT** | Port de la DB| `number` | '5432' | 
| <span style="color: #FF5500; text-decoration: underline;">***APPLICATION***</span> | | | | 
| **PORT** | Port de l'application | `number` | '8080' | 
| **JWT** | Clé d'encryption pour les calls API | `string` | *Pas de valeur par défaut* | 
| **HOST** | Url d'host de l'application | `string` | 'localhost' |
| **LEAGUE_API_KEY** | Clé d'application API de league of legend | `string` | *Pas de valeur par défaut* |
| **JWT_EMAIL_SECRET** | Clé d'encryption pour les tokens de mail | `string` | *Pas de valeur par défaut* |
| **TWITCH_CLIENT_ID** | Nom de client de l'application Twitch | `string` | *Pas de valeur par défaut* |
| **TWITCH_CLIENT_SECRET** | Mot de passe de l'application Twitch | `string` | *Pas de valeur par défaut* |
| **TWITCH_REDIRECT_URI** | Lien de redirection pour l'OAUTH Twitch | `string` | *Pas de valeur par défaut* |

## Comment rajouter un service ?

1. Aller dans le dossier server => src => services
2. Créer un nouveau fichier .js (ex: leNomDuService.js)
3. Créer une nouvelle classe qui hérite de l'interface des classes exemple:``` class myService extends require('./interfaces').Service("LeNomDuService", "urldelogo")```
4. Si vous utilisez une clé d'API ou un client (librarie pour communiquer à l'API), donnez la à la classe en faisant ```votreClasse.setClient(votreClient)```
5. Pensez bien à require ce nouveau service dans le index.js au même niveau que votre service, et de la rajouter dans la nouvelle liste de service du index.js !
6. Voila votre service est créer, il suffit juste de lui rajouter des Widgets maintenant ! 

## Comment rajouter un Widget à un service.

1. Aller dans le fichier de votre service.
2. Créer une nouvelle classe comme pour le service, mais avec un Widget. exemple: ```class myWidget extends require('./interfaces').Widget```
3. Dans cette nouvelle classe, redéfinissez la fonction callThisWidget.
4. Cette fonction reçoit jusqu'à 3 arguments selon le type de service, 1. son client 2. le paramètre de la requête, 3. le code d'accès OAUTH de l'utilisateur actuel.
5. Maintenant à l'aide de ces arguments, il vous suffit dans cette fonction de récuperer les informations qui vous sont utiles (ex le temps à un paramètre donné) de faire votre requète, et de return l'affichage du widget dans la fonction exemple: ```return(`<div> ceQueJeVeuxAfficher </div>`)```
6. Maintenant une fois la méthode construire, il vous suffit de créer votre widget en grace à votre nouvelle classe en lui donnant en paramètre, son nom, sa déscription, le nom de son paramètre, et le type de son paramètre ! ex: ```const myCreatedWidget = new myWidget('nom', 'description', 'nom du param', 'le type de param')``` !
7. Maintenant, pour qu'il soit actif, il suffit de le donner à votre interface en faisant : ```VotreInterface.addWidget(votreWidget)```

## Architecture du projet

(Veuillez regarder les diagrames dans le dosser /doc pour mieux comprendre l'architecture et ou chercher vos fichiers !)

### client (Visuel)
##### client/components
Dossier comprenant tout les fichiers .vue qui sont des components réutilisables.
##### client/assets
Dossier comprenant les fonts/images/musique etc..
##### client/views
Dossier comprenant toutes les pages accessibles, qui utilisent des components du dossier components.
##### client/router
Dossier comprenant le fichier qui permet de gérer les différentes routes à afficher et leur autorisations.
##### client/store
Dossier comprenant le state global de l'application (valeurs gardées sur toutes les pages)
##### client/locales
Dossier comprenant les différentes traductions de i18n
##### client/App.vue
Fichier .vue dans lequel est injecté tout le reste du site grâce au router.
##### client/i18n.js
Fichier permettant la gestion des langues.
##### client/main.js
Fichier permettant l'utilisation de librairies dans votre application vue.js
    
### server
##### server/src/api
Dossier dans lequel se trouve toutes les différentes routes d'API
##### server/src/database
Dossier dans lequel se trouve l'instance de sequelize et son initialisation
##### server/src/database/models
Dossier dans lequel se trouve tout les différents modeles de la DB
##### server/src/oauth
Dossier dans lequel se trouve les différentes instances de OAUTH
##### server/src/services
Dossier dans lequel se trouve les différentes instances de services
##### server/src/services
Dossier dans lequel se trouve les différentes instances de services et leur widgets
##### server/src/config.js
Un fichier contenant la configuration globale de l'application utilisant les variables d'environnement
##### server/src/index.js
le fichier principal au serveur, c'est lui qui appele tout les autres dans le bon ordre afin de lancer l'application
##### server/src/swagger.js
fichier permettant de récuperer les infos commentaires de swagger afin de créer la route /api/api-docs

## Comment utiliser le dashbaord.

Veuillez vous connecter en créant un compte / ou vous connectant en utilisant un oauth (ex: twitch).

Une fois connecté, il ne vous reste plus qu'à créer vos widgets depuis le bouton Ajouter un widget (page dashboard)
De le configurer comme vous le souhaitez et ensuite utiliser l'outil afin de retrouver vos informations préférées en temps réel !

# BONUS

- i18n
- SWAGGER
- Gestion de comptes par mail
- Oubli de mot de passe
- Connexion / Création de compte par OAUTH
