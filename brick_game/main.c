#include "tetris.h"

int main() {
  srand(time(NULL));
  initscr();
  keypad(stdscr, true);
  curs_set(false);
  start_color();
  noecho();

  createGame();
  endwin();
  return 0;
}

void createGame() {
  UserAction_t* action = getStateAction();
  GameInfo_t* gameInfo = getStateGameInfo();
  Fsm* state = getStateFsm();
  Figure* figure = getFigure();
  figure = randomFigure(figure);
  Figure* nextFigure = getNextFigure();
  nextFigure = randomFigure(nextFigure);

  int* ch = getStateCh();

  *state = StartGame;
  gameInfo->level = 1;

  unsigned long firstTime = clock();

  while ((*ch = getch()) != 'q' || *action != Terminate) {
    unsigned long curTime = clock();
    unsigned long timeDiff = curTime - firstTime;

    fsmState(state, action, figure, gameInfo, ch, nextFigure);

    if (*state == GameOver) {
      break;
    }

    if (timeDiff >= (unsigned long)(500000 / gameInfo->level)) {
      if (!gameInfo->pause) {
        *state = Shifting;
        firstTime = curTime;
      }
    }
  }
  clearMemoryFigure(figure);
}