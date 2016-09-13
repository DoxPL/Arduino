/* Gra Arduino
 *  Dox
 *  wersja 0.2
 */

#include "Keypad.h"
#include "LiquidCrystal.h"


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int pos = 16;
int enemy = 0;
int start = 0;
int score = 0;


byte character[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};
const byte ROWS = 3; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
};
byte rowPins[ROWS] = {8, 9, 10};
byte colPins[COLS] = {13, 12, 11};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void loop() {
  
 game();
 
}


void scoreboard() {
    //tablica wynikow
    lcd.setCursor(0, 0);
    lcd.print("Wynik: ");
    lcd.print(score);
}

void enemy_spawn() {
    //pojawianie sie przeciwnikow
   char key = keypad.getKey();
    while(pos > 0) {
      for(int i=1; i<=1; i++) {
      lcd.setCursor(0, 1);
      lcd.write((byte) 1);
      enemy = enemy+1;
      pos = pos-1;
      lcd.setCursor(pos, 1);
      lcd.print("@"); 
      hit();   
      delay(500);
      
      }   
      lcd.setCursor(15, 0);
      lcd.print("!"); 
      for (int j=1; j<=7; j++) {
      hit();
      }
      lcd.setCursor(15, 0);
      lcd.print(" ");
      delay(200);
      scoreboard();
      if(pos == 1) {   
    //koniec gry
      game_over(); 
      }
      }
        
}

void game_over() {
  //koniec gry
      pos = 0;
      start = start-1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Koniec gry!");
      lcd.setCursor(0, 1);
      lcd.print("Wynik: ");
      lcd.print(score);
      delay(5000);
      lcd.clear();  
      game();
      
}

void hit() {
    char key = keypad.getKey();
    lcd.setCursor(pos, 1);
    lcd.print(" ");    
    enemy = enemy-1;
    pos = pos+1; 
    score = score + 1;   
    }
}

void game() {
  char key = keypad.getKey();
  if(start == 0) {
  lcd.setCursor(0, 0); 
  lcd.print("Witaj w grze!");  
  lcd.setCursor(0, 1);
  lcd.print("Nac. przycisk...");
  }
  if(key != NO_KEY) {
    lcd.clear();
    start = start + 1; 
    pos = 16;
    score = 0;
    hit();
    scoreboard();
    enemy_spawn();
        switch (keypad.getState()){
        case PRESSED:
        if (key == '5') {
            hit();
        }
        break;

    }
  }


void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, character);
  char key = keypad.getKey();

  
}
