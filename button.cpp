#include "button.h"


myButton::myButton(int x, int y, int sizeX, int sizeY, bool is_text){
	x0 = x;
	y0 = y;
	sizeX0 = sizeX;
	sizeY0 = sizeY;
	pressed = false;
	visible = true;
	holdButton = false;
	alwaysButton = false;
	mouse_is_over = false;
	button_font = nullptr;
    text_button = false;

    if(!is_text){
        load_sprites();
    }
}

myButton::myButton(bool is_text){
	x0 = 0;
	y0 = 0;
	sizeX0 = 100;
	sizeY0 = 100;
	pressed = false;
	visible = true;
	holdButton = false;
	alwaysButton = false;
	mouse_is_over = false;
	button_font = nullptr;
    text_button = false;

    if(!is_text){
        load_sprites();
    }
}

void myButton::setTextFont(const std::string filepath, const int size, const int flags)
{

    if(button_font) return;

    button_font = al_load_ttf_font(filepath.c_str(), size, flags);
    if(!button_font){
        fprintf(stderr, "Font %s cannot be loaded!", filepath.c_str());
        return;
    }

    this->font_size = size;

}

void myButton::setTextFont(ALLEGRO_FONT *font)
{
    button_font = font;
}

float myButton::getButtontextWidth(void) const
{
    return al_get_text_width(button_font, button_text.c_str());
}

void myButton::insertText(const std::string text)
{
    this->button_text = text;
}

void myButton::setInfo(int x, int y, int sizeX, int sizeY){
	x0 = x;
	y0 = y;
	sizeX0 = sizeX;
	sizeY0 = sizeY;
}

void myButton::setVisible(bool v1){
	visible = v1;
}

void myButton::toogle(){
		if(!holdButton){
			if(pressed){
				pressed = false;
			}else{
				pressed = true;
			}
		}else{
			pressed = alwaysButton;
		}

		for(size_t i = 0;i<CallBackList.size();i++){
			ObjectCallBack obj1;
			obj1.object = CallBackList[i].object;
			obj1.func = CallBackList[i].func;
			(obj1.object->*obj1.func)(pressed);
		}
}

void myButton::setPressedAlwaysFalse(){
	holdButton = true;
	alwaysButton = false;
	pressed = alwaysButton;
}

void myButton::setPressedAlwaysTrue(){
	holdButton = true;
	alwaysButton = true;
	pressed = alwaysButton;
}

void myButton::update_input(ALLEGRO_EVENT *e){
    mouse_event_input(e);
}

void myButton::mouse_event_input(ALLEGRO_EVENT *ev){
	ALLEGRO_MOUSE_STATE state;

	if(visible == true){

        if(ev->type == ALLEGRO_EVENT_MOUSE_AXES){
            al_get_mouse_state(&state);

            if((state.x >= x0)&&(state.x <= x0+sizeX0)){
                if((state.y >= y0)&&(state.y <= y0+sizeX0)){
						mouse_is_over = true;
                }
            }else {
                mouse_is_over = false;
                //printf("MOUSE OVER %d \n\n",mouse_is_over);
            }
        }

		if(ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            al_get_mouse_state(&state);

            if (state.buttons & 1) {

				//Primary (e.g. left) mouse button is held.
				//printf("KKKK Mouse position: (%d, %d)\n", state.x, state.y);
				if((state.x >= x0)&&(state.x <= x0+sizeX0)){
					if((state.y >= y0)&&(state.y <= y0+sizeX0)){
						toogle();
					}
				}
			}
		}
	}
}

void myButton::registerCallBack(myButtonCallback* object, funcCallBack f1){
	ObjectCallBack obj1;
	obj1.object = object;
	obj1.func = f1;
	CallBackList.push_back(obj1);
}

void myButton::update(){

}

void myButton::load_sprites()
{
   picture1 = al_load_bitmap("pictures//play.png");
   if (!picture1){
	   printf("\n\nNAO CARREGOU picture1\n\n");
	   picture1 = tmp_button();
   }
   picture2 = al_load_bitmap("pictures//stop.png");
   if (!picture2){
	   printf("\n\nNAO CARREGOU picture2\n\n");
	   picture2 = tmp_button();
   }

   this->button_font = al_create_builtin_font();
}

void myButton::set_sprite1(const char *filename){
	picture1 = al_load_bitmap(filename);
	if (!picture1){
		printf("\n\nNAO CARREGOU Sprite1\n\n");
        picture1 = tmp_button();
	}
}

void myButton::set_sprite2(const char *filename){
	picture2 = al_load_bitmap(filename);
	if (!picture2){
		printf("\n\nNAO CARREGOU Sprite2\n\n");
        picture2 = tmp_button();
	}
}

void myButton::drawHint(){
	if(mouse_is_over && query_description.size() > 0){
		const int query_width = al_get_text_width(button_font, query_description.c_str()) + 20;
	    const int query_height = sizeY0+30;
        al_draw_filled_rectangle(x0,y0+sizeY0, x0+query_width,y0+query_height, al_map_rgba(0,0,0,255));
        al_draw_rectangle(x0,y0+sizeY0, x0+query_width-1,y0+query_height, al_map_rgba(255,255,255,255),1.0);
        al_draw_textf(button_font, al_map_rgba(255,255,255,255), x0 + 10, y0+sizeY0 + 10, 0, "%s", query_description.c_str());
	}
}

void myButton::draw_sprites(){
	if(!pressed && picture1){
        al_draw_scaled_bitmap(picture1,
                0,                                 //Source x
                0,								   //Source y
                al_get_bitmap_width(picture1),     //Source Width
                al_get_bitmap_height(picture1),    //Source Height
                x0, 							   //Destination x
                y0, 							   //Destination y
                sizeX0, 						   //Destination Width
                sizeY0, 						   //Destination Height
                0);

        drawHint();

	}else if(picture2){
		al_draw_scaled_bitmap(picture2,
				0,                                 //Source x
				0,								   //Source y
				al_get_bitmap_width(picture2),     //Source Width
				al_get_bitmap_height(picture2),    //Source Height
				x0, 							   //Destination x
				y0, 							   //Destination y
				sizeX0, 						   //Destination Width
				sizeY0, 						   //Destination Height
				0);

		if((holdButton)&&(alwaysButton)){
			drawHint();
		}
	}



}

void myButton::set_description(const std::string text){
    query_description = text;
}

void myButton::draw(){

    if(isTextButton()){
        al_draw_textf(button_font, al_map_rgb(255,255,255), x0,y0, 0, "%s", button_text.c_str());
        return;
    }

    if(visible == true){
        draw_sprites();
        return;
    }
}

ALLEGRO_BITMAP* myButton::tmp_button(){
    ALLEGRO_BITMAP *tmp = nullptr;

    tmp  = al_create_bitmap(100,100);

    //change the render to render inside this bitmap
    // dont forget to restore to backbuffer a.k.a screen
    al_set_target_bitmap(tmp);
    al_clear_to_color(al_map_rgb(255,0,0));
    ALLEGRO_FONT *fnt = al_create_builtin_font();
    const char *text = this->query_description.size() > 0 ? this->query_description.c_str() : "TMP Button";
    al_draw_text(fnt, al_map_rgba(255,255,255,255), 0, 0, 0, text);
    //restore the render to the backbuffer
    al_set_target_backbuffer(display);
    al_destroy_font(fnt);
    return tmp;
}
