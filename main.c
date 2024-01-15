#include "LCD_Test.h" //Examples
#include <stdio.h>
#include "pico/stdlib.h"
#include "DEV_Config.h"

int main(void)
{
    char buffer(200);

    stdio_init_all();
    DEV_Module_Init();

    printf("Getting started\n");
    LCD_1in28_init();

    setMainText("Main Text");
    setNameText("Name Text");
    setStatusText(0, "Status Text 0");
    setStatusText(1, "Status Text 1");
    setStatusText(2, "Status Text 2");
    setGaugeText("Gauge Text");
    setGauge(25);

    for (;;)
    {
        gets(buffer);
        // buffer is filled with one line.  Each line starts with a command followed by data
        // MT <text> is main text update
        // NT <text> is name text update
        // S0 <text> is status text 0
        // S1 <text> is status text 1
        // S2 <text> is status text 2
        // GT <text> is gauge text
        // GV <0-100> is gauge value digits 0-100

        if (strncmp(buffer, "MT", 2) == 0)
        {
            // process MT
        }
        else if (strncmp(buffer, "NT", 2) == 0)
        {
            // process MT
        }
        else if (strncmp(buffer, "S0", 2) == 0)
        {
            // process MT
        }
        else if (strncmp(buffer, "S1", 2) == 0)
        {
            // process MT
        }
        else if (strncmp(buffer, "S2", 2) == 0)
        {
            // process MT
        }
        else if (strncmp(buffer, "GT", 2) == 0)
        {
            // process MT
        }
        else if (strncmp(buffer, "GV", 2) == 0)
        {
            // process MT
        }
        else
        {
            printf("Error: %s\n", buffer);
        }

        LCD_1in28_test();
    }

    return 0;
}
