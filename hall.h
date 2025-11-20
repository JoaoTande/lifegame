#ifndef HALL_CPP
#define HALL_CPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include "interfaceComponent.h"
#include "button.h"
#include "bigTextLabel.h"
#include "classCallBack.h"
#include "FPSCounter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



enum {
	SPEED_NORMAL,
	SPEED_SLOW1,
	SPEED_SLOW2,
	SPEED_SLOW3,
	SPEED_SLOWER,
	SPEED_STOPPED,
    NUMBER_OF_SPEEDS
};

enum {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
	NUMBER_OF_KEYS
};

typedef struct Position {
    int x;
    int y;
}Position;

typedef struct EVOLUTION_SPEED {
    int div;
    float speed;
    int type;
}EVOLUTION_SPEED;

class Quadrado{
public:
	bool checked;
	int x;
	int y;
	int size;
	int number_of_neighbors;
	ALLEGRO_COLOR white = al_map_rgb_f(1.0, 1.0, 1.0);
	Quadrado(){
		checked = false;
		x = 0;
		y = 0;
		size = 50;
		number_of_neighbors = 0;
	}

	void checkNeighbors(){
		if(!checked){
			if(number_of_neighbors == 3) {
				toogle();
			}
		}else{
			if((number_of_neighbors < 2)||(number_of_neighbors > 3)){
				toogle();
			}
		}
	}

	void draw(){
		if(checked){
			al_draw_filled_rectangle(x, y, x+size, y+size, white);
		}
	}

	int drawFast(ALLEGRO_VERTEX *buffer, int nextPos){
		if(checked){
			int ret = add_square_vertices(
    		x, y,
    		x+size, y+size,
    		white,
    		buffer,
    		nextPos);
			
			return ret;
		}
		return nextPos;
	}

    int add_square_vertices(
    float x1, float y1,
    float x2, float y2,
    ALLEGRO_COLOR color,
    ALLEGRO_VERTEX *buffer,
    int nextPos)   // index where the 6 vertices will be written
	{
    	// Triangle 1
    	buffer[nextPos + 0].x = x1; buffer[nextPos + 0].y = y1; buffer[nextPos + 0].z = 0; buffer[nextPos + 0].color = color;
    	buffer[nextPos + 1].x = x2; buffer[nextPos + 1].y = y1; buffer[nextPos + 1].z = 0; buffer[nextPos + 1].color = color;
    	buffer[nextPos + 2].x = x1; buffer[nextPos + 2].y = y2; buffer[nextPos + 2].z = 0; buffer[nextPos + 2].color = color;

    	// Triangle 2
    	buffer[nextPos + 3].x = x2; buffer[nextPos + 3].y = y1; buffer[nextPos + 3].z = 0; buffer[nextPos + 3].color = color;
    	buffer[nextPos + 4].x = x2; buffer[nextPos + 4].y = y2; buffer[nextPos + 4].z = 0; buffer[nextPos + 4].color = color;
    	buffer[nextPos + 5].x = x1; buffer[nextPos + 5].y = y2; buffer[nextPos + 5].z = 0; buffer[nextPos + 5].color = color;

    	return nextPos + 6;  // next free vertex slot
	}

	void toogle(){
		if(checked){
			checked = false;
		}else{
			checked = true;
		}
	}
};

class hall: public interfaceComponent, myButtonCallBack{
private:
	int x0;
	int y0;
	int size;
	int numero_x;
	int numero_y;
	int numBloc_X;
	int numBloc_Y;
	int bloco_x0;
	int bloco_y0;
	int screen_W;
	int screen_H;
	int lastScrollPosition;
	Quadrado** QuadradosList;
	Quadrado** QuadradosListBackup;

	int keys[7];
	int FPS_Count;
	FPSCounter fpsCounter;

	ALLEGRO_FONT *text_font = NULL;

	ALLEGRO_COLOR Color_white;
	ALLEGRO_COLOR Color_grey;

	myButton* buttonReset;
	myButton* buttonRestore;
	myButton* buttonFunPatterns;
	myButton* buttonFillRand;
	myButton* buttonSaveFile;
	myButton* buttonLoadFile;

	bool play; //If true game is playing if false it is the development fase.
	int generationNumber;
	float evolution_speed;
	int actual_speed;


	bool load_dialog_open;
	bool save_dialog_open;

public:

	EVOLUTION_SPEED ev_speed[NUMBER_OF_SPEEDS] = {
			{1,1.0, SPEED_NORMAL},
			{20,0.75, SPEED_SLOW1},
			{40,0.50, SPEED_SLOW2},
			{60,0.25, SPEED_SLOW3},
			{80,0.10, SPEED_SLOWER},
		    {120,0.00, SPEED_STOPPED}// This one will not be 120 it will stop.
	};

	hall(int x, int y, int screen_Wj, int screen_Hj);
	~hall();
	void calcNumBlocs();
	void draw_line();
	void draw_text();
	void draw_markers();
	void makeScreenBackup();
	void update();
	void checkQuadrado(int x, int y, bool check);
	void setQuadradoInf();
	void mouse_event_input(ALLEGRO_EVENT *ev);
	void keyboard_event_input(ALLEGRO_EVENT *ev);

	void moveGrid();
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();

	int saveToFile(const std::string file);
	int readFile(const std::string file);

	bool randGenerator();
	void fillRandomGrid();

	Position get_Position(int pos_x, int pos_y);
	void setTextGenerations(bigTextLabel<int> &t1);
	void setTextFPS(bigTextLabel<int> &t1);
	int contNeighbors(int x, int y);
	void contAllNeighbors();
	void calcNewBlocZeroZero(int pos_x, int pos_y, int nextSize);
	void CreateAndKillLife();

	//CallBack Register Functions
	void setButtonCallBack(myButton &b1);
	void setButtonCallBack_Reset(myButton &b1);
	void setButtonCallBack_Restore(myButton &b1);
	void setButtonCallBack_FunPatterns(myButton &b1);
	void setButtonCallBack_FillRand(myButton &b1);
	void setButtonCallBack_SaveFile(myButton &b1);
	void setButtonCallBack_LoadFile(myButton &b1);
	void setButtonCallBack_NextSpeed(myButton &b1);
	void setButtonCallBack_PrevSpeed(myButton &b1);
	void setButtonCallBack_Zoom(myButton &b1);
	//CallBack Pointer Functions
	void restoreScreenBackup(bool);
	void loadFunPatterns(bool);
	void fillRand(bool);
	void FuncCallBack(bool);
	void resetAll(bool);
	void saveFile(bool);
	void loadFile(bool);
	void NextSpeed(bool) override;
	void PrevSpeed(bool) override;
	void changeSize(bool zoom);
	void draw_square_batch(ALLEGRO_VERTEX *buffer, int vertex_count);
	virtual void draw();
	virtual void update_input(ALLEGRO_EVENT *e);


};

#endif
