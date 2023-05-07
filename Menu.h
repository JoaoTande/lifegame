#ifndef MENU_H
#define MENU_H
#include <string>
#include <memory>
#include <array>
#include <vector>
#include <algorithm>
#include <allegro5/allegro.h>
#include <list>

#include "gameScreenContext.h"
#include "bigTextLabel.h"
#include "button.h"


#include "myButtonCallback.h"

using myButtonPtr = std::shared_ptr<myButton>;

class Menu : public myButtonCallback {

public:

    enum class MenuOptionId: int {
        START_GAME=1,
        LOAD_FILE,
        QUIT
    };

    struct MenuOption {
        std::string text;
        std::string name;
        myButton button;
    };

    using MenuOptionPtr = std::shared_ptr<MenuOption>;

    Menu(gameScreenContext& context);
    ~Menu();
    void addSingleButton(std::string name, std::string text);

    void menuFunc(bool status);

    virtual void FuncCallBack(bool status){
        menuFunc(status);
        printf("apertou virtual funccallback\n");
    }

    void setMenuOffset(int x, int y, int height_offset = 0);
    void setMenuOptionFont(const std::string filepath, int size, int flags);
    void setMenuOptionFont(ALLEGRO_FONT* font);

    void moveMenuUp();
    void moveMenuDown();

    void drawMenuSelected();
    void drawTitle();

    void updateMenu();

private:
    int y;
    int x;
    int width_offset;
    int height_offset;

    int menu_selected;
    int selected_x;
    int selected_y;

    ALLEGRO_BITMAP *cursor;

    gameScreenContext& menuContext;
    std::list<MenuOptionPtr> m_menu_options;
    MenuOptionId menu_chosen;


};

#endif // MENU_H
