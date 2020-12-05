#include "RPI.h"

int main()
{

  if(map_peripheral(&gpio) == -1)
  {
    printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
    return -1;
  }
  else
  {
    printf("Succeded to map the physical GPIO registers into the virtual memory space.\n");
  }


  // Define pin 7 as output
  INP_GPIO(4);
  OUT_GPIO(4);

  printf("Going into infinite while loop...\n");

  while(1)
  {
    // Toggle pin 7 (blink a led!)
    printf("LED on\n");
    GPIO_SET = 1 << 4;
    for(unsigned int i=0; i<1E8; i++);
    //sleep(1);

    printf("LED off\n");
    GPIO_CLR = 1 << 4;
    for(unsigned int i=0; i<1E8; i++);
    //sleep(1);
  }

  return 0;
}
