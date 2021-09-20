#include "tpl_os.h"
#include "mcp23s17.h"

FUNC(int, OS_APPL_CODE) main(void)
{
    initCoroBoard();
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
    t_switch_event event = updateStateOfB0();
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
