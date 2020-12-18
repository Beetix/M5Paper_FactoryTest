#ifndef __EPDGUI_SLIDER_H
#define __EPDGUI_SLIDER_H

#include "epdgui_base.h"

class EPDGUI_Slider: public EPDGUI_Base
{
public:
    static const int16_t EVENT_VALUE_CHANGED = 0;

    EPDGUI_Slider(int16_t x, int16_t y, int16_t w, int16_t h);
    EPDGUI_Slider();
    ~EPDGUI_Slider();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_DU4);
    void Bind(int16_t event, void (* func_cb)(epdgui_args_vector_t&));
    void UpdateState(int16_t x, int16_t y);
    void Draw(M5EPD_Canvas* canvas);
    void AddArgs(int16_t event, uint16_t n, void* arg);
    void setValue(uint8_t value);
    uint8_t getValue();

private:
    M5EPD_Canvas* _Canvas = NULL;
    uint8_t _value = 0;

    void (*_value_changed_cb)(epdgui_args_vector_t& args) = NULL;
    epdgui_args_vector_t _value_changed_cb_args;
};

#endif
