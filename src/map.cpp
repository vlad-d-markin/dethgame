#include "map.h"
#include "pugixml/pugixml.hpp"
#include <stdlib.h>
#include <iostream>
#include "Sprite.h"
#include "dethgame.h"
#include "mySprite.h"


#define COLLISION   "Collision"
#define HERO        "Hero"
#define MOBS        "Mobs"
#define BOSSES      "Bosses"
#define TREASURE    "Treasure"


#define MELEE_FAN   "melee_fan"
#define RANGE_FAN   "range_fan"
#define RAPPER      "rapper"
#define ARMY        "army"
#define DEVIL       "devil"
#define ZOMBIE      "zombie"
#define PIXIE       "pixie"



Map::Map()
{
	xmlParser("example.tmx");
	loadTiles();
}

void Map::xmlParser(std::string path)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path.c_str());
	if (result.status == 1)
	{
		std::cout << "File " << path << " was not found\n";
	}
	pugi::xml_node map = doc.child("map");

	row_map = atoi(map.attribute("width").value());
	col_map = atoi(map.attribute("height").value());

	width_tile = atoi(map.attribute("tilewidth").value());
	height_tile = atoi(map.attribute("tileheight").value());


	// tilesets
	for (pugi::xml_node tiles = map.child("tileset"); tiles; tiles = tiles.next_sibling("tileset"))
	{
		tileset ts;

		ts.firstgid = atoi(tiles.attribute("firstgid").value());
		ts.name = tiles.attribute("name").value();
		ts.tilewidth = atoi(tiles.attribute("tilewidth").value());
		ts.tileheight = atoi(tiles.attribute("tileheight").value());
		ts.tilecount = atoi(tiles.attribute("count").value());
		ts.columns = atoi(tiles.attribute("columns").value());

		ts.source = tiles.child("image").attribute("source").value();
		ts.img_width = atoi(tiles.child("image").attribute("width").value());
		ts.img_height = atoi(tiles.child("image").attribute("height").value());

		tilesets.push_back(ts);
	}


	// layers
	for (pugi::xml_node _layer = map.child("layer"); _layer; _layer = _layer.next_sibling("layer"))
	{
		layer ly;

		ly.name = _layer.attribute("name").value();
		ly.width = atoi(_layer.attribute("width").value());
		ly.height = atoi(_layer.attribute("height").value());

		std::vector<int> gd;
		for (pugi::xml_node gids = _layer.child("data").child("tile"); gids; gids = gids.next_sibling("tile"))
			gd.push_back(atoi(gids.attribute("gid").value()));
		ly.gid_set = gd;

		layers.push_back(ly);
	}


	// objects
	for (pugi::xml_node _objectgroup = map.child("objectgroup"); _objectgroup; _objectgroup = _objectgroup.next_sibling("objectgroup"))
	{

		if (_objectgroup.attribute("name").value() == std::string(COLLISION)) {
			// TODO: make collision handler
		}

		if (_objectgroup.attribute("name").value() == std::string(HERO)) {
			hero_pos.x = atoi(_objectgroup.child("object").attribute("x").value());
			hero_pos.y = atoi(_objectgroup.child("object").attribute("y").value());
			hero_pos.name = _objectgroup.child("object").attribute("name").value();
		}

		if (_objectgroup.attribute("name").value() == std::string(MOBS)) {
			for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
			{
				position mob_pos;

				mob_pos.x = atoi(_object.attribute("x").value());
				mob_pos.y = atoi(_object.attribute("y").value());
				mob_pos.name = _object.attribute("name").value();


				if (_object.attribute("name").value() == std::string(MELEE_FAN)) {
					melee_fan_pos.push_back(mob_pos);
				}

				if (_object.attribute("name").value() == std::string(RANGE_FAN)) {
					range_fan_pos.push_back(mob_pos);
				}

				if (_object.attribute("name").value() == std::string(RAPPER)) {
					rapper_pos.push_back(mob_pos);
				}

				if (_object.attribute("name").value() == std::string(ARMY)) {
					army_pos.push_back(mob_pos);
				}

				if (_object.attribute("name").value() == std::string(DEVIL)) {
					devil_pos.push_back(mob_pos);
				}

				if (_object.attribute("name").value() == std::string(ZOMBIE)) {
					zombie_pos.push_back(mob_pos);
				}

				if (_object.attribute("name").value() == std::string(PIXIE)) {
					pixie_pos.push_back(mob_pos);
				}

			}
		}

		if (_objectgroup.attribute("name").value() == std::string(BOSSES)) {
			for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
			{
				position bos_pos;

				bos_pos.x = atoi(_object.attribute("x").value());
				bos_pos.y = atoi(_object.attribute("y").value());
				bos_pos.name = _object.attribute("name").value();

				boss_pos.push_back(bos_pos);
			}
		}


		if (_objectgroup.attribute("name").value() == std::string(TREASURE)) {

			for (pugi::xml_node _object = _objectgroup.child("object"); _object; _object = _object.next_sibling("object"))
			{
				position tr_pos;

				tr_pos.x = atoi(_object.attribute("x").value());
				tr_pos.y = atoi(_object.attribute("y").value());
				tr_pos.name = _object.attribute("name").value();

				treasure_pos.push_back(tr_pos);
			}
		}

	}
}

void Map::loadTiles()
{
	m_resources = new Resources();
	m_resources->loadXML(DethGame::instance()->getTileResPath());
}

void Map::attachToMap(GameScreen *gs)
{
	drawLayer(layers[0], gs);

	spMySprite sprite = new MySprite;
	sprite->setAnchor(0.5, 0.5);
	sprite->setResAnim(gs->getResources()->getResAnim("skin"));
	sprite->attachTo(gs);
	sprite->setPosition(gs->getSize() / 2);
	sprite->setMapSize(Vector2(row_map * width_tile, col_map * height_tile));
}


void Map::drawLayer(layer& m_layer, GameScreen *gs)
{
	spSprite tile = new Sprite();
	tile->setResAnim(m_resources->getResAnim("background"));


	for (int i_row = 0, x = -(tile->getWidth()), y = 0; i_row < m_layer.gid_set.size(); i_row++) {

		spSprite tile = new Sprite();
		tile->setResAnim(m_resources->getResAnim("background"));

		int width = tile->getResAnim()->getColumns();

		tile->setRow(m_layer.gid_set[i_row] / width);
		if (m_layer.gid_set[i_row] % width == 0)
			tile->setRow(m_layer.gid_set[i_row] / width - 1);

		tile->setColumn(m_layer.gid_set[i_row] % width - 1);
		if (m_layer.gid_set[i_row] % width == 0)
			tile->setColumn(width);


		x += tile->getWidth();
		if (x >= (tile->getWidth())*(m_layer.width)) {
			x = 0;
			y += tile->getHeight();
		}


		tile->setPosition(x, y);
		tile->setSize(getStage()->getSize());
		tile->attachTo(gs);
	}
}


Map::~Map()
{

}


