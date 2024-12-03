#include "tetris.h"

GameInfo_t updateCurrentState() {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  int* startPositionFigureY = getStatePosFigY();
  int* startPositionFigureX = getStatePosFigX();
  putFigureInGameZone(figure, *startPositionFigureX, *startPositionFigureY);
  calculationInformationAboutGame();
  return *gameInfo;
}

void putFigureInGameZone(Figure* figure, int startPositionFigureX,
                         int startPositionFigureY) {
  GameInfo_t* gameInfo = getStateGameInfo();
  figure->startX = startPositionFigureX;
  figure->startY = startPositionFigureY;

  for (int i = 0; i < figure->heightFigure; i++) {
    for (int k = 0; k < figure->widthFigure; k++) {
      if (figure->figure[i][k] == '*') {
        gameInfo->field[figure->startY + i][figure->startX + k] =
            figure->figure[i][k];
      }
    }
  }
}

void putAction() {
  int* hold = getStateHold();
  int* ch = getStateCh();
  UserAction_t* action = getStateAction();

  switch (*ch) {
    case 'q':
      *action = Terminate;
      *hold = true;
      userInput(*action, hold);
      break;
    case 'p':
      *action = Pause;
      *hold = true;
      userInput(*action, hold);
      break;
    case KEY_LEFT:
      *action = Left;
      *hold = true;
      userInput(*action, hold);
      break;
    case KEY_RIGHT:
      *action = Right;
      *hold = true;
      userInput(*action, hold);
      break;
    case KEY_UP:
      *action = Up;
      *hold = true;
      userInput(*action, hold);
      break;
    case KEY_DOWN:
      *action = Down;
      *hold = true;
      userInput(*action, hold);
      break;
    case ' ':
      *action = Action;
      *hold = true;
      userInput(*action, hold);
      break;
    default:
      break;
  }
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t* gameInfo = getStateGameInfo();
  int* startPositionFigureX = getStatePosFigX();
  int* startPositionFigureY = getStatePosFigY();

  if (hold == true) {
    switch (action) {
      case Start:
        break;
      case Pause:
        gameInfo->pause = !gameInfo->pause;
        break;
      case Terminate:
        action = Terminate;
        break;
      case Left:
        (*startPositionFigureX)--;
        break;
      case Right:
        (*startPositionFigureX)++;
        break;
      case Up:
        break;
      case Down:
        (*startPositionFigureY)++;
        break;
      case Action:
        actionRotateFigure();
        break;
      default:
        break;
    }
  }
}

void actionRotateFigure() {
  Figure* figure = getFigure();
  Figure* bufferFig = NULL;
  bufferFig = rotateFigure();

  clearMemoryFigure(figure);

  figure->heightFigure = bufferFig->heightFigure;
  figure->widthFigure = bufferFig->widthFigure;

  figure->figure = malloc(bufferFig->heightFigure * sizeof(int*));
  for (int i = 0; i < bufferFig->heightFigure; i++) {
    figure->figure[i] = malloc(bufferFig->widthFigure * sizeof(int));
  }

  for (int i = 0; i < bufferFig->heightFigure; i++) {
    for (int k = 0; k < bufferFig->widthFigure; k++) {
      figure->figure[i][k] = bufferFig->figure[i][k];
    }
  }

  clearMemoryFigure(bufferFig);
  free(bufferFig);
}

void spawnNewFigure() {
  Figure* figure = getFigure();
  Figure* nextFigure = getNextFigure();

  clearMemoryFigure(figure);

  figure->widthFigure = nextFigure->widthFigure;
  figure->heightFigure = nextFigure->heightFigure;

  figure->figure = malloc(figure->heightFigure * sizeof(int*));
  for (int i = 0; i < figure->heightFigure; i++) {
    figure->figure[i] = malloc(figure->widthFigure * sizeof(int));
  }

  for (int i = 0; i < nextFigure->heightFigure; i++) {
    for (int k = 0; k < nextFigure->widthFigure; k++) {
      figure->figure[i][k] = nextFigure->figure[i][k];
    }
  }

  nextFigure = randomFigure(nextFigure);
}

Figure* drawFigure(int width, int height, Figure* figure) {
  figure->widthFigure = width;
  figure->heightFigure = height;

  figure->figure = malloc(figure->heightFigure * sizeof(int*));
  for (int i = 0; i < figure->heightFigure; i++) {
    figure->figure[i] = malloc(figure->widthFigure * sizeof(int));
  }

  for (int i = 0; i < figure->heightFigure; i++) {
    for (int k = 0; k < figure->widthFigure; k++) {
      figure->figure[i][k] = '*';
    }
  }
  return figure;
}

Figure* randomFigure(Figure* figure) {
  int randomNum = rand() % (7 - 1 + 1) + 1;

  switch (randomNum) {
    case 1:
      figure = drawFigure(4, 1, figure);
      break;
    case 2:
      figure = drawFigure(2, 2, figure);
      break;
    case 3:
      figure = drawFigure(3, 2, figure);
      figure->figure[0][0] = ' ';
      figure->figure[0][1] = ' ';
      break;
    case 4:
      figure = drawFigure(3, 2, figure);
      figure->figure[0][1] = ' ';
      figure->figure[0][2] = ' ';
      break;
    case 5:
      figure = drawFigure(3, 2, figure);
      figure->figure[0][0] = ' ';
      figure->figure[1][2] = ' ';
      break;
    case 6:
      figure = drawFigure(3, 2, figure);
      figure->figure[0][2] = ' ';
      figure->figure[1][0] = ' ';
      break;
    case 7:
      figure = drawFigure(3, 2, figure);
      figure->figure[0][0] = ' ';
      figure->figure[0][2] = ' ';
      break;
  }
  return figure;
}

void isOutBorder(Figure* figure) {
  int* currentPositionFigureX = getStatePosFigX();
  int* currentPositionFigureY = getStatePosFigY();

  if (*currentPositionFigureX + figure->widthFigure > 10) {
    *currentPositionFigureX = 10 - figure->widthFigure;
  }
  if (*currentPositionFigureX < 0) {
    *currentPositionFigureX = 0;
  }
  if (*currentPositionFigureY + figure->heightFigure > 20) {
    *currentPositionFigureY = 20 - figure->heightFigure;
  }
  if (*currentPositionFigureY == 0) {
    *currentPositionFigureY = 0;
  }
}

bool isCollision(int startPositionFigureX, int startPositionFigureY,
                 Figure* figure, GameInfo_t* gameInfo) {
  bool isBool = false;
  for (int y = 0; y < figure->heightFigure; y++) {
    for (int x = 0; x < figure->widthFigure; x++) {
      if (figure->figure[y][x] == '*') {
        if (startPositionFigureY + y > 19 || startPositionFigureX + x < 0 ||
            startPositionFigureX + x > 9 ||
            gameInfo->field[startPositionFigureY + y]
                           [startPositionFigureX + x] != ' ') {
          isBool = true;
        }
      }
    }
  }
  return isBool;
}

void clearFilledRows() {
  GameInfo_t* gameInfo = getStateGameInfo();
  int num = 0;
  for (int y = 19; y >= 0; y--) {
    bool isFilled = true;
    // проверяем заполнена ли строка
    for (int x = 0; x < 10; x++) {
      if (gameInfo->field[y][x] == ' ') {
        isFilled = false;
        break;
      }
    }

    if (isFilled == true) {
      num++;
      // очищаем заполненую строку
      for (int x = 0; x < 10; x++) {
        gameInfo->field[y][x] = ' ';
      }
      // перемещаем все фигры вниз
      for (int moveY = y - 1; moveY >= 0; moveY--) {
        for (int x = 0; x < 10; x++) {
          gameInfo->field[moveY + 1][x] = gameInfo->field[moveY][x];
        }
      }
      // очищаем верхнюю строку
      for (int x = 0; x < 10; x++) {
        gameInfo->field[0][x] = ' ';
      }
      y++;
    }
  }
  if (num > 0) {
    calculationCurrentRecord(num);
    calculationMaxRecord();
  }
}

void calculationInformationAboutGame() {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* nextFigure = getNextFigure();

  (void)nextFigure;
  int* record = getRecord();
  int* highRecord = getHighRecord();
  gameInfo->score = *record;
  gameInfo->high_score = *highRecord;
  if (gameInfo->level < 0) {
    gameInfo->level = 1;
  }
  int lvl = gameInfo->level;

  if (lvl < 10 && gameInfo->score >= (lvl) * 600) {
    lvl++;
    gameInfo->level = lvl;
    gameInfo->speed = lvl;
  }
}

Figure* rotateFigure() {
  Figure* figureCur = getFigure();
  Figure* rotatedFig = malloc(sizeof(Figure));
  rotatedFig->widthFigure = figureCur->heightFigure;
  rotatedFig->heightFigure = figureCur->widthFigure;

  rotatedFig->figure = malloc(rotatedFig->heightFigure * sizeof(int*));
  for (int i = 0; i < rotatedFig->heightFigure; i++) {
    rotatedFig->figure[i] = malloc(rotatedFig->widthFigure * sizeof(int));
  }

  // Заполняем новую фигуру, поворачивая оригинальную
  for (int i = 0; i < figureCur->heightFigure; i++) {
    for (int k = 0; k < figureCur->widthFigure; k++) {
      rotatedFig->figure[k][rotatedFig->widthFigure - 1 - i] =
          figureCur->figure[i][k];
    }
  }
  return rotatedFig;
}

void figureClear(GameInfo_t* gameInfo, Figure* figure) {
  for (int i = 0; i < figure->heightFigure; i++) {
    for (int k = 0; k < figure->widthFigure; k++) {
      if (figure->figure[i][k] == '*') {
        gameInfo->field[figure->startY + i][figure->startX + k] = ' ';
      }
    }
  }
}

void clearMemoryFigure(Figure* figure) {
  for (int i = 0; i < figure->heightFigure; i++) {
    free(figure->figure[i]);
  }
  free(figure->figure);
}

void calculationCurrentRecord(int num) {
  int* curRecord = getRecord();
  switch (num) {
    case 1:
      *curRecord = *curRecord + 100;
      break;
    case 2:
      *curRecord = *curRecord + 300;
      break;
    case 3:
      *curRecord = *curRecord + 700;
      break;
    case 4:
      *curRecord = *curRecord + 1500;
      break;
  }
}

int calculationMaxRecord() {
  int* curRecord = getRecord();
  int maxRecord = 0;
  if (*curRecord > 0) {
    FILE* file = fopen("record.txt", "r");
    if (file != NULL) {
      fscanf(file, "%d", &maxRecord);
      fclose(file);
    }
    if (*curRecord > maxRecord) {
      file = fopen("record.txt", "w");
      fprintf(file, "%d", *curRecord);
      fclose(file);
    }
  }
  return maxRecord;
}

void createGameZone() {
  GameInfo_t* gameInfo = getStateGameInfo();

  gameInfo->field = (int**)malloc(20 * sizeof(int*));
  for (int i = 0; i < 20; i++) {
    gameInfo->field[i] = (int*)malloc(10 * sizeof(int));
  }

  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 10; k++) {
      gameInfo->field[i][k] = ' ';
    }
  }
}

void clearMemoryGameZone() {
  GameInfo_t* gameInfo = getStateGameInfo();

  for (int i = 0; i < 20; i++) {
    free(gameInfo->field[i]);
  }
  // Очищаем сам массив field
  free(gameInfo->field);
}