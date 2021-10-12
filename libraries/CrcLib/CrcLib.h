#ifndef CrcLib_h
#define CrcLib_h

#include <Arduino.h>
#include <Servo.h>
#include "CrcXbee.h"
#include "CrcNeo.h"
#include "CrcBuzz.h"

namespace Crc
{
    //---------- Constants or Defaults ------------
    static const int DEFAULT_DEBOUNCE = 5;
    static const int DEFAULT_DEADBAND = 4;

    //Array for all possible pin numbers
    static const int PIN_ARRAY_LENGTH = 70;

    //Exposed analog pins
    #define CRC_ANA_1 A0
    #define CRC_ANA_2 A1
    #define CRC_ANA_3 A2
    #define CRC_ANA_4 A3

    //Exposed digital pins
    #define CRC_DIG_1 22
    #define CRC_DIG_2 23
    #define CRC_DIG_3 24
    #define CRC_DIG_4 25
    #define CRC_DIG_5 26
    #define CRC_DIG_6 27
    #define CRC_DIG_7 28
    #define CRC_DIG_8 29
    #define CRC_DIG_9 30
    #define CRC_DIG_10 31
    #define CRC_DIG_11 A4
    #define CRC_DIG_12 A5

    //Exposed pwm pins
    #define CRC_PWM_1 4
    #define CRC_PWM_2 5
    #define CRC_PWM_3 6
    #define CRC_PWM_4 7
    #define CRC_PWM_5 8
    #define CRC_PWM_6 9
    #define CRC_PWM_7 10
    #define CRC_PWM_8 11
    #define CRC_PWM_9 12
    #define CRC_PWM_10 13
    #define CRC_PWM_11 44
    #define CRC_PWM_12 45

    //Temperature
    #define CRC_LM35D A14

    //Battery voltage
    #define CRC_VBATT A15

    //SPI pins
    #define CRC_SPI_MISO 50
    #define CRC_SPI_MOSI 51
    #define CRC_SPI_SCK 52
    #define CRC_SPI_SS 53

    //I2C pins
    #define CRC_I2C_A 20 //SDA
    #define CRC_I2C_B 21 //SCL

    //Serial pins, also interrupt
    #define CRC_SERIAL_A 18 //TXD1
    #define CRC_SERIAL_B 19 //RXD1

    //Encoder pins
    #define CRC_ENCO_A 2
    #define CRC_ENCO_B 3


    //ERROR condes
    #define ERROR_UNSAFE_DIGITAL_PIN 1
    #define ERROR_UNSAFE_ANALOG_PIN 2
    #define ERROR_UNSAFE_PWM_PIN 3
    #define ERROR_UNSAFE_PWM_DIG_PIN 4

    #define ERROR_PIN_UNBINDABLE 10
    #define ERROR_PIN_BOUND_TO_ANALOG 11
    #define ERROR_PIN_BOUND_TO_BUTTON 12

    #define ERROR_INCORRECT_DIGITAL_VALUE 20

    #define ERROR_SERVO_ALREADY_INITIALIZED 30
    #define ERROR_SERVO_NOT_INITIALIZED 31
    #define ERROR_INCORRECT_SERVO_PERIODS 32


    //Button mapping for use with readAnalogChannel(uint8_t channel)
    enum class ANALOG : uint8_t
    {
        LCHANX = 2,
        LCHANY = 3,
        RCHANX = 4,
        RCHANY = 5,
        NONE = 255
    };

    //Button mapping for use with readDigitalChannel(uint8_t channel)
    enum class BUTTON : uint8_t
    {
        SELECT = 0,
        START = 1,
        L1 = 2,
        L2 = 3,
        L3 = 4,
        R1 = 5,
        R2 = 6,
        R3 = 7,
        UP = 8,
        RIGHT = 9,
        DOWN = 10,
        LEFT = 11,
        GREENONE = 12,
        REDTWO = 13,
        BLUETHREE = 14,
        PINKFOUR = 15,
        NONE = 255
    };
    //---------------------------------------------

    class CrcLib
    {
        public:

            /** Default constructor. */
            CrcLib();

            static void Initialize();
            static void Initialize(int debounce, int deadband);

            /** Takes care of any calls or calculations that have to be done continuously (every loop).
            * If any features requiring a continuous update are being used, such as
            * automatically binding channels to ports, this function should be called
            * once in the "loop" function of your .ino file.
            */
            static void Update();

            //Returns the time in millis since the last update.
            //This has a strong possibility if being very small (0 or 1)
            //if nothing else is happening in the loop, in which case
            //the micros function should be used instead.
            static unsigned int GetDeltaTimeMillis();

            //Returns the time in micros since the last update.
            static unsigned int GetDeltaTimeMicros();

            /** Sets the pin mode for a digital pin.
            * Should be "INPUT", "OUTPUT", or "INPUT_PULLUP".
            */
            static void SetDigitalPinMode(unsigned char pin, unsigned char mode);

            /** Gets the input from a digital pin. */
            static unsigned char GetDigitalInput(unsigned char pin);

            /** Sets the value of a digital pin.
            * Should be "LOW" or "HIGH".
            */
            static void SetDigitalOutput(unsigned char pin, unsigned char value);

            /** Check if a given pin is an allowed digital pin. */
            static bool IsSafeDigitalPin(unsigned char pin);

            /** Sets the value of a digital pin. */
            static void SetPwmOutput(unsigned char pin, char value);

            static void InitializePwmOutput(unsigned char pin);

            static void InitializePwmOutput(unsigned char pin, int minPeriod, int maxPeriod);

            static void InitializePwmOutput(unsigned char pin, bool reverse);

            static void InitializePwmOutput(unsigned char pin, int minPeriod, int maxPeriod, bool reverse);

            /** Check if a given pin is an allowed pwm pin. */
            static bool IsSafePwmPin(unsigned char pin);

            /** Gets the input from an analog pin. */
            static unsigned int GetAnalogInput(unsigned char pin);

            /** Checks if a given pin is an allowed analog pin. */
            static bool IsSafeAnalogPin(unsigned char pin);

            static void BindPinToButton(unsigned char pin, BUTTON button);

            static void BindPinToAnalog(unsigned char pin, ANALOG analog);

            /** Resets a pin binding. */
            static void UnbindPin(unsigned char pin);

            /** Read battery voltage. */
            /* Correction allows to compensate tiny resistance difference between everyboards. A perfect board would have  acorerction of 1.0 */
            static float GetBatteryVoltage(float correction);

            // Reads a digital channel value from the remote
            // To be used with btn::channel enum
            static bool ReadDigitalChannel(BUTTON channel);

            // Reads an analog (-127 to 127) value from the joysticks
            // To be used with analog::channel enum
            static int8_t ReadAnalogChannel(ANALOG channel);

            // Sets two (-127 to 127) values to two motors
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveTank(int8_t leftChannel, int8_t rightChannel, unsigned char leftMotor, unsigned char rightMotor);

            // Sets two analog channels to two motors
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveTank(ANALOG leftChannel, ANALOG rightChannel, unsigned char leftMotor, unsigned char rightMotor);

            // Sets two (-127 to 127) values to four motors
            // Make sure to use IntializePWMOutput first for each motor!
            // Motors on each side are sent the same command
            static void MoveTank(int8_t leftChannel, int8_t rightChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            // Sets two analog channels to four motors
            // Make sure to use IntializePWMOutput first for each motor!
            // Motors on each side are sent the same command
            static void MoveTank(ANALOG leftChannel, ANALOG rightChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            // Sets two (-127 to 127) values to two motors in an arcade fashion
            // fChannel corresponds to the forwards/backwards input
            // yChannel corresponds to the yaw (rotation) channel
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveArcade(int8_t forwardChannel, int8_t yawChannel, unsigned char leftMotor, unsigned char rightMotor);

            // Sets two analog channels to two motors in an arcade fashion
            // fChannel corresponds to the forwards/backwards input
            // yChannel corresponds to the yaw (rotation) channel
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveArcade(ANALOG forwardChannel, ANALOG yawChannel, unsigned char leftMotor, unsigned char rightMotor);

            // Sets two (-127 to 127) values to four motors in an arcade fashion
            // fChannel corresponds to the forwards/backwards input
            // yChannel corresponds to the yaw (rotation) channel
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveArcade(int8_t forwardChannel, int8_t yawChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            // Sets two analog channels to four motors in an arcade fashion
            // fChannel corresponds to the forwards/backwards input
            // yChannel corresponds to the yaw (rotation) channel
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveArcade(ANALOG forwardChannel, ANALOG yawChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            // Sets two analog channels to four motors in an holonomic fashion, to be used with omni wheels
            // forwardChannel corresponds to the forwards/backwards input
            // yawChannel corresponds to the yaw (rotation) channel
            // strafeChannel corresponds to the strafing (side to side) channel
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveHolonomic(int8_t forwardChannel, int8_t yawChannel, int8_t strafeChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            // Sets two analog channels to four motors in an holonomic fashion, to be used with omni wheels
            // forwardChannel corresponds to the forwards/backwards input
            // yawChannel corresponds to the yaw (rotation) channel
            // strafeChannel corresponds to the strafing (side to side) channel
            // Make sure to use IntializePWMOutput first for each motor!
            static void MoveHolonomic(ANALOG forwardChannel, ANALOG yawChannel, ANALOG strafeChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            static void Belise(int8_t forwardChannel, int8_t yawChannel, int8_t strafeChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);

            static void Belise(ANALOG forwardChannel, ANALOG yawChannel, ANALOG strafeChannel, unsigned char frontLeftMotor, unsigned char backLeftMotor, unsigned char frontRightMotor, unsigned char backRightMotor);



        private:

            struct ServoInfo
            {
                Servo* servo;
                int minPeriod;
                int maxPeriod;
                int reverse;
            };

            /** Sets up any pin initialization stuff. */
            static void SetupPins();

            /** Updates the time and delta time variables. */
            static void UpdateTime();

            /** Updates any pins which have been bound to channels. */
            static void UpdateBoundPins();

            // Updates a particular bound pin.
            static void UpdatePinButton(unsigned char pin);
            static void UpdatePinAnalog(unsigned char pin);

            /** Stops all stuff that's currently happening and displays some form of error output. */
            static void StopEverythingFromError(unsigned char errorCode);

            static unsigned char GetErrorTune(unsigned char errorCode);

            static unsigned char GetErrorLightPattern(unsigned char errorCode);

            //Reset all outputs that were potentially set to 0
            static void StopAllOutput();

            static int PinToServoIndex(unsigned char pin);

            // The time in microseconds at the beginning of the current update. Used to determine the delta time.
            static unsigned long _lastUpdateTime;

            //The time in microseconds since the last update
            static unsigned int _deltaTime;

            //Last known communication state
            static bool _commsLastConnected;

            static int _debounce;
            static int _deadband;

            static BUTTON _pinBindingsButton[PIN_ARRAY_LENGTH];
            static ANALOG _pinBindingsAnalog[PIN_ARRAY_LENGTH];

            static ServoInfo _servos[12];

            static unsigned char _pwmPins[12];

            /** Neopixel pin */
            static const unsigned char CRC_LED_NEO;

            /** Status LED pin, green. */
            static const unsigned char CRC_LED_ST;

            /** Fail LED pin, red. */
            static const unsigned char CRC_LED_FAIL;

            /** Buzzer pin */
            static const unsigned char CRC_BUZZER;

            /** 2560 output going to TXD pin of the Board XBee */
            static const unsigned char CRC_TXD_XBEE;

            /** 2560 input coming from RXD pin of the Board XBee */
            static const unsigned char CRC_RXD_XBEE;

            static CrcUtility::CrcNeo _crcNeo;

            static CrcUtility::CrcXbee _crcXbee;

            static CrcUtility::CrcBuzz _crcBuzz;
    };

}

#endif
