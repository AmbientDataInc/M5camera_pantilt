#include <Arduino.h>
#include "Wire.h"
#include "JoyStick.h"

void JOYSTICK::begin(uint8_t addr) {
    _addr = addr;
    Xref = Yref = 0;
    for (int i = 0; i < 10; i++) {  // x、ｙの値を10回読んで、基準値を求める
        Wire.requestFrom(_addr, 3);
        if (Wire.available()) {
            Xref += Wire.read();
            Yref += Wire.read();
            Wire.read();  // button data
        }
        delay(50);
    }
    _x = Xref /= 10;
    _y = Yref /= 10;
    Serial.printf("Xref:%d Yref:%d\r\n", Xref, Yref);
}

void JOYSTICK::read(void) {
    Wire.requestFrom(_addr, 3);
    if (Wire.available()) {
        _x = Wire.read();
        _y = Wire.read();
        _button = Wire.read();
    }
}

int JOYSTICK::x(void) {
    if ((_x - Xref) > GAP) return 1;
    else if ((_x - Xref) < -GAP)  return -1;
    else return 0;
}

int JOYSTICK::y(void) {
    if ((_y - Yref) > GAP) return -1;
    else if ((_y - Yref) < -GAP)  return 1;
    else return 0;
}

bool JOYSTICK::button(void) {
    return _button;
}
