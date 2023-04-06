# AREA EPITECH

Création d'une plateforme d'actions réactions utilisant de multiples API

## Installation

Prérequis: - Avoir docker d'installé.
           - Avoir créer un fichier .env à la racine avec les valeurs valides (voir suite)
1. `sudo docker-compose build` Création des containers avec leur dépendences.
1. `sudo docker-compose up` Lancer le serveur, le web, et construire l'apk mobile.

## Environnement

/!\ IMPORTANT /!\

Si vous voulez utiliser le serveur en dehors de l'environnement docker, veuillez copier coller le .env dans la racine du dossier server et enlever les lignes en commentaire dans le fichier config.ts.

//import dotenv from 'dotenv'
//dotenv.config();

DB: Base de données

| Nom | Description | Type | Valeur par défaut |
|:----|:------------|:-----|:------------------|
| <span style="color: #FF5500; text-decoration: underline;">***BASE DE DONNEE***</span> | | | | 
| **POSTGRES_PASSWORD** | Mot de passe de la DB | `string` | 'postgres' | 
| **POSTGRES_USER** | Utilisateur de la DB | `string` | 'postgres' | 
| **POSTGRES_SCHEMA** | Nom de la DB | `string` | 'postgres' | 
| **POSTGRES_HOST** | Host de la DB | `string` | 'postgres' | 
| **POSTGRES_PORT** | Port de la DB| `number` | '5432' | 
| **APP_PORT** | Port de l'application | `number` | '8080' | 
| **JWT_SECRET** | Clé d'encryption pour les calls API | `string` | 'secret' | 
| **APP_HOST** | Url d'host de l'application | `string` | 'http://localhost' |
| **APP_DOMAIN_NAME** | Host de l'application mobile | `string` | 'com.area.app' |
| **ERASE_DB** | Permet de reset la db (true/false) | `string` | 'false' |
| **TWITCH_REDIRECT_URI** | Clé d'application API de league of legend | `string` | *Pas de valeur par défaut* |
| **TWITCH_CLIENT_ID** | Clé d'encryption pour les tokens de mail | `string` | *Pas de valeur par défaut* |
| **TWITCH_CLIENT_SECRET** | Nom de client de l'application Twitch | `string` | *Pas de valeur par défaut* |
| **TWITTER_REDIRECT_URI** | Lien de redirection de l'oauth twitter | `string` | *Pas de valeur par défaut* |
| **TWITTER_CLIENT_ID** | Client ID de l'oauth twitter | `string` | *Pas de valeur par défaut* |
| **TWITTER_CLIENT_SECRET** | Token secret de l'oauth twitter | `string` | *Pas de valeur par défaut* |
| **GITHUB_REDIRECT_URI** | Lien de redirection de l'oauth github | `string` | *Pas de valeur par défaut* |
| **GITHUB_CLIENT_ID** | Client id de github | `string` | *Pas de valeur par défaut* |
| **GITHUB_CLIENT_SECRET** | Token secret de l'oauth github | `string` | *Pas de valeur par défaut* |
| **GITHUB_STATE** | State de l'oauth github | `string` | *Pas de valeur par défaut* |
| **REDDIT_CLIENT_ID** | Client id de reddit oauth | `string` | *Pas de valeur par défaut* |
| **REDDIT_STATE** | State de l'oauth reddit | `string` | *Pas de valeur par défaut* |
| **REDDIT_CLIENT_SECRET** | Token secret de reddit | `string` | *Pas de valeur par défaut* |
| **REDDIT_REDIRECT_URI** | Lien de redirection reddit | `string` | *Pas de valeur par défaut* |
| **REDDIT_CLIENT_ID** | Client reddit | `string` | *Pas de valeur par défaut* |
| **REDDIT_STATE** | State reddit oauth | `string` | *Pas de valeur par défaut* |
| **TRELLO_LOGINCALLBACK** | Lien de redirection pour l'OAUTH Trello | `string` | *Pas de valeur par défaut* |
| **TRELLO_APPNAME** | Nom de l'application trello | `string` | *Pas de valeur par défaut* |
| **TRELLO_AUTHORIZE_URL** | Lien de redirection permettant l'access token trello | `string` | *Pas de valeur par défaut* |
| **TRELLO_ACCESS_URL** | Lien de redirection permettant l'access token trello | `string` | *Pas de valeur par défaut* |
| **TRELLO_REQUEST_URL** | Lien permettant d'avoir un token trello | `string` | *Pas de valeur par défaut* |
| **TRELLO_SECRET** | Secret token utilisé pour l'oauth trello | `string` | *Pas de valeur par défaut* |
| **TRELLO_TOKEN** | Token utilisé pour l'oauth trello | `string` | *Pas de valeur par défaut* |


Le reste de la documentation se trouve dans le dossier doc.
