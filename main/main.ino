#include <CrcLib.h>
using namespace Crc;

void setup()
{
  CrcLib::Initialize();

  CrcLib::InitializePwmOutput (CRC_PWM_12); // multi-use motor
  CrcLib::InitializePwmOutput (CRC_PWM_5); // front left
  CrcLib::InitializePwmOutput (CRC_PWM_7); // back left
  CrcLib::InitializePwmOutput (CRC_PWM_9, true); // front right
  CrcLib::InitializePwmOutput (CRC_PWM_11); // back right

  //Not necessary
  Serial.begin(9600);
}

void loop()
{
  CrcLib::Update();
  CrcLib::Belise (ANALOG :: LCHANY, ANALOG :: LCHANX, ANALOG::RCHANX, CRC_PWM_5, CRC_PWM_7, CRC_PWM_9, CRC_PWM_11);
  Test(8);

}

void Test(int MyPWM) {
  if (CrcLib::ReadDigitalChannel(BUTTON::R2)) {
    CrcLib::SetDigitalOutput(CRC_DIG_4, HIGH);
    CrcLib::SetPwmOutput(CRC_PWM_12, 127);
    bool R2Button = CrcLib::ReadDigitalChannel(BUTTON::R2);
    Serial.print(" R2-"); Serial.println(R2Button);
  }

  /*else if (CrcLib::ReadDigitalChannel(BUTTON::L2)) {
    CrcLib::SetDigitalOutput(CRC_DIG_4, HIGH);
    CrcLib::SetPwmOutput(CRC_PWM_5, -127);
    bool L2Button = CrcLib::ReadDigitalChannel(BUTTON::L2);
    Serial.print(" L2-"); Serial.println(L2Button);
  } */

  /*else if (CrcLib::ReadAnalogChannel(ANALOG::LCHANY)) {
    CrcLib::SetDigitalOutput(CRC_DIG_4, HIGH);
    CrcLib::SetPwmOutput(CRC_PWM_5, 127);
    unsigned char LjoyY = CrcLib::ReadAnalogChannel(ANALOG::LCHANY);
    Serial.print(" bruh"); Serial.println(LjoyY);
  }*/
  
  else {
    CrcLib::SetDigitalOutput(CRC_DIG_4, LOW);
    CrcLib::SetPwmOutput(CRC_PWM_12, 0);
    Serial.println("noButt");
  }


}
