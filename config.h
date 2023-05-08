#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class Config {
public:
    Config();
    bool loadFile(const std::string filepath);
    bool saveFile(const std::string filepath);

    //try to resolve automatic
    template<typename T>
    static T getConfig(Config &cfg, const char *sector, const char *key)
    {
        const char *v = al_get_config_value(cfg.cfg, sector, key);


        return  static_cast<T>(std::atoi(v));

    }

    static const char* getConfigStr(Config& cfg, const char *sector, const char *key, const char *def  = "");
    static bool  getConfigBool(Config& cfg, const char *sector, const char *key,  bool def = false);
    static int   getConfigInt(Config& cfg, const char *sector, const char *key, int def=0);
    static float getConfigFloat(Config& cfg, const char *sector, const char *key, float def=0.0f);

    ALLEGRO_CONFIG* createDefaultConfig();
    void Unload();

    template<typename T>
    inline T getConfigValue(const char *sector, const char *key){
        const char *v = al_get_config_value(cfg, sector, key);
        return  static_cast<T>(std::atoi(v));
    }


private:
    ALLEGRO_CONFIG *cfg;
};

#endif // CONFIG_H
