#include <CrcLib.h>
using namespace Crc;
void setup()
{
    CrcLib::Initialize();

  //  static void Crc::CrcLib::InitialisePwmOutput(CRC_PWM_5);

    Serial.begin(19200);
}
void loop()
{
    CrcLib::Update();
  unsigned char LjoyY = Crc::CrcLib::ReadAnalogChannel(ANALOG::LCHANY);
  unsigned char LjoyX = Crc::CrcLib::ReadAnalogChannel(ANALOG::LCHANX);
  unsigned char RjoyY = Crc::CrcLib::ReadAnalogChannel(ANALOG::RCHANY);
  unsigned char RjoyX = Crc::CrcLib::ReadAnalogChannel(ANALOG::RCHANX);
  /*bool selectButton = CrcLib::ReadDigitalChannel(BUTTON::SELECT);
  bool startButton = CrcLib::ReadDigitalChannel(BUTTON::START);
  bool L1Button = CrcLib::ReadDigitalChannel(BUTTON::L1);
  bool L2Button = CrcLib::ReadDigitalChannel(BUTTON::L2);
  bool L3Button = CrcLib::ReadDigitalChannel(BUTTON::L3);
  bool R1Button = CrcLib::ReadDigitalChannel(BUTTON::R1);
  bool R2Button = CrcLib::ReadDigitalChannel(BUTTON::R2);
  bool R3Button = CrcLib::ReadDigitalChannel(BUTTON::R3);
  bool upButton = CrcLib::ReadDigitalChannel(BUTTON::UP);
  bool rightButton = CrcLib::ReadDigitalChannel(BUTTON::RIGHT);
  bool downButton = CrcLib::ReadDigitalChannel(BUTTON::DOWN);
  bool leftButton = CrcLib::ReadDigitalChannel(BUTTON::LEFT);
  bool greenButton = CrcLib::ReadDigitalChannel(BUTTON::GREENONE);
  bool redButton = CrcLib::ReadDigitalChannel(BUTTON::REDTWO);
  bool blueButton = CrcLib::ReadDigitalChannel(BUTTON::BLUETHREE);
  bool pinkButton = CrcLib::ReadDigitalChannel(BUTTON::PINKFOUR);*/
  
   /*Serial.print(" L2-");Serial.print(L2Button); 
   Serial.print(" R2-");Serial.print(R2Button); 
   Serial.print(" L1-");Serial.print(L1Button); 
   Serial.print(" R1-");Serial.print(R1Button);
   Serial.print(" L3-");Serial.print(L3Button); 
   Serial.print(" R3-");Serial.print(R3Button);
   Serial.print(" SEL-");Serial.print(selectButton); 
   Serial.print(" STAR-");Serial.print(startButton); 
   Serial.print(" up-");Serial.print(upButton); 
   Serial.print(" down-");Serial.print(downButton);
   Serial.print(" right-");Serial.print(rightButton); 
   Serial.print(" left-");Serial.print(leftButton);
   Serial.print(" G1-");Serial.print(greenButton); 
   Serial.print(" Re2-");Serial.print(redButton);
   Serial.print(" B3-");Serial.print(blueButton); 
   Serial.print(" P4-");Serial.print(pinkButton);*/
   Serial.print(" LJoy(");Serial.print(LjoyX); Serial.print(",");Serial.print(LjoyY); Serial.print(")");
   Serial.print(" RJoy(");Serial.print(RjoyX); Serial.print(",");Serial.print(RjoyY); Serial.print(")");
   Serial.println();  

}
