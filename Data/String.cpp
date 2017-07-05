#include "String.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace Silexars::Data;

const uint32 String::npos = static_cast<uint32>(-1);

String::~String() { free(s); }

String::String() {
    l = 0;
    s = (char*) malloc(1);
    s[0] = 0;
}

String::String(uint32 size) {
    l = size;
    s = (char*) malloc(l+1);
    s[size] = 0;
}

String::String(const String &str) {
    l = 0;
    s = (char*) malloc(0);
    s[0] = 0;
    operator=(str);
}

String::String(const char *str) {
    if (str) {
        s = 0;
        copy(str, strlen(str));
    } else {
        l = 0;
        s = (char*) malloc(1);
        s[0] = 0;
    }
}
String::String(const char *str, size_t n) {
    s = 0;
    uint32 strl = strlen(str);
    if (strl < n) n = strl;
    copy(str,n);
}

String::String(const void *data, size_t n) {
    s = 0;
    copy(data,n);
}

String::String(const std::string &str) {
    s = 0;
    copy(str.c_str(),str.length());
}

String& String::format(const char *str, ...) {
    va_list args;
    va_start(args, str);
    format(str, args);
    va_end(args);
    return *this;
}

String& String::format(const char *str, va_list args) {
    va_list cargs;
    va_copy(cargs, args);
    int32 size = vsnprintf(0, 0, str, cargs);
    va_end(cargs);

    if (size < 0) resize(0);
    else {
        resize(size);
        vsprintf(s, str, args);
    }
    return *this;
}

void String::resize(uint32 size) {
    l = size;
    s = (char*) realloc(s,l+1);
    s[l] = 0;
}

void String::copy(const void *data, size_t n) {
    resize(n);
    memcpy(s, data, n);
}

uint32 String::lastIndexOf(const char c) const {
    for (uint32 i = l-1; i; --i)
        if (s[i] == c) return i;
    if (s[0] == c) return 0;
    else return npos;
}

#warning uint32 String::lastIndexOf(const String& str) const;

uint32 String::indexOf(uint32 i0, const char c) const {
    for (uint32 i = i0; i < l; ++i)
        if (s[i] == c) return i;
    return npos;
}

uint32 String::indexOf(uint32 i0, const char *ns) const {
    int32 lns = strlen(ns);
    for (uint32 i = i0; i < l; ++i)
        if (!::strncmp(s+i,ns,lns)) return i;
    return npos;
}

uint32 String::indexOf(uint32 i0, const char *ns, size_t n) const {
    for (uint32 i = i0; i < l; ++i)
        if (!::strncmp(s+i,ns,n)) return i;
    return npos;
}

uint32 String::indexOf(uint32 i0, const String& input) const {
    const char *ns = input.c_str();
    int32 lns = input.length();
    for (uint32 i = i0; i < l; ++i)
        if (!::strncmp(s+i,ns,lns)) return i;
    return npos;
}

uint32 String::nextWord(uint32 i0, uint32 *len) const {
    for (uint32 i = i0; i < l; ++i) {
        if (!isspace(s[i])) {
            if (len) {
                uint32 j;
                for (j = i; j < l; ++j)
                    if (isspace(s[j])) break;
                *len = j - i;
            }
            return i;
        }
    }
    return npos;
}

uint32 String::length() const { return l; }

String String::toLowerCase() const {
    String str = *this;
    for (uint32 i = 0; i < l; i++) str.s[i] = tolower(s[i]);
    return str;
}

String String::toUpperCase() const {
    String str = *this;
    for (uint32 i = 0; i < l; i++) str.s[i] = toupper(s[i]);
    return str;
}

String String::substr(size_t pos, size_t len) const {
    if (pos > l) pos = l;
    uint32 copySize = l - pos;
    return String(&s[pos],len < copySize ? len : copySize);
}

void String::replace(char oldc, char newc) {
    for (uint32 i=0; i < l; ++i)
        if (s[i] == oldc) s[i] = newc;
}

void String::replace(char c, const char *ns) {
    String news;
    for (uint32 i=0; i < l; i++)
        if (s[i] == c) news += ns;
        else news += s[i];
    *this = news;
}

void String::replace(const char *s0, const char *s1) {
    uint32 i0 = 0;
    uint32 i1 = indexOf(i0, s0);

    if (i1 != npos) {
        uint32 s0l = strlen(s0);
        uint32 s1l = strlen(s1);

        String news;

        do {
            news += substr(i0, i1 - i0);
            news += s1;
            i0 = i1 + s0l;
            i1 = indexOf(i0, s0);
        } while (i1 != npos);
        news += substr(i0);

        *this = news;
    }
}

void String::replace(uint32 i0, uint32 size0, const String &sin) {
    int32 dsize = sin.length() - size0;

    if (dsize > 0) {
        resize(length() + dsize);
        for (uint32 i = length() - 1; i >= i0 + sin.length(); i--)
            s[i] = s[i - dsize];
    }

    if (dsize < 0) {
        for (uint32 i = i0 + size0; i < length(); i++)
            s[i + dsize] = s[i];
        resize(length() + dsize);
    }

    for (uint32 i = 0; i < sin.length(); i++)
        s[i0 + i] = sin.c_str()[i];
}

void String::replace(const String &s0, const char *s1) { replace(s0.c_str(), s1); }
void String::replace(const String &s0, const String &s1) { replace(s0.c_str(), s1.c_str()); }

void String::insert(uint32 i, const String &s) { replace(i, 0, s); }

void String::erase(uint32 offset, uint32 amount) {
    for (uint32 i = offset; i < l; i++)
        s[i] = s[i+amount];
    l -= amount;
    s[l] = 0;
}

char *String::c_str() { return s; }
const char *String::c_str() const { return s; }

char &String::operator[](uint32 i) { return s[i]; }
const char String::operator[](uint32 i) const { return s[i]; }

void String::operator=(const String &str) {
    if (c_str() != str.c_str()) copy((void*) str.c_str(), str.length());
}
void String::operator=(const std::string &s) { copy((void*)s.c_str(),s.length()); }
void String::operator=(const char *str) { copy(str,strlen(str)); }
void String::operator=(const char c) { copy(&c,1); }

bool String::operator>(const String &str) const { return strcmp(str) > 0; }
bool String::operator<(const String &str) const { return strcmp(str) < 0; }

void String::operator+=(char c) {
    ++l;
    s = (char*) realloc(s,l+1);
    s[l-1] = c;
    s[l] = 0;
}

void String::operator+=(const char *str) {
    uint32 strl = strlen(str);
    s = (char*) realloc(s,l+strl+1);
    strcpy(&s[l],str);
    l += strl;
}

int32 String::toInt32(uint32 offset) const { return atoi(s+offset); }
int64 String::toInt64(uint32 offset) const { return atol(s+offset); }
float32 String::toFloat32(uint32 offset) const { return atof(s+offset); }

int8 String::strncmp(const String& s, uint32 n) const { return ::strncmp(c_str(),s.c_str(),n); }
int8 String::strcmp(const String& s) const { return ::strcmp(c_str(),s.c_str()); }

void String::operator+=(const std::string &str) { operator+=(str.c_str()); }
void String::operator+=(const String &str) { operator+=(str.c_str()); }


uint32 String::getCharCodeFromUTF8(const char *s) {
    if      ((unsigned char) s[0] >= 240) return (s[0] & 0x07) << 18 | (s[1] & 0x3F) << 12 | (s[2] & 0x3F) << 6 | (s[3] & 0x3F);
    else if ((unsigned char) s[0] >= 224) return                       (s[0] & 0x0F) << 12 | (s[1] & 0x3F) << 6 | (s[2] & 0x3F);
    else if ((unsigned char) s[0] >= 192) return                                             (s[0] & 0x1F) << 6 | (s[1] & 0x3F);
    return   (unsigned char) s[0];
}

bool operator==(const String&        lhs, const String&         rhs) { return !strcmp(lhs.c_str(),rhs.c_str()); }
bool operator==(const std::string&   lhs, const String&         rhs) { return !strcmp(lhs.c_str(),rhs.c_str()); }
bool operator==(const String&        lhs, const std::string&    rhs) { return !strcmp(lhs.c_str(),rhs.c_str()); }
bool operator==(const char*          lhs, const String&         rhs) { return !strcmp(lhs,rhs.c_str()); }
bool operator==(const String&        lhs, const char*           rhs) { return !strcmp(lhs.c_str(),rhs); }

bool operator!=(const String&        lhs, const String&         rhs) { return strcmp(lhs.c_str(),rhs.c_str()); }
bool operator!=(const std::string&   lhs, const String&         rhs) { return strcmp(lhs.c_str(),rhs.c_str()); }
bool operator!=(const String&        lhs, const std::string&    rhs) { return strcmp(lhs.c_str(),rhs.c_str()); }
bool operator!=(const char*          lhs, const String&         rhs) { return strcmp(lhs,rhs.c_str()); }
bool operator!=(const String&        lhs, const char*           rhs) { return strcmp(lhs.c_str(),rhs); }

String operator+(const Silexars::Data::String &lhs, const Silexars::Data::String &rhs) { String str(lhs); str += rhs; return str; }
String operator+(const Silexars::Data::String &lhs, std::string                  &rhs) { String str(lhs); str += rhs; return str; }
String operator+(std::string &lhs                 , const Silexars::Data::String &rhs) { String str(lhs); str += rhs; return str; }
String operator+(const Silexars::Data::String &lhs, const char                   *rhs) { String str(lhs); str += rhs; return str; }
String operator+(const char *lhs                  , const Silexars::Data::String &rhs) { String str(lhs); str += rhs; return str; }

std::ostream& operator<<(std::ostream &os, const Silexars::Data::String &str) {
    os << str.c_str();
    return os;
}
