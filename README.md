# Raspberry Pi projects
A few, simple, Raspberry Pi projects
<p align="center">
  <img src="GPIO-Pinout-Diagram.png" width=800/>
</p>

## Development Setup
+ [Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/?resellerType=home)
+ [Raspberry Pi OS with desktop and recommended software](https://downloads.raspberrypi.org/raspios_full_armhf/images/raspios_full_armhf-2020-12-04/2020-12-02-raspios-buster-armhf-full.zip)
+ [Latest available Linux kernel (rpi-5.10.y)](https://github.com/raspberrypi/linux/tree/rpi-5.10.y) builded following instructions from [here (*Local building* section)](https://www.raspberrypi.org/documentation/linux/kernel/building.md) and from [here](https://www.kernel.org/doc/html/latest/kbuild/headers_install.html)
+ [libgpiod (master)](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/tree/?h=master) builded following istructions from [here](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/about/)

## Projects
+ [A classic Blink project with variable speed.](https://github.com/nicola-masarone/raspberrypi-projects/tree/main/libgpiod-blink-variable-speed) This project aims to close the loop between input and output on a Raspberry Pi board. Using a push-button we can change the LED blinking speed, in a circular way so that when the speed reaches the max value then it returns to the minimum at the next button press.
