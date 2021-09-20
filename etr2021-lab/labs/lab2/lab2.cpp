#include "mcp23s17.h"
#include "pinAccess.h"
#include "tft.h"
#include "tpl_os.h"

volatile int val = 0;
volatile int activationCount = 0;

int main(void) {
  initCoroBoard();
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

TASK(bgTask) {
  while (1) {
    val++;
    val--;
  }
}

TASK(periodicTask) {
  activationCount++;
  if (activationCount & 1)
    val++; // odd
  else
    val--; // even
  TerminateTask();
}

TASK(displayTask) {
  Tft.setTextCursor(0, 0);
  Tft.eraseText(20);
  Tft.setTextCursor(0, 0);
  Tft.print(activationCount);
  Tft.print(": ");
  Tft.print(val);
  TerminateTask();
}
