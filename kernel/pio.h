#pragma once
#include "main.h"
#include "logging.h"

#define IO_BASE 0x1F0
#define CTRL_BASE 0x3F6


void AtaPioRead28(DWORD LBA, BYTE sector_count, BYTE *target);
void ata_pio_write28(DWORD LBA, BYTE sector_count, BYTE *target);