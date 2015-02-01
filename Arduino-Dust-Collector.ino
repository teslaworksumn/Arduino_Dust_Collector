/*
This script was created by Bob Clagett for I Like To Make Stuff
For more projects, check out iliketomakestuff.com

Parts of this sketch were taken from the keypad and servo sample sketches that comes with the keypad and servo libraries.
*/


#include <ctype.h>
#include <Servo.h>
#include <Keypad.h>

const byte servoCount = 10;
const int OPEN_ALL = 100;
const int CLOSE_ALL = 99;
const int openPos = 165;
const int closedPos = 5;

static Servo servoList[servoCount];
int servoPins[servoCount] = { A0, A1, A2, A3, A4, A5, 2, 3, 4, 5 };

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
// Define the keymaps.  The blank spot (lower left) is the space character.
char numberKeys[ROWS][COLS] = {
  { '1','2','3'   }
  ,
  { '4','5','6'   }
  ,
  { '7','8','9'   }
  ,
  { ' ','0','#'   }
};

int keypadRows[ROWS] = { 9,8,7,6 };
int keypadCols[COLS] = { 12,11,10 }; 

byte keypadRows_byte[ROWS] = { keypadRows[0], keypadRows[1], keypadRows[2], keypadRows[3] };
byte keypadCols_byte[COLS] = { keypadCols[0], keypadCols[1], keypadCols[2] };

// Create two new keypads, one is a number pad and the other is a letter pad.
Keypad numpad( makeKeymap(numberKeys), keypadRows_byte, keypadCols_byte, sizeof(keypadRows_byte), sizeof(keypadCols_byte) );

const byte ledPin = 13;  // Use the LED on pin 13.

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  pinMode(keypadRows[0], INPUT);
  pinMode(keypadRows[1], INPUT);
  pinMode(keypadRows[2], INPUT);
  pinMode(keypadRows[3], INPUT);
  
  pinMode(keypadCols[0], INPUT);
  pinMode(keypadCols[1], INPUT);
  pinMode(keypadCols[2], INPUT);

  pinMode(servoPins[0], OUTPUT);
  pinMode(servoPins[1], OUTPUT);
  pinMode(servoPins[2], OUTPUT);
  pinMode(servoPins[3], OUTPUT);
  pinMode(servoPins[4], OUTPUT);
  pinMode(servoPins[5], OUTPUT);
  pinMode(servoPins[6], OUTPUT);
  pinMode(servoPins[7], OUTPUT);
  pinMode(servoPins[8], OUTPUT);
  pinMode(servoPins[9], OUTPUT);
  
  numpad.begin( makeKeymap(numberKeys) );
  numpad.addEventListener(keypadEvent_num);  // Add an event listener.
  numpad.setHoldTime(500);                   // Default is 1000mS
  
  servoList[0].attach(servoPins[0]);
  servoList[1].attach(servoPins[1]);
  servoList[2].attach(servoPins[2]);
  servoList[3].attach(servoPins[3]);
  servoList[4].attach(servoPins[4]);
  servoList[5].attach(servoPins[5]);
  servoList[6].attach(servoPins[6]);
  servoList[7].attach(servoPins[7]);
  servoList[8].attach(servoPins[8]);
  servoList[9].attach(servoPins[9]);
  
 // setServoState(CLOSE_ALL); //reset all servos
}

char key;
static char virtKey = NO_KEY;      // Stores the last virtual key press. (Alpha keys only)
static char physKey = NO_KEY;      // Stores the last physical key press. (Alpha keys only)
static char buildStr[12];
static byte buildCount;
static byte pressCount;
static byte kpadState;

void loop() {
  key = numpad.getKey( );
}

void serialEvent() {
  while (Serial.available()) {
    key = Serial.read();
    kpadState = PRESSED;
    swOnState(key);
    kpadState = RELEASED;
  }
}

// Take care of some special events.
void setServoState(char number) {
  int thisServ = 0;
  int val;
  boolean ignoreAll = false;
  switch (number){
  case '1':
    val = 0;
    break;
  case '2':
    val = 1;
    break;
  case '3':
    val = 2;
    break;
  case '4':
    val = 3;
    break;
  case '5':
    val = 4;
    break;
  case '6':
    val = 5;
    break;
  case '7':
    val = 6;
    break;
  case '8':
    val = 7;
    break;
  case '9':
    val = 8;
    break;
  case '0':
    val = 9;
    break;
  default:
    val=number;
    break;
  }
  if(!ignoreAll){
    for(thisServ = 0; thisServ < servoCount; thisServ += 1){
      int newPos = 0;
      if(thisServ == val or val == OPEN_ALL){
        newPos = openPos;
      } 
      else {
        newPos = closedPos;
      }
      servoList[thisServ].write(newPos);
    }
  }
}

void keypadEvent_num( KeypadEvent key ) {
  // in here when using number keypad
  kpadState = numpad.getState();
  swOnState( key );

} // end numbers keypad events

void swOnState( char key ) {
  Serial.print("key = ");
  Serial.print(key);
  Serial.println();

  switch( kpadState ) {
  case PRESSED:

    if (isdigit(key) || key == ' ' || key == '.'){
      setServoState(key);
    }
    if (key == '#') {
      Serial.print("CLOSE ALL");
      Serial.println();
      setServoState(CLOSE_ALL);
    }
    if (key == ' ') {
      Serial.print("OPEN ALL");
      Serial.println();
      setServoState(OPEN_ALL);
    }
    break;
  case HOLD:
    if (key == '#')  {               // Toggle between keymaps.
    }
    else  {                          // Some key other than '#' was pressed.

    }
    break;

  case RELEASED:
    break;
  }  // end switch-case
}// end switch on state function



