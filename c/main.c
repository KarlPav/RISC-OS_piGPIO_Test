
#include "swis.h"
#include "kernel.h"

#include "sflib/debug.h"

#define GPIO_Read 0x58F80       // Reads the state of the given GPIO pin, or returns an error if the pin number is not valid.
#define GPIO_Write 0x58F81      // Writes the state of the given GPIO pin, or returns an error if the pin number is not valid.
#define GPIO_ReadOE 0x58F82     // Reads the "Output Enable" state of the given GPIO pin, or returns an error if the pin number is not valid.
#define GPIO_WriteOE 0x58F83    // Writes the "Output Enable" state of the given GPIO pin, or returns an error if the pin number is not valid.
#define GPIO_ReadEvent 0x58FAB  // Polls the event state of the GPIO pin, the event type is set with flag bits in GPIO_WriteMode, or returns an error if the pin number is not valid.
#define GPIO_WriteEvent 0x58FAC // Writes the event state of the given GPIO pin, or returns an error if the pin number is not valid.
#define GPIO_Features 0x58FAF   // This call returns additional features supported by the GPIO module.

int read_gpio(int pin);
void write_gpio(int pin, int value);
int readOE_gpio(int pin);
void writeOE_gpio(int pin, int value);

int main(void)
{

    /*Input*/
    if (readOE_gpio(26) != 1)
    {
        write_gpio(26, 0);
        writeOE_gpio(26, 1);
    }
    debug_printf("GPIO pin 26 Input mode");
    debug_printf("GPIO pin 26 Input = %d\n", read_gpio(26));

    /*Output*/
    // if (readOE_gpio(26) != 0)
    // {
    //     writeOE_gpio(26, 0);
    // }
    // debug_printf("GPIO pin 26 Output mode");
    // write_gpio(26, 1);
    // debug_printf("GPIO pin 26 Output = %d\n", read_gpio(26));

    return 0;
}

int read_gpio(int pin)
{
    _kernel_swi_regs r;
    r.r[0] = pin;

    _kernel_swi(GPIO_Read, &r, &r);

    return r.r[0]; // Usually returns 0 or 1
}

void write_gpio(int pin, int value)
{
    _kernel_swi_regs r;
    r.r[0] = pin;
    r.r[1] = value;

    _kernel_swi(GPIO_Write, &r, &r);
}

int readOE_gpio(int pin)
{
    _kernel_swi_regs r;
    r.r[0] = pin;

    _kernel_swi(GPIO_ReadOE, &r, &r);

    return r.r[0]; // Usually returns 0 or 1
}

void writeOE_gpio(int pin, int value)
{
    _kernel_swi_regs r;
    r.r[0] = pin;
    r.r[1] = value;

    _kernel_swi(GPIO_WriteOE, &r, &r);
}

int readEvent_gpio(int pin)
{
    _kernel_swi_regs r;
    r.r[0] = pin;

    _kernel_swi(GPIO_ReadEvent, &r, &r);

    return r.r[0]; // Usually returns 0 or 1
}

void writeEvent_gpio(int pin, int value)
{
    _kernel_swi_regs r;
    r.r[0] = pin;
    r.r[1] = value;

    _kernel_swi(GPIO_WriteEvent, &r, &r);
}

int features_gpio(void)
{
    _kernel_swi_regs r;

    _kernel_swi(GPIO_Features, &r, &r);

    return r.r[0]; // Usually returns 0 or 1
}