#include "main.h"
#include "logging.h"
#include "isr.h"

#define CHANNEL_0_DATA_PORT 0x40
#define CLOCK_BASE_FREQUENCY 1193181
#define MODE_REGISTER 0x43

void InitTimer(int rate);
void TimerHandler(struct registers_t* r);
QWORD read_tsc(void);