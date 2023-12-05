#include <Arduino.h>

extern int setmotorspeed;
int previousspeed;

#define OPTO D6

int checkRPM()
{
    int speed = 0;
    speed = map(setmotorspeed, 0, 10000, 0, 9000);
    // long unsigned int previoustime = 0;
    // long unsigned int currenttime = 0;
    // long unsigned int starttime = 0;

    // starttime = millis();
    // for (int i = 0; i <= 100000; i++)
    // {

    //     previoustime = millis();
    //     long int temptime = starttime - previoustime;
    //     if (digitalRead(OPTO) == 1)
    //         break;
    //     else
    //         delay(1);
    //     if (temptime > 10000)
    //     {
    //         break;
    //     }

    //     delayMicroseconds(100);
    // }
    // delay(1);
    // for (int i = 0; i <= 100000; i++)
    // {

    //     currenttime = millis();
    //     long int temptime = starttime - currenttime;
    //     if (digitalRead(OPTO) == 0)
    //         break;
    //     else
    //         delay(1);
    //     if (temptime > 10000)
    //     {
    //         break;
    //     }
    //     delayMicroseconds(100);
    // }
    // double time = currenttime - previoustime;
    // if (time == 0)
    //     return 1;

    // speed = 6000 / time;
    return speed;
}