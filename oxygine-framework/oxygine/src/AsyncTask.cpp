#include "AsyncTask.h"
#include "core/oxygine.h"
#include <typeinfo>
namespace oxygine
{
    const int successID = sysEventID('s', 'c', 'm');
    //const int customID = sysEventID('s', 'c', 'm');
    const int runID = sysEventID('r', 'u', 'n');
    const int errorID = sysEventID('s', 'e', 'r');

    AsyncTask::AsyncTask() : _status(status_not_started), _mainThreadSync(false), _uiThreadSync(false)
    {

    }

    AsyncTask::~AsyncTask()
    {

    }

    void AsyncTask::run()
    {
        _prerun();
        log::messageln("AsyncTask::run %d - %s", getObjectID(), typeid(*this).name());

        OX_ASSERT(_status == status_not_started);
        _status = status_inprogress;
        if (!syncEvent(runID))
            _run();
    }

    void AsyncTask::threadCB(const ThreadDispatcher::message& msg)
    {
        ((AsyncTask*)msg.cbData)->_threadCB(msg);
    }

    void AsyncTask::_threadCB(const ThreadDispatcher::message& msg)
    {
        switch (msg.msgid)
        {
            case successID:
                _complete();
                break;
            case errorID:
                _error();
                break;
            case runID:
                _run();
                break;
            case customID:
                _custom(msg);
                break;
            default:
                break;
        }
        if (msg.msgid != customID)
            releaseRef();
    }

    void AsyncTask::_complete()
    {
        log::messageln("AsyncTask::_complete %d - %s", getObjectID(), typeid(*this).name());

        _status = status_completed;
        _onFinal(false);
        _finalize(false);
        _onComplete();

        AsyncTaskEvent ev(COMPLETE, this);
        dispatchEvent(&ev);
    }

    void AsyncTask::_error()
    {
        log::messageln("AsyncTask::_error %d - %s", getObjectID(), typeid(*this).name());

        _status = status_failed;
        _onFinal(true);
        _finalize(true);
        _onError();

        AsyncTaskEvent ev(ERROR, this);
        dispatchEvent(&ev);
    }

    bool AsyncTask::syncEvent(int msgid, void* arg1, void* arg2)
    {
        if (_mainThreadSync)
        {
            if (msgid != customID)
                addRef();
            core::getMainThreadDispatcher().postCallback(msgid, arg1, arg2, AsyncTask::threadCB, this);
            return true;
        }

        return false;
    }

    void AsyncTask::onComplete()
    {
        if (!syncEvent(successID, 0, 0))
            _complete();
    }

    void AsyncTask::onError()
    {
        if (!syncEvent(errorID, 0, 0))
            _error();
    }
}