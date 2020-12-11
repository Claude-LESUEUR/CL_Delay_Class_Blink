

// exemple de blink dans un delay non bloquant avec une injection de dépendance

// Event sert de clef d'entrée, elle doit rester telle quelle, c'est cette classe
// qui normalise la dépendance de Delay
// Delay est la classe qui execute l'objet hérité de Event le temps indiqué. c'est
// dans Delay qu'on injecte notre objet hérité de Event et qui contient le code injecté
// Blink est la classe "métier", vous pouvez vous en inspirer pour créer un
// code qui sera executé par Delay. le nom de classe "Blink" peut être changé.



// la classe Event est "abstraite" (vitual et =0) c'est elle qui sert de
// prototype à la classe qui contient le code à exécuter. elle permet de
// normaliser la dépendance
class Event {
  public:
    virtual void doEvent() = 0;
};

// la classe Delay a la responsabilité de lancer la fonction doEvent
// tant qu'elle le peut (et on instancie immédiatement l'objet "pause")
class Delay {
  public:
    void delay(unsigned long tempo, Event & act) {
      unsigned long before = millis();
      do {
        act.doEvent();
      } while ((unsigned long)(millis() - before) < tempo );
    }
} pause;// <- ici on instancie l'objet "pause" en même temps qu'on décrit la classe

// la classe Blink hérite de Event et c'est donc elle qui sera exécuté par
// l'instance "pause" de la classe Delay. elle contient la dépendance "doEvent()"
class Blink: public Event {
  private:
    unsigned long tempo;

  public:
    Blink(unsigned long tempo_): tempo(tempo_) {
      // on en profite pour initialiser le mode de la pin de la led embarqué
      pinMode(LED_BUILTIN, OUTPUT);
    }

    // le code exécuté par doEvent() sera répété tout le temps de la pause,
    // veillez donc a faire en sorte qu'il soit court à l'exécution car cela
    // influt sur la précision de durée de la pause
    void doEvent() {
      // bidouille rapide pour faire clignoter la led embarqué
      digitalWrite(LED_BUILTIN, (unsigned long)(millis() / tempo) % 2);
    }
};

// instanciation de la classe Blink dans l'objet blinkEvent avec 250
// comme parametre de clignotement
Blink blinkEvent(250);

void setup() {
  // vide: l'initialisation de la led émbarqué se fait dans le constructeur
  // de Blink
}

void loop() {
  // pause de cinq seconde avec un clignotetment actif
  pause.delay(5000, blinkEvent);
  // pause de cinq seconde sans clignotement possible : la led reste
  // dans l'état où elle est
  delay(5000);
  // on peut appeler l'objet Blink en dehors de Delay n'importe quand
  // sans perturber le fonctionnement du reste du programme car le contenu
  // d'un objet est isolé du reste du programme
  blinkEvent.doEvent();
}
