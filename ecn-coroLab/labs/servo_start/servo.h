#ifndef __SERVO_H__
#include <stdint.h>

void initServo();
void setServoPulse(uint16_t widthInMicroseconds);

#endif
