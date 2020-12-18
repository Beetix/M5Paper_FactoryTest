#include "epdgui_slider.h"

#define LINE_W (_w - _h)
#define PIXEL_TO_VALUE(p) ((p) * 10 / LINE_W)
#define VALUE_TO_PIXEL(v) ((v) * LINE_W / 10 + _h / 2)

EPDGUI_Slider::EPDGUI_Slider(int16_t x, int16_t y, int16_t w, int16_t h):
EPDGUI_Base(x, y, w, h)
{
    _Canvas = new M5EPD_Canvas(&M5.EPD);
    _Canvas->createCanvas(_w, _h);
}

EPDGUI_Slider::~EPDGUI_Slider()
{
    delete _Canvas;
}

void EPDGUI_Slider::Draw(m5epd_update_mode_t mode)
{
    _Canvas->fillCanvas(0);
    _Canvas->drawFastHLine(_h / 2, _h / 2, LINE_W , _h / 6, 15);
    _Canvas->fillCircle(VALUE_TO_PIXEL(_value), _h / 2, _h / 2, 15);
    _Canvas->fillCircle(VALUE_TO_PIXEL(_value), _h / 2, _h / 2 - 3, 0);
    _Canvas->pushCanvas(_x, _y, mode);
}

void EPDGUI_Slider::Bind(int16_t event, void (* func_cb)(epdgui_args_vector_t&))
{
    if (event == EVENT_VALUE_CHANGED)
        _value_changed_cb = func_cb;
}

void EPDGUI_Slider::UpdateState(int16_t x, int16_t y)
{
    bool is_in_area = isInBox(x, y);

    if(is_in_area)
    {
        int16_t d = x - _x - _h / 2;
        if (d < 0)
            d = 0;
        else if (d > LINE_W)
            d = LINE_W;
        if (_value != PIXEL_TO_VALUE(d))
        {
            _value = PIXEL_TO_VALUE(d); 
            Draw();
            if (_value_changed_cb != NULL)
                _value_changed_cb(_value_changed_cb_args);
        }
    }
}

void EPDGUI_Slider::Draw(M5EPD_Canvas* canvas)
{
    _Canvas->pushToCanvas(_x, _y, canvas);
}

void EPDGUI_Slider::AddArgs(int16_t event, uint16_t n, void* arg)
{
    if(event == EVENT_VALUE_CHANGED)
    {
        if(_value_changed_cb_args.size() > n)
        {
            _value_changed_cb_args[n] = arg;
        }
        else
        {
            _value_changed_cb_args.push_back(arg);
        }
    }
}

uint8_t EPDGUI_Slider::getValue()
{
    return _value;
}

void EPDGUI_Slider::setValue(uint8_t value)
{
    if (value == _value) return;
    _value = value;
    Draw();
}
