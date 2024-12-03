#include "../brick_game/tetris.h"

void printGameZone() {
  GameInfo_t* gameInfo = getStateGameInfo();
  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 10; k++) {
      init_pair(1, COLOR_BLUE, COLOR_BLUE);
      attron(COLOR_PAIR(1));
      init_pair(2, COLOR_YELLOW, COLOR_YELLOW);

      if (gameInfo->field[i][k] == '*') {
        attron(COLOR_PAIR(2));
      }
      printw("  ", gameInfo->field[i][k]);
    }
    printw("\n");
  }
}

void viewInformationAboutGame() {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* nextFigure = getNextFigure();
  FILE* file = fopen("record.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d",
           &gameInfo->high_score);  // записываем значение из файла в переменную
    fclose(file);
  }
  mvprintw(2, 21, "Maximum Record: %d", gameInfo->high_score);
  mvprintw(4, 21, "Current record: %d", gameInfo->score);
  mvprintw(6, 21, "level: %d", gameInfo->level);
  mvprintw(8, 21, "next figure:");
  mvprintw(14, 21, "'space' - rotate figure");
  mvprintw(16, 21, "'q' - exit");
  mvprintw(18, 21, "'p' - pause");

  for (int i = 0; i < nextFigure->heightFigure; i++) {
    for (int k = 0; k < nextFigure->widthFigure; k++) {
      if (nextFigure->figure[i][k] == '*') {
        init_pair(3, COLOR_YELLOW, COLOR_WHITE);
        attron(COLOR_PAIR(3));
        mvprintw(10 + i, 23 + k, "  ", nextFigure->figure[i][k]);
      }
    }
  }
}

void startGameBaner() {
  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 20; k++) {
      init_pair(1, COLOR_WHITE, COLOR_YELLOW);
      attron(COLOR_PAIR(1));

      printw("  ", i);
    }
    printw("\n");
  }
  mvprintw(0, 10, "Welcome to Tetris");
  mvprintw(5, 4, "To start the game, click on 's'");
}

void gameOver() {
  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 20; k++) {
      init_pair(1, COLOR_RED, COLOR_BLACK);
      attron(COLOR_PAIR(1));
      printw("  ", i);
    }
    printw("\n");
  }
  mvprintw(6, 13, "You are loser");
  mvprintw(8, 14, "game over :(");
  mvprintw(10, 14, "press to 'q'");
}