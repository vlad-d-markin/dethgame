#include <string>
#include "STDFileSystem.h"
#include "file.h"
#include "log.h"
#include "utils/stringUtils.h"
#include "Object.h"

#ifdef __S3E__
#include <s3eFile.h>
#elif _WIN32
#include <direct.h>
#elif __APPLE__
#include "ios/ios.h"
#elif EMSCRIPTEN
#else
#include "SDL_system.h"
#endif


#ifdef OXYGINE_SDL
#  include "SDL_filesystem.h"
#elif _WIN32
#  include <shlwapi.h>
#  include <shlobj.h>
#endif

#include <sys/stat.h>

//#define LOGD(...) oxygine::log::messageln(__VA_ARGS__)
#define LOGD(...)


namespace oxygine
{
    namespace file
    {
        std::string _additionalFolder;

        STDFileSystem _nfs(true);
        STDFileSystem _nfsWrite(false);

        bool _fsInitialized = false;

        void init(const char* company, const char* app)
        {
            if (_fsInitialized)
                return;
            _fsInitialized = true;

#ifdef __S3E__
            _nfs.setPath("rom://");
            _nfsWrite.setPath("ram://");
#elif EMSCRIPTEN
            //mkdir("data-ram/", S_IRWXU|S_IRWXG|S_IRWXO);
            //_nfsWrite.setPath("data-ram/");

#elif __ANDROID__
            log::messageln("internal %s", SDL_AndroidGetInternalStoragePath());
            log::messageln("external %s", SDL_AndroidGetExternalStoragePath());
            _nfsWrite.setPath(SDL_AndroidGetInternalStoragePath());
#elif OXYGINE_EDITOR
#elif __APPLE__
            _nfsWrite.setPath(getSupportFolder().c_str());
#else
            if (company && app && *company && *app)
            {
                char* base_path = SDL_GetPrefPath(company, app);
                if (base_path)
                {
                    _nfsWrite.setPath(base_path);
                    SDL_free(base_path);
                }
            }
            else
            {
#   ifdef _WIN32
                _mkdir("../data-ram/");
#   else
                mkdir("../data-ram/", ACCESSPERMS);
#   endif
                _nfsWrite.setPath("../data-ram/");
            }
#endif
            _nfs.mount(&_nfsWrite);
        }

        void free()
        {
            _nfs.unmount(&_nfsWrite);
        }

        void mount(FileSystem* fs)
        {
            _nfs.mount(fs);
        }

        void unmount(FileSystem* fs)
        {
            _nfs.unmount(fs);
        }

        handle open(const char* file_, const char* mode, error_policy ep)
        {
#ifdef OX_DEBUG
            if (!strstr(mode, "b"))
                log::warning("file::open for file '%s' should be called with 'b' (means binary) flag", file_);
#endif
            //OX_ASSERT(_openedFiles == 0);
            LOGD("open file: %s %s %d", file_, mode, _openedFiles);
            char file[512];
            path::normalize(file_, file);
            LOGD("q1");


            fileHandle* fh = 0;
            _nfs.open(file, mode, ep_ignore_error, fh);

            LOGD("q3");

            if (!fh)
            {
                handleErrorPolicy(ep, "can't open file: %s", file);
            }

            return (handle)fh;
        }

        void close(handle h)
        {
            LOGD("close file %x", fh);
            fileHandle* fh = (fileHandle*)h;
            fh->release();
        }

        int seek(handle h, unsigned int offset, int whence)
        {
            fileHandle* fh = (fileHandle*)h;
            return fh->seek(offset, whence);
        }

        unsigned int tell(handle h)
        {
            fileHandle* fh = (fileHandle*)h;
            return fh->tell();
        }

        bool deleteFile(const char* path, error_policy ep)
        {
            bool ok = _nfs.deleteFile(path) == FileSystem::status_ok;
            if (!ok)
            {
                handleErrorPolicy(ep, "can't delete file: %s", path);
            }

            return ok;
        }

        bool rename(const char* src, const char* dest, error_policy ep)
        {
            bool ok = _nfs.renameFile(src, dest) == FileSystem::status_ok;
            if (!ok)
            {
                handleErrorPolicy(ep, "can't rename file: %s to %s", src, dest);
            }

            return ok;
        }

        unsigned int read(handle h, void* dest, unsigned int destSize)
        {
            fileHandle* fh = (fileHandle*)h;
            OX_ASSERT(fh && dest);
            LOGD("read file %x %d", fh, destSize);

            return fh->read(dest, destSize);
        }

        bool read(const char* file_, buffer& dest, error_policy ep)
        {
            LOGD("open file: %s %s %d", file_, mode, _openedFiles);
            char file[512];
            path::normalize(file_, file);

            dest.data.clear();
            bool ok = _nfs.read(file, dest, ep) == FileSystem::status_ok;
            if (!ok)
            {
                handleErrorPolicy(ep, "can't read file: %s to buffer", file);
            }
            return ok;
        }

        unsigned int read(handle fh_, buffer& dest)
        {
            fileHandle* fh = (fileHandle*)fh_;

            unsigned int size  = fh->getSize();
            if (!size)
                return 0;

            dest.data.resize(size);
            unsigned int t = fh->read(&dest.data[0], size);
            LOGD("read file %x %d", fh, t);
            return t;
        }

        void write(handle fh_, const void* data, unsigned int size)
        {
            fileHandle* fh = (fileHandle*)fh_;
            fh->write(data, size);
        }

        void write(const char* file, const buffer& data, error_policy ep)
        {
            write(file, data.getData(), data.getSize(), ep);
        }

        void write(const char* file, const void* data, unsigned int size, error_policy ep)
        {
            autoClose ac(open(file, "wb", ep));
            if (!ac.getHandle())
                return;
            write(ac.getHandle(), data, size);
        }

        unsigned int size(handle fh_)
        {
            fileHandle* fh = (fileHandle*)fh_;
            return fh->getSize();
        }


        bool exists(const char* file_)
        {
            char file[512];
            path::normalize(file_, file);

            return _nfs.isExists(file);
        }

        bool makeDirectory(const char* path)
        {
            return _nfs.makeDirectory(path) == FileSystem::status_ok;
        }

        void deleteDirectory(const char* path)
        {
            _nfs.deleteDirectory(path);
        }

        file::STDFileSystem& fs()
        {
            return _nfs;
        }

        file::STDFileSystem& wfs()
        {
            return _nfsWrite;
        }
    }
}
