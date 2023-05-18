#ifndef INTERFACECOMPONENT_CPP
#define INTERFACECOMPONENT_CPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>

class interfaceComponent{
protected:
	ALLEGRO_TIMER *timer;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *queue;

public:
	interfaceComponent(){
		timer = nullptr;
		display = nullptr;
		queue = nullptr;
	}
	virtual ~interfaceComponent(){}
	void setGlobalTimer(ALLEGRO_TIMER *t1){
		timer = t1;
	}

	void setGlobalDisplay(ALLEGRO_DISPLAY *dsp){
        display = dsp;
	}

	void setGlobalEventQueue(ALLEGRO_EVENT_QUEUE *q){
        queue = q;
	}

	virtual void update() = 0;
	virtual void update_input(ALLEGRO_EVENT *ev) = 0;
	virtual void draw() = 0;
};

#endif
