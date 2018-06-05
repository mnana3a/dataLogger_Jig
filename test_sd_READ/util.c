/*  UTILITY FUNCTIONS
 *  1- PROVIDES DIFFERENT FUNCTIONS THAT CAN BE USED WITH DIFFERENT MODULES TO CONVERT DATA FORMAT
 *
 * Author: mnana3a
 * Date  : 05/03/2018
 *
 * USAGE : used in a data logger device
*/

#include "util.h"
#include "main_ht66f0185.h"

void delay_100us(void)
{
    GCC_DELAY(200);
}

#if 0
void ftoa(float x, char *a)
{
    int i = 0;
    unsigned int integer = (unsigned int)x;
    unsigned int fraction = (((x - integer) < 0.11) ? (0) : (x-integer)*100);
    if (integer == 0) a[i++] = '0';
    else{
        while (integer > 0)
        {
            a[i] = (integer % 10) | 0x30;
            integer /= 10;
            i++;    
        }  
    } 
    a[i++] = '.';
    reverse(a);
    if (fraction == 0) {a[i++] = '0';  a[i] = '\0';}
    else{
        while (fraction > 0)
        {
            a[i] = (fraction % 10) | 0x30;
            fraction /= 10;
            i++;    
        }   
        a[i] = '\0';
        reverse(&a[i-2]);
    }
}
#endif

void itoa(int n, char s[])
{
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do { 
    s[i++] = n % 10 + ' 0'; 
  } while ((n /= 10) > 0); 
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0'; 
  reverse(s);
}

void reverse(char *str)
{
    int i , j;
    char temp;
    for(i = 0, j = strlen(str) - 1 ; i < j ; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int strlen(char *s)
{
    int i = 0;
    while(s[i] != 0 && s[i] != '.') i++;
    return i;
}

void delay(unsigned long x)
{
    while (x-- > 0);
}
