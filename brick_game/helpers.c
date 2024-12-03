#include "tetris.h"

int* getStateHold() {
  static int hold = true;
  return &hold;
}

int* getStateCh() {
  static int ch = 0;
  return &ch;
}

int* getStatePosFigX() {
  static int startPositionPlayerX = 4;
  return &startPositionPlayerX;
}

int* getStatePosFigY() {
  static int startPositionPlayerY = 0;
  return &startPositionPlayerY;
}

GameInfo_t* getStateGameInfo() {
  static GameInfo_t gameInfo = {0};
  return &gameInfo;
}

UserAction_t* getStateAction() {
  static UserAction_t userAction = Start;
  return &userAction;
}

Fsm* getStateFsm() {
  static Fsm fsm = StartGame;
  return &fsm;
}

Figure* getFigure() {
  static Figure curFig = {0};
  return &curFig;
}

Figure* getNextFigure() {
  static Figure nextFig = {0};
  return &nextFig;
}

int* getRecord() {
  static int curRecord = 0;
  return &curRecord;
}

int* getHighRecord() {
  static int highRecord = 0;
  return &highRecord;
}