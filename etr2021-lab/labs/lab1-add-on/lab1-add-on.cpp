typedef enum {stOPEN, stCLOSED} t_switch_state;
typedef enum {evOPENED, evCLOSED, evNOTHING} t_switch_event;

FUNC(t_switch_event, OS_APPL_CODE) updateStateOfB7()
{
    static t_switch_state state = stCLOSED;
    t_switch_event event = evNOTHING;

    uint8_t bitVal = ioExt.digitalRead(mcp23s17::PORTB, 7);
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

TASK(pulse2)
{
    t_switch_event event = updateStateOfB7();
    if (event == evOPENED)
    {
        ioExt.digitalToggle(mcp23s17::PORTA, 3);
    }
    TerminateTask();
}
