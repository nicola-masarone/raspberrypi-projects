#include <stdio.h>
#include <stdlib.h>
#include <gpiod.h>
#include <unistd.h>

#define LED_PIN 4

int main()
{
        struct gpiod_chip *gpiochip;
        struct gpiod_line *gpioline;
        int ret;

        gpiochip = gpiod_chip_open("/dev/gpiochip0");
        if (gpiochip == NULL)
                goto error1;
        printf("gpiochip open is ok\r\n");
        gpioline = gpiod_chip_get_line(gpiochip, LED_PIN);
        if (gpioline == NULL)
                goto error2;
        printf("gpioline open is ok\r\n");
        ret = gpiod_line_request_output(gpioline, "gpio", 0);
        if (ret != 0)
                goto error2;
        printf("request output is ok\r\n");
        for (int i = 0; i < 10; i++)
        {
                ret = gpiod_line_set_value(gpioline, 1);
                printf("LED on\r\n");
                sleep(1);
                ret = gpiod_line_set_value(gpioline, 0);
                printf("LED off\r\n");
                sleep(1);
        }
        gpiod_line_release(gpioline);
error2:
        gpiod_chip_close(gpiochip);
error1:
        return 0;
}
