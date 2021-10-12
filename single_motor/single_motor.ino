#include <CrcLib.h>
using namespace Crc;

void setup()
{
  CrcLib::Initialize();

  CrcLib::InitializePwmOutput(CRC_PWM_5);

  CrcLib::SetDigitalPinMode(CRC_DIG_4, OUTPUT);

  //Not necessary
  Serial.begin(9600);
}

void loop()
{
  CrcLib::Update();
  //Not necessary
  //unsigned int deltaMicros = CrcLib::GetDeltaTimeMicros();
  //Serial.println(deltaMicros);
  Test(8);

}

void Test(int MyPWM) {
  if (CrcLib::ReadDigitalChannel(BUTTON::R2)) {
    CrcLib::SetDigitalOutput(CRC_DIG_4, HIGH);
    CrcLib::SetPwmOutput(CRC_PWM_5, 127);
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
    CrcLib::SetPwmOutput(CRC_PWM_5, 0);
    Serial.println("noButt");
  }


}
