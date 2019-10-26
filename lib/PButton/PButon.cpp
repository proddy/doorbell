/*
 * Button Library
 * Inspired by:
 * http://jmsarduino.blogspot.nl/2009/10/4-way-button-click-double-click-hold.html
 * https://pastebin.com/87cCn6h9
 * https://forum.arduino.cc/index.php?topic=315909.0 
 * 
 */

#include "PButton.h"
#include <Arduino.h>

// Constructor
PButton::PButton(int pin, int pullMode, int Debounce, int DblClickDelay, int LongPressDelay, int VLongPressDelay) {
    _pin = pin;

    // Initialization of properties
    _Debounce        = Debounce;        // Debounce period to prevent flickering when pressing or releasing the button (in ms)
    _DblClickDelay   = DblClickDelay;   // Max period between clicks for a double click event (in ms)
    _LongPressDelay  = LongPressDelay;  // Hold period for a long press event (in ms)
    _VLongPressDelay = VLongPressDelay; // Hold period for a very long press event (in ms)

    // Initialization of variables
    _state              = true;  // Value read from button
    _lastState          = true;  // Last value of button state
    _dblClickWaiting    = false; // whether we're waiting for a double click (down)
    _dblClickOnNextUp   = false; // whether to register a double click on next release, or whether to wait and click
    _singleClickOK      = true;  // whether it's OK to do a single click (default is true)
    _downTime           = -1;    // time the button was pressed down
    _upTime             = -1;    // time the button was released
    _ignoreUP           = true;  // whether to ignore the button release because the click+hold was triggered, changed from false for ESP32
    _waitForUP          = false; // when held, whether to wait for the up event
    _longPressHappened  = false; // whether or not the hold event happened already
    _vLongPressHappened = false; // whether or not the long hold event happened already
    _pullMode           = pullMode; // 1=HIGH 0=LOW

    _buttonBusy = false; // idle

    //pinMode(_pin, INPUT_PULLUP);
    pinMode(_pin, INPUT); // for ESP32

    digitalWrite(_pin, LOW); // probably not needed, but just to be sure
}

void PButton::onClick(buttonEventHandler handler) {
    cb_onClick = handler;
}

void PButton::onDblClick(buttonEventHandler handler) {
    cb_onDblClick = handler;
}

void PButton::onLongPress(buttonEventHandler handler) {
    cb_onLongPress = handler;
}

void PButton::onVLongPress(buttonEventHandler handler) {
    cb_onVLongPress = handler;
}

bool PButton::check(void) {
    int  resultEvent = 0;
    long millisRes   = millis();

    //_state = digitalRead(_pin) == _pullMode;
    _state = digitalRead(_pin) == HIGH;

    //Serial.printf("%d %lu\n", _state, millisRes);

    // Button pressed down
    if (_state != _pullMode && _lastState == _pullMode && (millisRes - _upTime) > _Debounce) {
        // Serial.println("*pressed*");
        _downTime           = millisRes;
        _ignoreUP           = false;
        _waitForUP          = false;
        _singleClickOK      = true;
        _longPressHappened  = false;
        _vLongPressHappened = false;
        if ((millisRes - _upTime) < _DblClickDelay && _dblClickOnNextUp == false && _dblClickWaiting == true) {
            _dblClickOnNextUp = true;
            // Serial.println("*double up next*");
        } else {
            _dblClickOnNextUp = false;
        }
        _dblClickWaiting = false;

        _buttonBusy = true; // something is happening so we'll wait and see what action it is
    }

    // Button released

    else if (_state == _pullMode && _lastState != _pullMode && (millisRes - _downTime) > _Debounce) {
        if (_ignoreUP == false) {
            _upTime = millisRes;
            //Serial.println("*released*");
            if (_dblClickOnNextUp == false) {
                _dblClickWaiting = true;
            } else {
                resultEvent = 2;
                //Serial.println("*double*");
                _dblClickOnNextUp = false;
                _dblClickWaiting  = false;
                _singleClickOK    = false;
            }
        }
    }

    // Test for normal click event: DblClickDelay expired
    if (_state == _pullMode && (millisRes - _upTime) >= _DblClickDelay && _dblClickWaiting == true && _dblClickOnNextUp == false
        && _singleClickOK == true && resultEvent != 2) {
        //Serial.println("*single click!! pressed*");
        resultEvent      = 1;
        _dblClickWaiting = false;
    }


    // added code: raise OnLongPress event when only when the button is released
    if (_state == _pullMode && _longPressHappened && !_vLongPressHappened) {
        resultEvent        = 3;
        _longPressHappened = false;
    }

    // Test for hold
    if (_state != _pullMode && (millisRes - _downTime) >= _LongPressDelay) {
        // Trigger "normal" hold
        if (_longPressHappened == false) {
            // resultEvent = 3;
            _waitForUP        = true;
            _ignoreUP         = true;
            _dblClickOnNextUp = false;
            _dblClickWaiting  = false;
            // _downTime = millis();
            _longPressHappened = true;
        }
        // Trigger "long" hold
        if ((millisRes - _downTime) >= _VLongPressDelay) {
            if (_vLongPressHappened == false) {
                resultEvent         = 4;
                _vLongPressHappened = true;
                // _longPressHappened = false;
            }
        }
    }

    _lastState = _state;

    if (resultEvent == 1 && cb_onClick)
        cb_onClick(*this);
    if (resultEvent == 2 && cb_onDblClick)
        cb_onDblClick(*this);
    if (resultEvent == 3 && cb_onLongPress)
        cb_onLongPress(*this);
    if (resultEvent == 4 && cb_onVLongPress)
        cb_onVLongPress(*this);

    // if any action has been prefromed we can stop waiting, and become idle
    if (resultEvent >= 1 && resultEvent <= 4) {
        _buttonBusy = false;
    }

    return _buttonBusy;

} // PButton::check
