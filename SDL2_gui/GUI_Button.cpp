//
//  GUI_Button.cpp
//  GUI_Button
//
//  Created by Panutat Tejasen on 13/1/2562 BE.
//  Copyright © 2562 Jimmy Software Co., Ltd. All rights reserved.
//

#include "GUI_Button.h"
#include "GUI_shapes.h"

extern GUI_View * GUI_mouseCapturedView;

GUI_Button *GUI_Button::create( GUI_View *parent, const char *title, uint16_t unicode, int x, int y, int width, int height,
                          std::function<void(GUI_Button*)>callbackFunction ) {
    return new GUI_Button( parent, title, unicode, x, y, width, height, callbackFunction );
}

GUI_Button::GUI_Button(GUI_View *parent, const char *title, uint16_t unicode, int x, int y, int width, int height,
                       std::function<void(GUI_Button*)>callbackFunction) :
GUI_Label(parent, title, unicode, x, y, width, height, NULL ),
isDown(false)
{
    dragable = false;
    showInteract = true;
    
    setBackgroundColor(cCyan);
    callback = callbackFunction;
    
    border = 1;
    focusBorder = 8;
    corner = 4;
    setPadding( 5, 12, 5, 12 );
    updateLayout();
}

GUI_Button::~GUI_Button() {
    
}



bool GUI_Button::eventHandler(SDL_Event*event) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
        {
            if( isVisible() && isEnable() ) {
                SDL_MouseButtonEvent e = event->button;
                
                int x = (int)(e.x*GUI_mouseScale);
                int y = (int)(e.y*GUI_mouseScale);
                if( hitTest(x, y, false) ) {
                    GUI_Log( "Button hit %s\n", title.c_str() );
                    isDown = true;
                    setFocus();
                    GUI_mouseCapturedView = (GUI_View *)this;
                    touchTime = SDL_GetTicks(); // time in millis
                    touchHoldTime = touchTime;
                }
            }
            break;
        }
            
        case SDL_MOUSEMOTION:
        {
            if( isVisible() && isEnable() ) {
                SDL_MouseButtonEvent e = event->button;
                
                int x = (int)(e.x*GUI_mouseScale);
                int y = (int)(e.y*GUI_mouseScale);
                if( hitTest(x, y, false) ) {
                    setInteract(true);
                }
                else {
                    setInteract(false);
                }
            }
            break;
        }
            
        case SDL_MOUSEBUTTONUP:
        {
            if( isVisible() && isEnable() ) {
                SDL_MouseButtonEvent e = event->button;
                GUI_mouseCapturedView = NULL;
                
                int x = (int)(e.x*GUI_mouseScale);
                int y = (int)(e.y*GUI_mouseScale);
                if( hitTest(x, y, false) ) {
                    GUI_Log( "Button UP %s\n", title.c_str() );
                }
            }
            break;
        }
            
        default:
        {
            GUI_View::eventHandler(event);
        }
    }
    
    return false;
}


