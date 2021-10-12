#include <CrcLib.h>

using namespace Crc;

#define  LEFT_MOTOR CRC_PWM_5
#define  RIGHT_MOTOR CRC_PWM_6

int8_t leftJoystickY = 0;
int8_t rightJoystickX = 0;

void Test(unsigned char pin, BUTTON button1, BUTTON button2);

void setup()
{
    CrcLib::Initialize();

    CrcLib::InitialisePwmOutput(LEFT_MOTOR);
    CrcLib::InitialisePwmOutput(RIGHT_MOTOR, true);

    CrcLib::SetDigitalPinMode(CRC_DIG_4, OUTPUT);

    CrcLib::BindPinToButton(CRC_PWM_9, BUTTON::DOWN);
}

void loop()
{
    CrcLib::Update();

    leftJoystickY = CrcLib::ReadAnalogChannel(ANALOG::LCHANY);
    rightJoystickX = CrcLib::ReadAnalogChannel(ANALOG::RCHANX);

    CrcLib::Arcade(leftJoystickY, rightJoystickX, LEFT_MOTOR, RIGHT_MOTOR)

    Test(CRC_DIG_4, BUTTON::L1, BUTTON::L2);
}

void Test(unsigned char pin, BUTTON button1, BUTTON button2){
  if(CrcLib::ReadDigitalChannel(button1) || CrcLib::ReadDigitalChannel(button2){
    CrcLib::SetDigitalOutput(pin, HIGH);
  }
  else{
    CrcLib::SetDigitalOutput(pin, LOW);
  }
}
