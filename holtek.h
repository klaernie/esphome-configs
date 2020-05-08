#include "esphome.h"

class HoltekChip : public Component {
 public:
  void setup() override {
    // Initialize the device here. Usually Wire.begin() will be called in here,
    // though that call is unnecessary if you have an 'i2c:' entry in your config

    //Wire.begin();
  }
  void loop() override {
    byte DATA = 0;
    Wire.beginTransmission(0x50);
    Wire.write(0x0D);
    Wire.endTransmission();
    Wire.requestFrom(0x50, 1);
    while (Wire.available()) { // slave may send less than requested
      DATA = Wire.read(); // receive a DATA as character
      ESP_LOGD("custom",
              "got: %x",
              DATA
      );
    }
  }
};
