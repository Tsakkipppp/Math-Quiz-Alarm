#include <LiquidCrystal.h>
#include <Keypad.h>
#define BUZZER_PIN 13
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);


unsigned long previousMoment = 0;
const long interval = 1000;
int seconds = 10;
const byte ROWS = 4;
bool waitingForAnswer = true;
bool lcdState = true;
const byte COLUMNS = 4;
char keys[ROWS][COLUMNS] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowPin[ROWS] = {2, 3, 4, 5};
byte colsPin[COLUMNS] = {6, 7, 8, 9};
int num1, num2, answer;
int score = 0;
char inputBuffer[5];
byte index = 0;
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colsPin, ROWS, COLUMNS);
enum GameState { QUIZ_MODE, CONGRATS_MODE, ALARM_MODE };
GameState currentState = ALARM_MODE;


void waitForKey(char targetKey){
  char key = NO_KEY;
  while (key != targetKey){
    key = keypad.getKey();
  }
}

void generateQuestion() {
  num1 = random(1, 12);
  num2 = random(1, 12);
  answer = num1 * num2;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(num1);
  lcd.print(" x ");
  lcd.print(num2);
  lcd.print(" = ?");
  index = 0;
  inputBuffer[0] = '\0';
}

void getAnswer() {
  char key = keypad.getKey();
  if (key >= '0' && key <= '9') {
    if (index < 4) {
      inputBuffer[index] = key;
      index++;
      inputBuffer[index] = '\0';
      lcd.setCursor(0, 1);
      lcd.print(inputBuffer);
    }
  }

  if (key == '#') {
    int userAnswer = atoi(inputBuffer);
    lcd.clear();
    if (userAnswer == answer) {
      lcd.print("Correct!");
      score++;
    } else {
      lcd.print("Wrong!");
    }
    delay(2000);
    generateQuestion();  // Next question
  }

  if (key == '*') {
    index = 0;
    inputBuffer[0] = '\0';
    lcd.setCursor(0, 1);
    lcd.print("                ");  // Clear line manually
    lcd.setCursor(0, 1);
  }
}


void timerClock() {
  unsigned long currentMoment = millis();
  if (currentMoment - previousMoment >= 1000) {
    previousMoment += 1000;
    int minutes = seconds / 60;
    int secs = seconds % 60;

    if (seconds <= 0) {
      lcd.setCursor(0, 0);
      lcd.print("00:00");
      tone(BUZZER_PIN, 1000);
      generateQuestion();
      currentState = QUIZ_MODE;
    } else {
      lcd.setCursor(0, 0);
      if (minutes < 10) {
        lcd.print("0");  // Print leading zero
      }
      lcd.print(minutes);
      lcd.setCursor(2, 0);
      lcd.print(":");
      lcd.setCursor(3, 0);
      if (secs < 10) {
        lcd.print("0");  // Print leading zero
      }
      lcd.print(secs);
    }
    seconds--;
  }
}

void setup() {
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
}

void loop() {
  switch(currentState){
    case QUIZ_MODE:
    getAnswer();
    if(score == 3){
      currentState = CONGRATS_MODE;  
    }
    break;
    case CONGRATS_MODE:
    if(lcdState){
      lcd.clear();
      lcd.print("WAKE UP BRO!");
      noTone(BUZZER_PIN);
      lcdState = false;
    }
    break;
    case ALARM_MODE:
    timerClock();
    break;
  }
}

