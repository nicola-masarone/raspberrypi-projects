# PWM management using sysfs
This project shows how to use PWM output on Raspberry Pi via appropriate calls to /sys/class/pwm/
## Presettings
Please note that in order to use PWM output on the 40 pin Raspberry Pi header we have to enable this functionality. One way is to add a line in the board configuration file */boot/config.txt* with the following content: 
```
# Configures PWM0 on pin 12: 12,4(Alt0)
dtoverlay=pwm,pin=12,func=4
```
In this manner we have GPIO12(PWM0), i.e. pin#32 on board header, set as PWM output. 
These settings have been taken from */boot/overlays/README* file (line 2176):
```
Name:   pwm
Info:   Configures a single PWM channel
        Legal pin,function combinations for each channel:
          PWM0: 12,4(Alt0) 18,2(Alt5) 40,4(Alt0)            52,5(Alt1)
          PWM1: 13,4(Alt0) 19,2(Alt5) 41,4(Alt0) 45,4(Alt0) 53,5(Alt1)
        N.B.:
          1) Pin 18 is the only one available on all platforms, and
             it is the one used by the I2S audio interface.
             Pins 12 and 13 might be better choices on an A+, B+ or Pi2.
          2) The onboard analogue audio output uses both PWM channels.
          3) So be careful mixing audio and PWM.
          4) Currently the clock must have been enabled and configured
             by other means.
Load:   dtoverlay=pwm,<param>=<val>
Params: pin                     Output pin (default 18) - see table
        func                    Pin function (default 2 = Alt5) - see above
        clock                   PWM clock frequency (informational)
```
