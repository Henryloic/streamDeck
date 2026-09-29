// Stream Deck / Macro Pad avec ATmega32U4 (SparkFun Pro Micro)
// 8 boutons -> raccourcis clavier envoyés au PC via USB HID
//
// Cablage : chaque bouton entre sa pin et la masse commune (GND)
// Pull-up interne activee -> HIGH au repos, LOW quand presse

#include <Keyboard.h>

const int nbBoutons = 8;
const int pins[nbBoutons] = {2, 3, 4, 5, 6, 7, 8, 9}; // adapte selon ton cablage

bool etatPrecedent[nbBoutons];
unsigned long dernierAppui[nbBoutons];
const unsigned long antiRebond = 30; // ms

void setup() {
  for (int i = 0; i < nbBoutons; i++) {
    pinMode(pins[i], INPUT_PULLUP);
    etatPrecedent[i] = HIGH;
    dernierAppui[i] = 0;
  }

  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < nbBoutons; i++) {
    bool etat = digitalRead(pins[i]);

    if (etat != etatPrecedent[i] && (millis() - dernierAppui[i]) > antiRebond) {
      dernierAppui[i] = millis();
      etatPrecedent[i] = etat;

      if (etat == LOW) {
        // Bouton presse -> declenche l'action correspondante
        actionBouton(i);
      }
    }
  }
}

// Definit ici l'action de chaque bouton (index 0 a 7)
void actionBouton(int index) {
  switch (index) {
    case 0:
      // Exemple : Copier (Ctrl+C)
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      Keyboard.releaseAll();
      break;

    case 1:
      // Exemple : Coller (Ctrl+X)
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('x');
      Keyboard.releaseAll();
      break;

    case 2:
      // Exemple : Copier (Ctrl+V)
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      Keyboard.releaseAll();
      break;

    case 3:
      // Exemple : Coller (Ctrl+A)
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('q');
      Keyboard.releaseAll();
      break;

    case 4:
      // Exemple : ctrl+Shift+end)
      Keyboard.press(KEY_KP_3); // touche "1" du pavé numérique
      Keyboard.releaseAll();
      break;

    case 5:
      // Exemple : 
      Keyboard.press(KEY_KP_2); // touche "1" du pavé numérique
      Keyboard.releaseAll();
      break;

    case 6:
      Keyboard.press(KEY_KP_1); // touche "1" du pavé numérique
      Keyboard.releaseAll();
      break;

    case 7:
      Keyboard.press(KEY_F3);
      Keyboard.releaseAll();
      break;
  }
}
