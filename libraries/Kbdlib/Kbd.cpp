#include "Kbd.h"

Kbd::Kbd(int rowPins[Kbd::ROWS], int colPins[Kbd::COLS])
{
  setRepeatInterval(500);
  setDebounceTime(50);
  setDelayInterval(50);

  this->keyAvailable = false;
  this->timer = 0;

  this->rowPins = rowPins;
  this->colPins = colPins;

  setupPins();
  init();
}

void Kbd::init()
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      setBtnState(i, j, State::Idle);
      setKeyPressed(i, j, false);
      setLastDebounce(i, j, 0);
    }
  }
}

void Kbd::scan()
{
  for (int i = 0; i < COLS; i++)
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);

    for (int j = 0; j < ROWS; j++)
    {
      bool input = digitalRead(rowPins[j]);

      if (!input != isKeyPressed(i, j))
      {
        setLastDebounce(i, j, millis());
      }

      if ((millis() - getLastDebounce(i, j)) > getDebounceTime())
      {
        getChar(i, j, input);
      }

      setKeyPressed(i, j, !input);
    }

    digitalWrite(colPins[i], HIGH);
    pinMode(colPins[i], INPUT);
  }
}

void Kbd::getChar(int i, int j, bool input)
{
  if (!input && !checkStates(getBtnState(i, j)))
  {
    if (isKeyPressed(i, j) && getBtnState(i, j) == State::Idle)
    {
      updateState(i, j, State::WaitRepeat);
    }
    else if (getBtnState(i, j) == State::WaitRepeat && (millis() - getTimer()) > getRepeaptInterval())
    {
      updateState(i, j, State::WaitDelay);
    }
    else if (getBtnState(i, j) == State::WaitDelay && (millis() - getTimer()) > getDelayInterval())
    {
      updateState(i, j, State::WaitDelay);
    }
  }
  else
  {
    setBtnState(i, j, State::Idle);
  }
}

void Kbd::updateState(int i, int j, State state)
{
  setBtnState(i, j, state);
  setTimer(millis());
  setChar(getKeyChar(i, j));
  setKeyAvailable(true);
}

char Kbd::readKey()
{
  scan();
  if (isKeyAvailable())
  {
    setKeyAvailable(false);
    return this->key;
  }
  return '\0';
}

bool Kbd::checkStates(State state)
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (getBtnState(i, j) > state)
      {
        return true;
      }
    }
  }
  return false;
}

void Kbd::setupPins()
{
  for (int i = 0; i < ROWS; i++)
  {
    pinMode(rowPins[i], INPUT_PULLUP);
  }
}