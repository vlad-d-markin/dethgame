#pragma once
#include "test.h"

class TestTextureFormat: public Test
{
public:
    bool loaded;

    TestTextureFormat()
    {
        loaded = true;
        addButton("", "R8G8B8A8");
        addButton("_565", "R5G6B5");
        addButton("_4444", "R4G4B4A4");
        addButton("_5551", "R5G5B5A1");

        updateTest("");
    }

    void updateTest(string prefix)
    {
        content->removeChildren();

        ResAnim* res = resources.getResAnim("bg" + prefix);

        //I unloaded some resources by default to safe some memory
        //see res.xml
        //line: <set load = "false" /> <!--do not load next atlasses by default-->
        Resource* atlas = res->getAtlas();//or use resources.get("your atlas id")
        //lets load it now
        atlas->load();

        spSprite sp = new Sprite;
        sp->attachTo(content);
        sp->setResAnim(res);
    }

    void clicked(string id)
    {
        updateTest(id);
    }

};
