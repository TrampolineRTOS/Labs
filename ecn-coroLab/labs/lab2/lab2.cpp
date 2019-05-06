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

enum switch_states {stOPEN, stCLOSED};
enum switch_events {evOPENED, evCLOSED, evNOTHING};

typedef enum switch_states t_switch_state;
typedef enum switch_events t_switch_event;

FUNC(t_switch_event, OS_APPL_CODE) updateStateOfB0()
{
    static t_switch_state state = stOPEN;
    t_switch_event event = evNOTHING;

    uint8_t bitVal = ioExt.digitalRead(mcp23s17::PORTB, 0);
    switch (state)
    {
        case stOPEN:
            if (bitVal == 1)
            {
                event = evCLOSED;
                state = stCLOSED;
            }
            break;
        case stCLOSED:
            if (bitVal == 0)
            {
                event = evOPENED;
                state = stOPEN;
            }
            break;
    }
    return event;
}

TASK(tpoll)
{
    t_switch_event event = updateStateOfB4();
    if (event == evCLOSED)
    {
        ioExt.digitalWrite(mcp23s17::PORTA, 3, 1);
    }
    if (event == evOPENED)
    {
        ioExt.digitalWrite(mcp23s17::PORTA, 3, 0);
    }
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
