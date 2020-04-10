#include <stdio.h>
#include "tpl_os.h"

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


TASK(task1)
{
	printf("Hello world\n");
    TerminateTask();
}

