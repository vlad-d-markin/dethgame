#include "map.h"
#include "tile.h"
#include "dethgame.h"
#include "player.h"

#include "pugixml/pugixml.hpp"
#include "Sprite.h"
#include <stdlib.h>
#include <iostream>


// the names of object types in the "Tiled"
#define HERO        "Hero"
#define MOBS        "Mobs"
#define BOSSES      "Bosses"
#define TREASURE    "Treasure"
#define BANANAS     "Bananas"

// object names in the "Tiled"
#define MELEE_FAN   "melee_fan"
#define RANGE_FAN   "range_fan"
#define RAPPER      "rapper"
#define ARMY        "army"
#define DEVIL       "devil"
#define ZOMBIE      "zombie"
#define PIXIE       "pixie"



Map::Map()
{
    parseXML();
    loadResources();
}


void Map::loadResources()
{
    map_resources = new Resources();
    map_resources->loadXML(DethGame::instance()->getTileResPath());
}


void Map::parseXML()
{
    // upload TMX file with map specifications
    std::string path = DethGame::instance()->getMapTmxPath();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (result.status == 1) {
        std::cout << "File " << path << " was not found\n";
    }
    pugi::xml_node map = doc.child("map");

    // read map specifications
    num_tiles_in_row = atoi(map.attribute("width").value());
    num_tiles_in_col = atoi(map.attribute("height").value());
    pix_tile_width = atoi(map.attribute("tilewidth").value());
    pix_tile_height = atoi(map.attribute("tileheight").value());


    // read specifications of tilesets
    for (pugi::xml_node tiles = map.child("tileset"); tiles; tiles = tiles.next_sibling("tileset"))
    {
        Tileset ts;

        ts.first_gid = atoi(tiles.attribute("firstgid").value());
        ts.name = tiles.attribute("name").value();
        ts.pix_tile_width = atoi(tiles.attribute("tilewidth").value());
        ts.pix_tile_height = atoi(tiles.attribute("tileheight").value());
        ts.tile_count = atoi(tiles.attribute("tilecount").value());
        ts.columns_count = atoi(tiles.attribute("columns").value());
        ts.source = tiles.child("image").attribute("source").value();
        ts.pix_img_width = atoi(tiles.child("image").attribute("width").value());
        ts.pix_img_height = atoi(tiles.child("image").attribute("height").value());

        vec_tilesets.push_back(ts);
    }

    // create fiction last tileset (represents right GID border of the previous tilesets)
    {
        Tileset ts;
        Tileset last_ts = vec_tilesets.back();

        ts.first_gid = last_ts.first_gid + last_ts.tile_count;

        vec_tilesets.push_back(ts);
    }


    // read specifications of layers
    for (pugi::xml_node _layer = map.child("layer"); _layer; _layer = _layer.next_sibling("layer"))
    {
        Layer ly;

        ly.name = _layer.attribute("name").value();
        ly.num_tile_row = atoi(_layer.attribute("width").value());
        ly.num_tile_col = atoi(_layer.attribute("height").value());

        // read sequence of gid in this layer
        std::vector<int> gid;
        for (pugi::xml_node gids = _layer.child("data").child("tile"); gids; gids = gids.next_sibling("tile"))
            gid.push_back(atoi(gids.attribute("gid").value()));
        ly.gid_set = gid;

        vec_layers.push_back(ly);
    }


    // read specifications of the objects
    for (pugi::xml_node _objectgroup = map.child("objectgroup"); _objectgroup; _objectgroup = _objectgroup.next_sibling("objectgroup"))
    {

        if (_objectgroup.attribute("name").value() == std::string(HERO)) {
            pos_hero.x = atoi(_objectgroup.child("object").attribute("x").value());
            pos_hero.y = atoi(_objectgroup.child("object").attribute("y").value());
            pos_hero.name = _objectgroup.child("object").attribute("name").value();
        }

        if (_objectgroup.attribute("name").value() == std::string(MOBS)) {
            for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
            {
                Position pos_mob;

                pos_mob.x = atoi(_object.attribute("x").value());
                pos_mob.y = atoi(_object.attribute("y").value());
                pos_mob.name = _object.attribute("name").value();


                if (_object.attribute("name").value() == std::string(MELEE_FAN)) {
                    vec_pos_melee_fan.push_back(pos_mob);
                }

                if (_object.attribute("name").value() == std::string(RANGE_FAN)) {
                    vec_pos_range_fan.push_back(pos_mob);
                }

                if (_object.attribute("name").value() == std::string(RAPPER)) {
                    vec_pos_rapper.push_back(pos_mob);
                }

                if (_object.attribute("name").value() == std::string(ARMY)) {
                    vec_pos_army.push_back(pos_mob);
                }

                if (_object.attribute("name").value() == std::string(DEVIL)) {
                    vec_pos_devil.push_back(pos_mob);
                }

                if (_object.attribute("name").value() == std::string(ZOMBIE)) {
                    vec_pos_zombie.push_back(pos_mob);
                }

                if (_object.attribute("name").value() == std::string(PIXIE)) {
                    vec_pos_pixie.push_back(pos_mob);
                }

            }
        }

        if (_objectgroup.attribute("name").value() == std::string(BOSSES)) {
            for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
            {
                Position bos_pos;

                bos_pos.x = atoi(_object.attribute("x").value());
                bos_pos.y = atoi(_object.attribute("y").value());
                bos_pos.name = _object.attribute("name").value();

                vec_pos_boss.push_back(bos_pos);
            }
        }

        if (_objectgroup.attribute("name").value() == std::string(TREASURE)) {

            for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
            {
                Position tr_pos;

                tr_pos.x = atoi(_object.attribute("x").value());
                tr_pos.y = atoi(_object.attribute("y").value());
                tr_pos.name = _object.attribute("name").value();

                vec_pos_treasure.push_back(tr_pos);
            }
        }

        if (_objectgroup.attribute("name").value()==std::string(BANANAS)){
            for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
            {
                Vector2 banana_pos;

                banana_pos.x = atoi(_object.attribute("x").value());
                banana_pos.y = atoi(_object.attribute("y").value());

                vec_pos_bananas.push_back(banana_pos);
            }
        }

        // if (_objectgroup.attribute("name").value() == std::string(COLLISION))

    }
}


void Map::drawGround(GameScreen *gamescreen)
{
    drawLayer(vec_layers[BACKGROUND], gamescreen, BACKGROUND);
    drawLayer(vec_layers[BACKGROUND_OBJECTS], gamescreen);
    drawLayer(vec_layers[COLLISIONS], gamescreen, COLLISIONS);
}


void Map::drawTop(GameScreen *gamescreen)
{
    drawLayer(vec_layers[TOP_OBJECTS], gamescreen);
}


void Map::drawLayer(Layer& layer, GameScreen *gs, int tiletype)
{
    // for each GID of the layer
    for (int i_gid = 0, x = -pix_tile_width, y = 0; i_gid < layer.gid_set.size(); i_gid++)
    {
        // initial values
        Sprite *tile = new Sprite();
        tile->setResAnim(map_resources->getResAnim(vec_tilesets[0].name));      
        int columns_count, gid = layer.gid_set[i_gid];

        // set tile coordinates
        x += tile->getWidth();
        if (x >= (tile->getWidth())*(layer.num_tile_row)) {
            x = 0;
            y += tile->getHeight();
        }

        // check on an empty tile
        if(gid == 0)
            continue;

        // search of the necessary tileset
        for(int i = 0; i < (vec_tilesets.size()-1); i++) {

            if( (gid >= vec_tilesets[i].first_gid) && (gid < vec_tilesets[i+1].first_gid) ) {

                gid = gid - vec_tilesets[i].first_gid + 1;
                tile->setResAnim(map_resources->getResAnim(vec_tilesets[i].name));
                columns_count = vec_tilesets[i].columns_count;

                break;
            }
        }

        // take the necessary tile from the tileset
        if (gid % columns_count == 0)
            tile->setRow(gid / columns_count - 1);
        else
            tile->setRow(gid / columns_count);

        if ( (gid % columns_count) != 0)
            tile->setColumn( (gid % columns_count) - 1);
        else
            tile->setColumn(columns_count-1);

        // draw the tile on the stage
        tile->setPosition(x, y);
        tile->setSize(getStage()->getSize());
        tile->attachTo(gs);

        // filling the vec of collisions
        if (tiletype == BACKGROUND) {
            Tile obj_tile(tile, tiletype);
            vec_collisions.push_back(obj_tile);
        }
        if (tiletype == COLLISIONS) {
            Tile obj_tile(tile, tiletype);
            vec_collisions[i_gid] = obj_tile;
        }
    }
}


Vector2 Map::getMapSize()
{
    return Vector2(num_tiles_in_row * pix_tile_width, num_tiles_in_col * pix_tile_height);
}


bool Map::isObstacle(RectT<Vector2> rect_player)
{
    // make collision box of hero
    rect_player.setPosition(rect_player.getLeftTop()-Vector2((rect_player.getSize().x)/2, 0));
    rect_player.setSize(rect_player.getSize().x, (rect_player.getSize().y)/2);

    if(isPointCollision(rect_player.getLeftTop())==true)
        return true;
    if(isPointCollision(rect_player.getRightTop())==true)
        return true;
    if(isPointCollision(rect_player.getRightBottom())==true)
        return true;
    if(isPointCollision(rect_player.getLeftBottom())==true)
        return true;
    return false;
}


bool Map::isPointCollision(Vector2 pos)
{
    int col = pos.x / pix_tile_width+1;
    int row = pos.y / pix_tile_height+1;
    int gid = num_tiles_in_row * (row-1) + col - 1;
    if (vec_collisions[gid].getTiletype()==COLLISIONS)
        return true;
    else
        return false;
}


Position Map::getPosHero()
{
    return pos_hero;
}


std::vector<Position> Map::getPosBoss()
{
    return vec_pos_boss;
}


std::vector<Position> Map::getPosMeleeFan()
{
    return vec_pos_melee_fan;
}


std::vector<Position> Map::getPosRangeFan()
{
    return vec_pos_range_fan;
}


std::vector<Position> Map::getPosRapper()
{
    return vec_pos_rapper;
}


std::vector<Position> Map::getPosArmy()
{
    return vec_pos_army;
}


std::vector<Position> Map::getPosDevil()
{
    return vec_pos_devil;
}


std::vector<Position> Map::getPosZombie()
{
    return vec_pos_zombie;
}


std::vector<Position> Map::getPosPixie()
{
    return vec_pos_pixie;
}

std::vector<Vector2> Map::getPosBananas()
{
    return vec_pos_bananas;
}


Map::~Map()
{

}
