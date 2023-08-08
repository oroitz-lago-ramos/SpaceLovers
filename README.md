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