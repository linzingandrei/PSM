#include "timer.h"


int timer_ticks = 0;
void InitTimer(int rate) {
    timer_ticks = 0;
    int divisor = CLOCK_BASE_FREQUENCY / rate; 
    __outbyte(MODE_REGISTER, 0x36);
    __outbyte(CHANNEL_0_DATA_PORT, divisor & 0xFF);
    __outbyte(CHANNEL_0_DATA_PORT, divisor >> 8);
}

void TimerHandler(struct registers_t* r) {
    timer_ticks += 1;

    // Log("Numar");
    if (timer_ticks % 60 == 0) {
        if (timer_ticks / 3600 != 0) {
            if (timer_ticks / 60 % 60 < 10) {
                LogScreen("%d:0%d", timer_ticks / 3600 , timer_ticks / 60 % 60);
            }
            else {
                LogScreen("%d:%d", timer_ticks / 3600 , timer_ticks / 60 % 60);
            }
        }
        else {
            LogScreen("%d", timer_ticks / 60 % 60);
        }
    }
}