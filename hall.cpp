#include "hall.h"
#include <cstdio>
#include <cstdlib>


hall::hall(int x, int y, int screen_Wj, int screen_Hj) : interfaceComponent() {
	x0 = x;
	y0 = y;
	size = 10;
	numero_x = screen_Wj-100;
	numero_y = screen_Hj-170;
	screen_W = screen_Wj;
	screen_H = screen_Hj;
	numBloc_X = (screen_W-100)/size;
	numBloc_Y = (screen_H-170)/size;
	bloco_x0 = 0;
	bloco_y0 = 0;

    //keys[6] = {0};

    memset(keys,0, sizeof(keys));


	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	lastScrollPosition = state.z;

	QuadradosList = new Quadrado*[numero_x];
	for(int i = 0;i<numero_x;i++){
		QuadradosList[i] = new Quadrado[numero_y];
	}
	setQuadradoInf();

	QuadradosListBackup = new Quadrado*[numero_x];
	for(int i = 0;i<numero_x;i++){
		QuadradosListBackup[i] = new Quadrado[numero_y];
	}

	text_font = al_create_builtin_font();

	buttonReset = nullptr;
	buttonRestore = nullptr;
	buttonFunPatterns = nullptr;
	buttonSaveFile = nullptr;
	buttonLoadFile = nullptr;

	play = false;
	actual_speed = SPEED_NORMAL;
	evolution_speed = ev_speed[actual_speed].type;
	generationNumber = 0;
	load_dialog_open = false;
	save_dialog_open = false;
}

hall::~hall(){

}

void hall::calcNumBlocs(){
	numBloc_X = (screen_W-100)/size;
	numBloc_Y = (screen_H-170)/size;


	if((numero_x - bloco_x0) < numBloc_X){
		bloco_x0 = numero_x - numBloc_X;
	}

	if((numero_y - bloco_y0) < numBloc_Y){
		bloco_y0 = numero_y - numBloc_Y;
	}

}

void hall::draw_line(){

#if 1
   ALLEGRO_COLOR color;
   color = al_map_rgb_f(0.3, 0.3, 0.3);
   int x = x0;
   int y = y0;
   int length = numBloc_X*size;
   int height = numBloc_Y*size;

   while(y <= y0+height){
	   al_draw_line(x, y, x+length, y, color, 0);
	   y = y + size;
   }

   y = y0;
   while(x <= x0+length){
   	   al_draw_line(x, y, x, y+height, color, 0);
   	   x = x + size;
    }
#endif
}

void hall::draw_text(){
    al_draw_textf(text_font,al_map_rgb(255,255,255), x0, y0 - 35, 0, "HALL");
    al_draw_textf(text_font,al_map_rgb(255,255,255), x0, y0 - 25, 0, "%d X %d", numero_x, numero_y);
    al_draw_textf(text_font,al_map_rgb(255,255,255), x0, y0 - 15, 0, "Evolution Speed: %.2f", ev_speed[actual_speed].speed);
}

void hall::draw_markers(){
	int step = (numBloc_Y*size)/4;
	int m0 = bloco_y0;
	int m1 = bloco_y0+(step/size);
	int m2 = bloco_y0+(step*2/size);
	int m3 = bloco_y0+(step*3/size);
	int m4 = bloco_y0+(step*4/size);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0-35, y0, 0, "%d-", m0);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0-35, y0+step, 0, "%d-", m1);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0-35, y0+step*2, 0, "%d-", m2);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0-35, y0+step*3, 0, "%d-", m3);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0-35, (y0+step*4)-size, 0, "%d-", m4);

	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+(numBloc_X*size), y0, 0, "-%d", m0);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+(numBloc_X*size), y0+step, 0, "-%d", m1);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+(numBloc_X*size), y0+step*2, 0, "-%d", m2);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+(numBloc_X*size), y0+step*3, 0, "-%d", m3);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+(numBloc_X*size), (y0+step*4)-size, 0, "-%d", m4);

	step = (numBloc_X*size)/4;
	m0 = bloco_x0;
	m1 = bloco_x0+(step/size);
	m2 = bloco_x0+(step*2/size);
	m3 = bloco_x0+(step*3/size);
	m4 = bloco_x0+(step*4/size)-1;
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0, y0+(numBloc_Y*size)+5, 0, "|%d", m0);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+step, y0+(numBloc_Y*size)+5, 0, "|%d", m1);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+step*2, y0+(numBloc_Y*size)+5, 0, "|%d", m2);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+step*3, y0+(numBloc_Y*size)+5, 0, "|%d", m3);
	al_draw_textf(text_font,al_map_rgb(255,255,255), x0+step*4-size, y0+(numBloc_Y*size)+5, 0, "|%d", m4);
}

void hall::resetAll(bool){
	if(!play){
		generationNumber = 0;
		for(int i = 0;i<numero_x;i++){
			for(int j = 0;j<numero_y;j++){
				QuadradosList[i][j].checked = false;
			}
		}
	}
}

void hall::makeScreenBackup(){
	for(int i = 0;i<numero_x;i++){
		for(int j = 0;j<numero_y;j++){
			QuadradosListBackup[i][j].checked = QuadradosList[i][j].checked;
		}
	}
}

void hall::restoreScreenBackup(bool){
	if(!play){
		for(int i = 0;i<numero_x;i++){
			for(int j = 0;j<numero_y;j++){
				QuadradosList[i][j].checked = QuadradosListBackup[i][j].checked;
			}
		}
	}
}

void hall::setButtonCallBack_Reset(myButton &b1){
	buttonReset = &b1;
    funcCallBack f1 = &myButtonCallback::resetAll;
	b1.registerCallBack(this, f1);
}

void hall::setButtonCallBack_Restore(myButton &b1){
	buttonRestore = &b1;
    funcCallBack f1 = &myButtonCallback::restoreScreenBackup;
	b1.registerCallBack(this, f1);
}

void hall::setButtonCallBack_FunPatterns(myButton &b1){
	buttonFunPatterns = &b1;
    funcCallBack f1 = &myButtonCallback::loadFunPatterns;
	b1.registerCallBack(this, f1);
}

void hall::setButtonCallBack_SaveFile(myButton &b1){
	buttonSaveFile = &b1;
    funcCallBack f1 = &myButtonCallback::saveFile;
	b1.registerCallBack(this, f1);
}

void hall::setButtonCallBack_LoadFile(myButton &b1){
	buttonLoadFile = &b1;
    funcCallBack f1 = &myButtonCallback::loadFile;
	b1.registerCallBack(this, f1);
}

void hall::saveFile(bool){
    ALLEGRO_FILECHOOSER *filechooser = nullptr;
    ALLEGRO_PATH *path = nullptr;

	if(!save_dialog_open){
		save_dialog_open = true;
		filechooser = al_create_native_file_dialog(".","SAVE File", "*.txt", ALLEGRO_FILECHOOSER_SAVE);

		if(!filechooser){
			return;
		}

		al_stop_timer(timer);
		al_flush_event_queue(queue);
		al_pause_event_queue(queue, true);
		//true when click OK
		if(al_show_native_file_dialog(display, filechooser) && save_dialog_open ){
			const char *fname = al_get_native_file_dialog_path(filechooser, 0);
			path = al_create_path(fname);
			const char *fullpath_save = al_path_cstr(path,ALLEGRO_NATIVE_PATH_SEP);
			saveToFile(fullpath_save);
			al_resume_timer(timer);
			al_pause_event_queue(queue, false);
			save_dialog_open = false;
		}

		al_destroy_native_file_dialog(filechooser);
		al_destroy_path(path);
		al_resume_timer(timer);
		al_pause_event_queue(queue, false);
		save_dialog_open = false;
	}
}

void hall::loadFile(bool){
	ALLEGRO_FILECHOOSER *filechooser = nullptr;
    ALLEGRO_PATH *path = nullptr;

	if(!load_dialog_open){
        load_dialog_open = true;
        filechooser = al_create_native_file_dialog(".","Load Saved File", "*.txt", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST |ALLEGRO_FILECHOOSER_SHOW_HIDDEN);

        if(!filechooser){
            return;
        }
        al_stop_timer(timer);
        al_flush_event_queue(queue);
        al_pause_event_queue(queue, true);
        //true when click OK
        if(al_show_native_file_dialog(display, filechooser) && load_dialog_open){
            const char *fname = al_get_native_file_dialog_path(filechooser, 0);
            path = al_create_path(fname);
            const char *fullpath = al_path_cstr(path,ALLEGRO_NATIVE_PATH_SEP);
            readFile(fullpath);
            al_resume_timer(timer);
            al_pause_event_queue(queue, false);
            load_dialog_open = false;
        }

        al_destroy_path(path);
        al_destroy_native_file_dialog(filechooser);
        al_resume_timer(timer);
        al_pause_event_queue(queue, false);
        load_dialog_open = false;
	}
}

void hall::CreateAndKillLife(){
	if(play && ev_speed[actual_speed].type != SPEED_STOPPED){
		double CurrentTimer = (al_get_timer_count(this->timer) / ev_speed[actual_speed].div);
        if(CurrentTimer >= evolution_speed){
        	generationNumber++;
        	for(int i = 0;i<numero_x;i++){
                for(int j = 0;j<numero_y;j++){
                    QuadradosList[i][j].checkNeighbors();
                }
            }
            evolution_speed = (al_get_timer_count(this->timer) / ev_speed[actual_speed].div)+ev_speed[actual_speed].speed;
        }
	}
}

void hall::update(){
	moveGrid();
    contAllNeighbors();
    CreateAndKillLife();
}

void hall::draw(){
    //contAllNeighbors();
    //CreateAndKillLife();
	draw_line();
	draw_markers();
	draw_text();
	for(int i = 0;i<numBloc_X;i++){
		for(int j = 0;j<numBloc_Y;j++){
			QuadradosList[i+bloco_x0][j+bloco_y0].draw();
		}
	}

#ifdef GAME_DEBUG
    renderMouseDebug();
#endif
}

void hall::setQuadradoInf(){
	for(int i = 0;i<numero_x;i++){
		for(int j = 0;j<numero_y;j++){
			if((i >= bloco_x0)&&(i < (bloco_x0+numBloc_X))&&(j >= bloco_y0)&&(j < (bloco_y0+numBloc_Y))){
				QuadradosList[i][j].size = size;
				QuadradosList[i][j].x = x0 + size*(i-bloco_x0);
				QuadradosList[i][j].y = y0 + size*(j-bloco_y0);
			}else{
				QuadradosList[i][j].size = 0;
				QuadradosList[i][j].x = -1;
				QuadradosList[i][j].y = -1;
			}
		}
	}
}

int hall::contNeighbors(int x, int y){
	int count = 0;

	if(x > 0){
		if(QuadradosList[x-1][y].checked){
			count++;
		}
		if((y > 0)&&(QuadradosList[x-1][y-1].checked)){
			count++;
		}
		if((y < numero_y-1)&&(QuadradosList[x-1][y+1].checked)){
			count++;
		}
	}

	if(x < numero_x-1){
		if(QuadradosList[x+1][y].checked){
			count++;
		}
		if((y > 0)&&(QuadradosList[x+1][y-1].checked)){
			count++;
		}
		if((y < numero_y-1)&&(QuadradosList[x+1][y+1].checked)){
			count++;
		}
	}

	if(y > 0){
		if(QuadradosList[x][y-1].checked){
			count++;
		}
	}

	if(y < numero_y-1){
		if(QuadradosList[x][y+1].checked){
			count++;
		}
	}

	return count;
}

void hall::contAllNeighbors(){
	for(int i = 0;i<numero_x;i++){
		for(int j = 0;j<numero_y;j++){
			QuadradosList[i][j].number_of_neighbors = contNeighbors(i,j);
		}
	}
}

Position hall::get_Position(int pos_x, int pos_y){
	Position Q1;
	Q1.x = -1;
	Q1.y = -1;

	if((pos_x < x0)||(pos_y < y0)){
		return Q1;
	}

	if((pos_x >= (x0 + size * numBloc_X))||(pos_y >= (y0 + size * numBloc_Y))){
		return Q1;
	}

	int x = pos_x - x0;
	x = x / size;

	int y = pos_y - y0;
	y = y / size;

	Q1.x = x + bloco_x0;
	Q1.y = y + bloco_y0;

	if(Q1.x >= numero_x || Q1.y >= numero_y){
		printf("ERROR: Out of memory space: Q1.x = %d, ", Q1.x);
		printf("Q1.y = %d\n\n", Q1.y);
	}

	return Q1;
}

void hall::mouse_event_input(ALLEGRO_EVENT *ev){
	ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);


    if (state.buttons & 1) {
        /* Primary (e.g. left) mouse button is held. */
        //printf("KKKK Mouse position: (%d, %d)\n", state.x, state.y);
        if(!play){
            Position Q1 = get_Position(state.x, state.y);
            if((Q1.x >= 0)&&(Q1.y >= 0)){
                if(!QuadradosList[Q1.x][Q1.y].checked){
                    QuadradosList[Q1.x][Q1.y].toogle();
                }
            }
        }
    }

    if (state.buttons & 2) {
        /* Primary (e.g. left) mouse button is held. */
        //printf("KKKK Mouse position: (%d, %d)\n", state.x, state.y);
        if(!play){
            Position Q1 = get_Position(state.x, state.y);
            if((Q1.x >= 0)&&(Q1.y >= 0)){
                if(QuadradosList[Q1.x][Q1.y].checked){
                    QuadradosList[Q1.x][Q1.y].toogle();
                }
            }
        }
    }

	if(ev->type == ALLEGRO_EVENT_MOUSE_AXES){
		al_get_mouse_state(&state);
		if(lastScrollPosition != state.z){
			if(lastScrollPosition < state.z){
				calcNewBlocZeroZero(state.x, state.y, size+1);
				changeSize(true);
				lastScrollPosition = state.z;
			}else{
				//Just ´Zoom in´ have to position the camera.
				//because of it, the below function is commented.
				//calcNewBlocZeroZero(state.x, state.y, size-1);
				changeSize(false);
				lastScrollPosition = state.z;
			}
		}
	}

}

void hall::keyboard_event_input(ALLEGRO_EVENT *ev){
	 if(ev->type == ALLEGRO_EVENT_KEY_DOWN){
	            if(ev->keyboard.keycode == ALLEGRO_KEY_W || ev->keyboard.keycode == ALLEGRO_KEY_UP){
	            	keys[KEY_UP] = 1;
	            }

	            if(ev->keyboard.keycode == ALLEGRO_KEY_S || ev->keyboard.keycode == ALLEGRO_KEY_DOWN){
	            	keys[KEY_DOWN] = 1;
	            }

	            if(ev->keyboard.keycode == ALLEGRO_KEY_A || ev->keyboard.keycode == ALLEGRO_KEY_LEFT){
	            	keys[KEY_LEFT] = 1;
	            }

	            if(ev->keyboard.keycode == ALLEGRO_KEY_D || ev->keyboard.keycode == ALLEGRO_KEY_RIGHT){
	            	keys[KEY_RIGHT] = 1;
	            }
	            setQuadradoInf();
	 }

	 if(ev->type == ALLEGRO_EVENT_KEY_UP){
	 	            if(ev->keyboard.keycode == ALLEGRO_KEY_W || ev->keyboard.keycode == ALLEGRO_KEY_UP){
	 	            	keys[KEY_UP] = 0;
	 	            }

	 	            if(ev->keyboard.keycode == ALLEGRO_KEY_S || ev->keyboard.keycode == ALLEGRO_KEY_DOWN){
	 	            	keys[KEY_DOWN] = 0;
	 	            }

	 	            if(ev->keyboard.keycode == ALLEGRO_KEY_A || ev->keyboard.keycode == ALLEGRO_KEY_LEFT){
	 	            	keys[KEY_LEFT] = 0;
	 	            }

	 	            if(ev->keyboard.keycode == ALLEGRO_KEY_D || ev->keyboard.keycode == ALLEGRO_KEY_RIGHT){
	 	            	keys[KEY_RIGHT] = 0;
	 	            }
	 }
}

void hall::moveGrid(){
	bool updateGrid = false;
	if(keys[KEY_UP] == 1){
		moveUp();
		updateGrid = true;
	}

	if(keys[KEY_DOWN] == 1){
		moveDown();
		updateGrid = true;
	}

	if(keys[KEY_LEFT] == 1){
		moveLeft();
		updateGrid = true;
	}

	if(keys[KEY_RIGHT] == 1){
		moveRight();
		updateGrid = true;
	}

	if(updateGrid){
		setQuadradoInf();
	}
}



void hall::moveUp(){
	if(bloco_y0 > 0){
		bloco_y0 = bloco_y0 - 1;
	}
}

void hall::moveLeft(){
	if(bloco_x0 > 0){
		bloco_x0 = bloco_x0 - 1;
	}
}

void hall::moveDown(){
	if((bloco_y0 + numBloc_Y) < numero_y){
		bloco_y0 = bloco_y0 + 1;
	}
}

void hall::moveRight(){
	if((bloco_x0 + numBloc_X) < numero_x){
		bloco_x0 = bloco_x0 + 1;
	}
}

void hall::checkQuadrado(int x, int y, bool check){
	QuadradosList[x][y].checked = check;
}

void hall::calcNewBlocZeroZero(int pos_x, int pos_y, int nextSize){
	Position Q1 = get_Position(pos_x, pos_y);
	if(nextSize < 1) return;
	if(nextSize > 25) return;
	if((Q1.x == -1)||(Q1.y == -1)) return;

	int distanceToBorderX = pos_x - x0;
	int distanceToBorderY = pos_y - y0;

	int oldQtyBlocksToBorderX = distanceToBorderX/size;
	int oldQtyBlocksToBorderY = distanceToBorderY/size;

	int newQtyBlocksToBorderX = distanceToBorderX/nextSize;
	int newQtyBlocksToBorderY = distanceToBorderY/nextSize;


	if(Q1.x >= numBloc_X/2){
		bloco_x0 = bloco_x0 - newQtyBlocksToBorderX + oldQtyBlocksToBorderX;
	}

	if(Q1.y >= numBloc_Y/2){
		bloco_y0 = bloco_y0 - newQtyBlocksToBorderY + oldQtyBlocksToBorderY;
	}

	if(bloco_x0 < 0){
		bloco_x0 = 0;
	}

	if(bloco_y0 < 0){
		bloco_y0 = 0;
	}
}

void hall::loadFunPatterns(bool){
	if(!play){

		//Pattern 1
		int x1 = 106;
		int y1 = 25;
		QuadradosList[x1][y1].checked = true;
		QuadradosList[x1][y1+1].checked = true;
		QuadradosList[x1+1][y1].checked = true;
		QuadradosList[x1+2][y1].checked = true;
		QuadradosList[x1+3][y1].checked = true;
		QuadradosList[x1+4][y1].checked = true;
		QuadradosList[x1+4][y1+1].checked = true;

		//Pattern 2
		int x2 = 100;
		int y2 = 0;
		QuadradosList[x2][y2].checked = true;
		QuadradosList[x2][y2+1].checked = true;
		QuadradosList[x2][y2+2].checked = true;
		QuadradosList[x2+1][y2+2].checked = true;
		QuadradosList[x2+2][y2+1].checked = true;

		//Pattern 3
		int x3 = 74;
		int y3 = 30;
		QuadradosList[x3][y3].checked = true;
		QuadradosList[x3+1][y3].checked = true;
		QuadradosList[x3][y3+1].checked = true;
		QuadradosList[x3+1][y3+1].checked = true;

		//Pattern 4
		int x4 = 24;
		int y4 = 26;
		QuadradosList[x4][y4].checked = true;
		QuadradosList[x4][y4-1].checked = true;
		QuadradosList[x4][y4+1].checked = true;
		QuadradosList[x4+1][y4].checked = true;
		QuadradosList[x4+2][y4].checked = true;
		QuadradosList[x4+3][y4].checked = true;
		QuadradosList[x4+4][y4].checked = true;
	}
}

void hall::FuncCallBack(bool pressed){
	if(pressed)generationNumber = 0;
	buttonReset->setVisible(!pressed);
	buttonRestore->setVisible(!pressed);
	buttonFunPatterns->setVisible(!pressed);
	buttonSaveFile->setVisible(!pressed);
	buttonLoadFile->setVisible(!pressed);

	if(pressed == true)makeScreenBackup();
	play = pressed;
}

void hall::setButtonCallBack(myButton &b1){
    funcCallBack f1 = &myButtonCallback::FuncCallBack;
	b1.registerCallBack(this, f1);
}

int hall::saveToFile (const std::string file) {
  std::ofstream myfile;
  myfile.open (file);
  myfile << numero_x << " " <<  numero_y << "\n";
  for(int i = 0;i<numero_x;i++){
  	for(int j = 0;j<numero_y;j++){
        if(!QuadradosList[i][j].checked) continue;
  		myfile << i << " " <<  j << " " << QuadradosList[i][j].checked << "\n";
  	}
  }
  myfile.close();
  return 0;
}

int hall::readFile (const std::string file) {
	std::string line;
	std::ifstream myfile (file);

    if(myfile.bad()){
        return -1;
    }




    resetAll(true);
    getline (myfile,line);
    std::stringstream gridInfo(line);
    std::string word0;
    int numX = -1;
    int numY = -1;
    gridInfo >> numX;
    gridInfo >> numY;

    while ( getline (myfile,line) )
    {

        std::stringstream ss(line);
        std::string word;
        int i = -1;
        int j = -1;
        bool check = false;
        ss >> i;
        ss >> j;
        ss >> check;
        if((i < numero_x)&&(j < numero_y) && !QuadradosList[i][j].checked){
            QuadradosList[i][j].checked = check;
        }
    }
    myfile.close();
    return 0;
}

void hall::setButtonCallBack_NextSpeed(myButton &b1){
    funcCallBack cb = &myButtonCallback::NextSpeed;
    b1.registerCallBack(this,cb);
}

void hall::setButtonCallBack_PrevSpeed(myButton &b1){
    funcCallBack cb = &myButtonCallback::PrevSpeed;
    b1.registerCallBack(this,cb);
}

void hall::setButtonCallBack_Zoom(myButton &b1){
    funcCallBack cb = &myButtonCallback::changeSize;
	b1.registerCallBack(this,cb);
}


void hall::setTextGenerations(bigTextLabel<int> &t1){
	t1.insertText("Generation #%d", &generationNumber);
}

void hall::NextSpeed(bool)
{
	if (actual_speed == SPEED_NORMAL){
		actual_speed = SPEED_STOPPED;//Go back to the stopped speed
	} else{
		actual_speed--;
	}
	this->evolution_speed = (al_get_timer_count(timer) / ev_speed[actual_speed].div);
}

void hall::PrevSpeed(bool) {
	actual_speed++;
	if (actual_speed == NUMBER_OF_SPEEDS) actual_speed = SPEED_NORMAL;//Go back to the normal speed
	this->evolution_speed = (al_get_timer_count(timer) / ev_speed[actual_speed].div);
}

void hall::changeSize(bool zoom){
	if(zoom){
		if(size <= 25)size++;
		calcNumBlocs();
		setQuadradoInf();
	}else{
		if(size >= 2) size--;
		calcNumBlocs();
		setQuadradoInf();
	}
}

void hall::update_input(ALLEGRO_EVENT *e){
    mouse_event_input(e);
    keyboard_event_input(e);
}

void hall::renderMouseDebug()
{
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    al_draw_textf(text_font, al_map_rgb(255,0,0), 10,100,0, "BOTAO ESQUERDO %s", state.buttons & 1 ? "PRESSIONADO" : "LIVRE");
    al_draw_textf(text_font, al_map_rgb(255,0,0), 10,120,0, "BOTAO DIREITO %s", state.buttons & 2 ? "PRESSIONADO" : "LIVRE");
    al_draw_textf(text_font, al_map_rgb(255,0,0), 10,140,0, "X: %d Y: %d", state.x, state.y);

}
