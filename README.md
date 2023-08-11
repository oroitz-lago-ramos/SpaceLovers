Entity 
    Button(extends entity)
    InGameItem(extends entity)
        XpBoost (extends InGameItem)
        AttackBoost (extends InGameItem)
        DefenseBoost (extends InGameItem)
        SpeedBoost (extends InGameItem)
    Character(extends entity)
        Enemy (extends Character)
            Boss (extends Enemy)
        Projectile (extends Character)
        Player (extends Character)
Menu
Game
Level
Graphic


# Présentation d'un projet en C++

## Travail effectué en collaboration entre OroitzLR (https://github.com/OroitzLR), Dhjali (https://github.com/Dhjali), Sluchai40 (https://github.com/Sluchai40) grace au support de notre senseï Rle-ru (https://github.com/rle-ru).

### Premier jour de travail 07.08.2023

Découverte des bases du language C++, démarrage du projet.
Premier pas dans l'orienté objet

### 08.08.2023

Discution concernant les divers fonctionnalité necessaire a notre projet création d'un arbre des famille objet.
Trvail sur les différents objets que sont les Entity, Charaters et tous leurs enfants Enemy, Projectile, Player.
Fin de journée et but pour la suite du projet:
    - Oroitz calcul des attaques et dommages
    - Barbara calcul des collisions entre les projectiles et les ennemies.
    - Anthony recherche d'une solution pour les FPS

### 09.08.2023

Mise en place du travail effectué sur les time stamps dommages et collisions, c'est parti pour les nouveaux projet:
- Oroitz / Limiter la cadence de tir du joueur 
- Oroitz  / Projectile tiré par les ennemis avec cadence de tir (aléatoire (pour plus tard) ) beaucoup moins rapide de joueur
- Barbara / Page de menu et démarrage de partie
- Barbara / Mort du joueur = retour au menu

Anthony et Rodolphe reflexion sur la road map du jeu pour les 3 prochaines semaines:

Xp utilisable après la mort via un menu d'evolution

Arbre de compétences Vitesse:
    - Vitesse de déplacement 0 / 5 (augmentation à déterminer jusque * 3 max?)
    - Vitesse des projectiles 0 / 5
    - Déblocage d'un skill socket avec 1 emplacements (5 points de compétences necessaires)
        -
        -
        -
    - Ennemi transpercable 0 / 2
    - Déblocage d'un skill / arme légendaire (arbre de compétences spécifique a l'arme) (10 points de compétences necessaires)
        - Arme legendaire
        - Skill légendaire 1
        - Skill légendaire 2

Arbre de compétences Puissance:
    - Puissance de tir 0 / 5 (augmentation à déterminer)
    - Double Projectiles puis Triple projectiles 0 / 2
    - Déblocage d'un skill socket avec 1 emplacements (5 points de compétences necessaires)
        -
        -
        -
    - Largeur du projectile 0/2
    - Déblocage d'un skill / arme légendaire (arbre de compétences spécifique a l'arme) (10 points de compétences necessaires)
        - Arme legendaire
        - Skill légendaire 1
        - Skill légendaire 2

Arbre de compétences Defense:
    - Augmentation de la Défense 0 / 5 (augmentation à determiner)
    - Shield supplementaire 0 / 2
    - Déblocage d'un skill socket avec 1 emplacements (5 points de compétences necessaires)
        -
        -
        -
    - Réduction de la hit box
    - Déblocage d'un skill / arme légendaire (arbre de compétences spécifique a l'arme) (10 points de compétences necessaires)
        - Arme legendaire
        - Skill légendaire 1
        - Skill légendaire 2

Arbre de compétences inGame:
    - Augmentation du gain d'xp 0 / 5
    - Augmentation de la puissance des boosts 0 / 5 (+0.2 par niveau) (transforme le boost double projectile en triple)
    - Augmentation de la durée des boosts 0 / 5 (+ 2 sec par niveau)

Chaque niveau dure entre 1 à 2 min (de manière random) et le nombre d'ennemi est généré selon le temps que dure le niveau 
Gain d'xp par ennemi normal au level 1 = 1 xp avec un multiplicateur par level fois 0.1% par niveau diffuclté augmenté d'autant
Dans les 20 dernières secondes de chaque 10 eme level rencontre d'un boss les attribus sont 10 fois supérieur.

Boosts InGame:
    - PowerUp puissance * 1.5 pendant 10 sec
    - VitessUp vitesse * 1.5 pendant 10 sec
    - DefenseUp defense * 1.5 pendant 10 sec
    - Double Projectile pendant 10 sec 

Apres la mort on peut recommencer au lvl d'après n'importe quel boss vaincu

### 10.08.23 Oroitz, Rodolphe et Anthony

Ajout de differentes fonctionalités.

### 11.08.23 Oroitz, Rodolphe et Anthony

Validation de nombreuses fonctionnalités:
    - Augmentation du niveau de difficulté toutes les 60 secondes
    - Gain d'xp pour chaque ennemi tué
    - Création du visuel d'un arbre de compétences
    - Visuel plus complet de la fenetre de jeu avec timer + barre de vie + gain d'exp
    - Boost de gain de vie, bombe et d'autres

Objectif:
    - Implementation des boss
    - 

