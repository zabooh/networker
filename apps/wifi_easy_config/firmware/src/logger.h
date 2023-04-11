

#include <stdint.h>
#include <stdbool.h>

#ifndef _LOGGER_H    
#define _LOGGER_H

void LOG_Start(void);
void LOG_Stop(void);
void LOG_log(char *str, uint32_t data_1, uint32_t data_2);
uint32_t LOG_GetLogSize(void);
void LOG_GetData(uint32_t ix, char *str);

#endif 