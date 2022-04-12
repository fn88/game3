#include "set_up.h"
#include "raylib.h"
#include "models.h"



void update_counters()
{
    if (counter1 < 16000) counter1++;
    else counter1 = 0;
}



