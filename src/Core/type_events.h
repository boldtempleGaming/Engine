/* 
 * File:   type_events.h
 * Author: WinPooh32
 *
 * Created on 28 Jan 2015 г., 11:21
 */

#ifndef TYPE_EVENTS_H
#define	TYPE_EVENTS_H

#include <SDL2/SDL_events.h>

enum type_events{
    EVENT_NONE = SDL_USEREVENT,//bound BEGIN
    EVENT_MOVE,
    EVENT_DIE,
    EVENT_END //bound END
};

#endif	/* TYPE_EVENTS_H */

