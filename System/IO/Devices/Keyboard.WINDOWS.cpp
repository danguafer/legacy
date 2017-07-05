//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS

#include "Keyboard.h"
#include <windows.h>
#include <winable.h>

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

void Keyboard::press(uint32 key) {
    uint32 vk = key;
    INPUT Input;
    ZeroMemory(&Input, sizeof(Input));
    Input.type = INPUT_KEYBOARD;
    Input.ki.wScan = MapVirtualKey(vk,0);
    Input.ki.wVk = vk;
    SendInput(1, &Input, sizeof(INPUT));
}

void Keyboard::release(uint32 key) {
    uint32 vk = key;
    INPUT Input;
    ZeroMemory(&Input, sizeof(Input));
    Input.type = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wScan = MapVirtualKey(vk,0);
    Input.ki.wVk = vk;
    SendInput(1, &Input, sizeof(INPUT));
}

uint8 Keyboard::translationTable[256] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    Keyboard::BACKSPACE, // 8
    Keyboard::TAB, // 9
    10,
    11,
    12,
    Keyboard::RETURN, // 13
    14,
    15,
    16,
    Keyboard::LCONTROL, // 17
    Keyboard::LALT, // 18
    Keyboard::PAUSE, // 19
    Keyboard::CAPS_LOCK, // 20
    21,
    22,
    23,
    24,
    25,
    26,
    Keyboard::ESCAPE, // 27
    28,
    29,
    30,
    31,
    Keyboard::SPACEBAR, // 32
    Keyboard::PAGEUP, // 33
    Keyboard::PAGEDOWN, // 34
    Keyboard::END, // 35
    Keyboard::HOME, // 36
    Keyboard::LEFT, // 37
    Keyboard::UP,
    Keyboard::RIGHT,
    Keyboard::DOWN, // 40
    41,
    42,
    43,
    Keyboard::PRINTSCREEN, // 44
    Keyboard::INSERT, // 45
    Keyboard::DEL, // 46
    47,
    Keyboard::N0, // 48
    Keyboard::N1,
    Keyboard::N2,
    Keyboard::N3,
    Keyboard::N4,
    Keyboard::N5,
    Keyboard::N6,
    Keyboard::N7,
    Keyboard::N8,
    Keyboard::N9, // 57
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    Keyboard::A, // 65
    Keyboard::B,
    Keyboard::C,
    Keyboard::D,
    Keyboard::E,
    Keyboard::F,
    Keyboard::G,
    Keyboard::H,
    Keyboard::I,
    Keyboard::J,
    Keyboard::K,
    Keyboard::L,
    Keyboard::M,
    Keyboard::N,
    Keyboard::O,
    Keyboard::P,
    Keyboard::Q,
    Keyboard::R,
    Keyboard::S,
    Keyboard::T,
    Keyboard::U,
    Keyboard::V,
    Keyboard::W,
    Keyboard::X,
    Keyboard::Y,
    Keyboard::Z,
    Keyboard::LGUI, // 91
    Keyboard::RGUI, // 92
    Keyboard::APPLICATION, // 93
    94,
    95,
    Keyboard::PAD0, // 96
    Keyboard::PAD1,
    Keyboard::PAD2,
    Keyboard::PAD3,
    Keyboard::PAD4,
    Keyboard::PAD5,
    Keyboard::PAD6,
    Keyboard::PAD7,
    Keyboard::PAD8,
    Keyboard::PAD9, // 105
    Keyboard::PADMUL, // 106
    Keyboard::PADPLUS, // 107
    108,
    Keyboard::PADMINUS,
    Keyboard::PADDOT, // 110
    Keyboard::PADDIV, // 111
    Keyboard::F1, // 112
    Keyboard::F2,
    Keyboard::F3,
    Keyboard::F4,
    Keyboard::F5,
    Keyboard::F6,
    Keyboard::F7,
    Keyboard::F8,
    Keyboard::F9,
    Keyboard::F10,
    Keyboard::F11,
    Keyboard::F12, // 123
    124,
    125,
    126,
    127,
    128,
    129,
    130,
    131,
    132,
    133,
    134,
    135,
    136,
    137,
    138,
    139,
    140,
    141,
    142,
    143,
    Keyboard::NUM_LOCK, // 144
    Keyboard::SCROLL_LOCK, // 145
    146,
    147,
    148,
    149,
    150,
    151,
    152,
    153,
    154,
    155,
    156,
    157,
    158,
    159,
    Keyboard::LSHIFT, // 160
    Keyboard::RSHIFT, // 161
    162,
    Keyboard::RCONTROL, // 163
    164,
    Keyboard::RALT,
    166,
    167,
    168,
    169,
    170,
    171,
    172,
    173,
    174,
    175,
    176,
    177,
    178,
    179,
    180,
    181,
    182,
    183,
    184,
    185,
    Keyboard::SEMICOLON, // 186
    Keyboard::EQUAL, // 187
    Keyboard::COMMA, // 188
    Keyboard::MINUS, // 189
    Keyboard::DOT, // 190
    Keyboard::SLASH, // 191
    Keyboard::GRAVE, // 192
    Keyboard::INTERNATIONAL1, // 193
    194,
    195,
    196,
    197,
    198,
    199,
    200,
    201,
    202,
    203,
    204,
    205,
    206,
    207,
    208,
    209,
    210,
    211,
    212,
    213,
    214,
    215,
    216,
    217,
    218,
    Keyboard::OPEN_SQUARE_BRACKET, // 219
    Keyboard::BACKSLASH, // 220
    Keyboard::CLOSE_SQUARE_BRACKET, // 221
    Keyboard::APOSTROPHE, // 222
    223,
    224,
    225,
    Keyboard::BACKSLASH2, // 226 Non-US BACKSLASH
    227,
    228,
    229,
    230,
    231,
    Keyboard::PADENTER, // 232
    233,
    234,
    235,
    236,
    237,
    238,
    239,
    240,
    241,
    242,
    243,
    244,
    245,
    246,
    247,
    248,
    249,
    250,
    251,
    252,
    253,
    254,
    255
};

#endif // WINDOWS
