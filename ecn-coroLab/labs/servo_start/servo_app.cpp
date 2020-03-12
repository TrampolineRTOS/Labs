#include "tpl_os.h"
#include "coroBoard.h"
#include "pinAccess.h"
#include "tft.h"
#include "servo.h"

FUNC(int, OS_APPL_CODE) main(void)
{
  initCoroBoard();
  Tft.erase();
  Tft.print("Starting");
  initServo();

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
