#include "Menu.h"
#include "config.h"
#include "main.h"


char title_text[][127] = {
    {"Conway\'s Game of Life"},
    {"LIFEGAME!"}
};



Menu::Menu(gameScreenContext &context) : menuContext(context)
{
    menu_selected = 1;
    selected_x = 0;
    selected_y = 0;
    cursor = nullptr;

    //cursor  = al_load_bitmap("pictures//gl.png");

    cursor = al_create_bitmap(16,16);
    al_set_target_bitmap(cursor);
    al_clear_to_color(al_map_rgb(255,255,255));
    al_set_target_backbuffer(display);

    menu_chosen  = MenuOptionId::START_GAME;

    /*
    if(!cursor){
        cursor = al_create_bitmap(32,32);
        al_set_target_bitmap(cursor);
        al_clear_to_color(al_map_rgb(255,255,255));
        al_set_target_backbuffer(display);
    }
    */

}

Menu::~Menu()
{

}



void Menu::addSingleButton(std::string name, std::string text)
{

    MenuOptionPtr opt = std::make_shared<MenuOption>();

    opt->button.setTextButton(true);
    opt->button.insertText(text);
    opt->text = text;
    opt->name = name;


    funcCallBack f1 = &myButtonCallback::FuncCallBack;
    opt->button.registerCallBack(this,f1);

   m_menu_options.push_back(std::move(opt));
   menuContext.insertComponent(&m_menu_options.back()->button);

}

void Menu::menuFunc(bool status)
{
    printf("status %d", status);
}

void Menu::setMenuOffset(int x, int y, int height_offset)
{

    this->x = x;
    this->y = y;
    this->height_offset = height_offset;
    int count = 1;

    for(auto& m : m_menu_options){
        int text_width = al_get_text_width(m->button.getFont(), m->text.c_str()) + 2;
        m->button.setInfo(x, y + (count + height_offset) * count,text_width, m->button.getFontSize());
        count++;
    }




}

void Menu::setMenuOptionFont(const std::string filepath, int size, int flags)
{
    for(auto& m : m_menu_options){
        m->button.setTextFont(filepath,size,flags);
    }
}

void Menu::setMenuOptionFont(ALLEGRO_FONT *font)
{
    if(!font){
        for(auto& m : m_menu_options){
            m->button.setTextFont(al_create_builtin_font());
        }
        return;
    }

    for(auto& m : m_menu_options){
            m->button.setTextFont(font);
    }
    return;
}

void Menu::moveMenuUp()
{
    if(static_cast<size_t>(menu_selected) <= 1){
        menu_selected = m_menu_options.size();
        return;
    }

    menu_selected--;
}

void Menu::moveMenuDown()
{
    if(static_cast<size_t>(menu_selected) > m_menu_options.size()-1){
        menu_selected = 1;
        return;
    }


    menu_selected++;
}

void Menu::drawMenuSelected()
{

    al_draw_scaled_rotated_bitmap(cursor,
                                  al_get_bitmap_width(cursor)/2,
                                  al_get_bitmap_height(cursor)/2,
                                  this->x - 50,
                                  (this->y + this->height_offset * menu_selected)+this->height_offset/2,
                                  1.0f,1.0f,0.0,0
                                  );
}

void Menu::drawTitle()
{
    ALLEGRO_FONT *fnt = al_load_ttf_font("fonts//Game Of Squids.ttf", 48,0);




    if(!fnt) return;

    for(size_t i = 0;i < sizeof(title_text)/sizeof(title_text[0]);i++){
        int text_size = al_get_text_width(fnt,title_text[i]);
        al_draw_textf(fnt,al_map_rgb(255,255,255), al_get_display_width(display)/2 - text_size/2 ,i * 80 +10,0,"%s", title_text[i]);
    }

    al_destroy_font(fnt);
}

void Menu::updateMenu()
{
    menu_chosen = static_cast<MenuOptionId>(menu_selected);

    switch(menu_chosen){
        case MenuOptionId::START_GAME:
            g_gamestate = GameState::IN_GAME_SCREEN;
        break;

        case MenuOptionId::LOAD_FILE:
        break;

        case MenuOptionId::QUIT:
        //printf("QUIT");
        running = false;
        fprintf(stdout,"QUIT");
        break;
    }
}





