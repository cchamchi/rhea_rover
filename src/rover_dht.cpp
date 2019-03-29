#include "rover_dht.h"

#define MIN_INTERVAL 2000
#define TIMEOUT -1

DHT::DHT(uint8_t pin, uint8_t type, uint8_t count) {
  _pin = pin;
  _type = type;
  #ifdef __AVR
    _bit = digitalPinToBitMask(pin);
    _port = digitalPinToPort(pin);
  #endif
  _maxcycles = microsecondsToClockCycles(1000);  
}

void DHT::begin(uint8_t usec) {
  pinMode(_pin, INPUT_PULLUP);
   _lastreadtime = millis() - MIN_INTERVAL;
  pullTime = usec;
}

//boolean S == Scale.  True == Fahrenheit; False == Celcius
float DHT::readTemperature(bool S, bool force) {
  float f = NAN;

  if (read(force)) {
    switch (_type) {
    case DHT11:
      f = data[2];
      if (data[3] & 0x80) {
        f = -1 - f ;
      }
      f += (data[3] & 0x0f) * 0.1;
      if(S) {
        f = convertCtoF(f);
      }
      break;
    
      }
  }
  return f;
}

float DHT::convertCtoF(float c) {
  return c * 1.8 + 32;
}

float DHT::convertFtoC(float f) {
  return (f - 32) * 0.55555;
}

float DHT::readHumidity(bool force) {
  float f = NAN;
  if (read(force)) {
    switch (_type) {
    case DHT11:

      f = data[0] + data[1] * 0.1;
      break;
     }
  }
  return f;
}

//boolean isFahrenheit: True == Fahrenheit; False == Celcius
float DHT::computeHeatIndex(bool isFahrenheit) {
  float hi = computeHeatIndex(readTemperature(isFahrenheit), readHumidity(),
    isFahrenheit);
  return isFahrenheit ? hi : convertFtoC(hi);
}

//boolean isFahrenheit: True == Fahrenheit; False == Celcius
float DHT::computeHeatIndex(float temperature, float percentHumidity,
  bool isFahrenheit) {
  float hi;

  if (!isFahrenheit)
    temperature = convertCtoF(temperature);

  hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) + (percentHumidity * 0.094));

  if (hi > 79) {
    hi = -42.379 +
             2.04901523 * temperature +
            10.14333127 * percentHumidity +
            -0.22475541 * temperature*percentHumidity +
            -0.00683783 * pow(temperature, 2) +
            -0.05481717 * pow(percentHumidity, 2) +
             0.00122874 * pow(temperature, 2) * percentHumidity +
             0.00085282 * temperature*pow(percentHumidity, 2) +
            -0.00000199 * pow(temperature, 2) * pow(percentHumidity, 2);

    if((percentHumidity < 13) && (temperature >= 80.0) && (temperature <= 112.0))
      hi -= ((13.0 - percentHumidity) * 0.25) * sqrt((17.0 - abs(temperature - 95.0)) * 0.05882);

    else if((percentHumidity > 85.0) && (temperature >= 80.0) && (temperature <= 87.0))
      hi += ((percentHumidity - 85.0) * 0.1) * ((87.0 - temperature) * 0.2);
  }

  return isFahrenheit ? hi : convertFtoC(hi);
}

bool DHT::read(bool force) {
  uint32_t currenttime = millis();
  if (!force && ((currenttime - _lastreadtime) < MIN_INTERVAL)) {
    return _lastresult; // return last correct measurement
  }
  _lastreadtime = currenttime;

  // Reset 40 bits of received data to zero.
  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

#if defined(ESP8266)
    yield(); // Handle WiFi / reset software watchdog
#endif


  pinMode(_pin, INPUT_PULLUP);
  delay(1);

  // First set data line low for a period according to sensor type
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  switch(_type) {
    case DHT11:
    default:
      delay(20); //data sheet says at least 18ms, 20ms just to be safe
      break;
  }
}
 
uint32_t DHT::expectPulse(bool level) {
#if (F_CPU > 16000000L)
  uint32_t count = 0;
#else
  uint16_t count = 0; // To work fast enough on slower AVR boards
#endif
    #ifdef __AVR
    uint8_t portState = level ? _bit : 0;
    while ((*portInputRegister(_port) & _bit) == portState) {
      if (count++ >= _maxcycles) {
        return TIMEOUT; // Exceeded timeout, fail.
      }
    }
    #else
    while (digitalRead(_pin) == level) {
      if (count++ >= _maxcycles) {
        return TIMEOUT; // Exceeded timeout, fail.
      }
    }
  #endif

  return count;
}