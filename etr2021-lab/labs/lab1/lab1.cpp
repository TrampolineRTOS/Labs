#include "mcp23s17.h"
#include "pinAccess.h"
#include "tft.h"
#include "tpl_os.h"

FUNC(int, OS_APPL_CODE) main(void) {
  initCoroBoard();
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

TASK(task1) {
  ioExt.digitalWrite(mcp23s17::PORTA, 0, 1);
  TerminateTask();
}

TASK(pulse) {
  static int count = 0;

  digitalToggle(GPIOB, 0);
  Tft.setTextCursor(0, 0);
  Tft.eraseText(6);
  Tft.setTextCursor(0, 0);
  Tft.print(count++);
  TerminateTask();
}
