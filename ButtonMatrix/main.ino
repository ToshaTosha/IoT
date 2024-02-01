const int buttonPin = 2; // кнопка на выводе 2

int buttonState; // текущее состояние вывода для кнопки
int lastButtonState = LOW; // предыдущее состояние вывода для кнопки

unsigned long lastDebounceTime = 0; // последнее время
unsigned long debounceDelay = 50; // задержка

void setup() {
    pinMode(buttonPin, INPUT);
}

void loop() {
int reading = digitalRead(buttonPin);

// если состояние изменилось (дребезг или нажатие)
if (reading != lastButtonState) {
    // сбрасываем таймер
    lastDebounceTime = millis();
}

if ((millis() - lastDebounceTime) > debounceDelay) {

    // если состояние кнопки изменилось
    if (reading != buttonState) {
        buttonState = reading;
    }
}

    lastButtonState = reading;
}