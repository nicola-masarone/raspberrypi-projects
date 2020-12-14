#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_MAX 20
#define FILE_WRITE_DELAY 100E3  // us
#define LOOP_DELAY 10E3         // us

#define PWM_PERIOD 10000000     // ns
#define DUTY_MIN 0              // ns
#define DUTY_MAX PWM_PERIOD     // ns
#define DUTY_DELTA 100000       // ns

int main()
{
    char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd, duty_cycle = DUTY_MIN;

	fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
	if (fd == -1) {goto error_exit;}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", 0);
	write(fd, buffer, bytes_written);
	close(fd);

	usleep(FILE_WRITE_DELAY);

	fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
	if (fd == -1) {goto error_exit;}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", PWM_PERIOD);
	write(fd, buffer, bytes_written);
	close(fd);

	usleep(FILE_WRITE_DELAY);

	fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
	if (fd == -1) {goto error_exit;}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", duty_cycle);
	write(fd, buffer, bytes_written);
	close(fd);

	usleep(FILE_WRITE_DELAY);

	fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
	if (fd == -1) {goto error_exit;}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", 1);
	write(fd, buffer, bytes_written);
	close(fd);

    usleep(FILE_WRITE_DELAY);

    fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    if (fd == -1) {goto error_exit;}

    printf("This program modifies LED brightness with PWM, in 5 cycles.\n");
	for(int i=0; i<5; i++)
	{
        printf("Cycle number: %d\n", i+1);
        for(duty_cycle=DUTY_MIN; duty_cycle<=DUTY_MAX; duty_cycle+=DUTY_DELTA)
        {
            bytes_written = snprintf(buffer, BUFFER_MAX, "%d", duty_cycle);
            write(fd, buffer, bytes_written);
            usleep(LOOP_DELAY);
        }
        for(duty_cycle=DUTY_MAX; duty_cycle>=DUTY_MIN; duty_cycle-=DUTY_DELTA)
        {
            bytes_written = snprintf(buffer, BUFFER_MAX, "%d", duty_cycle);
            write(fd, buffer, bytes_written);
            usleep(LOOP_DELAY);
        }
	}
    close(fd);
    usleep(FILE_WRITE_DELAY);

	fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
	if (fd == -1) {goto error_exit;}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", 0);
	write(fd, buffer, bytes_written);
	close(fd);

	usleep(FILE_WRITE_DELAY);

    fd = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
	if (fd == -1) {goto error_exit;}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", 0);
	write(fd, buffer, bytes_written);
	close(fd);

	usleep(FILE_WRITE_DELAY);

	error_exit:
        close(fd);

    return 0;
}
