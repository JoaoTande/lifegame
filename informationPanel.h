#ifndef INFORMATIONPANEL_CPP
#define INFORMATIONPANEL_CPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "interfaceComponent.h"
#include "myButtonCallback.h"
#include "button.h"
#include "gameScreenContext.h"



class myInformationPanel: public interfaceComponent, myButtonCallback{
private:
	int x0;
	int y0;
	int sizeX0;
	int sizeY0;
	bool visible;
	myButton closeButton;
	ALLEGRO_COLOR white = al_map_rgb_f(1.0, 1.0, 1.0);
	ALLEGRO_COLOR red = al_map_rgb_f(1.0, 1.0, 1.0);
	ALLEGRO_COLOR blue = al_map_rgb_f(1.0, 1.0, 1.0);
	ALLEGRO_COLOR yellow = al_map_rgb_f(1.0, 1.0, 0);
	ALLEGRO_COLOR black = al_map_rgb_f(0, 0, 0);
	ALLEGRO_FONT *gamefont;
	ALLEGRO_FONT *latoRegular;
	ALLEGRO_FONT *latoRegularDate;
	ALLEGRO_FONT *latoBold;


public:
	myInformationPanel();
	myInformationPanel(int x, int y, int sizeX, int sizeY);
	~myInformationPanel();
	void drawBackPanel();
	void drawLines();
	void writeInformation();
	void setVisible(bool v1);

	void setButtonCallBack_OpenAbout(myButton &b1);
	void FuncCallBack(bool check);
	void closePanel();
	void update();

	virtual void update_input(ALLEGRO_EVENT *ev);
	virtual void draw();

};

#endif
