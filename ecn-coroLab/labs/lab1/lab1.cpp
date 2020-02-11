#include "tpl_os.h"
#include "mcp23s17.h"

FUNC(int, OS_APPL_CODE) main(void)
{
    initCoroBoard();
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(task1)
{
    ioExt.digitalWrite(mcp23s17::PORTA, 0, 1);
    TerminateTask();
}


