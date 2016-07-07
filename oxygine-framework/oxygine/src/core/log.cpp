#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>




#if defined(ANDROID)
#include <android/log.h>
#define  LOG_TAG    "SDL"
#define  LOGD(str)  __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, str)

#else
#ifdef _WIN32
#include <Windows.h>
#define LOGD(str) fputs(str, stdout); OutputDebugStringA(str);
#else
#define LOGD(str) fputs(str, stdout)
#endif
#endif



namespace oxygine
{
    bool _enabled = true;
    FILE* fh = 0;


#ifdef __S3E__
    const int SIZE = 512;
#else
#ifdef OX_DEBUG
    const int SIZE = 16384;
#else
    const int SIZE = 4096;
#endif
#endif

    namespace log
    {
        void enable()
        {
            _enabled = true;
        }

        void disable()
        {
            _enabled = false;
        }

        error_handler _eh = 0;

        void setErrorHandler(error_handler eh)
        {
            _eh = eh;
        }

        void out(const char* str)
        {
            if (!_enabled)
                return;

            //if (!fh)
            //  fh = fopen("log.txt", "w");
            //fprintf(fh, str);
            //fflush(fh);
            LOGD(str);
        }

        void out_line(char* str, int i)
        {
            out(str);
#if __ANDROID__
#else
            out("\n");
#endif
        }

        void out_line_prefix(error_handler eh, const char* pref, const char* format, va_list args)
        {
            char buff[SIZE] = {0};
            strcpy(buff, pref);

            int len = (int)strlen(buff);
            int i = vsnprintf(buff + len, sizeof(buff) - len, format, args);
            if (i == -1)
                buff[SIZE - 1] = 0;
            out_line(buff, i + len);

            if (eh)
                eh(buff);
        }

        void out_prefix(error_handler eh, const char* pref, const char* format, va_list args)
        {
            char buff[SIZE] = {0};
            strcpy(buff, pref);

            int len = (int)strlen(buff);
            int i = vsnprintf(buff + len, sizeof(buff) - len, format, args);
            if (i == -1)
                buff[SIZE - 1] = 0;
            out(buff);

            if (eh)
                eh(buff);
        }

        void message(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            message_va(format, args);
            va_end(args);
        }

        void message_va(const char* format, va_list args)
        {
            out_prefix(0, "", format, args);
        }

        void warning(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            warning_va(format, args);
            va_end(args);
        }

        void warning_va(const char* format, va_list args)
        {
            out_line_prefix(0, "warning: ", format, args);
        }

        void error(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            error_va(format, args);
            va_end(args);
        }

        void error_va(const char* format, va_list args)
        {
            out_line_prefix(_eh, "error: ", format, args);
        }

        void messageln(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            messageln_va(format, args);
            va_end(args);
        }

        void messageln_va(const char* format, va_list args)
        {
            out_line_prefix(0, "", format, args);
        }
    }
}