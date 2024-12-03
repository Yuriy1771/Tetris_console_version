#include "test.h"

int main(void) {
  int failed = 0;

  Suite *functionTests[] = {functionChecks(), NULL};

  for (int i = 0; functionTests[i] != NULL; i++) {
    SRunner *suite_runner = srunner_create(functionTests[i]);

    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);

    failed += srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }

  return failed == 0 ? 0 : 1;
}
