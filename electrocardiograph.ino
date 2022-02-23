// This program reads the incoming signal from the electrocardiograph and outputs the heart rate

// Pin D7 is connected to the signal input
// Pin D6 is connected to a mini-speaker
// For the connection to the liquid crystal display, see the LiquidCrystal Librairy

// External variables
const int  signal = 7; 
unsigned long time;   
unsigned long frequency;

// Internal variables
int period = 2000;
int starttime = 2000;
int input = 0;
int lastinput = 0;
unsigned long death = 0;

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  pinMode(signal, INPUT);
  lcd.createChar(1, heart);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.write(1);
  lcd.setCursor(1,0);
  lcd.print("    bpm : ");
  lcd.setCursor(0,1);
  // lcd.print("ALERT ");
}

void loop() {
  
  lcd.setCursor(1,0);
  time = millis();
  input = digitalRead(signal);

  if ((input != lastinput)&&(input == HIGH)) {
     period = time - starttime;
     starttime = time;
     death = time;
     tone(6,800,100);
  }
  lastinput = input; 

  if (period < 0) {
    frequency = 0;
  }
  else {
    frequency = 60000/period;
  }
  
  
  if ((time - death) > 2000) { 
    tone(6,900); 
    lcd.print("<60");
    lcd.setCursor(8,1);
    lcd.print("BRADYCARDIA");
  }
  
  else {
    char freq[3];
    
    if (frequency/100 == 0) {
      freq[0] = 32;
    } 
    else {
      freq[0] = frequency/100+48;
    }
    freq[1] = (frequency/10)%10+48;
    freq[2] = frequency%10+48;
    
    lcd.print(freq);
    lcd.setCursor(8,1);
    lcd.print("Normal Rate");
  }
    
}
