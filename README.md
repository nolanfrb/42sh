# 42sh

## 🧠 Description

**42sh** est un projet de shell Unix avancé inspiré du comportement de `tcsh`, développé dans le cadre du cursus de l'École Epitech. Il constitue une suite directe aux projets `minishell`, avec pour objectif de créer un shell stable, puissant et compatible avec les principales fonctionnalités d’un shell moderne.

Le projet a été réalisé par une équipe de 4 étudiants :

- **Nolan**
- **Lukas**
- **Loann**
- **Yannis**

## ⚙️ Compilation

Le shell se compile à l’aide d’un `Makefile` standard, avec les règles suivantes :

- `make` : compile le binaire `42sh`
- `make clean` : supprime les fichiers objets
- `make fclean` : supprime les fichiers objets **et** le binaire
- `make re` : relance une compilation complète

## 🧪 Fonctionnalités principales

Voici la liste des fonctionnalités implémentées dans le shell `42sh` :

### 🔡 Syntaxe et parsing
- **Inhibiteurs** : `' '` (guillemets simples)
- **Globbing** : `*`, `?`, `[ ]`
- **Backticks** : `` `command` ``

### 🧵 Job control
- Lancement en arrière-plan avec `&`
- Commandes `fg`, `bg`

### 🧠 Variables
- Variables d’environnement et locales
- Variables spéciales (`$term`, `$cwd`, `$precmd`, etc.)

### 📜 Historique
- Rappel avec `!` (ex: `!ls`)

### 🧩 Alias
- Exemple : `alias ll="ls -l"`

### ✍️ Édition de ligne
- Multilignes
- Rebind dynamique des touches
- Auto-complétion

### 🧬 Parenthèses
- Gestion des sous-shells avec `(` et `)`

### 🧠 Script
- Support basique de scripts shell

## 🧰 Fonctions autorisées

Vous pouvez utiliser toutes les fonctions de la **libC** ainsi que celles de la **librairie ncurses**.

## 🧪 Recommandations

- Écrire des **tests unitaires** à chaque ajout de fonctionnalité.
- Utiliser **Git** activement (branches, commits fréquents, historique propre).
- Veiller à la **stabilité** avant d’ajouter de nouvelles fonctionnalités.
- Travailler en équipe efficacement : partage de connaissance, revue de code, entraide.

## 🏅 Bonus

Les bonus peuvent inclure toute fonctionnalité additionnelle tant qu’elle respecte la cohérence globale du projet. Un répertoire `bonus/` est dédié à cela.

---

> Projet réalisé dans le cadre du module `B-PSU-200` de l'École Epitech.
