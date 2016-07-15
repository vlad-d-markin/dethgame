#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include <oxygine-framework.h>
#include "tile.h"
#include "screens/gamescreen.h"

using namespace oxygine;


// information about the specific tileset
typedef struct {
    int first_gid;
    int pix_tile_width;
    int pix_tile_height;
    int tile_count;
    int columns_count;

    int pix_img_width;
    int pix_img_height;

    std::string name;
	std::string source;
} Tileset;

// information about the specific layer
typedef struct {
	std::string name;
    int num_tile_row;
    int num_tile_col;
	std::vector<int> gid_set;
} Layer;

// position and name of the object
typedef struct {
	int x;
	int y;
	std::string name;
} Position;



class Map
{
    Resources * map_resources;
    std::vector<Tile> vec_maptiles;

    // map specifications
    int num_tiles_row;
    int num_tiles_col;
    int pix_tile_width;
    int pix_tile_height;

    // vectors of tilesets and layers
    std::vector<Tileset> vec_tilesets;
    std::vector<Layer> vec_layers;

    // positions of hero, bosses, mobs and treasures
    Position pos_hero;
    std::vector<Position> vec_pos_boss;
    std::vector<Position> vec_pos_treasure;
    std::vector<Position> vec_pos_melee_fan;
    std::vector<Position> vec_pos_range_fan;
    std::vector<Position> vec_pos_rapper;
    std::vector<Position> vec_pos_army;
    std::vector<Position> vec_pos_devil;
    std::vector<Position> vec_pos_zombie;
    std::vector<Position> vec_pos_pixie;


public:
    Map();
	~Map();

    void parseXML();
    void loadResources();

    void drawGround(GameScreen *gamescreen);\
    void drawTop(GameScreen *gamescreen);
    void drawLayer(Layer &m_layer, GameScreen *gamescreen, int tiletype=-1);

    Vector2 getMapSize();
    std::vector<Tile>* getTileVec();
    std::vector<Vector2> getBananasPos();

    bool checkObstacle(RectT<Vector2> rect_player);
};


#endif // MAP

