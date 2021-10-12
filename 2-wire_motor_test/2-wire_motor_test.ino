#include <CrcLib.h>
using namespace Crc;
#define LEFT_MOTOR CRC_PWM_5
#define RIGHT_MOTOR CRC_PWM_6

void setup()
{

    CrcLib::Initialize();
    //Initialize on pin CRC_PWM_5 with all default values
    CrcLib::InitializePwmOutput(LEFT_MOTOR);

    //This one will be the same on CRC_PWM_6 but reversed
    CrcLib::InitializePwmOutput(RIGHT_MOTOR, true);

    //Let's say your motor has a min period of 2400 and max period of 3600.
    //Then you'd want to initialize it like this in order for the conversion from
    //[-127, 127] to a PWM signal to work properly and use the full range of your servo
    CrcLib::InitializePwmOutput(CRC_PWM_9, 2400, 3600);
}
