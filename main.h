#ifndef MAIN_H
#define MAIN_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "hall.h"
#include "button.h"
#include "gameScreenContext.h"
#include "bigTextLabel.h"
#include "informationPanel.h"
#include "config.h"
#include <memory>
#include "Menu.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;

enum class GameState {
    IN_GAME_SCREEN,
    MAIN_MENU_SCREEN,
    LOGO_SCREEN
};

extern GameState g_gamestate;
extern bool running;

#endif // MAIN_H
