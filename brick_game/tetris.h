#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum { StartGame, Spawn, Moving, Shifting, Attaching, GameOver } Fsm;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int widthFigure;
  int heightFigure;
  int startX;
  int startY;
  int** figure;
} Figure;

void createGameZone();
void printGameZone();
void createGame();
void userInput(UserAction_t action, bool hold);
void putAction();
Figure* drawFigure(int width, int height, Figure* figure);
void clearMemoryFigure(Figure* figure);
void putFigureInGameZone(Figure* figure, int startPositionPlayerX,
                         int startPositionPlayerY);
void isOutBorder(Figure* figure);
Figure* randomFigure(Figure* figure);
void figureClear(GameInfo_t* gameInfo, Figure* figure);
Figure* rotateFigure();
bool isCollision(int startPositionPlayerX, int startPositionPlayerY,
                 Figure* figure, GameInfo_t* gameInfo);
void spawnNewFigure();
void clearFilledRows();
int calculationMaxRecord();
void calculationCurrentRecord(int num);
UserAction_t* getStateAction();
GameInfo_t* getStateGameInfo();
GameInfo_t* getStateGameInfo();
UserAction_t* getStateAction();
Figure* getFigure();
int* getRecord();
int* getStateHold();
int* getStateCh();
void actionRotateFigure();
int* getStateHold();
int* getStatePosFigX();
int* getStatePosFigY();
int* getHighRecord();
Figure* getNextFigure();
GameInfo_t updateCurrentState();
void startGameBaner();
Fsm* getStateFsm();
void fsmState(Fsm* state, UserAction_t* action, Figure* figure,
              GameInfo_t* gameInfo, int* ch, Figure* nextFigure);
void gameOver();
void viewInformationAboutGame();
void clearMemoryGameZone();
void movingState(int* ch, GameInfo_t* gameInfo, Figure* figure,
                 int* startPositionFigureX, int* startPositionFigureY,
                 Fsm* state);
void calculationInformationAboutGame();

#endif