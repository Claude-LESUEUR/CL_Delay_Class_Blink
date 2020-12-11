
class Event {
  public:
    virtual void doEvent() = 0;
};

class Delay {
  public:
    void delay(unsigned long tempo, Event & act) {
      unsigned long before = millis();
      do {
        act.doEvent();
      } while ((unsigned long)(millis() - before) < tempo );
    }
} pause;

class Blink: public Event {
  private:
    unsigned long tempo;

  public:
    Blink(unsigned long tempo_): tempo(tempo_) {
      pinMode(LED_BUILTIN, OUTPUT);
    }

    void doEvent() {
      digitalWrite(LED_BUILTIN, (unsigned long)(millis() / tempo) % 2);
    }
};

Blink blinkEvent(250);

void setup() {
}

void loop() {
  pause.delay(5000, blinkEvent);
  delay(5000);

  blinkEvent.doEvent();
}
