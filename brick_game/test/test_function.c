#include "test.h"

START_TEST(test_getAction) {
  UserAction_t* action = getStateAction();
  ck_assert_int_eq(*action, 0);
}
END_TEST

START_TEST(test_getStateGameInfo) {
  GameInfo_t* gameInfo = getStateGameInfo();
  ck_assert_ptr_eq(gameInfo->field, NULL);
}
END_TEST

START_TEST(test_getStateFsm) {
  Fsm* state = getStateFsm();
  ck_assert_int_eq(*state, 0);
}
END_TEST

START_TEST(test_getFigure) {
  Figure* figure = getFigure();
  ck_assert_ptr_eq(figure->figure, NULL);
}
END_TEST

START_TEST(test_getNextFigure) {
  Figure* nextFigure = getNextFigure();
  ck_assert_ptr_eq(nextFigure->figure, NULL);
}
END_TEST

START_TEST(test_getStateCh) {
  int* ch = getStateCh();
  ck_assert_int_eq(*ch, 0);
}
END_TEST

START_TEST(test_getStatePosFigY) {
  int* startPositionFigureY = getStatePosFigY();
  ck_assert_int_eq(*startPositionFigureY, 0);
}
END_TEST

START_TEST(test_getStatePosFigX) {
  int* startPositionFigureX = getStatePosFigX();
  ck_assert_int_eq(*startPositionFigureX, 4);
}
END_TEST

START_TEST(test_getStateHold) {
  int* hold = getStateHold();
  ck_assert_int_eq(*hold, 1);
}
END_TEST

START_TEST(test_getRecord) {
  int* record = getRecord();
  ck_assert_int_eq(*record, 0);
}
END_TEST

START_TEST(test_getHighRecord) {
  int* recordHigh = getHighRecord();
  ck_assert_int_eq(*recordHigh, 0);
}
END_TEST

START_TEST(test_createGameZone) {
  GameInfo_t* gameInfo = getStateGameInfo();
  ck_assert_ptr_nonnull(gameInfo);  // проверяем что не NULL
  createGameZone();
  ck_assert_ptr_nonnull(gameInfo->field);
}
END_TEST

START_TEST(test_putActionDown) {
  int* startPositionFigureY = getStatePosFigY();
  int* ch = getStateCh();
  *ch = KEY_DOWN;
  putAction();
  ck_assert_int_eq(*startPositionFigureY, 1);
  *startPositionFigureY = 0;
}
END_TEST

START_TEST(test_putActionLeft) {
  int* startPositionFigureX = getStatePosFigX();
  int* ch = getStateCh();
  *ch = KEY_LEFT;
  putAction();
  ck_assert_int_eq(*startPositionFigureX, 3);
  *startPositionFigureX = 4;
}
END_TEST

START_TEST(test_putActionRight) {
  int* startPositionFigureX = getStatePosFigX();
  int* ch = getStateCh();
  *ch = KEY_RIGHT;
  putAction();
  ck_assert_int_eq(*startPositionFigureX, 5);
  *startPositionFigureX = 4;
}
END_TEST

START_TEST(test_putActionUp) {
  int* startPositionFigureY = getStatePosFigY();
  int* ch = getStateCh();
  *ch = KEY_UP;
  putAction();
  ck_assert_int_eq(*startPositionFigureY, 0);
}
END_TEST

START_TEST(test_putActionExit) {
  UserAction_t* action = getStateAction();
  int* ch = getStateCh();
  *ch = 'q';
  putAction();
  ck_assert_int_eq(*action, 2);
}
END_TEST

START_TEST(test_putActionPause) {
  UserAction_t* action = getStateAction();
  int* ch = getStateCh();
  *ch = 'p';
  putAction();
  ck_assert_int_eq(*action, 1);
}
END_TEST

START_TEST(test_putAction) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  clearMemoryFigure(figure);
  figure = drawFigure(4, 1, figure);
  int* startPositionPlayerX = getStatePosFigX();
  *startPositionPlayerX = 4;
  int* startPositionPlayerY = getStatePosFigY();
  *startPositionPlayerY = 0;
  int* ch = getStateCh();
  *ch = ' ';
  putAction();
  putFigureInGameZone(figure, *startPositionPlayerX, *startPositionPlayerY);
  ck_assert_int_eq(gameInfo->field[2][4], 42);
  clearMemoryFigure(figure);
  *startPositionPlayerX = 4;
  *startPositionPlayerY = 0;
}
END_TEST

START_TEST(test_userInputDown) {
  UserAction_t action = Down;
  int* hold = getStateHold();
  int* startPositionFigureY = getStatePosFigY();
  userInput(action, *hold);
  ck_assert_int_eq(*startPositionFigureY, 1);
  *startPositionFigureY = 0;
}
END_TEST

START_TEST(test_userInputLeft) {
  UserAction_t action = Left;
  int* hold = getStateHold();
  int* startPositionFigureX = getStatePosFigX();
  *startPositionFigureX = 4;
  userInput(action, *hold);
  ck_assert_int_eq(*startPositionFigureX, 3);
  *startPositionFigureX = 4;
}
END_TEST

START_TEST(test_userInputRight) {
  UserAction_t action = Right;
  int* hold = getStateHold();
  int* startPositionFigureX = getStatePosFigX();
  userInput(action, *hold);
  ck_assert_int_eq(*startPositionFigureX, 5);
  *startPositionFigureX = 4;
}
END_TEST

START_TEST(test_userInputUp) {
  UserAction_t action = Up;
  int* hold = getStateHold();
  int* startPositionFigureY = getStatePosFigY();
  userInput(action, *hold);
  ck_assert_int_eq(*startPositionFigureY, 0);
}
END_TEST

START_TEST(test_userInputStart) {
  UserAction_t action = Start;
  int* hold = getStateHold();
  int* startPositionFigureY = getStatePosFigY();
  userInput(action, *hold);
  ck_assert_int_eq(*startPositionFigureY, 0);
}
END_TEST

START_TEST(test_userInputPause) {
  UserAction_t action = Pause;
  GameInfo_t* gameInfo = getStateGameInfo();
  int* hold = getStateHold();
  userInput(action, *hold);
  ck_assert_int_eq(gameInfo->pause, 0);
}
END_TEST

START_TEST(test_userInputExit) {
  UserAction_t action = Terminate;
  int* hold = getStateHold();
  userInput(action, *hold);
  ck_assert_int_eq(action, 2);
}
END_TEST

START_TEST(test_userInputAction) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  figure = drawFigure(4, 1, figure);
  int* hold = getStateHold();
  UserAction_t action = Action;
  int* startPositionPlayerX = getStatePosFigX();
  *startPositionPlayerX = 4;
  int* startPositionPlayerY = getStatePosFigY();
  *startPositionPlayerY = 0;
  userInput(action, *hold);
  putFigureInGameZone(figure, *startPositionPlayerX, *startPositionPlayerY);
  ck_assert_int_eq(gameInfo->field[2][4], 42);
  clearMemoryFigure(figure);
  *startPositionPlayerX = 4;
  *startPositionPlayerY = 0;
}
END_TEST

START_TEST(test_drawFigure) {
  int width = 4;
  int height = 4;
  Figure* figure = getFigure();
  figure = drawFigure(width, height, figure);
  ck_assert_int_eq(figure->heightFigure, 4);
  ck_assert_int_eq(figure->widthFigure, 4);
  ck_assert_ptr_eq(figure->figure, figure->figure);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_putFigureInGameZone) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  figure = drawFigure(4, 1, figure);
  int startPositionPlayerX = 0;
  int startPositionPlayerY = 4;
  putFigureInGameZone(figure, startPositionPlayerX, startPositionPlayerY);
  ck_assert_int_eq(gameInfo->field[4][0], 42);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_isOutBorder) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  figure = randomFigure(figure);
  int* startPositionPlayerX = getStatePosFigX();
  *startPositionPlayerX = 9;
  int* startPositionPlayerY = getStatePosFigY();
  *startPositionPlayerY = 4;
  (*startPositionPlayerX)++;
  isOutBorder(figure);
  putFigureInGameZone(figure, *startPositionPlayerX, *startPositionPlayerY);
  ck_assert_int_eq(gameInfo->field[4][9], 42);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_isOutBorder2) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  figure = randomFigure(figure);
  int* startPositionPlayerX = getStatePosFigX();
  *startPositionPlayerX = 0;
  int* startPositionPlayerY = getStatePosFigY();
  *startPositionPlayerY = 4;
  putFigureInGameZone(figure, *startPositionPlayerX, *startPositionPlayerY);
  (*startPositionPlayerX)--;
  (*startPositionPlayerX)--;
  isOutBorder(figure);
  putFigureInGameZone(figure, *startPositionPlayerX, *startPositionPlayerY);
  ck_assert_int_eq(gameInfo->field[4][0], 42);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_randomFigure) {
  Figure* figure = getFigure();
  figure = randomFigure(figure);
  ck_assert_ptr_nonnull(figure->figure);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_rotateFigure) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  Figure* rotFigure = NULL;
  figure = drawFigure(4, 1, figure);
  int* startPositionPlayerX = getStatePosFigX();
  *startPositionPlayerX = 4;
  int* startPositionPlayerY = getStatePosFigY();
  *startPositionPlayerX = 0;
  rotFigure = rotateFigure();
  putFigureInGameZone(rotFigure, *startPositionPlayerX, *startPositionPlayerY);
  ck_assert_int_eq(gameInfo->field[4][2], 42);
  clearMemoryFigure(figure);
  clearMemoryFigure(rotFigure);
  free(rotFigure);
}
END_TEST

// START_TEST(test_isCollision) {
//   GameInfo_t* gameInfo = getStateGameInfo();
//   Figure* figure = getFigure();
//   figure = drawFigure(4, 1, figure);
//   int* startPositionPlayerX = getStatePosFigX();
//   *startPositionPlayerX = 9;
//   int* startPositionPlayerY = getStatePosFigY();
//   *startPositionPlayerY = 0;
//   // putFigureInGameZone(figure, *startPositionPlayerX,
//   *startPositionPlayerY);
//   (*startPositionPlayerX)++;
//   bool isCol = isCollision(*startPositionPlayerX, *startPositionPlayerY,
//   figure,
//                           gameInfo);
//   ck_assert_int_eq(isCol, true);
//   clearMemoryFigure(figure);
// }
// END_TEST

START_TEST(test_isCollision2) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  figure = drawFigure(4, 1, figure);
  int* startPositionPlayerX = getStatePosFigX();
  *startPositionPlayerX = 5;
  int* startPositionPlayerY = getStatePosFigY();
  *startPositionPlayerY = 4;
  putFigureInGameZone(figure, 5, 5);
  (*startPositionPlayerX)++;
  putFigureInGameZone(figure, *startPositionPlayerX, *startPositionPlayerY);
  bool isCol = isCollision(*startPositionPlayerX, *startPositionPlayerY, figure,
                           gameInfo);
  ck_assert_int_eq(isCol, true);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_clearFilledRows) {
  GameInfo_t* gameInfo = getStateGameInfo();
  Figure* figure = getFigure();
  figure = drawFigure(2, 2, figure);
  putFigureInGameZone(figure, 0, 18);
  putFigureInGameZone(figure, 2, 18);
  putFigureInGameZone(figure, 4, 18);
  putFigureInGameZone(figure, 6, 18);
  putFigureInGameZone(figure, 8, 18);
  clearFilledRows();
  ck_assert_int_eq(gameInfo->field[18][0], 32);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_figureClear) {
  GameInfo_t* gameInfo = getStateGameInfo();

  Figure* figure = getFigure();
  figure = drawFigure(2, 2, figure);
  putFigureInGameZone(figure, 0, 0);
  figureClear(gameInfo, figure);
  ck_assert_int_eq(gameInfo->field[0][0], 32);
  clearMemoryFigure(figure);
}
END_TEST

START_TEST(test_updateCurrentState) {
  GameInfo_t* gameInfo = getStateGameInfo();
  gameInfo->score = 0;
  Figure* figure = getFigure();
  figure = drawFigure(2, 2, figure);
  putFigureInGameZone(figure, 0, 18);
  putFigureInGameZone(figure, 2, 18);
  putFigureInGameZone(figure, 4, 18);
  putFigureInGameZone(figure, 6, 18);
  clearFilledRows();
  updateCurrentState();
  ck_assert_int_eq(gameInfo->score, 300);
  // clearMemoryGameZone();
  clearMemoryFigure(figure);
}
END_TEST

Suite* functionChecks(void) {
  Suite* s = suite_create("tetris");
  TCase* tc = tcase_create("tetris");

  tcase_add_test(tc, test_getAction);
  tcase_add_test(tc, test_getStateGameInfo);
  tcase_add_test(tc, test_getStateFsm);
  tcase_add_test(tc, test_getFigure);
  tcase_add_test(tc, test_getNextFigure);
  tcase_add_test(tc, test_getStateCh);
  tcase_add_test(tc, test_getStatePosFigY);
  tcase_add_test(tc, test_getStatePosFigX);
  tcase_add_test(tc, test_getStateHold);
  tcase_add_test(tc, test_getRecord);
  tcase_add_test(tc, test_getHighRecord);
  tcase_add_test(tc, test_createGameZone);
  tcase_add_test(tc, test_putActionDown);
  tcase_add_test(tc, test_putActionLeft);
  tcase_add_test(tc, test_putActionRight);
  tcase_add_test(tc, test_putActionUp);
  tcase_add_test(tc, test_putAction);
  tcase_add_test(tc, test_putActionExit);
  tcase_add_test(tc, test_putActionPause);
  tcase_add_test(tc, test_userInputDown);
  tcase_add_test(tc, test_userInputLeft);
  tcase_add_test(tc, test_userInputRight);
  tcase_add_test(tc, test_userInputUp);
  tcase_add_test(tc, test_userInputPause);
  tcase_add_test(tc, test_userInputAction);
  tcase_add_test(tc, test_userInputStart);
  tcase_add_test(tc, test_userInputExit);
  tcase_add_test(tc, test_drawFigure);
  tcase_add_test(tc, test_putFigureInGameZone);
  tcase_add_test(tc, test_isOutBorder);
  tcase_add_test(tc, test_isOutBorder2);
  tcase_add_test(tc, test_randomFigure);
  tcase_add_test(tc, test_rotateFigure);
  // tcase_add_test(tc, test_isCollision);
  tcase_add_test(tc, test_isCollision2);
  tcase_add_test(tc, test_clearFilledRows);
  tcase_add_test(tc, test_figureClear);
  tcase_add_test(tc, test_updateCurrentState);

  suite_add_tcase(s, tc);
  return s;
}