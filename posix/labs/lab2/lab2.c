#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

ISR (when_a)
{
    static bool set = true;

    if (set) {
        set_leds(GREEN);
    } else {
        reset_leds(GREEN);
    }
    set = !set;
}

TASK (task1)
{
    static bool set = true;

    if (set) {
        set_leds(RED);
    } else {
        reset_leds(RED);
    }
    set = !set;
}
