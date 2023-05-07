#ifndef GAMESCREENCONTEXT_CPP
#define GAMESCREENCONTEXT_CPP

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
#include <vector>
#include "interfaceComponent.h"
#include "button.h"
#include "hall.h"
#include "config.h"
#include <memory>

class gameScreenContext{
private:
	//int x0;
	//int y0;
	int screen_W;
	int screen_H;
	std::vector<interfaceComponent*> list_of_components;


public:
	gameScreenContext();
	virtual ~gameScreenContext(){}
	void setScreenSize(int w, int h);
	void insertComponent(interfaceComponent* c1);
	void setGlobalTimer(ALLEGRO_TIMER *timer);
   	void setGlobalDisplay(ALLEGRO_DISPLAY *dsp);
    void setGlobalEventQueue(ALLEGRO_EVENT_QUEUE *q);
    void setComponents();
    void setConfig(Config &config);

    int getScreenW(void) const { return screen_W; }
    int getScreenH(void) const { return screen_H; }

    Config* getConfig();

	virtual void update();
	virtual void update_input(ALLEGRO_EVENT *e);
	virtual void draw();



};

#endif
