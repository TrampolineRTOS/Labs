#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

DeclareMessage(from_send);
DeclareMessage(for_receive);


int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK (send)
{
    uint32_t data = 0XC4C0FFEE;
    SendMessage(from_send, &data);
    TerminateTask();
}

TASK (receive)
{
    uint32_t data;
    ReceiveMessage(for_receive, &data);
    printf("received data: %x\r\n", data);
    ShutdownOS(E_OK);
    TerminateTask();
}
