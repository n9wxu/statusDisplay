/*****************************************************************************
* | File      	:   LCD_1in28_test.c
* | Author      :   Waveshare team
* | Function    :   1.3inch LCD  test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-08-20
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LCD_Test.h"
#include "LCD_1in28.h"
#include "QMI8658.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <math.h>
#include <string.h>

struct displayInfo
{

    char mainText[30];
    char nameText[30];
    char statusText1[20];
    char statusText2[20];
    char statusText3[20];
    char gaugeText[20];  //
    int gaugePercentage; // 0 - 100

} info;

const float PI = (3.141593);
void plotArc(int X_Center, int Y_Center, int Start_Angle, int End_Angle, int Radius, uint16_t Color, DOT_PIXEL Line_width)
{
    const float radius = (float)Radius;
    float startAngleR = (((float)Start_Angle * PI) / 180.0);
    float endAngleR = (((float)End_Angle * PI) / 180.0);
    for (float theta = startAngleR; theta < endAngleR; theta += 0.01)
    {
        int x = X_Center + (int)(radius * cos(theta));
        int y = Y_Center + (int)(radius * sin(theta));
        Paint_DrawPoint(x, y, Color, Line_width, DOT_STYLE_DFT);
    }
}

void drawGauge(uint16_t position)
{
    const int radius = 117;
    int startAngle = 135;
    int endAngle = startAngle + ((270 * position) / 100);
    plotArc(120, 120, startAngle, endAngle, radius, RED, DOT_PIXEL_3X3);
    plotArc(120, 120, endAngle, 360 + 45, radius, GRAY, DOT_PIXEL_3X3);
}

uint16_t p = 0;
#define IMAGESIZE (LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2)
UWORD *BlackImage;

int LCD_1in28_init(void)
{
    printf("LCD_1in28_test Demo\r\n");

    adc_init();
    adc_gpio_init(29);
    adc_select_input(3);
    /* LCD Init */
    printf("1.28inch LCD demo...\r\n");
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);
    DEV_SET_PWM(60);
    BlackImage = malloc(IMAGESIZE);
    return 0;
}

int LCD_1in28_test(void)
{

    // /* GUI */
    printf("drawing...\r\n");
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_SetRotate(ROTATE_90);
    Paint_Clear(BLACK);

    drawGauge(info.gaugePercentage);
    Paint_DrawString_EN(120, 50, info.nameText, &Font24, WHITE, BLACK, 1);
    Paint_DrawString_EN(120, 100, info.mainText, &Font24, WHITE, BLACK, 1);
    Paint_DrawString_EN(120, 135, info.statusText1, &Font16, WHITE, BLACK, 1);
    Paint_DrawString_EN(120, 155, info.statusText2, &Font16, WHITE, BLACK, 1);
    Paint_DrawString_EN(120, 175, info.statusText3, &Font16, WHITE, BLACK, 1);
    Paint_DrawString_EN(120, 200, info.gaugeText, &Font16, WHITE, BLACK, 1);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_1IN28_Display(BlackImage);
    DEV_Delay_ms(10);

    return 0;
}

void setMainText(char *text)
{
    strncpy(info.mainText, text, sizeof(info.mainText));
}

void setNameText(char *text)
{
    strncpy(info.nameText, text, sizeof(info.nameText));
}

void setStatusText(int n, char *text)
{
    switch (n)
    {
    case 0:
        strncpy(info.statusText1, text, sizeof(info.statusText1));
        break;
    case 1:
        strncpy(info.statusText2, text, sizeof(info.statusText2));
        break;
    case 2:
        strncpy(info.statusText3, text, sizeof(info.statusText3));
        break;
    default:
        break;
    }
}

void setGaugeText(char *text)
{
    strncpy(info.gaugeText, text, sizeof(info.gaugeText));
}

void setGauge(int p)
{
    if (p > 100)
        p = 100;
    if (p < 0)
        p = 0;
    info.gaugePercentage = p;
}