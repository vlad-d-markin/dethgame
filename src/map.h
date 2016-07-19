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
    int first_gid;//id of 1st grid
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
    std::vector<Tile> vec_collisions;
    std::vector<std::vector<bool>> vecCollisionsBool;

    // map specifications
    int num_tiles_in_row;
    int num_tiles_in_col;
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

    std::vector<Vector2> vec_pos_bananas;
public:
    Map();
    ~Map();

    void parseXML();
    void loadResources();

    void drawGround(GameScreen *gamescreen);\
    void drawTop(GameScreen *gamescreen);
    void drawLayer(Layer &m_layer, GameScreen *gamescreen, int tiletype=-1);

    void setVecBoolCollisions();

    Vector2 getMapSize() const;
    bool isObstacle(RectT<Vector2> rect_player);
    bool isPointCollision(Vector2 pos);
    std::vector< std::vector<bool> > getVecBoolCollisions() const;

    Position getPosHero();
    std::vector<Position> getPosBoss();
    std::vector<Position> getPosMeleeFan();
    std::vector<Position> getPosRangeFan();
    std::vector<Position> getPosRapper();
    std::vector<Position> getPosArmy();
    std::vector<Position> getPosDevil();
    std::vector<Position> getPosZombie();
    std::vector<Position> getPosPixie();
    std::vector<Tile>* getTileVec();
    std::vector<Vector2> getPosBananas();

};


#endif // MAP

