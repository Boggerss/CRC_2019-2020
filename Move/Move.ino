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
  CrcLib::SetDigitalPinMode(CRC_DIG_10, INPUT); // multi-use motor digital output

  Serial.begin(9600);  
}

void loop() 
{
  CrcLib::Update();
  bool dig10 = CrcLib::GetDigitalInput(CRC_DIG_10);
  bool L2Button = CrcLib::ReadDigitalChannel(BUTTON::L2);
  unsigned char LjoyY = LjoyY = Crc::CrcLib::ReadAnalogChannel(ANALOG::LCHANY);
  unsigned char LjoyX = LjoyX = Crc::CrcLib::ReadAnalogChannel(ANALOG::LCHANX);
  unsigned char RjoyY = RjoyY = Crc::CrcLib::ReadAnalogChannel(ANALOG::RCHANY);
  unsigned char RjoyX = RjoyX = Crc::CrcLib::ReadAnalogChannel(ANALOG::RCHANX); 

  CrcLib::Belise (ANALOG :: LCHANY, ANALOG :: LCHANX, ANALOG::RCHANX, CRC_PWM_5, CRC_PWM_7, CRC_PWM_9, CRC_PWM_11);

  LCCTest();
  //LCCSwitch();
  Serial.println(dig10);
}

void LCCTest()
{
  if (CrcLib::ReadDigitalChannel(BUTTON::L2)) {
    //CrcLib::SetDigitalOutput(CRC_DIG_4, HIGH);
    CrcLib::SetPwmOutput(CRC_PWM_12, 127);
    bool L2Button = CrcLib::ReadDigitalChannel(BUTTON::L2);
    //Serial.print(" L2-"); Serial.println(L2Button);
  }

    else {
    //CrcLib::SetDigitalOutput(CRC_DIG_4, LOW);
    CrcLib::SetPwmOutput(CRC_PWM_12, 0);
    //Serial.println("noButt");
  }
}

/*void LCCSwitch()
{
  if (digitalRead(CRC_DIG_10) == HIGH){
    CrcLib::SetPwmOutput(CRC_PWM_10, 127);
  }

  else {
    CrcLib::SetPwmOutput(CRC_PWM_12, 0);
  }
}*/
