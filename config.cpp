#include "config.h"
#include <vector>
#include <string>
#include <cstdlib>

#define STRINGIFY(x) #x
#define STRINGIFY2(x) STRINGIFY(x)

typedef struct CONFIG_FIELD {
    char sector[127];
    char key[127];
    char value[127];

}CONFIG_FIELD;

#define MAX_DEFAULT_CONFIG 255

#define CONFIG_END {"","", {0} }

CONFIG_FIELD default_config[MAX_DEFAULT_CONFIG] = {
    {"game", "fullscreen", "0"},
    {"game", "zoom", "1"},
    {"game", "speed", "1"},
    {"game","width","1300"},
    {"game","height","700"},
    {"game","vsync", "1"},
    {"game","laptop_mode", "0"},
    {"game","max_fps_desired", "60"},
    CONFIG_END


};


Config::Config() :
    cfg(nullptr)
{

}

bool Config::loadFile(const std::string filepath){
    ALLEGRO_PATH *path = nullptr;

    path = al_create_path(filepath.c_str());
    this->cfg = al_load_config_file(al_path_cstr(path,ALLEGRO_NATIVE_DRIVE_SEP));

    if(!this->cfg){
        //se nao encontrar gerar um novo
        this->cfg = createDefaultConfig();
        if(!this->cfg){
            return false;
        }

        saveFile("config.cfg");
        return true;
    }

    al_destroy_path(path);
    return true;

}

bool Config::saveFile(const std::string filepath){

    if(!cfg){
        return false;
    }
    ALLEGRO_PATH *path = nullptr;
    path = al_create_path(filepath.c_str());
    al_save_config_file(al_path_cstr(path,ALLEGRO_NATIVE_DRIVE_SEP), cfg);
    al_destroy_path(path);
    return true;
}

const char *Config::getConfigStr(Config &cfg, const char *sector, const char *key, const char *def)
{
    const char *v = al_get_config_value(cfg.cfg, sector, key);
   return (v) ? v : def;
}

ALLEGRO_CONFIG* Config::createDefaultConfig(){
    ALLEGRO_PATH *path = nullptr;
    ALLEGRO_CONFIG *tmp_cfg = nullptr;

    path = al_create_path("config.cfg");
    tmp_cfg = al_create_config();
    al_add_config_section(tmp_cfg, "game");


    uint32_t config_size = sizeof(default_config) / sizeof(default_config[0]);

    for(uint32_t i = 0; i < config_size; i++){
        CONFIG_FIELD *f = &default_config[i];
        if(strlen(f->key) == 0 || strlen(f->sector) == 0) continue;
        al_set_config_value(tmp_cfg, f->sector, f->key, f->value);
    }

    al_destroy_path(path);

    return tmp_cfg;
}



bool  Config::getConfigBool(Config& cfg, const char *sector, const char *key, bool def){
    bool result = false;
    const char *val = al_get_config_value(cfg.cfg, sector, key);

    if(strcmp(val, "true") == 0){
        result = true;
    }

    return (val) ? result : def ;

}

int   Config::getConfigInt(Config& cfg, const char *sector, const char *key, int def){
    const char *val = al_get_config_value(cfg.cfg, sector, key);
    return (val) ? std::atoi(val) : def;
}
float Config::getConfigFloat(Config& cfg, const char *sector, const char *key, float def){
    const char *val = al_get_config_value(cfg.cfg, sector, key);
    return (val) ?  std::atof(val) : def;
}

void Config::Unload(){
    if(cfg){
        al_destroy_config(cfg);
    }
}

