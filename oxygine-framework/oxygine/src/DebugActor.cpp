#include <sstream>
#include "core/oxygine.h"

#include "res/ResAnim.h"
#include "res/ResFont.h"
#include "res/Resources.h"

#include "utils/stringUtils.h"
#include "core/NativeTexture.h"
#include "core/ZipFileSystem.h"
#include "core/system_data.h"
#include "STDRenderer.h"

#include "dev_tools/DeveloperMenu.h"
#include "dev_tools/TreeInspector.h"
#include "dev_tools/TexturesInspector.h"

#include "STDRenderer.h"
#include "DebugActor.h"
#include "Stage.h"
#include "TextField.h"
#include "ColorRectSprite.h"
#include "Button.h"
#include "Event.h"
#include "RenderState.h"
#include "initActor.h"
#include "MaskedSprite.h"
#include "STDMaterial.h"

#include <stdio.h>
#include <stdarg.h>
#include <iomanip>

#ifdef __S3E__
#include "s3eMemory.h"
#elif __APPLE__
#include "core/ios/ios.h"
#endif

namespace oxygine
{
    Resources* DebugActor::resSystem = 0;
    file::ZipFileSystem zp;

    spDebugActor DebugActor::instance;

    void DebugActor::initialize()
    {
        if (resSystem)
            return;

        log::messageln("DebugActor::initialize");

        zp.setPrefix("system/");
        zp.add(system_data, system_size);

        //file::ZipFileSystem zp;
        file::mount(&zp);
        resSystem = new Resources;
        resSystem->loadXML("system/res.xml", ResourcesLoadOptions().prebuiltFolder("system"));
    }

    void DebugActor::show()
    {
        initialize();

        if (!DebugActor::instance)
            DebugActor::instance = new DebugActor;

        getStage()->addChild(DebugActor::instance);
    }

    void DebugActor::hide()
    {
        if (DebugActor::instance)
            DebugActor::instance->detach();
    }

    void DebugActor::setCorner(int corner)
    {
        if (DebugActor::instance)
            DebugActor::instance->setCornerPosition(corner);
    }

    void DebugActor::release()
    {
        instance = 0;
        delete resSystem;
        resSystem = 0;
        file::unmount(&zp);
        zp.reset();
    }

    void DebugActor::setCornerPosition(int corner)
    {
        _corner = corner;
    }

    void DebugActor::addButton(float& x, const char* name, const char* anim)
    {
        spButton btn;
        btn = initActor(new Button,
                        arg_resAnim = resSystem->getResAnim(anim),
                        arg_y = 1,
                        arg_name = name,
                        arg_attachTo = this);
        x = x - btn->getWidth();
        btn->setX(x);
        btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DebugActor::_btnClicked));
    }

    DebugActor::DebugActor(): _frames(0), _startTime(0), _corner(0), _showTexel2PixelErrors(false), _showTouchedActor(false)
    {
        DebugActor::initialize();

        setName(getDefaultName());

        _startTime = getTimeMS();
        setPriority(30000);

        setTouchEnabled(false);

        TextStyle st;
        st.font = NULL;

        if (ResFont* fnt = resSystem->getResFont("mono"))
        {
            st.font = fnt->getFont();
        }

        OX_ASSERT(st.font != NULL);

        st.vAlign = TextStyle::VALIGN_TOP;
        st.hAlign = TextStyle::HALIGN_LEFT;
        //st.color = Color(rand()%255, rand()%255, rand()%255, 255);
        st.color = Color(Color::Black, 255);
        st.multiline = true;
        setWidth(230);
        setHeight(45);

        _bg = new ColorRectSprite;
        _bg->setColor(Color(Color::White, 180));
        _bg->setSize(getSize());
        _bg->setTouchEnabled(false);
        addChild(_bg);


        float x = getWidth();
        addButton(x, "tree", "tree");
        addButton(x, "finger", "finger");
#ifdef OXYGINE_DEBUG_T2P
        addButton(x, "t2p", "t2p");
#endif

#ifdef OXYGINE_DEBUG_TRACE_LEAKS

        addButton(x, "images", "images");
#endif



        _text = new TextField;
        addChild(_text);
        _text->setPosition(2, 7);
        _text->setTouchEnabled(false);
        _text->setStyle(st);
        _text->setWidth(getWidth());
        _text->setText("debug text");


        instance = this;
    }

    void DebugActor::onAdded2Stage()
    {
        _stage->addEventListener(TouchEvent::MOVE, CLOSURE(this, &DebugActor::onDAEvent));
    }

    void DebugActor::onRemovedFromStage()
    {
        _stage->removeEventListeners(this);
    }

    /*
    void DebugActor::addDebugString(const string &str)
    {
        _debugText += str;
    }
    */

    void DebugActor::addDebugString(const char* format, ...)
    {
        char buff[1024] = "";
        va_list args;
        va_start(args, format);
        int len = (int)strlen(buff);
        vsnprintf(buff + len, sizeof(buff) - len, format, args);
        va_end(args);

        if (DebugActor::instance)
        {
            DebugActor::instance->_debugText += buff;
            DebugActor::instance->_debugText += "\n";
        }
    }

    void DebugActor::_btnClicked(Event* ev)
    {
        std::string name = ev->currentTarget->getName();
        if (name == "finger")
        {
            showTouchedActor(!_showTouchedActor);
            return;
        }

        if (name == "t2p")
        {
            showTexel2PixelErrors(!_showTexel2PixelErrors);
            return;
        }

        spActor inspector = _getStage()->getChild(DeveloperMenu::getDefaultName(), ep_ignore_error);
        if (inspector)
            inspector->detach();
        else
        {
            spDeveloperMenu dm = new DeveloperMenu();
            dm->setPriority(getPriority()  + 1);
            float scale = _getStage()->getScaleX();
            Vector2 size = core::getDisplaySize();

            Vector2 s = size;// * scale;
            s.y -= 24;

            if (name == "tree")
            {
                spTreeInspector tree = new TreeInspector;
                tree->init(s, _getStage());

                dm->init(s, "Tree Inspector", tree, Color(230, 230, 230, 255));
            }

            if (name == "images")
            {
                spTexturesInspector tree = new TexturesInspector(s);
                dm->init(s, "Textures Inspector", tree, Color(60, 60, 60, 255));
            }

            dm->setScale(1.0f / scale);
            Vector2 p = -_getStage()->getPosition() / scale;
            dm->setPosition(p);
            _getStage()->addChild(dm);
        }
    }

    DebugActor::~DebugActor()
    {
    }

    extern IVideoDriver::Stats _videoStats;

    std::string aligned(int v, int width)
    {
        char str[32];
        str[0] = '%';
        str[1] = width + 48;
        str[2] = 'd';
        str[3] = 0;
        char rs[32];
        safe_sprintf(rs, str, v);

        return rs;
    }

    void DebugActor::doUpdate(const UpdateState& us)
    {
        static int fps = 0;
        ++_frames;
        if (_frames > 50)
        {
            timeMS this_time = getTimeMS();
            if (this_time != _startTime)
            {
                fps = int(((float)_frames / (this_time - _startTime)) * 1000);
            }
            _startTime = this_time;
            _frames = 0;
        }

        std::stringstream s;
        s << "fps=" << fps << std::endl;



#ifdef __S3E__
        int mem_used = -1;
        int mem_free = -1;

        mem_used = s3eMemoryGetInt(S3E_MEMORY_USED);
        mem_free = s3eMemoryGetInt(S3E_MEMORY_FREE);

        s << "mfree=" << mem_free << " mem=" << mem_used << std::endl;
#endif



#ifdef OXYGINE_DEBUG_TRACE_LEAKS
        s << "objects=" << (int)ObjectBase::__getCreatedObjects().size() << std::endl;
#endif
#ifdef OXYGINE_TRACE_VIDEO_STATS
        s << "batches=" << aligned(_videoStats.batches, 3) << " triangles=" << aligned(_videoStats.triangles, 3) << std::endl;
#endif

        s << "update=" << aligned(getStage()->_statUpdate, 2) << "ms ";
        s << "render=" << aligned(getStage()->_statRender, 2) << "ms ";
        s << "textures=" << aligned(NativeTexture::created, 2) << " ";

#ifdef __APPLE__
        size_t mem;
        iosGetMemoryUsage(mem);
        s << "memory=" << mem / 1024 << "kb ";
#endif
        //s << "\nlisteners=" << getStage()->getListenersCount() << "";

        if (!_debugText.empty())
        {
            s << "\n";
            s << _debugText;
        }
        _debugText = "";

        _text->setText(s.str());


        setHeight(_text->getTextRect().size.y + _text->getY() + 3);
        _bg->setSize(getSize());


        Vector2 ds = core::getDisplaySize();

        Vector2 pos(0, 0);

        switch (_corner)
        {
            case 1:
                pos.x = ds.x;
                break;
            case 2:
                pos = ds;
                break;
            case 3:
                pos.y = ds.y;
                break;
        }

        pos = getStage()->global2local(pos);

        Vector2 realSize = getScaledSize();
        switch (_corner)
        {
            case 1:
                pos.x -= realSize.x;
                break;
            case 2:
                pos -= realSize;
                break;
            case 3:
                pos.y -= realSize.y;
                break;
        }

        setPosition(pos);
        setScale(1.0f / getStage()->getScaleX());
    }

    void DebugActor::render(RenderState const& parentRS)
    {
        RenderState rs = parentRS;
        parentRS.material->finish();

        STDRenderer renderer;
        STDMaterial mat(&renderer);
        mat.apply(0);
        //STDRenderer* renderer = mat.getRenderer();
        IVideoDriver* driver = renderer.getDriver();
        driver->setDebugStats(false);

        Rect vp(Point(0, 0), core::getDisplaySize());
        driver->setViewport(vp);
        renderer.initCoordinateSystem(vp.getWidth(), vp.getHeight());
        renderer.resetSettings();
        rs.material = &mat;
        Actor::render(rs);
        renderer.drawBatch();
        driver->setDebugStats(true);
        mat.finish();

        Material::setCurrent(0);
    }

    void DebugActor::showTexel2PixelErrors(bool show)
    {
        _showTexel2PixelErrors = show;
#ifdef OXYGINE_DEBUG_T2P
        STDRenderer::showTexel2PixelErrors(_showTexel2PixelErrors);
        spActor btn = getChild("t2p");
        btn->removeTweens(true);
        if (show)
            btn->addTween(Actor::TweenAlpha(0), 300, 999999, true);
#endif
    }

    void DebugActor::showTouchedActor(bool show)
    {
        _getStage()->removeEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &DebugActor::onEvent));
        _showTouchedActor = show;
        if (show)
            _getStage()->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &DebugActor::onEvent));

        spActor btn = getChild("finger");
        btn->removeTweens(true);
        if (show)
            btn->addTween(Actor::TweenAlpha(0), 300, 999999, true);
    }

    void DebugActor::onDAEvent(Event* ev)
    {
        TouchEvent* t = safeCast<TouchEvent*>(ev);
        Vector2 loc = stage2local(t->localPosition, _getStage());
        setAlpha(isOn(loc) ? 64 : 255);
    }

    void DebugActor::onEvent(Event* ev)
    {
        TouchEvent* te = safeCast<TouchEvent*>(ev);
        spActor actor = safeSpCast<Actor>(ev->target);
        spColorRectSprite cr = new ColorRectSprite;
        cr->setTouchEnabled(false);
        cr->setColor(Color(rand() % 255, rand() % 255, rand() % 255, 0));
        cr->setSize(actor->getSize());
        cr->addTween(ColorRectSprite::TweenColor(Color(Color::White, 200)), 700, 1, true, 0, Tween::ease_inCubic)->setDetachActor(true);
        actor->addChild(cr);
        std::string dmp = actor->dump(0);
        log::messageln("touched actor '%s' local pos: (%.0f,%.0f), pos: (%.0f,%.0f)\n%s",
                       actor->getName().c_str(),
                       te->localPosition.x, te->localPosition.y,
                       te->position.x, te->position.y,
                       dmp.c_str());

        actor = actor->getParent();
        while (actor)
        {
            log::messageln("parent: %s", actor->getName().c_str());
            actor = actor->getParent();
        }
    }
}