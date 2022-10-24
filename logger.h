#pragma once
/* date = June 23rd 2022 11:37 am */

/*
Heavy Mod of Pilzschaf's (https://www.github.com/Pilzschaf) simple_logger.
Major changes:
 - support for console attributes
- new log levels: debug, critical
*/

/*#ifndef LOGGER_H
#define LOGGER_H*/

#include <iostream>
#include <string>
//#include <windows.h>
#ifndef LHG_LINUX
#include <wincon.h>
#endif // LHG_LINUX
#include <sstream>

#define LOG_INFO(...) lhg::log_info(__FILE__, __LINE__, false, __VA_ARGS__)
#define LOG_INFO_IV(...) lhg::log_info(__FILE__, __LINE__, true, __VA_ARGS__) // IV stands for Ignore Verbose
#define LOG_DEBUG(...) lhg::log_debug(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) lhg::log_warning(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) lhg::log_error(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_CRIT(...) lhg::log_critical(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_EMPTY() lhg::log_empty()

#define LOG_INIT(...) LOG_INFO(__VA_ARGS__, " initializing...")
#define LOG_INIT_OK(...) LOG_INFO(__VA_ARGS__, " initializing... OK")
#define LOG_INIT_AB(...) LOG_WARN(__VA_ARGS__, " initializing... ABORTED")

#define LOG_DEST(...) LOG_INFO("destroying ", __VA_ARGS__, "... ")
#define LOG_DEST_OK(...) LOG_INFO("destroying ", __VA_ARGS__, "... OK")
#define LOG_DEST_AB(...) LOG_WARN("destroying ", __VA_ARGS__, "... ABORTED")

#define LOG_DEIN(...) LOG_INFO("deinitializing ", __VA_ARGS__, "... ")
#define LOG_DEIN_OK(...) LOG_INFO("deinitializing ", __VA_ARGS__, "... OK")
#define LOG_DEIN_AB(...) LOG_WARN("deinitializing ", __VA_ARGS__, "... ABORTED")

#define LOG_QUER(...) LOG_INFO("querying ", __VA_ARGS__, "... ")
#define LOG_QUER_OK(...) LOG_INFO("querying ", __VA_ARGS__, "... OK")
#define LOG_QUER_AB(...) LOG_WARN("querying ", __VA_ARGS__, "... ABORTED")

namespace lhg
{
    struct Col
    {
        public:
        const char* att;
        const int col;
        
        Col(const char* att, const int col)
            : col(col), att(att){};
    };
    
    enum WinConCol : int32_t
    {
        FOREGROUND_BLUE = 0x0001,
        FOREGROUND_GREEN = 0x0002,
        FOREGROUND_RED = 0x0004,
        FOREGROUND_INTENSITY = 0x0008,
        BACKGROUND_BLUE = 0x0010,
        BACKGROUND_GREEN = 0x0020,
        BACKGROUND_RED = 0x00040,
        BACKGROUND_INTENSITY = 0x00080,
    };

    static Col normal_col = Col("\033[3;00;37m", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    static Col info_col = Col("\033[3;00;37m", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    static Col debug_col = Col("\033[3;00;96m", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    static Col warning_col = Col("\033[3;00;33m", FOREGROUND_RED | FOREGROUND_INTENSITY);
    static Col error_col = Col("\033[1;00;31m", FOREGROUND_RED);
    static Col critical_col = Col("\033[1;101;37m", /*FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | /*FOREGROUND_INTENSITY |*/ BACKGROUND_RED /*| BACKGROUND_INTENSITY*/);
    
    static bool verbose =
#ifdef LHG_VERBOSE
        true
#else
        false
#endif // LHG_VERBOSE
        ;
    
#ifndef LHG_LINUX
    static bool use_attributes = false;
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#else
    static const bool use_attributes = true;
#endif
    
    static void variadic_unpack(std::string& buf) {}
    
    template<typename T, typename... Args>
        static void variadic_unpack(std::string& buf, const T arg, const Args... args)
    {
        std::ostringstream oss;
        oss << arg;
        buf.append(oss.str());
        
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, void* arg, const Args... args)
    {
        std::ostringstream oss;
        oss << arg;
        buf.append(oss.str());
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, char* arg, const Args... args)
    {
        buf.append(arg);
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, const char* arg, const Args... args)
    {
        buf.append(arg);
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, int arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, unsigned arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, long arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, unsigned long arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, long long arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, unsigned long long arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, float arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, double arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    template<typename... Args>
        static void variadic_unpack(std::string& buf, long double arg, const Args... args)
    {
        buf.append(std::to_string(arg));
        variadic_unpack(buf, args...);
    }
    
    
    static void log_line(const char* file, const size_t line, const char* msg, const char* col_att, const char* norm_att)
    {
        std::cout << col_att;
        #ifndef LHG_HIDE_PATH
        std::cout << '[' << file << ':' << line << "]: ";
        #endif // LHG_HIDE_PATH
        std::cout << msg << norm_att << std::endl;
    }
    
    static void log(const char* file, const size_t line, const char* msg, const Col col)
    {
        char* col_att = (char*) col.att;
        char* norm_att = (char*) normal_col.att;
        if (!use_attributes)
        {
            col_att = (char*) "";
            norm_att = (char*) "";
#ifndef LHG_LINUX
            SetConsoleTextAttribute(hConsole, col.col);
#endif // LHG_LINUX
            log_line(file, line, msg, col_att, norm_att);
#ifndef LHG_LINUX
            SetConsoleTextAttribute(hConsole, normal_col.col);
#endif // LHG_LINUX
            return;
        }
        log_line(file, line, msg, col_att, norm_att);
    }
    
    static void log_empty()
    {
        std::cout<<std::endl;
    }
    
    template<typename... Args>
        static void log_info(const char* file, const size_t line, bool ignoreVerbosity, const Args &... msg)
    {
        if (!(verbose || ignoreVerbosity)) return;
        std::string buf;
        #ifdef LHG_PRINT_LVL
        buf = "(INFO)  ";
        #endif // LHG_PRINT_LVL
        variadic_unpack(buf, msg...);
        log(file, line, buf.c_str(), info_col);
    }
    
    template<typename... Args>
        static void log_debug(const char* file, const size_t line, const Args &... msg)
    {
        std::string buf;
        #ifdef LHG_PRINT_LVL
        buf = "(DEBUG) ";
        #endif // LHG_PRINT_LVL
        variadic_unpack(buf, msg...);
        log(file, line, buf.c_str(), debug_col);
    }
    
    template<typename... Args>
        static void log_warning(const char* file, const size_t line, const Args &... msg)
    {
        std::string buf;
        #ifdef LHG_PRINT_LVL
        buf = "(WARN)  ";
        #endif // LHG_PRINT_LVL
        variadic_unpack(buf, msg...);
        log(file, line, buf.c_str(), warning_col);
    }
    
    template<typename... Args>
        static void log_error(const char* file, const size_t line, const Args &... msg)
    {
        std::string buf;
        #ifdef LHG_PRINT_LVL
        buf = "(ERROR) ";
        #endif // LHG_PRINT_LVL
        variadic_unpack(buf, msg...);
        log(file, line, buf.c_str(), error_col);
    }
    
    template<typename... Args>
        static void log_critical(const char* file, const size_t line, const Args &... msg)
    {
        std::string buf;
        #ifdef LHG_PRINT_LVL
        buf = "(!CRIT) ";
        #endif // LHG_PRINT_LVL
        variadic_unpack(buf, msg...);
        log(file, line, buf.c_str(), critical_col);
    }
}

//#endif //LOGGER_H
