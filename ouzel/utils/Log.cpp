// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#if defined(__APPLE__)
#  include <TargetConditionals.h>
#endif

#if defined(__ANDROID__)
#  include <android/log.h>
#elif TARGET_OS_IOS || TARGET_OS_TV
#  include <sys/syslog.h>
#elif TARGET_OS_MAC || defined(__linux__)
#  include <unistd.h>
#elif defined(_WIN32)
#  pragma push_macro("WIN32_LEAN_AND_MEAN")
#  pragma push_macro("NOMINMAX")
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  include <Windows.h>
#  pragma pop_macro("WIN32_LEAN_AND_MEAN")
#  pragma pop_macro("NOMINMAX")
#  include <strsafe.h>
#elif defined(__EMSCRIPTEN__)
#  include <emscripten.h>
#endif

#include "Log.hpp"

namespace ouzel
{
    Log::~Log()
    {
        if (!s.empty())
            logger.log(s, level);
    }

    void Logger::logString(const std::string& str, Log::Level level)
    {
#if defined(__ANDROID__)
        int priority = 0;
        switch (level)
        {
            case Log::Level::Error: priority = ANDROID_LOG_ERROR; break;
            case Log::Level::Warning: priority = ANDROID_LOG_WARN; break;
            case Log::Level::Info: priority = ANDROID_LOG_INFO; break;
            case Log::Level::All: priority = ANDROID_LOG_DEBUG; break;
            default: return;
        }
        __android_log_print(priority, "Ouzel", "%s", str.c_str());
#elif TARGET_OS_IOS || TARGET_OS_TV
        int priority = 0;
        switch (level)
        {
            case Log::Level::Error: priority = LOG_ERR; break;
            case Log::Level::Warning: priority = LOG_WARNING; break;
            case Log::Level::Info: priority = LOG_INFO; break;
            case Log::Level::All: priority = LOG_DEBUG; break;
            default: return;
        }
        syslog(priority, "%s", str.c_str());
#elif TARGET_OS_MAC || defined(__linux__)
        int fd = 0;
        switch (level)
        {
            case Log::Level::Error:
            case Log::Level::Warning:
                fd = STDERR_FILENO;
                break;
            case Log::Level::Info:
            case Log::Level::All:
                fd = STDOUT_FILENO;
                break;
            default: return;
        }

        std::vector<char> output(str.begin(), str.end());
        output.push_back('\n');

        size_t offset = 0;
        while (offset < output.size())
        {
            ssize_t written = write(fd, output.data() + offset, output.size() - offset);
            if (written == -1)
                return;

            offset += static_cast<size_t>(written);
        }
#elif defined(_WIN32)
        const int bufferSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        if (bufferSize == 0)
            return;

        std::vector<WCHAR> buffer(bufferSize + 1); // +1 for the newline
        if (MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer.data(), static_cast<int>(buffer.size())) == 0)
            return;

        if (FAILED(StringCchCatW(buffer.data(), buffer.size(), L"\n")))
            return;

        OutputDebugStringW(buffer.data());
#  if DEBUG
        HANDLE handle;
        switch (level)
        {
            case Log::Level::Error:
            case Log::Level::Warning:
                handle = GetStdHandle(STD_ERROR_HANDLE);
                break;
            case Log::Level::Info:
            case Log::Level::All:
                handle = GetStdHandle(STD_OUTPUT_HANDLE);
                break;
            default: return;
        }

        DWORD bytesWritten;
        WriteConsoleW(handle, buffer.data(), static_cast<DWORD>(wcslen(buffer.data())), &bytesWritten, nullptr);
#  endif
#elif defined(__EMSCRIPTEN__)
        int flags = EM_LOG_CONSOLE;
        switch (level)
        {
            case Log::Level::Error:
                flags |= EM_LOG_ERROR;
                break;
            case Log::Level::Warning:
                flags |= EM_LOG_WARN;
                break;
            case Log::Level::Info:
            case Log::Level::All:
                break;
            default: return;
        }
        emscripten_log(flags, "%s", str.c_str());
#endif
    }
}
