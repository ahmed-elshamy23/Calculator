#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/DIO/DIO_private.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/LCD/LCD_private.h"
#include "HAL/Keypad/KPD_interface.h"

#define F_CPU 8000000UL

int main()
{
    LCD_voidInit();
    LCD_voidSendCommand(cursorOff);
    KPD_voidInit(PORTA);
    u8 keys[10], i = 0, flag = 0, done = 0, op;
    s16 num1 = 0, num2 = 0, result = 0;
    while (1)
    {
        while (KPD_u8GetPressedKey(PORTA) != NOT_PRESSED)
        {
            u8 key = KPD_u8GetPressedKey(PORTA);
            LCD_voidSendChar(key);
            if (key == 'c')
            {
                LCD_voidSendCommand(clearDisplay);
                i = 0;
                num1 = 0;
                num2 = 0;
                result = 0;
                continue;
            }
            if (key == '=')
            {
                done = 1;
                break;
            }
            keys[i] = key;
            i++;
        }
        if (done)
        {
            keys[i] = '\0';
            i = 0;
            while (keys[i] != '\0')
            {
                if (keys[i] >= '0' && keys[i] <= '9')
                {
                    if (flag == 0)
                        num1 = (num1 * 10) + keys[i] - '0';
                    else
                        num2 = (num2 * 10) + keys[i] - '0';
                }
                else
                {
                    op = keys[i];
                    flag = 1;
                }
                i++;
            }
            switch (op)
            {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            }
            LCD_voidSendNumber(result);
            flag = 0;
            done = 0;
        }
    }
}