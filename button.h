#ifndef BUTTON_CPP
#define BUTTON_CPP

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
#include <iostream>
#include <vector>

typedef void (myButtonCallback::*funcCallBack)(bool);

struct ObjectCallBack{
    myButtonCallback* object;
	funcCallBack func;
};

class myButton: public interfaceComponent{
private:
	int x0;
	int y0;
	int sizeX0;
	int sizeY0;
    bool text_button;
	bool pressed;
	bool visible;
	bool holdButton; //Hold the button always in the same position. Always true or always false. See "alwaysButton"
	bool alwaysButton; // If holdButton = true the button pressed will be kept always in this position.
	ALLEGRO_BITMAP *picture1 = NULL;
	ALLEGRO_BITMAP *picture2 = NULL;
	ALLEGRO_FONT *button_font;
	std::vector<ObjectCallBack> CallBackList;

	std::string query_description;  //an info when you put mouse over the button pop up a short description
    std::string button_text; // button text of not  image is loaded
    bool mouse_is_over;

    int font_size;

public:


    myButton(int x, int y, int sizeX, int sizeY, bool is_text = false);
    myButton(bool is_text = false);

    void setTextButton(const bool v) {

        if(button_font){
            al_destroy_font(button_font);
            button_font = nullptr;
        }

        text_button = v;
    }
    bool isTextButton(void) const { return text_button; }
    void setTextFont(const std::string filepath, const int size, const int flags);
    void setTextFont(ALLEGRO_FONT *font);
    float getButtontextWidth(void) const;


    void insertText(const std::string text);
	void setInfo(int x, int y, int sizeX, int sizeY);
	void setVisible(bool v1);
	void toogle();
	void setPressedAlwaysFalse();
	void setPressedAlwaysTrue();
	void mouse_event_input(ALLEGRO_EVENT *ev);
	void update();
	void load_sprites();
	void draw_sprites();
	void drawHint();
	void set_description(const std::string text);
    void registerCallBack(myButtonCallback* object, funcCallBack c1);
	void set_sprite1(const char *filename);
	void set_sprite2(const char *filename);

	virtual void update_input(ALLEGRO_EVENT *e);
	virtual void draw();

	ALLEGRO_BITMAP *tmp_button(); // called only when cannot find the image
    ALLEGRO_FONT* getFont() const { return button_font; }
    int getFontSize() const { return font_size; }


};


#endif
