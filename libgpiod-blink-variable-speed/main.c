#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include<pthread.h>

#ifndef	CONSUMER
#define	BUTTON "Button"
#define LED "LED"
#endif

#define MAX_LED_PERIOD 500E3
#define MIN_LED_PERIOD 10E3

int LED_period = MAX_LED_PERIOD;    // LED period in us

char *chipname = "gpiochip0";
unsigned int input_offset = 24;	// GPIO Pin #24
unsigned int output_offset = 4;	// GPIO Pin #4
struct timespec ts = { 1, 0 };
struct gpiod_line_event event;
struct gpiod_chip *chip;
struct gpiod_line *input_line, *output_line;
int ret;

struct timeval before = {0, 0}, now = {0, 0};
long secs_used, micros_used;

void *res;

struct thread_info
{    /* Used as argument to thread_start() */
       pthread_t thread_id;        /* ID returned by pthread_create() */
       int       thread_num;       /* Application-defined thread # */
};

struct thread_info blink_LED_tinfo;
struct thread_info capture_button_tinfo;


// Thread blink_LED: toggles LED on/off
void* blink_LED(void* arg)
{
    bool LED_status=0;
    int ret=0;

    while(!ret)
    {
        usleep(LED_period);
        LED_status = !LED_status;
        ret = gpiod_line_set_value(output_line, LED_status);
        printf("                        \r");
        printf("LED period: %d ms\r", 2*LED_period/1000);
        fflush(NULL);
    }
    return NULL;
}

// Thread capture_button
void* capture_button(void* arg)
{
    int ret=0;

	while(!ret)
	{
		ret = gpiod_line_event_wait(input_line, &ts);
		switch(ret)
		{
            case -1:                // an error occured during gpiod_line_event_wait()
            break;
            case 1:                 // an event occured during gpiod_line_event_wait()
                ret = gpiod_line_event_read(input_line, &event);
                if(event.event_type==GPIOD_LINE_EVENT_FALLING_EDGE)
                {
                    gettimeofday (&now, NULL );
                    secs_used = now.tv_sec - before.tv_sec;
                    micros_used = ((secs_used*1E6) + now.tv_usec) - before.tv_usec;

                    if(micros_used>2E5)
                    {
                        before = now;
                        LED_period/=2;
                        if(LED_period<MIN_LED_PERIOD)
                            LED_period=MAX_LED_PERIOD;
                    }
                }
                ret=0;
            break;
        }
    }

    return NULL;
}


int main(int argc, char **argv)
{
	chip = gpiod_chip_open_by_name(chipname);
	if (!chip)
        goto end;

	input_line = gpiod_chip_get_line(chip, input_offset);
	if (!input_line)
        goto close_chip;

	output_line = gpiod_chip_get_line(chip, output_offset);
	if (!output_line)
        goto close_chip;

	ret = gpiod_line_request_falling_edge_events_flags(input_line, BUTTON, GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
	if (ret!=0)
	{
        gpiod_line_release(input_line);
        goto close_chip;
	}

    ret = gpiod_line_request_output(output_line, LED, 0);
	if (ret!=0)
	{
        gpiod_line_release(input_line);
        gpiod_line_release(output_line);
        goto close_chip;
    }


    ret = pthread_create(&blink_LED_tinfo.thread_id, NULL, &blink_LED, &blink_LED_tinfo);

    ret = pthread_create(&capture_button_tinfo.thread_id, NULL, &capture_button, &capture_button_tinfo);

    ret = pthread_join(blink_LED_tinfo.thread_id, &res);
    free(res);
    ret = pthread_join(capture_button_tinfo.thread_id, &res);
    free(res);

close_chip:
	gpiod_chip_close(chip);
end:
	return ret;
}
