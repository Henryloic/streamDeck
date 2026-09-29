# Guide utilisateur — Stream deck

## 1. Présentation
![Premier prototype](20260929_074717.jpg)

Ce projet transforme un **SparkFun Pro Micro compatible ATmega32U4** en petit clavier de raccourcis USB à 8 boutons.

Lorsqu'un bouton est pressé, la carte envoie au PC une combinaison de touches comme un clavier USB classique : copier, couper, coller, sélectionner tout, lancer une commande ou piloter un logiciel.

> [!IMPORTANT]
> Utiliser une carte équipée d'un **ATmega32U4**. Un Arduino Uno ou un Nano classique ATmega328P ne peut pas utiliser directement `Keyboard.h` comme clavier USB natif.

---

## 2. Matériel nécessaire

- 1 carte SparkFun Pro Micro ou compatible ATmega32U4 ;
- 8 boutons poussoirs momentanés ;
- 1 câble USB compatible avec la carte ;
- fils de câblage ;
- 1 boîtier, imprimé en 3D ;
- 8 étiquettes ou capuchons identifiant les fonctions.

Aucune résistance externe n'est nécessaire : le programme active les résistances de tirage internes avec `INPUT_PULLUP`.

---

## 3. Câblage

Chaque bouton doit être connecté entre une entrée numérique et la masse commune `GND`.

| Bouton | Broche Pro Micro | Action actuelle |
|---:|---:|---|
| 1 | D2 | `Ctrl+C` |
| 2 | D3 | `Ctrl+X` |
| 3 | D4 | `Ctrl+V` |
| 4 | D5 | `Ctrl+Q` |
| 5 | D6 | Pavé numérique `3` |
| 6 | D7 | Pavé numérique `2` |
| 7 | D8 | Pavé numérique `1` |
| 8 | D9 | `F3` |

Schéma de principe pour chaque bouton :

```text
Broche numérique ─── bouton ─── GND
```

Avec `INPUT_PULLUP` :

```text
Bouton relâché : HIGH
Bouton appuyé  : LOW
```

---

## 4. Logiciels et bibliothèque

### Logiciel

- Arduino IDE ;
- paquet de cartes compatible avec le Pro Micro ;
- pilote USB de la carte si nécessaire sous Windows.

### Bibliothèque

Le programme utilise :

```cpp
#include <Keyboard.h>
```

La bibliothèque `Keyboard` est fournie avec l'environnement Arduino compatible ATmega32U4. Elle permet à la carte d'être reconnue comme un clavier USB HID.

Documentation officielle : [Arduino Keyboard](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/)

---

## 5. Configuration de l'Arduino IDE

Selon le paquet de cartes installé, sélectionner par exemple :

```text
Carte : SparkFun Pro Micro
Processeur : ATmega32U4 5 V / 16 MHz
Port : port COM associé à la carte
```

Si le profil SparkFun n'est pas installé, certains modèles compatibles peuvent être programmés avec un profil Arduino Micro ou Leonardo. Toujours vérifier la tension et la fréquence indiquées sur la carte.

> [!CAUTION]
> Une mauvaise sélection entre `5 V / 16 MHz` et `3,3 V / 8 MHz` peut empêcher le fonctionnement correct de l'USB ou compliquer le téléversement.

---

## 6. Téléversement

1. connecter le Pro Micro au PC ;
2. sélectionner la carte et le port ;
3. ouvrir le fichier `.ino` ;
4. compiler le programme ;
5. téléverser ;
6. tester les boutons dans un éditeur de texte sans document important ouvert.

Le Pro Micro est reconnu par le PC comme un clavier. Un raccourci envoyé par erreur peut donc agir immédiatement sur l'application active.

Si le port disparaît après un mauvais programme, effectuer rapidement deux appuis sur `RESET`, puis relancer le téléversement pendant la fenêtre du bootloader.

---

## 7. Fonctionnement du programme

Le tableau suivant définit les huit broches :

```cpp
const int pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
```

Le programme lit chaque bouton en boucle. Lorsqu'un passage de `HIGH` vers `LOW` est détecté, la fonction suivante est appelée :

```cpp
actionBouton(i);
```

Un anti-rebond logiciel de 30 ms évite qu'un seul appui soit interprété plusieurs fois :

```cpp
const unsigned long antiRebond = 30;
```

Après chaque raccourci, cette instruction libère toutes les touches :

```cpp
Keyboard.releaseAll();
```

---

## 8. Modifier un raccourci

### Exemple : copier

```cpp
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press('c');
Keyboard.releaseAll();
```

### Exemple : sélectionner tout

```cpp
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press('a');
Keyboard.releaseAll();
```

### Exemple : enregistrer

```cpp
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press('s');
Keyboard.releaseAll();
```

### Exemple : combinaison avec Maj

```cpp
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press(KEY_LEFT_SHIFT);
Keyboard.press('s');
Keyboard.releaseAll();
```

### Exemple : touche de fonction

```cpp
Keyboard.press(KEY_F5);
Keyboard.releaseAll();
```

---

## 9. Exemples de raccourcis courants

### Windows et logiciels généraux

| Fonction | Raccourci |
|---|---|
| Copier | `Ctrl+C` |
| Couper | `Ctrl+X` |
| Coller | `Ctrl+V` |
| Sélectionner tout | `Ctrl+A` |
| Enregistrer | `Ctrl+S` |
| Annuler | `Ctrl+Z` |
| Rétablir | `Ctrl+Y` |
| Rechercher | `Ctrl+F` |
| Nouvelle fenêtre | `Ctrl+N` |
| Fermer l'application | `Alt+F4` |
| Afficher le Bureau | `Windows+D` |
| Verrouiller le PC | `Windows+L` |

### Microsoft PowerPoint

| Fonction | Raccourci |
|---|---|
| Démarrer le diaporama depuis le début | `F5` |
| Démarrer depuis la diapositive actuelle | `Shift+F5` |
| Dupliquer l'objet sélectionné | `Ctrl+D` |
| Grouper les objets | `Ctrl+G` |
| Dissocier les objets | `Ctrl+Shift+G` |

### Microsoft Excel

| Fonction | Raccourci |
|---|---|
| Modifier la cellule active | `F2` |
| Répéter la dernière action | `F4` |
| Rechercher | `Ctrl+F` |
| Enregistrer | `Ctrl+S` |
| Insérer la date du jour | `Ctrl+;` |

### Visual Studio Code

| Fonction | Raccourci |
|---|---|
| Ouvrir la palette de commandes | `Ctrl+Shift+P` |
| Commenter ou décommenter une ligne | `Ctrl+/` |
| Rechercher dans le fichier | `Ctrl+F` |
| Rechercher dans le projet | `Ctrl+Shift+F` |
| Formater le document | `Shift+Alt+F` |
| Ouvrir le terminal | `` Ctrl+` `` |

### Navigateurs Web

| Fonction | Raccourci |
|---|---|
| Nouvel onglet | `Ctrl+T` |
| Fermer l'onglet | `Ctrl+W` |
| Rouvrir le dernier onglet fermé | `Ctrl+Shift+T` |
| Actualiser la page | `Ctrl+R` ou `F5` |
| Aller à la barre d'adresse | `Ctrl+L` |

> [!NOTE]
> Les raccourcis peuvent varier selon le logiciel, sa version, la langue du clavier et les personnalisations de l'utilisateur.

---

## 10. Exemple de configuration des 8 boutons

Configuration polyvalente proposée :

| Bouton | Fonction |
|---:|---|
| 1 | Copier `Ctrl+C` |
| 2 | Couper `Ctrl+X` |
| 3 | Coller `Ctrl+V` |
| 4 | Sélectionner tout `Ctrl+A` |
| 5 | Enregistrer `Ctrl+S` |
| 6 | Annuler `Ctrl+Z` |
| 7 | Rechercher `Ctrl+F` |
| 8 | Fonction personnalisée `F3` |

Exemple pour corriger le bouton 4 du programme :

```cpp
case 3:
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  Keyboard.releaseAll();
  break;
```

---

## 11. Remarques sur le code fourni

Les commentaires de certaines actions ne correspondent pas aux touches réellement envoyées :

- le bouton 2 envoie `Ctrl+X`, donc **Couper** ;
- le bouton 3 envoie `Ctrl+V`, donc **Coller** ;
- le bouton 4 envoie actuellement `Ctrl+Q`, pas `Ctrl+A` ;
- `KEY_KP_3`, `KEY_KP_2` et `KEY_KP_1` correspondent respectivement aux touches `3`, `2` et `1` du pavé numérique.

Il est conseillé de corriger les commentaires en même temps que la configuration des raccourcis.

---

## 12. Sécurité et dépannage

### Des touches se répètent

- augmenter légèrement `antiRebond`, par exemple à 50 ms ;
- contrôler les soudures ;
- vérifier que chaque bouton est relié entre sa broche et GND.

### Un bouton ne répond pas

- vérifier la continuité du bouton ;
- vérifier le numéro de broche ;
- tester la broche avec un programme simple et `Serial.println()`.

### Le PC reçoit des touches en continu

- débrancher immédiatement la carte ;
- vérifier qu'aucune entrée n'est reliée en permanence à GND ;
- vérifier que `Keyboard.releaseAll()` est bien appelé ;
- ajouter un interrupteur général d'activation HID pour sécuriser les essais.

### Le téléversement ne fonctionne plus

- utiliser le double reset pour ouvrir le bootloader ;
- sélectionner le nouveau port temporaire ;
- relancer immédiatement le téléversement.

---

## 13. Évolutions possibles

- ajouter des LED pour identifier les boutons ;
- ajouter un écran OLED ;
- créer plusieurs profils de raccourcis ;
- ajouter un bouton de changement de page ;
- utiliser des touches `F13` à `F24` avec un logiciel de remappage ;
- imprimer un boîtier et des touches personnalisées ;
- ajouter un interrupteur physique pour activer ou désactiver `Keyboard.begin()`.

---

## 14. Résumé

```text
Carte       : Pro Micro ATmega32U4
Entrées     : 8 boutons sur D2 à D9
Câblage     : bouton entre la broche et GND
Résistances : pull-up internes
USB         : clavier HID
Bibliothèque: Keyboard.h
Anti-rebond : 30 ms
```

Le projet constitue une base simple pour créer un Stream Deck ou un Macro Pad USB compact et entièrement personnalisable.
