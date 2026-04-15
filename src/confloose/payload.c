#include <stdlib.h>

#include "payload.h"

int screen_rotator()
{
    ssize_t choice = rand();
    
    if (choice < RAND_MAX / 4)
        system("xrandr -o right");
    
    else if (choice < RAND_MAX / 2)
        system("xrandr -o left");

    else if (choice < RAND_MAX / 4 * 3)
        system("xrandr -o inverted");
    
    else
        system("xrandr -o normal");

    return 0;
}
