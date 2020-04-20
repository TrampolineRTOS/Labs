#include <stdio.h>
#include "tpl_os.h"

volatile int val = 0;
volatile int activationCount = 0;

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK(bgTask)
{
	printf("start background task\r\n");
	while(1)
	{
		//loop forever
	}
    TerminateTask();
}

