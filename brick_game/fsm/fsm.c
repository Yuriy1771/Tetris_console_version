#include "../tetris.h"

void fsmState(Fsm* state, UserAction_t* action, Figure* figure,
              GameInfo_t* gameInfo, int* ch, Figure* nextFigure) {
  int* startPositionFigureY = getStatePosFigY();
  int* startPositionFigureX = getStatePosFigX();

  switch (*state) {
    case StartGame:
      startGameBaner();
      if ((*ch = getch() == 's')) {
        erase();
        *state = Moving;
        nodelay(stdscr, true);
        cbreak();
        createGameZone();
      }
      break;
    case Spawn:
      gameInfo->next = nextFigure->figure;
      *startPositionFigureX = 4;
      *startPositionFigureY = 0;
      spawnNewFigure();
      *state = Moving;
      break;
    case Moving:
      movingState(ch, gameInfo, figure, startPositionFigureX,
                  startPositionFigureY, state);
      break;
    case Shifting:
      (*startPositionFigureY)++;
      figureClear(gameInfo, figure);
      isOutBorder(figure);
      *state = Moving;
      break;
    case Attaching:
      *state = Spawn;
      break;
    case GameOver:
      *action = Terminate;
      break;
    default:
      break;
  }

  if (gameInfo->pause == false && *state != StartGame && *state != GameOver) {
    updateCurrentState();
    erase();
    printGameZone();
    viewInformationAboutGame();
  }
}

void movingState(int* ch, GameInfo_t* gameInfo, Figure* figure,
                 int* startPositionFigureX, int* startPositionFigureY,
                 Fsm* state) {
  if (*ch && gameInfo->pause == false) {
    figureClear(gameInfo, figure);
    putAction();
    isOutBorder(figure);
    if (isCollision(*startPositionFigureX, *startPositionFigureY + 1, figure,
                    gameInfo) &&
        *startPositionFigureY == 0) {
      erase();
      gameInfo->pause = true;
      putAction();
      gameOver();
      if ((*ch = getch() == 's')) {
        *state = GameOver;
      }
    } else if (isCollision(*startPositionFigureX, *startPositionFigureY + 1,
                           figure, gameInfo)) {
      putFigureInGameZone(figure, *startPositionFigureX, *startPositionFigureY);
      clearFilledRows();
      *state = Attaching;
    }
  } else {
    putAction();
  }
}