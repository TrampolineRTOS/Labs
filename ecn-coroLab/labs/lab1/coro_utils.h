#ifndef __CORO_UTILS_H__
#define __CORO_UTILS_H__

void setupIOExtender();

void setupDisplay();
void eraseDisplay();
void println_string(const char* str);
void println_uint(uint32_t ui);
void println_int(int32_t i);

void setupTimer();
void resetTimer();
uint32_t getTimerValue();

#endif
