#include <SDL/SDL.h>
#include "event.h"

static event_type
_sdl_to_event_type(SDL_EventType type) {
    switch(type) {
    case SDL_ACTIVEEVENT: return ET_ACTIVEEVENT;
    case SDL_KEYDOWN: return ET_KEYDOWN;
    case SDL_KEYUP: return ET_KEYUP;
    case SDL_MOUSEMOTION: return ET_MOUSEMOTION;
    case SDL_MOUSEBUTTONDOWN: return ET_MOUSEBUTTONDOWN;
    case SDL_MOUSEBUTTONUP: return ET_MOUSEBUTTONUP;
    case SDL_JOYAXISMOTION: return ET_JOYAXISMOTION;
    case SDL_JOYBALLMOTION: return ET_JOYBALLMOTION;
    case SDL_JOYHATMOTION: return ET_JOYHATMOTION;
    case SDL_JOYBUTTONDOWN: return ET_JOYBUTTONDOWN;
    case SDL_JOYBUTTONUP: return ET_JOYBUTTONUP;
    case SDL_QUIT: return ET_QUIT;
    case SDL_SYSWMEVENT: return ET_SYSWMEVENT;
    case SDL_EVENT_RESERVEDA: return ET_EVENT_RESERVEDA;
    case SDL_EVENT_RESERVEDB: return ET_EVENT_RESERVEDB;
    case SDL_VIDEORESIZE: return ET_VIDEORESIZE;
    case SDL_VIDEOEXPOSE: return ET_VIDEOEXPOSE;
    case SDL_USEREVENT: return ET_USEREVENT;
    default: return ET_NOEVENT;
    }
}

static key_sym
_sdl_to_keysym(SDLKey key) {
    switch(key) {
    case SDLK_ESCAPE:       return KEY_ESCAPE;
    case SDLK_RETURN:       return KEY_RETURN;
    case SDLK_BACKSPACE:	return KEY_BACKSPACE;
    case SDLK_EXCLAIM:    	return KEY_EXCLAIM;
    case SDLK_QUOTEDBL:    	return KEY_QUOTEDBL;
    case SDLK_HASH:         return KEY_HASH;
    case SDLK_DOLLAR:    	return KEY_DOLLAR;
    case SDLK_AMPERSAND:    return KEY_AMPERSAND;
    case SDLK_QUOTE:    	return KEY_QUOTE;
    case SDLK_LEFTPAREN:    return KEY_LEFTPAREN;
    case SDLK_RIGHTPAREN:   return KEY_RIGHTPAREN;
    case SDLK_ASTERISK:     return KEY_ASTERISK;
    case SDLK_PLUS:         return KEY_PLUS;
    case SDLK_COMMA:    	return KEY_COMMA;
    case SDLK_MINUS:    	return KEY_MINUS;
    case SDLK_PERIOD:    	return KEY_PERIOD;
    case SDLK_SLASH:    	return KEY_SLASH;
    case SDLK_COLON:        return KEY_COLON;
    case SDLK_SEMICOLON:	return KEY_SEMICOLON;
    case SDLK_LESS:         return KEY_LESS;
    case SDLK_EQUALS:       return KEY_EQUALS;
    case SDLK_GREATER:      return KEY_GREATER;
    case SDLK_QUESTION:     return KEY_QUESTION;
    case SDLK_AT:           return KEY_AT;
    case SDLK_LEFTBRACKET:	return KEY_LEFTBRACKET;
    case SDLK_BACKSLASH:	return KEY_BACKSLASH;
    case SDLK_RIGHTBRACKET:	return KEY_RIGHTBRACKET;
    case SDLK_CARET:        return KEY_CARET;
    case SDLK_UNDERSCORE:	return KEY_UNDERSCORE;
    case SDLK_LALT:         return KEY_ALT;
    case SDLK_RALT:         return KEY_ALT;
    case SDLK_LCTRL:        return KEY_CONTROL;
    case SDLK_RCTRL:        return KEY_CONTROL;
    case SDLK_LSHIFT:       return KEY_SHIFT;
    case SDLK_RSHIFT:       return KEY_SHIFT;
    case SDLK_SPACE:        return KEY_SPACE;
    case SDLK_DELETE:       return KEY_DELETE;
    case SDLK_PAGEUP:       return KEY_PAGEUP;
    case SDLK_PAGEDOWN:     return KEY_PAGEDOWN;
    case SDLK_F1:           return KEY_F1;
    case SDLK_F2:           return KEY_F2;
    case SDLK_F3:           return KEY_F3;
    case SDLK_F4:           return KEY_F4;
    case SDLK_F5:           return KEY_F5;
    case SDLK_F6:           return KEY_F6;
    case SDLK_F7:           return KEY_F7;
    case SDLK_F8:           return KEY_F8;
    case SDLK_F9:           return KEY_F9;
    case SDLK_F10:          return KEY_F10;
    case SDLK_F11:          return KEY_F11;
    case SDLK_F12:          return KEY_F12;
    case SDLK_PRINT:        return KEY_PRINT;
    case SDLK_LEFT:         return KEY_LEFT;
    case SDLK_RIGHT:        return KEY_RIGHT;
    case SDLK_UP:           return KEY_UP;
    case SDLK_DOWN:         return KEY_DOWN;
    case SDLK_0:            return KEY_0;
    case SDLK_1:            return KEY_1;
    case SDLK_2:            return KEY_2;
    case SDLK_3:            return KEY_3;
    case SDLK_4:            return KEY_4;
    case SDLK_5:            return KEY_5;
    case SDLK_6:            return KEY_6;
    case SDLK_7:            return KEY_7;
    case SDLK_8:            return KEY_8;
    case SDLK_9:            return KEY_9;
    case SDLK_a:            return KEY_a;
    case SDLK_b:            return KEY_b;
    case SDLK_c:            return KEY_c;
    case SDLK_d:            return KEY_d;
    case SDLK_e:            return KEY_e;
    case SDLK_f:            return KEY_f;
    case SDLK_g:            return KEY_g;
    case SDLK_h:            return KEY_h;
    case SDLK_i:            return KEY_i;
    case SDLK_j:            return KEY_j;
    case SDLK_k:            return KEY_k;
    case SDLK_l:            return KEY_l;
    case SDLK_m:            return KEY_m;
    case SDLK_n:            return KEY_n;
    case SDLK_o:            return KEY_o;
    case SDLK_p:            return KEY_p;
    case SDLK_q:            return KEY_q;
    case SDLK_r:            return KEY_r;
    case SDLK_s:            return KEY_s;
    case SDLK_t:            return KEY_t;
    case SDLK_u:            return KEY_u;
    case SDLK_v:            return KEY_v;
    case SDLK_w:            return KEY_w;
    case SDLK_x:            return KEY_x;
    case SDLK_y:            return KEY_y;
    case SDLK_z:            return KEY_z;
    default:                return KEY_NONE;
    }
}

event *
event_get(void) {
    event *ret = NULL;

    GK_NEW(ret, event);
    GK_NEW(ret->data, SDL_Event);

    ret->mouse_motion = GKFALSE;
    ret->key_pressed = GKFALSE;
    ret->key_value = KEY_NONE;

    ret->mouse_cu.x = -1;
    ret->mouse_cu.y = -1;

    ret->mouse_state = 0;

    ret->mouse_pressed = GKFALSE;
    ret->mouse_button = 0;

    ret->mouse_pm.x = -1;
    ret->mouse_pm.y = -1;

    ret->mouse_rm.x = -1;
    ret->mouse_rm.y = -1;

    ret->mouse_pl.x = -1;
    ret->mouse_pl.y = -1;

    ret->mouse_rr.x = -1;
    ret->mouse_rr.y = -1;

    ret->mouse_pr.x = -1;
    ret->mouse_pr.y = -1;

    ret->mouse_rl.x = -1;
    ret->mouse_rl.y = -1;

    return (ret);
}

void
event_del(event *event) {
    GK_DELETE(event->data);
    GK_DELETE(event);
}

void
_handle_keyboard(event *et, SDL_KeyboardEvent *kb, gbool pressed) {
    et->key_pressed = pressed;
    et->key_value = _sdl_to_keysym(kb->keysym.sym);
}

void
_handle_mousemotion(event *et, SDL_MouseMotionEvent *mm) {
    et->mouse_state = mm->state;
    et->mouse_motion = GKTRUE;
    et->mouse_cu.x = mm->x;
    et->mouse_cu.y = mm->y;
}

void
_handle_mousewheel(event *et, SDL_MouseButtonEvent *mb) {
    et->mouse_pressed = (mb->state == SDL_PRESSED);
    et->mouse_button = mb->button;

    et->mouse_cu.x = mb->x;
    et->mouse_cu.y = mb->y;

    if(et->mouse_pressed) {
        et->mouse_pm.x = mb->x;
        et->mouse_pm.y = mb->y;
    } else {
        et->mouse_rm.x = mb->x;
        et->mouse_rm.y = mb->y;
    }
}

void
_handle_mousebutton(event *et, SDL_MouseButtonEvent *mb) {
    et->mouse_pressed = (mb->state == SDL_PRESSED);
    et->mouse_button = mb->button;
    et->mouse_cu.x = mb->x;
    et->mouse_cu.y = mb->y;

    if(et->mouse_pressed) {
        switch(mb->button) {
        case SDL_BUTTON_LEFT:
            et->mouse_pl.x = mb->x;
            et->mouse_pl.y = mb->y;
            break;
        case SDL_BUTTON_MIDDLE:
            et->mouse_pm.x = mb->x;
            et->mouse_pm.y = mb->y;
            break;
        case SDL_BUTTON_RIGHT:
            et->mouse_pr.x = mb->x;
            et->mouse_pr.y = mb->y;
            break;
        default:
            break;
        }
    } else {
        switch(mb->button) {
        case SDL_BUTTON_LEFT:
            et->mouse_rl.x = mb->x;
            et->mouse_rl.y = mb->y;
            break;
        case SDL_BUTTON_MIDDLE:
            et->mouse_rm.x = mb->x;
            et->mouse_rm.y = mb->y;
            break;
        case SDL_BUTTON_RIGHT:
            et->mouse_rr.x = mb->x;
            et->mouse_rr.y = mb->y;
            break;
        default:
            break;
        }
    }
}

gbool event_handle_events(event *et) {
    et->mouse_motion = GKFALSE;
    et->key_pressed = GKFALSE;

    while(SDL_PollEvent(et->data)) {
        // keyboard events
        if(SDL_KEYDOWN == et->data->type) {
            _handle_keyboard(et, &et->data->key, GKTRUE);

            if (SDLK_ESCAPE == et->data->key.keysym.sym) {
                GK_MSG("Quit window");
                return GKFALSE;
            }
        } else {
            if(SDL_KEYUP == et->data->type) {
                _handle_keyboard(et, &et->data->key, GKFALSE);
            }
        }
        // mouse motion events
        if(SDL_MOUSEMOTION == et->data->type) {
            _handle_mousemotion(et, &et->data->motion);
        }
        // mouse button events
        if(SDL_MOUSEBUTTONDOWN == et->data->type || SDL_MOUSEBUTTONUP == et->data->type) {
            // mouse wheel
            if(SDL_BUTTON_WHEELDOWN == et->data->button.button || SDL_BUTTON_WHEELUP == et->data->button.button) {
                _handle_mousewheel(et, &et->data->button);
                break;
            }  else {
                _handle_mousebutton(et, &et->data->button);
            }
        }
        // exit
        if(SDL_QUIT == et->data->type){
            GK_MSG("Quit event.");
            return GKFALSE;
        }
    }
    SDL_Delay(1);
    return GKTRUE;
}

key_sym
event_keyvalue(event *event) {
    return (_sdl_to_keysym(event->data->key.keysym.sym));
}

event_type
event_gettype(event *event) {
    return (_sdl_to_event_type(event->data->type));
}

gint16 event_mouse_x(event *event) {
    return (event->data->motion.x);
}

gint16
event_mouse_y(event *event) {
    return (event->data->motion.y);
}

point2d
event_mouse_position(event *event) {
    point2d pos = {event->data->motion.x, event->data->motion.y};
    return (pos);
}

gbool
event_mouse_leftbutton_down(event *event) {
    return (event->data->button.button == SDL_BUTTON_LEFT);
}

gbool
event_mouse_rightbutton_down(event *event) {
    return (event->data->button.button == SDL_BUTTON_RIGHT);
}
