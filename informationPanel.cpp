#include "informationPanel.h"

myInformationPanel::myInformationPanel(){
	x0 = 0;
	y0 = 0;
	sizeX0 = 300;
	sizeY0 = 300;
	visible = false;
	closeButton.setInfo(x0+sizeX0-30, y0+10, 20, 20);
	closeButton.set_sprite1("pictures//close.png");
	closeButton.set_sprite2("pictures//close.png");
	closeButton.setPressedAlwaysFalse();
	funcCallBack f1 = &myButtonCallBack::FuncCallBack;
	closeButton.registerCallBack(this, f1);

    if( (gamefont = al_load_ttf_font("fonts//Game Of Squids.ttf", 30, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

    if( (latoRegular =  al_load_ttf_font("fonts//Lato-Regular.ttf", 20, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

    if( (latoBold  = al_load_ttf_font("fonts//Lato-Bold.ttf", 20, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

    if( (latoRegularDate = al_load_ttf_font("fonts//Lato-Regular.ttf", 10, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

}
myInformationPanel::myInformationPanel(int x, int y, int sizeX, int sizeY){
	x0 = x;
	y0 = y;
	sizeX0 = sizeX;
	sizeY0 = sizeY;
	visible = false;
	closeButton.setInfo(x0+sizeX0-30, y0+10, 20, 20);
	closeButton.set_sprite1("pictures//close.png");
	closeButton.set_sprite2("pictures//close.png");
	closeButton.setPressedAlwaysFalse();
	funcCallBack f1 = &myButtonCallBack::FuncCallBack;
	closeButton.registerCallBack(this, f1);


    if( (gamefont = al_load_ttf_font("fonts//Game Of Squids.ttf", 30, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

    if( (latoRegular =  al_load_ttf_font("fonts//Lato-Regular.ttf", 20, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

    if( (latoBold  = al_load_ttf_font("fonts//Lato-Bold.ttf", 20, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

    if( (latoRegularDate = al_load_ttf_font("fonts//Lato-Regular.ttf", 10, 0)) == nullptr){
        gamefont = al_create_builtin_font();
    }

}

myInformationPanel::~myInformationPanel(){}

void myInformationPanel::setVisible(bool v1){
	visible = v1;
}

void myInformationPanel::drawBackPanel(){
	if(visible){
		al_draw_filled_rectangle(x0, y0, x0+sizeX0, y0+sizeY0, black);
	}
}

void myInformationPanel::drawLines(){
	if(visible){
		int thickness = 3;
		al_draw_line(x0, y0, x0+sizeX0, y0, white, thickness);
		al_draw_line(x0, y0, x0, y0+sizeY0, white, thickness);
		al_draw_line(x0+sizeX0, y0, x0+sizeX0, y0+sizeY0, white, thickness);
		al_draw_line(x0, y0+sizeY0, x0+sizeX0, y0+sizeY0, white, thickness);
	}
}

void myInformationPanel::writeInformation(){
	if(visible){
		al_draw_textf(gamefont, white, x0+20, y0+20, 0, "<<< Life Game >>>");
		al_draw_textf(latoRegularDate, white, x0+250, y0+60, 0, "Ver: 1.0 - December 09, 2021");
		al_draw_textf(latoRegularDate, white, x0+250, y0+75, 0, "Ver: 1.1 - November 19, 2025");
		al_draw_textf(latoBold, white, x0+20, y0+70, 0, "Developers:");
		al_draw_textf(latoRegular, white, x0+20, y0+110, 0, "João Louzada (tandejoao-lifegame@yahoo.com),");
		al_draw_textf(latoRegular, white, x0+20, y0+135, 0, "Nicholas Oliveira (archdark@gmail.com)");
		al_draw_textf(latoBold, white, x0+20, y0+175, 0, "Game based on the original idea of:");
		al_draw_textf(latoRegular, white, x0+20, y0+215, 0, "John Conway (*1937 +2020)");
	}

}

void myInformationPanel::FuncCallBack(bool check){
	if(check){
		visible = true;
	}else{
		closePanel();
	}
}

void myInformationPanel::setButtonCallBack_OpenAbout(myButton &b1){
    funcCallBack cb = &myButtonCallBack::FuncCallBack;
    b1.registerCallBack(this,cb);
}

void myInformationPanel::closePanel(){
	visible = false;
}

void myInformationPanel::update(){
	closeButton.update();
    closeButton.setVisible(visible);
}

void myInformationPanel::update_input(ALLEGRO_EVENT* ev){
	closeButton.update_input(ev);
}

void myInformationPanel::draw(){
	drawBackPanel();
	drawLines();
	writeInformation();
	closeButton.draw();
}
