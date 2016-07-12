#include "map.h"
#include "tile.h"
#include "pugixml/pugixml.hpp"
#include <stdlib.h>
#include <iostream>
#include "Sprite.h"
#include "dethgame.h"
#include "mySprite.h"


// the names of object types in the "Tiled"
#define COLLISION   "Collision"
#define HERO        "Hero"
#define MOBS        "Mobs"
#define BOSSES      "Bosses"
#define TREASURE    "Treasure"

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
    num_tiles_row = atoi(map.attribute("width").value());
    num_tiles_col = atoi(map.attribute("height").value());
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

        // if (_objectgroup.attribute("name").value() == std::string(COLLISION))

    }
}


void Map::drawMap(GameScreen *gamescreen)
{
    // TODO: draw layers

    drawLayer(vec_layers[0], gamescreen);
    drawLayer(vec_layers[1], gamescreen);
    drawLayer(vec_layers[2], gamescreen);

	spMySprite sprite = new MySprite;
	sprite->setAnchor(0.5, 0.5);
    sprite->setResAnim(gamescreen->getResources()->getResAnim("skin"));
    sprite->attachTo(gamescreen);
    sprite->setPosition(gamescreen->getSize() / 2);
    sprite->setMapSize(Vector2(num_tiles_row * pix_tile_width, num_tiles_col * pix_tile_height));
}


void Map::drawLayer(Layer& layer, GameScreen *gs)
{
    // for each GID of the layer
    for (int i_gid = 0, x = -pix_tile_width, y = 0; i_gid < layer.gid_set.size(); i_gid++)
    {
        // initial values
        spSprite tile = new Sprite();
        tile->setResAnim(map_resources->getResAnim(vec_tilesets[0].name));
        //tile->setRes
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
                //Tile t(map_resources->getResAnim(vec_tilesets[i].name));
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
	}
}


Map::~Map()
{

}


