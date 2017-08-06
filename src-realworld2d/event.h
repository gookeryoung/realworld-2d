#ifndef EVENT_H
#define EVENT_H

#include "globaldefs.h"
#include "rect.h"

GK_BEGIN_HEADER

typedef enum EventType_ {
    ET_NOEVENT = 0,
    ET_ACTIVEEVENT,
    ET_KEYDOWN,
    ET_KEYUP,
    ET_MOUSEMOTION,
    ET_MOUSEBUTTONDOWN,
    ET_MOUSEBUTTONUP,
    ET_JOYAXISMOTION,
    ET_JOYBALLMOTION,
    ET_JOYHATMOTION,
    ET_JOYBUTTONDOWN,
    ET_JOYBUTTONUP,
    ET_QUIT,
    ET_SYSWMEVENT,
    ET_EVENT_RESERVEDA,
    ET_EVENT_RESERVEDB,
    ET_VIDEORESIZE,
    ET_VIDEOEXPOSE,
    ET_USEREVENT = 24,
    ET_NUMEVENTS = 32
} EventType;

typedef enum KeySym_ {
    KEY_NONE,
    KEY_BACKSPACE,
    KEY_RETURN,
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_EXCLAIM,
    KEY_QUOTEDBL,
    KEY_HASH,
    KEY_DOLLAR,
    KEY_AMPERSAND,
    KEY_QUOTE,
    KEY_LEFTPAREN,
    KEY_RIGHTPAREN,
    KEY_ASTERISK,
    KEY_PLUS,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_COLON,
    KEY_SEMICOLON,
    KEY_LESS,
    KEY_EQUALS,
    KEY_GREATER,
    KEY_QUESTION,
    KEY_AT,
    KEY_LEFTBRACKET,
    KEY_BACKSLASH,
    KEY_RIGHTBRACKET,
    KEY_CARET,
    KEY_UNDERSCORE,
    KEY_ALT,
    KEY_CONTROL,
    KEY_SHIFT,
    KEY_DELETE,
    KEY_PAGEUP,
    KEY_PAGEDOWN,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PRINT,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_a,
    KEY_b,
    KEY_c,
    KEY_d,
    KEY_e,
    KEY_f,
    KEY_g,
    KEY_h,
    KEY_i,
    KEY_j,
    KEY_k,
    KEY_l,
    KEY_m,
    KEY_n,
    KEY_o,
    KEY_p,
    KEY_q,
    KEY_r,
    KEY_s,
    KEY_t,
    KEY_u,
    KEY_v,
    KEY_w,
    KEY_x,
    KEY_y,
    KEY_z
} KeySym;

typedef struct Event_ {
    union SDL_Event *data;


    gbool mouse_motion;
    gbool key_pressed;

    KeySym key_value;

    guint8 mouse_state;
    point2d mouse_cu;

    gbool mouse_pressed;
    guint8 mouse_button;
    point2d mouse_pm;
    point2d mouse_rm;
    point2d mouse_pl;
    point2d mouse_rr;
    point2d mouse_pr;
    point2d mouse_rl;
} Event;

Event *event_get(void);
void event_del(Event *event);

gbool event_handle_events(Event *et);

KeySym event_keyvalue(Event *event);
EventType event_type(Event *event);
gint16 event_mouse_x(Event *event);
gint16 event_mouse_y(Event *event);
point2d event_mouse_position(Event *event);
gbool event_mouse_leftbutton_down(Event *event);
gbool event_mouse_rightbutton_down(Event *event);

GK_END_HEADER

#endif // EVENT_H
