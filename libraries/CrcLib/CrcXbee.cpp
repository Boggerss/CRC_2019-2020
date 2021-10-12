#include "CrcXbee.h"

namespace CrcUtility
{
    bool CrcXbee::ReadDigitalChannel(uint8_t channel) const
    {
        return  (channel > 7) ? bitRead(_payload[1], channel - 8) : bitRead(_payload[0], channel);
    }

    int8_t CrcXbee::ReadAnalogChannel(uint8_t channel) const
    {
        //Convert (0 to 255) to (-127 to 127) 
        return _payload[channel] == 255 ? 127 : _payload[channel] - 127;
    }

    void CrcXbee::Initialize()
    {
        Serial2.begin(115200);
        _xbee.setSerial(Serial2);
    }

    void CrcXbee::UpdateData()
    {

        _xbee.readPacket();

        if (_xbee.getResponse().isAvailable())
        {
            //Serial.println("Packet available");
            if (_xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
            {
                _xbee.getResponse().getZBRxResponse(_rx);
                for (int i{}; i < _rx.getDataLength(); ++i) {
                    _payload[i] = _rx.getData(i);
                }
                _communicationValid = true;
                _lastUpdate = millis();
                //Serial.println(millis());
            }
        }
        else if (_lastUpdate < millis() - _maxNoUpdateDelay)
        {
            //_rx.reset();
            ResetPayload();
            _communicationValid = false;
        }

        //Remove once running correctly
        //PrintPayload();
    }

    void CrcXbee::PrintPayload()
    {
            for (int b = 7; b >= 0; b--)
            {
                Serial.print(bitRead(_payload[0], b));
            }
            Serial.println("");
            for (int b = 7; b >= 0; b--)
            {
                Serial.print(bitRead(_payload[1], b));
            }
            Serial.println("");
            Serial.print("Left X: ");
            Serial.println(static_cast<uint16_t>(_payload[2]));
            Serial.print("Left Y: ");
            Serial.println(static_cast<uint16_t>(_payload[3]));
            Serial.print("Right X: ");
            Serial.println(static_cast<uint16_t>(_payload[4]));
            Serial.print("Right Y: ");
            Serial.println(static_cast<uint16_t>(_payload[5]));

    }
    void CrcXbee::ResetPayload()
    {
        _payload[0] = 0;
        _payload[1] = 0;
        _payload[2] = 127;
        _payload[3] = 127;
        _payload[4] = 127;
        _payload[5] = 127;

    }
    bool CrcXbee::IsCommValid() const
    {
        return _communicationValid;
    }
}
