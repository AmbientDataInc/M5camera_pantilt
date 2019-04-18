#ifndef JOYSTICK_H
#define JOYSTKCH_H

#define GAP 10

class JOYSTICK {
public:
    JOYSTICK(void) {};
    virtual ~JOYSTICK(void) {};
    void begin(uint8_t);
    void read(void);
    int x(void);
    int y(void);
    bool button(void);
private:
    uint8_t _addr;
    int Xref, Yref;  // x、yの基準値
    int _x, _y;    // x、yの最新値
    bool _button = false;  // ボタンの最新値
};

#endif // JOYSTICK_H
