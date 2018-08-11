#include <Keypad.h>
#include "Keyboard.h"
const byte ROWS = 7; //four rows
const byte COLS = 8; //four columns
byte rowPins[ROWS] = {15, 18, 16, 19, 28, 31, 30}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 4, 5, 6, 7, 8, 9, 14}; //connect to the column pinouts of the keypad
//define the cymbols on the buttons of the keypads
char directKeys[ROWS][COLS] = {
  {'`', '1', '2', '3', '4', '5', '6', 1},
  {KEY_ESC, 'q', 'w', 'e', 'r', 't', 'y', ';'},
  {'[', 'a', 's', 'd', 'f', 'g', 'h', 39}, //39 is '
  {']', 'z', 'x', 'c', 'v', 'b', 'n', '-'},
  {'7', '8', '9', '0', KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_UP_ARROW},
  {'u', 'i', 'o', 'p', '.', '/', ' ', '='},
  {'j', 'k', 'l', KEY_BACKSPACE, 'm', 92, KEY_RETURN, ','}
};
char shiftKeys[ROWS][COLS] = {
  {'~', '!', '@', '#', '$', '%', '^', 1},
  {KEY_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', ';'},
  {'{', 'A', 'S', 'D', 'F', 'G', 'H', 34}, //34 is "
  {'}', 'Z', 'X', 'C', 'V', 'B', 'N', '_'},
  {'&', '*', '(', ')', KEY_PAGE_DOWN, KEY_END, KEY_HOME, KEY_PAGE_UP},
  {'U', 'I', 'O', 'P', '>', '?', ' ', '+'},
  {'J', 'K', 'L', KEY_DELETE, 'M', 92, KEY_RETURN, ','}
};
char fnKeys[ROWS][COLS] = {
  {'`', KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, 1},
  {KEY_ESC, 'q', 'w', 'e', 'r', 't', 'y', ';'},
  {'[', 'a', 's', 'd', 'f', 'g', 'h', 39}, //39 is '
  {']', 'z', 'x', 'c', 'v', 'b', 'n', '-'},
  {KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_UP_ARROW},
  {'u', 'i', 'o', 'p', '.', '/', ' ', '='},
  {'j', 'k', 'l', KEY_BACKSPACE, 'm', 92, KEY_RETURN, ','}
};
char capsKeys[ROWS][COLS] = {
  {'`', '1', '2', '3', '4', '5', '6', 1},
  {KEY_ESC, 'Q', 'W', 'E', 'R', 'T', 'Y', ';'},
  {'[', 'A', 'S', 'D', 'F', 'G', 'H', 39}, //39 is '
  {']', 'Z', 'X', 'C', 'V', 'B', 'N', '-'},
  {'7', '8', '9', '0', KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_UP_ARROW},
  {'U', 'I', 'O', 'P', '.', '/', ' ', '='},
  {'J', 'K', 'L', KEY_BACKSPACE, 'M', 92, KEY_INSERT, ','}
};

// Create 3 new key layouts
Keypad directLayout( makeKeymap(directKeys), rowPins, colPins, sizeof(rowPins), sizeof(colPins) );
Keypad shiftLayout( makeKeymap(shiftKeys), rowPins, colPins, sizeof(rowPins), sizeof(colPins) );
Keypad fnLayout( makeKeymap(fnKeys), rowPins, colPins, sizeof(rowPins), sizeof(colPins) );
Keypad capsLayout( makeKeymap(capsKeys), rowPins, colPins, sizeof(rowPins), sizeof(colPins) );
byte Layout = 0;
char Key = 0;
#define ledaA 27
#define ledFn 17
void setup() {
  Keyboard.begin();
  pinMode(ledaA, OUTPUT);
  pinMode(ledFn, OUTPUT);
  digitalWrite(ledaA, LOW);
  digitalWrite(ledFn, LOW);
  directLayout.begin( makeKeymap(directKeys) );
  shiftLayout.begin( makeKeymap(shiftKeys) );
  fnLayout.begin( makeKeymap(fnKeys) );
  capsLayout.begin( makeKeymap(capsKeys) );
}

void loop() {
  switch (Layout) {
    case 0:
      digitalWrite(ledaA, LOW);
      digitalWrite(ledFn, LOW);
      Key = directLayout.getKey();
      break;

    case 1:
      digitalWrite(ledaA, HIGH);
      digitalWrite(ledFn, LOW);
      Key = shiftLayout.getKey();
      if (Key >= 2) {
        Layout = 0;
      }
      break;

    case 2:
      digitalWrite(ledaA, LOW);
      digitalWrite(ledFn, HIGH);
      Key = fnLayout.getKey();
      if (Key >= 2) {
        Layout = 0; //
      }
      if (Key == KEY_RETURN)
      {
        Keyboard.press(KEY_LEFT_SHIFT);
      }
      if ((Key >= 'a') && (Key <= 'z'))
      {
        Keyboard.press(KEY_LEFT_CTRL);
      }
      break;

    case 3:
      digitalWrite(ledaA, HIGH);
      digitalWrite(ledFn, HIGH);
      Key = capsLayout.getKey();
      break;
    default:
      Layout = 0;
      break;
  }
  if (Key == 1)
  {
    Layout++;
    Key = 0;
    delay(300); // teraz mozem mal!23!{}
  }

  if (Key) {
    //  Keyboard.press(ctrlKey);
    Keyboard.press(Key);
    delay(100);
    Keyboard.releaseAll();
  }
}
