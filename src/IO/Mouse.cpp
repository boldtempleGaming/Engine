#include "Mouse.h"

int Mouse::_wheel_x = 0; 
int Mouse::_wheel_y = 0;

void Mouse::SetWheel(const int& x, const int& y) {
    _wheel_x = x;
    _wheel_y = y;
}

void Mouse::ResetWheel(){
    if(_wheel_x != 0 || _wheel_y != 0){
        _wheel_x = 0;
        _wheel_y = 0;
    }
}