#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <cstdarg>
#include <ostream>

namespace Silexars {
    namespace Data {
        class String {
            public:
                String();
                String(uint32 size);
                String(const String &str);
                String(const char *s);
                String(const char *s, size_t n);
                String(const void *s, size_t n);
                String(size_t n, char c);
                String(const std::string &s);
                ~String();

                uint32 length() const;

                uint32 indexOf(uint32 i0, const char c) const;
                uint32 indexOf(uint32 i0, const char *str) const;
                uint32 indexOf(uint32 i0, const char *str, size_t n) const;
                uint32 indexOf(uint32 i0, const std::string &str) const;
                uint32 indexOf(uint32 i0, const String &str) const;
                template <class T> uint32 indexOf(T t) const { return indexOf(0, t); }

                uint32 lastIndexOf(const char c) const;
                uint32 lastIndexOf(const char *str) const;
                uint32 lastIndexOf(const std::string &str) const;
                uint32 lastIndexOf(const String &str) const;

                uint32 nextWord(uint32 i0 = 0, uint32 *len = 0) const;

                int32 toInt32(uint32 offset = 0) const;
                int64 toInt64(uint32 offset = 0) const;
                float32 toFloat32(uint32 offset = 0) const;

                void resize(uint32 size);

                String& format(const char *format, ...);
                String& format(const char *format, va_list args);
                String& format(const String& format, ...);
                String& format(const String& format, va_list args);

                void copy(const void *data, size_t length);

                void operator=(const String &str);
                void operator=(const std::string &s);
                void operator=(const char *s);
                void operator=(const char c);

                char& operator[](uint32 i);
                const char operator[](uint32 i) const;

                int8 strncmp(const String& s, uint32 n) const;
                int8 strcmp(const String& s) const;

                String substr(size_t pos = 0, size_t len = npos) const;
                void replace(uint32 i, uint32 len, const String& s);
                void replace(char c0, char c1);
                void replace(char  c, const char *s);
                void replace(const char *s, char  c);
                void replace(const char *s0, const char *s1);
                void replace(const String &s0, const char *s1);
                void replace(const String &s0, const String &s1);

                void insert(uint32 i, const String& s);

                void erase(uint32 i, uint32 amount);

                String toLowerCase() const;
                String toUpperCase() const;

                char *c_str();
                const char *c_str() const;

                void operator+=(const String &str);
                void operator+=(const std::string &str);
                void operator+=(const char *str);
                void operator+=(char c);

                bool operator<(const String &str) const;
                bool operator>(const String &str) const;

                static uint32 getCharCodeFromUTF8(const char *s);

                static const uint32 npos;
            private:
                uint32 l;
                char *s;
        };
    }
}



bool operator==(const Silexars::Data::String&        lhs, const Silexars::Data::String&  rhs);
bool operator==(const std::string&                   lhs, const Silexars::Data::String&  rhs);
bool operator==(const Silexars::Data::String&        lhs, const std::string&             rhs);
bool operator==(const char*                          lhs, const Silexars::Data::String&  rhs);
bool operator==(const Silexars::Data::String&        lhs, const char*                    rhs);

bool operator!=(const Silexars::Data::String&        lhs, const Silexars::Data::String&  rhs);
bool operator!=(const std::string&                   lhs, const Silexars::Data::String&  rhs);
bool operator!=(const Silexars::Data::String&        lhs, const std::string&             rhs);
bool operator!=(const char*                          lhs, const Silexars::Data::String&  rhs);
bool operator!=(const Silexars::Data::String&        lhs, const char*                    rhs);

Silexars::Data::String operator+(const Silexars::Data::String &lhs, const Silexars::Data::String &rhs);
Silexars::Data::String operator+(const Silexars::Data::String &lhs, std::string                  &rhs);
Silexars::Data::String operator+(std::string &lhs                 , const Silexars::Data::String &rhs);
Silexars::Data::String operator+(const Silexars::Data::String &lhs, const char                   *rhs);
Silexars::Data::String operator+(const char *lhs                  , const Silexars::Data::String &rhs);

std::ostream& operator<<(std::ostream &os, const Silexars::Data::String &str);
