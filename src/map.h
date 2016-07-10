#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include <oxygine-framework.h>
#include "screens/gamescreen.h"

using namespace oxygine;

typedef struct {
	int firstgid;
	std::string name;
	int tilewidth;
	int tileheight;
	int tilecount;
	int columns;

	std::string source;
	int img_width;
	int img_height;
}tileset;


typedef struct {
	std::string name;
	int width;
	int height;
	std::vector<int> gid_set;
}layer;


typedef struct {
	int x;
	int y;
	std::string name;
}position;




class Map
{
    Resources * m_resources;

    int row_map;  //tiles
    int col_map; //tiles

	int width_tile;
	int height_tile;

	std::vector<tileset> tilesets;
	std::vector<layer> layers;


	position hero_pos;

	std::vector<position> melee_fan_pos;
	std::vector<position> range_fan_pos;
	std::vector<position> rapper_pos;
	std::vector<position> army_pos;
	std::vector<position> devil_pos;
	std::vector<position> zombie_pos;
	std::vector<position> pixie_pos;

	std::vector<position> boss_pos;

	std::vector<position> treasure_pos;



public:
    Map();
	~Map();
    void xmlParser(std::string path);
    void loadTiles();
    void attachToMap(GameScreen *gs);
    void drawLayer(layer &m_layer, GameScreen *gs);
};


#endif // MAP

