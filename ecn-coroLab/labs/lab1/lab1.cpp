#include "tpl_os.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
#include "coro_utils.h"

FUNC(int, OS_APPL_CODE) main(void)
{
    setupIOExtender();
    setupDisplay();
    setupTimer();
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(task1)
{
    ioExt.digitalWrite(mcp23s17::PORTA, 0, 1);
    TerminateTask();
}


/*
 *  * This is necessary for ST libraries
 *   */
FUNC(void, OS_CODE) assert_failed(uint8_t* file, uint32_t line)
{
}

extern "C" void __cxa_pure_virtual() { while (1); }

#ifdef __cplusplus
}
#endif /* __cplusplus */
