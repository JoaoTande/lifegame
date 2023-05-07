#ifndef BIGTEXTLABEL_CPP
#define BIGTEXTLABEL_CPP

#include "interfaceComponent.h"
#include <vector>

template <typename T>
class bigTextLabel: public interfaceComponent{
private:
	int x0;
	int y0;
	ALLEGRO_COLOR white;
	ALLEGRO_COLOR red;
	ALLEGRO_COLOR blue;
	ALLEGRO_COLOR yellow;
	ALLEGRO_FONT *text_font = nullptr;
	std::vector<std::pair<const char*, T*>> listOfText;

public:


    void X(int x) {  this->x0 = x; }
    int X(void) { return this->x0; }

    void Y(int y) {  this->y0 = y; }
    int Y(void) { return this->y0; }

    bigTextLabel(){
        x0 = 0;
        y0 = 0;
        white = al_map_rgb_f(1.0, 1.0, 1.0);
        red = al_map_rgb_f(1.0, 1.0, 1.0);
        blue = al_map_rgb_f(1.0, 1.0, 1.0);
        yellow = al_map_rgb_f(1.0, 1.0, 0);
        text_font = al_create_builtin_font();
    }




    bigTextLabel(int x, int y){
        x0 = x;
        y0 = y;
        white = al_map_rgb_f(1.0, 1.0, 1.0);
        red = al_map_rgb_f(1.0, 1.0, 1.0);
        blue = al_map_rgb_f(1.0, 1.0, 1.0);
        yellow = al_map_rgb_f(1.0, 1.0, 0);
        text_font = al_create_builtin_font();
    }



    void insertText(const char* t1, T* num = nullptr){
        listOfText.push_back(std::make_pair(t1, num));
    }


    void update(){

    }

    void update_input(ALLEGRO_EVENT *e)
    {
        (void)e;// Left unused
    }


    void draw()
    {
        int position_x = x0;
        int position_y = y0;
        const ALLEGRO_COLOR white = al_map_rgb_f(1.0, 1.0, 1.0);

        for(size_t i = 0;i<listOfText.size();i++){
            if(listOfText[i].second == nullptr){
                al_draw_textf(text_font, white, position_x, position_y, 0, listOfText[i].first);
            }else{
                al_draw_textf(text_font, white, position_x, position_y, 0, listOfText[i].first, *listOfText[i].second);
            }
            position_y = position_y + 10;
        }
    }

};

#endif
