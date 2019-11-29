Arduino 4x4 keypad library

Description:
Library for Arduino 4x4 keypad. Uses four OUTPUT pins and four INPUT_PULLUP pins. Solved debounce, repeat interval, and repeat delay. If there were multiple key presses return first key pressed. Example code uses 16x2 display for demonstration.

Public:
enum State
	Button states. There is Three possible button states.
Idle: key is not pressed.
WaitRepeat: key is pressed and waits to expire repeat interval.
WaitDelay: key is pressed, repeat interval is expired and waits for delay interval to expire.

Kbd::Kbd(int rowPins[Kbd::ROWS], int colPins[Kbd::COLS])
	Constructor takes two arrays of length 4 with pin numbers for columns and rows.
Also in constructor are initialized default values for debounce time, repeat interval and repeat delay interval.

char Kbd::readKey()
	Scans keypad with void Kbd::scan(). If there is key available, sets key available to false and return corresponding key character. Otherwise return null terminator.

Private:
void Kbd::scan()
	Scans a keypad to check if there was key press. If key is pressed check if there was debounce and encode key character by calling void Kbd::getChar(int, int, bool).

void Kbd::getChar(int i, int j, bool input)
	If there were some input at corresponding row pin and State of pressed button is higher than State of other buttons, function updates Kbd object's state (void Kbd::updateState(int, int, State)) corresponding to current button state (bool Kbd::checkState(State state)). If there were no input or corresponding button is in lower state than some other button just sets button State to default.

void Kbd::updateState(int i, int j, State state)
	Updates Kbd's object state. Sets button state, timer, key char and sets keyAvailable to true.

bool Kbd::checkState(State state)
	Goes through buttons state matrix and checks if there is button with higher state. If finds any button with higher state return true, otherwise return false.

void Kbd::setupPins()
	Sets all row pins to INPUT_PULLUP.

void Kbd::init()
	Sets default values for buttonState, isKeyPressed and lastDebounceTime matrixes.



