/* Arduino Pudelka   
  * Autor: Dox  
  * http://programyarduino.blogspot.com  
  * Wersja 0.1  
  * LCD 16x2  
  * Keypad 4x4  
  */  
 #include <LiquidCrystal.h>  
 #include <Keypad.h>  
 LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  
 int start = 0;  
 int c_pos = 0;  
 int r_pos = 0;  
 int f_box_num = 1;  
 int s_box_num = 1;  
 long first_box;  
 long second_box;  
 int moves;  
//postac  
 byte character[8] = {  
  0b00100,  
  0b01010,  
  0b00100,  
  0b01110,  
  0b10101,   
  0b00100,  
  0b01010,  
  0b11011  
 };  
 //pudelko  
 byte box[8] = {  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111  
 };  
 //pole  
 byte field[8] = {  
  B11111,  
  B10001,  
  B10001,  
  B10001,  
  B10001,  
  B10001,  
  B10001,  
  B11111  
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
 void event() {  
  if(first_box == 15) {  
   f_box_num = 0;   
  }  
  if(second_box == 0) {  
   s_box_num = 0;  
  }  
  if(f_box_num == 0 && s_box_num == 0) {  
   win();  
  }  
 }  
 void win() {  
  lcd.clear();  
  lcd.setCursor(0, 0);  
  lcd.print("Wygrana :)");  
  lcd.setCursor(0, 1);  
  lcd.print("L. ruchow: ");  
  lcd.print(moves);  
  delay(3000);  
  f_box_num = 1;  
  s_box_num = 1;  
 }  
 void l_move_box() {  
  if(r_pos == 0) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    lcd.setCursor(first_box, r_pos);  
    lcd.print(" ");  
    first_box--;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    lcd.setCursor(first_box, r_pos);  
    lcd.write((byte) 0);    
  }  
   if(r_pos == 1) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    lcd.setCursor(second_box, r_pos);  
    lcd.print(" ");  
    second_box--;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    lcd.setCursor(second_box, r_pos);  
    lcd.write((byte) 0);    
  }  
 }  
 void r_move_box() {  
   if(r_pos == 0) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    lcd.setCursor(first_box, r_pos);  
    lcd.print(" ");  
    first_box++;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    lcd.setCursor(first_box, r_pos);  
    lcd.write((byte) 0);    
   }  
    if(r_pos == 1) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    lcd.setCursor(second_box, r_pos);  
    lcd.print(" ");  
    second_box++;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    lcd.setCursor(second_box, r_pos);  
    lcd.write((byte) 0);    
   }  
 }  
 void move_character() {  
  //akcje po nacisnieciu przyciskow  
  char key = keypad.getKey();  
  switch(keypad.getState()) {  
   case PRESSED:  
   if (key == '4') {  
    moves++;  
    if(c_pos>0) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    c_pos--;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    }  
    if(c_pos == first_box && r_pos == 0) {  
     l_move_box();  
    }  
    if(c_pos == second_box && r_pos == 1) {  
     l_move_box();  
    }  
   }  
   break;  
  }  
  switch(keypad.getState()) {  
   case PRESSED:  
    if (key == '6') {  
    moves++;  
    if(c_pos<15) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    c_pos++;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    }  
    if(c_pos == first_box && r_pos == 0) {  
     r_move_box();  
    }  
    if(c_pos == second_box && r_pos == 1) {  
     r_move_box();  
    }  
   }  
   break;  
  }  
  switch(keypad.getState()) {  
   case PRESSED:  
    if (key == '2') {  
    moves++;  
    if(r_pos==1) {  
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    r_pos--;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 1);  
    }  
   }  
   break;  
  }  
  switch(keypad.getState()) {  
   case PRESSED:  
    if (key == '8') {  
    moves++;  
    if(r_pos==0) {   
    lcd.setCursor(c_pos, r_pos);  
    lcd.print(" ");  
    r_pos++;  
    lcd.setCursor(c_pos, r_pos);  
    lcd.write((byte) 0);  
    }  
   }  
   break;  
  }  
 }  
 void create_box(){  
  //tworzenie pol  
  lcd.setCursor(15, 0);  
  lcd.write((byte) 2);  
  lcd.setCursor(0, 1);  
  lcd.write((byte) 2);  
  //tworzenie pudelek  
  lcd.setCursor(first_box, 0);  
  lcd.write(byte(0));  
  lcd.setCursor(second_box, 1);  
  lcd.write(byte(0));  
 }  
 void game() {  
  lcd.setCursor(c_pos, r_pos);  
  lcd.write((byte) 1);   
  create_box();  
  move_character();  
  event();  
 }  
 void setup() {  
  lcd.begin(16, 2);   
  randomSeed(analogRead(0));  
  lcd.createChar(0, box);  
  lcd.createChar(1, character);  
  lcd.createChar(2, field);  
  first_box = random(1, 10);  
  second_box = random(1, 10);  
 }  
 void loop() {  
  game();  
 }  