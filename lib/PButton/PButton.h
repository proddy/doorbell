#ifndef _PButton_H_
#define _PButton_H_

#include <inttypes.h>

class PButton;
typedef void (*buttonEventHandler)(PButton &);

class PButton {
  public:
    PButton(int pin, int pullMode, int Debounce, int DblClickDelay, int LongPressDelay, int VLongPressDelay);

    void onClick(buttonEventHandler handler);
    void onDblClick(buttonEventHandler handler);
    void onLongPress(buttonEventHandler handler);
    void onVLongPress(buttonEventHandler handler);

    bool check(void);

  private:
    int _Debounce;        // Debounce period to prevent flickering when pressing or releasing the button (in ms)
    int _DblClickDelay;   // Max period between clicks for a double click event (in ms)
    int _LongPressDelay;  // Hold period for a long press event (in ms)
    int _VLongPressDelay; // Hold period for a very long press event (in ms)

    int  _pin;
    bool _pullMode;

    bool _state;            // Value read from button
    bool _lastState;        // Last value of button state
    bool _dblClickWaiting;  // whether we're waiting for a double click (down)
    bool _dblClickOnNextUp; // whether to register a double click on next release, or whether to wait and click
    bool _singleClickOK;    // whether it's OK to do a single click

    long _downTime; // time the button was pressed down
    long _upTime;   // time the button was released

    bool _ignoreUP;           // whether to ignore the button release because the click+hold was triggered
    bool _waitForUP;          // when held, whether to wait for the up event
    bool _longPressHappened;  // whether or not the hold event happened already
    bool _vLongPressHappened; // whether or not the long hold event happened already

    bool _buttonBusy; // false if idle

    buttonEventHandler cb_onClick, cb_onDblClick, cb_onLongPress, cb_onVLongPress;
};

#endif // _PButton_H_
