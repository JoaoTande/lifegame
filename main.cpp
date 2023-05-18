#include "main.h"

//static int SCREEN_W = 1300;
//static int SCREEN_H = 700;

static double FPS = 60.0;
static bool background_mode = false;
static bool paused = false;

static bool fullscreen = false;


ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;

const ALLEGRO_COLOR white = al_map_rgb_f(1.0, 1.0, 1.0);
const ALLEGRO_COLOR red = al_map_rgb_f(1.0, 1.0, 1.0);
const ALLEGRO_COLOR blue = al_map_rgb_f(1.0, 1.0, 1.0);
const ALLEGRO_COLOR yellow = al_map_rgb_f(1.0, 1.0, 0);

bool running = true;
static bool redraw = false;
static Config config;




GameState g_gamestate = GameState::MAIN_MENU_SCREEN;

static int init_allegro(void)
{


		// Initialize allegro
		if (!al_init()) {
			fprintf(stderr, "Failed to initialize allegro.\n");
			return 1;
		}

		if (!al_init_image_addon()) {
			al_uninstall_system();
			fprintf(stdout, "Error Critical!");
			return 0;
		}

		if (!al_install_keyboard()) {
			al_uninstall_system();
		    fprintf(stdout, "Error Critical!");
			return 0;
		}

		if (!al_install_mouse()) {
			al_uninstall_system();
			fprintf(stdout, "Error Critical!");
			return 0;
		}


        config.loadFile("config.cfg");
        fullscreen = Config::getConfig<bool>(config, "game", "fullscreen");


        int display_width = Config::getConfigInt(config, "game", "width");
        int display_height = Config::getConfigInt(config, "game", "height");


		// Initialize the timer


        double fps_desired = Config::getConfigFloat(config, "game", "max_fps_desired", FPS);
        int laptop_mode =   Config::getConfigInt(config, "game", "laptop_mode", 0);


        if(laptop_mode){
            timer = al_create_timer(1.0 / 30.0);
        }else {
            if(fps_desired > 60.0){
                fprintf(stdout, "please set CFG  FPS less or equal to 60, higher speed can have some slowness issues");
            }

            timer = al_create_timer(1.0 / fps_desired);
        }


        if (!timer) {
			fprintf(stderr, "Failed to create timer.\n");
			return 1;
		}

		ALLEGRO_MONITOR_INFO info;
		al_get_monitor_info(0, &info);
		if(((info.x2 - info.x1) > 0)&&((info.y2 - info.y1) > 0)){ // Verify if the resolution is ok...
            display_width = info.x2 - info.x1;
            display_height = info.y2 - info.y1 - 80;
		}

        int flags = ALLEGRO_OPENGL_FORWARD_COMPATIBLE | ALLEGRO_PROGRAMMABLE_PIPELINE;

        if(fullscreen){
            flags |= ALLEGRO_FULLSCREEN_WINDOW;
        }else {
            flags |= ALLEGRO_WINDOWED;
        }

		// Create the display
		al_set_new_display_flags(flags);

        al_set_new_display_option(ALLEGRO_SAMPLES,1, ALLEGRO_SUGGEST);
        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS,1,ALLEGRO_SUGGEST);


        int vsync_enabled = Config::getConfigInt(config, "game", "vsync");

        if(vsync_enabled < 0) vsync_enabled = 0;
        if(vsync_enabled > 1) vsync_enabled = 1;


        al_set_new_display_option(ALLEGRO_VSYNC, vsync_enabled, ALLEGRO_SUGGEST);

        if(display_width <= 800)  display_width = 800;
        if(display_height <= 600) display_width = 600;


        display = al_create_display(display_width, display_height);
        if (!display) {
			fprintf(stderr, "Failed to create display.\n");
            return 0;
		}

        //force all bitmaps being used by GPU + better quality, less crisp
		al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP | ALLEGRO_MIN_LINEAR | ALLEGRO_MIPMAP);

		// Create the event queue
        event_queue = al_create_event_queue();
        if (!event_queue) {
			fprintf(stderr, "Failed to create event queue.");
			return 1;
		}


        if(!al_init_font_addon()){
                fprintf(stderr, "font addon cannot be initialized!");
        }


        if(!al_init_ttf_addon()){
            fprintf(stderr, "ttf addon cannot be initialized!");
        }

        if(!al_init_primitives_addon()){
            fprintf(stderr, "primitives addon cannot be initialized!");
        }

        ALLEGRO_BITMAP *icon = nullptr;

		if((icon = al_load_bitmap("pictures//gl.png")) != NULL ){
            al_set_display_icon(display, icon);
		}


		// Register event sources
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());

		// Display a black screen
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();
		// Start the timer
        al_start_timer(timer);




		return 1;
}


static void S_processWindowEvents(ALLEGRO_EVENT& e){
    if(e.type == ALLEGRO_EVENT_DISPLAY_CLOSE && !fullscreen){
            g_gamestate = GameState::MAIN_MENU_SCREEN;
    }

    if(e.type == ALLEGRO_EVENT_DISPLAY_HALT_DRAWING){
        al_acknowledge_drawing_halt(display);
        background_mode = true;
    }

    if(e.type == ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING){
        al_acknowledge_drawing_resume(display);
        background_mode = false;
    }

    if(e.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT){
        paused = true;
    }

    if(e.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){
        paused = false;
    }


    if(e.type == ALLEGRO_EVENT_KEY_DOWN){
        if(e.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            g_gamestate = GameState::MAIN_MENU_SCREEN;
        }
    }

}




int main()
{

    if(!init_allegro()){
        exit(0);
    }

    gameScreenContext mainMenuContext;
    gameScreenContext gameContext;

    int display_w,display_h;

    display_w = al_get_display_width(display);
    display_h = al_get_display_height(display);

    //gameContext.setScreenSize(w, h);






    hall hall1(50, 150, display_w, display_h);
	myButton playButton(570, 40, 100, 100);
	myButton resetButton(680, 40, 100, 100);
	myButton restoreButton(800, 40, 100, 100);
	myButton funButton(910, 40, 100, 100);
	myButton saveButton(1020, 40, 100, 100);
	myButton loadButton(1130, 40, 100, 100);
	myButton prevSpeedButton(230,110,32,32);
	myButton nextSpeedButton(265,110,32,32);
	myButton lessZoomButton(1250,110,32,32);
	myButton moreZoomButton(1250,75,32,32);
	myButton aboutButton(1250,40,32,32);
	//myButton moreZoomButton(1288,110,32,32);
	bigTextLabel<int> text1(50,50);
	bigTextLabel<int> textGenerations(320,135);
	myInformationPanel infoAbout(200,200,450,270);

	aboutButton.setPressedAlwaysTrue();
	lessZoomButton.setPressedAlwaysFalse();
	moreZoomButton.setPressedAlwaysTrue();

	text1.insertText("Life Game!");
	text1.insertText("");
	text1.insertText("3 WHITE neighbors and the BLACK becomes WHITE!! (It is ALIVE!)");
	text1.insertText("Less than 2 WHITE neighbors, or more than 3, and the WHITE");
	text1.insertText("becomes BLACK!! (It is DEAD!)");

	playButton.set_description("Play the Game! (Start generations)");
    aboutButton.set_description("About us...??");

	resetButton.set_sprite1("pictures//reset.png");
	resetButton.set_sprite2("pictures//reset.png");
	resetButton.set_description("Clears all the grid");

	restoreButton.set_sprite1("pictures//restore.png");
	restoreButton.set_sprite2("pictures//restore.png");
    restoreButton.set_description("Restore the last grid");

	funButton.set_sprite1("pictures//fun.png");
	funButton.set_sprite2("pictures//fun.png");
	funButton.set_description("Generates fun patterns");

	saveButton.set_sprite1("pictures//save.png");
	saveButton.set_sprite2("pictures//save.png");
	saveButton.set_description("Saves the grid to a file");

	loadButton.set_sprite1("pictures//load.png");
	loadButton.set_sprite2("pictures//load.png");
	loadButton.set_description("Loads a saved game file to the game");

	prevSpeedButton.set_sprite1("pictures//prev.png");
	prevSpeedButton.set_sprite2("pictures//prev.png");
	prevSpeedButton.set_description("Decreases speed of evolution");

	nextSpeedButton.set_sprite1("pictures//next.png");
	nextSpeedButton.set_sprite2("pictures//next.png");
    nextSpeedButton.set_description("Increase speed of evolution");

	aboutButton.set_sprite1("pictures//about.png");
	aboutButton.set_sprite2("pictures//about.png");

	lessZoomButton.set_sprite1("pictures//less.png");
	lessZoomButton.set_sprite2("pictures//less.png");
	lessZoomButton.set_description("Zoom out");

	moreZoomButton.set_sprite1("pictures//plus.png");
	moreZoomButton.set_sprite2("pictures//plus.png");
    moreZoomButton.set_description("Zoom in");


	hall1.setButtonCallBack(playButton);
	hall1.setButtonCallBack_Reset(resetButton);
	hall1.setButtonCallBack_Restore(restoreButton);
    hall1.setButtonCallBack_FunPatterns(funButton);
    hall1.setButtonCallBack_SaveFile(saveButton);
	hall1.setButtonCallBack_LoadFile(loadButton);
    hall1.setButtonCallBack_PrevSpeed(prevSpeedButton);
    hall1.setButtonCallBack_NextSpeed(nextSpeedButton);
    hall1.setTextGenerations(textGenerations);
    hall1.setButtonCallBack_Zoom(lessZoomButton);
    hall1.setButtonCallBack_Zoom(moreZoomButton);

    infoAbout.setButtonCallBack_OpenAbout(aboutButton);

    gameContext.insertComponent(&hall1);
    gameContext.insertComponent(&playButton);
    gameContext.insertComponent(&resetButton);
    gameContext.insertComponent(&restoreButton);
    gameContext.insertComponent(&funButton);
    gameContext.insertComponent(&saveButton);
    gameContext.insertComponent(&loadButton);
    gameContext.insertComponent(&prevSpeedButton);
    gameContext.insertComponent(&nextSpeedButton);
    gameContext.insertComponent(&text1);
    gameContext.insertComponent(&textGenerations);
    gameContext.insertComponent(&infoAbout);
    gameContext.insertComponent(&lessZoomButton);
    gameContext.insertComponent(&moreZoomButton);
    gameContext.insertComponent(&aboutButton);
    gameContext.setGlobalTimer(timer);
    gameContext.setGlobalDisplay(display);
    gameContext.setGlobalEventQueue(event_queue);

    Menu mainMenu(mainMenuContext);

    mainMenu.addSingleButton("menu_start", "START");
    mainMenu.addSingleButton("menu_load", "LOAD");
    mainMenu.addSingleButton("menu_quit", "QUIT");

    mainMenu.setMenuOptionFont("fonts//Game Of Squids.ttf",22,0);
    mainMenu.setMenuOffset(al_get_display_width(display)/2 - 100, al_get_display_height(display)/2 - 100 , 36);

    mainMenuContext.setGlobalTimer(timer);
    mainMenuContext.setGlobalDisplay(display);
    mainMenuContext.setGlobalEventQueue(event_queue);

    while(running){

        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;

        al_init_timeout(&timeout, 0.1);


        if(redraw){
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            switch(g_gamestate){

                case GameState::LOGO_SCREEN: break; //temporary disabled
                case GameState::IN_GAME_SCREEN:
                {
                    gameContext.draw();
                }
                break;

                case GameState::MAIN_MENU_SCREEN:
                {
                    mainMenu.drawTitle();
                    mainMenu.drawMenuSelected();
                    mainMenuContext.draw();
                }
                break;
            }

            al_flip_display();

        }

        while(al_wait_for_event_until(event_queue, &event, &timeout) ){

            if(event.type == ALLEGRO_EVENT_TIMER){


                switch(g_gamestate){

                    case GameState::LOGO_SCREEN: break;
                    case GameState::IN_GAME_SCREEN:
                    {
                        if(!paused){
                            gameContext.update();
                            redraw = true;
                        }
                    }
                    break;
                    case GameState::MAIN_MENU_SCREEN:
                            mainMenuContext.update();
                            redraw = true;
                    break;
                }
            }

            if(g_gamestate == GameState::IN_GAME_SCREEN){
                 S_processWindowEvents(event);
                 gameContext.update_input(&event);

            }

            if(g_gamestate == GameState::MAIN_MENU_SCREEN){
                mainMenu.processMenuEvents(event,mainMenu);
                mainMenuContext.update_input(&event);
            }

        };

    }

	// Clean up
    config.Unload();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

	return 0;
}
