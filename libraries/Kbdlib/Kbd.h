#include <Arduino.h>
#include <Wire.h>

#ifndef Kbd_h
#define Kbd_h

enum State
{
  Idle,
  WaitRepeat,
  WaitDelay
};

class Kbd
{
public:
  static const int ROWS = 4;
  static const int COLS = 4;

private:
  long debounceTime;
  int repeatInterval;
  int delayInterval;
  bool keyAvailable;
  char key;
  unsigned long timer;

  int *rowPins;
  int *colPins;

  State btnState[ROWS][COLS];
  bool keyPressed[ROWS][COLS];
  long lastDebounce[ROWS][COLS];

  char charMatrix[ROWS][COLS] = {
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}};

  void setupPins();
  void updateState(int i, int j, State state);
  void getChar(int i, int j, bool input);
  void setChar(char ch) { key = ch; };
  void init();
  void scan();
  bool checkStates(State state);

public:
  Kbd(int rowPins[ROWS], int colPins[COLS]);

  char readKey();

  void setDebounceTime(long ms) { debounceTime = ms; };
  long getDebounceTime() { return debounceTime; };
  void setRepeatInterval(int ms) { repeatInterval = ms; };
  int getRepeaptInterval() { return repeatInterval; };
  void setDelayInterval(int ms) { delayInterval = ms; };
  int getDelayInterval() { return delayInterval; };
  State getBtnState(int i, int j) { return btnState[i][j]; };
  void setBtnState(int i, int j, State state) { btnState[i][j] = state; };
  bool isKeyPressed(int i, int j) { return keyPressed[i][j]; };
  void setKeyPressed(int i, int j, bool value) { keyPressed[i][j] = value; };
  long getLastDebounce(int i, int j) { return lastDebounce[i][j]; };
  long setLastDebounce(int i, int j, long value) { lastDebounce[i][j] = value; };
  bool isKeyAvailable() { return keyAvailable; };
  void setKeyAvailable(bool value) { keyAvailable = value; };
  char getKeyChar(int i, int j) { return charMatrix[i][j]; };
  void setTimer(long ms) { timer = ms; };
  long getTimer() { return timer; };
};

#endif
