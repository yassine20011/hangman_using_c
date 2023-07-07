# Jeu du PENDU

## Qu'est-ce que nous utilisons pour réaliser ce projet ?

- C language
- Makefile (pour complier le projet facilement)
- Git (on a utilisé Git pour stocker le projet sur GitHub)

## Structure du projet

- src/ : Contient tous les fichiers source
- include/ : Contient tous les fichiers d'en-tête
- bin/ : Contient le fichier exécutable
- resouces/ : Contient les fichiers de ressources (\*.txt)
- html/ : Contient un fichier html pour afficher les resulats du joueur et avoir un historique des parties.
- tests/ : Contient les fichiers de tests


## les bibliothèques utilisées

- stdio.h
- stdlib.h
- string.h
- time.h
- unistd.h
- json-c/json.h
- termios.h
- ncurses.h

## Prérequis

Pour pouvoir compiler et exécuter ce projet, vous devez avoir installé `Docker` dans votre système d'exploitation.

### Pourquoi Utiliser Ubuntu avec WSLg ?

Nous avons choisi d'utiliser Ubuntu avec WSLg pour la compilation et l'exécution du projet, car cela présente plusieurs avantages. Premièrement, c'est plus facile et plus rapide à configurer par rapport à d'autres options. De plus, nous pouvons utiliser le terminal de Windows 11 pour compiler et exécuter le projet, ce qui simplifie davantage le processus. Cela est particulièrement important dans notre jeu, car il y a des éléments sonores que nous ne pourrions pas entendre si nous utilisions le terminal d'Ubuntu.

## Avant de compiler et exécuter le projet ?

Vous devez un subSystem Linux (WSL) dans votre windows pour compiler et exécuter le projet.

Sinon, vous pouvez utiliser un autre système d'exploitation (Linux, Mac OS, etc.)

Pour installer un subSystem Linux (WSL) dans votre windows, vous pouvez suivre les étapes suivantes :

- Ouvrez PowerShell en tant qu'administrateur
- Exécutez la commande suivante :

```bash
wsl --install
```

Verifiez si ubuntu définir comme distribution par défaut :

```bash
wsl --list
```

Cette commande affichera les noms des distributions WSL installées ainsi que leur statut. Définissez Ubuntu comme distribution par défaut en exécutant la commande suivante :

```bash
wsl --set-default ubuntu
```

Remplacez ubuntu par le nom de la distribution Ubuntu tel qu'indiqué dans l'étape précédente. Cette commande définit la distribution spécifiée comme distribution par défaut pour WSL.

Vérifiez la distribution par défaut en exécutant la commande suivante :

```bash
wsl --list --verbose
```

Cette commande affichera les noms des distributions WSL installées ainsi que leur statut. La distribution par défaut sera marquée par un astérisque (\*).

Redémarrez votre ordinateur pour appliquer les modifications.

## Comment compiler et exécuter le projet ?

Vous avez avoir un lien vers le projet sur GitHub. Vous pouvez le cloner ou le télécharger.

### Pour cloner le projet :

- Ouvrez le terminal de Windows 11
- Exécutez la commande suivante pour cloner le projet :

```bash
git clone <lien vers le projet>
```

Après avoir cloné le projet, vous devez charger l'image Docker et exécuter le conteneur Docker à partir de l'image Docker chargée précédemment.

- Exécutez la commande suivante pour charger l'image Docker :

```bash
docker build -t mini-project.
```

- Exécutez la commande suivante pour exécuter le conteneur Docker à partir de l'image Docker chargée précédemment et montez le dossier `/mnt/wslg` dans le conteneur Docker pour accéder aux fichiers de votre sous-système Linux (WSL) dans Windows 11 (WSLg) :

```bash
wsl docker run -t -i -e "PULSE_SERVER=/mnt/wslg/PulseServer" -v \\wsl$\Ubuntu\mnt\wslg:/mnt/wslg/ mini-project
```

- Naviguez vers le dossier du projet

```bash
cd mini-project
```

- Exécutez la commande suivante pour compiler le projet

```bash
make
```

- Exécutez la commande suivante pour exécuter le projet

```bash
./bin/pendu
```

C'est mieux d'exécuter le projet en plein écran. Avec un terminal dehors votre IDE.


C'est tout. Amusez-vous bien !
