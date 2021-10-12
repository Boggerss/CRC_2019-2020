#ifndef CrcXbee_h
#define CrcXbee_h

#include <Arduino.h>
#include <XBee.h>

namespace CrcUtility
{
    class CrcXbee
    {
        public:
            CrcXbee() = default;
            ~CrcXbee() = default;
            CrcXbee(const CrcXbee & bee) = default;
            CrcXbee& operator=(const CrcXbee & bee) = default;

            //Reads the boolean value of a button on the remote
            bool ReadDigitalChannel(uint8_t channel) const;

            //Reads the analog (-127 to 127) value of a joystick on the remote
            int8_t ReadAnalogChannel(uint8_t channel) const;

            //Starts the serial channels
            void Initialize();

            //Reads the data and saves it to the payload
            void UpdateData();

            //Function that prints to the serial port the current state of the payload
            //For Debugging purposes only
            //Remove from your code for release
            void PrintPayload();

            //Sets the payload to the default values
            void ResetPayload();

            //Returns true if communication is currently updating
            bool IsCommValid() const;

        private:
            //Maps to each bit of byte 0 of payload
            //For Documentation Use only
            enum class _btnBitMap
            {
                //Byte 0
                SELECT = 0,
                START = 1,
                L1 = 2,
                L2 = 3,
                L3 = 4,
                R1 = 5,
                R2 = 6,
                R3 = 7,
                //Byte 1
                UP = 0,
                RIGHT = 1,
                DOWN = 2,
                LEFT = 3,
                GREENONE = 4,
                REDTWO = 5,
                BLUETHREE = 6,
                PINKFOUR = 7
            };

            //Channel mapping for use with readAnalogChannel(uint8_t channel)
            //For Documentation Use only
            enum class _analogMap
            {
                LCHANX = 2,
                LCHANY = 3,
                RCHANX = 4,
                RCHANY = 5,
            };

            //xBee Object that manages data
            XBee _xbee = XBee();

            //Received data payload
            uint8_t _payload[6]{0,0,0,0,0,0};

            //xBee status management
            ZBRxResponse _rx = ZBRxResponse();

            //Watchdog and communication timer
            long _lastUpdate = 0;

            //Maximum allowed time to update the payload
            const int _maxNoUpdateDelay = 500;

            //Value that is true if payload was updated within the last acceptable time frame
            bool _communicationValid = false;
    };
}

#endif
