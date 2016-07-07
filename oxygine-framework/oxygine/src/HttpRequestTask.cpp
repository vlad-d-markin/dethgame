#include "HttpRequestTask.h"
#include "core/file.h"
#include "core/oxygine.h"

namespace oxygine
{
#if OX_NO_HTTP
    spHttpRequestTask HttpRequestTask::create()
    {
        return 0;
    }
    void HttpRequestTask::init() {}
    void HttpRequestTask::release() {}
#endif
    HttpRequestTask::HttpRequestTask() : _loaded(0), _cacheEnabled(true)
    {

    }
    HttpRequestTask::~HttpRequestTask()
    {
        log::messageln("~HttpRequestTask");
    }

    void HttpRequestTask::setPostData(const std::vector<unsigned char>& data)
    {
        _postData = data;
        _setPostData(data);
    }

    void HttpRequestTask::setUrl(const std::string& url)
    {
        _url = url;
        _setUrl(url);
    }

    void HttpRequestTask::setFileName(const std::string& name)
    {
        _fname = name;
        _setFileName(name);
    }

    void HttpRequestTask::setCacheEnabled(bool enabled)
    {
        _cacheEnabled = enabled;
        _setCacheEnabled(enabled);
    }

    const std::vector<unsigned char>&   HttpRequestTask::getPostData() const
    {
        return _postData;
    }

    const std::vector<unsigned char>& HttpRequestTask::getResponse() const
    {
        return _response;
    }

    void HttpRequestTask::getResponseSwap(std::vector<unsigned char>& r)
    {
        std::swap(r, _response);
    }

    const std::string& HttpRequestTask::getFileName() const
    {
        return _fname;
    }

    void HttpRequestTask::_prerun()
    {
        _loaded = 0;
        _response.clear();
        if (!_fname.empty())
        {
            file::deleteFile(_fname.c_str(), ep_ignore_error);
        }
    }

    void HttpRequestTask::dispatchProgress(int loaded, int total)
    {
        int delta = loaded - _loaded;
        _loaded = loaded;
        ProgressEvent event(delta, loaded, total);
        dispatchEvent(&event);
    }

    void HttpRequestTask::_onCustom(const ThreadDispatcher::message& msg)
    {
        dispatchProgress((int)(size_t)msg.arg1, (int)(size_t)msg.arg2);
    }

    void HttpRequestTask::progress(int loaded, int total)
    {
        if (!syncEvent(customID, (void*)(size_t)loaded, (void*)(size_t)total))
        {
            dispatchProgress(loaded, total);
        }
    }

    void HttpRequestTask::_onError()
    {
        log::warning("http request error: %s", _url.c_str());
    }
}
