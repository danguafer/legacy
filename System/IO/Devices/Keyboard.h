#pragma once

#include "Device.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices {
                class Keyboard : public Device {
                    public:
                        static bool isPressed(uint32 keyCode);

                        static void hit(uint32 keyCode);
                        static void press(uint32 keyCode);
                        static void release(uint32 keyCode);

                        static bool isNumLockActive();
                        static bool isCapsLockActive();
                        static bool isScrollLockActive();

                        enum KEYS {
                            // Based on USB HID Keyboard scancodes
                            A = 4,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
                            N1 = 30,N2,N3,N4,N5,N6,N7,N8,N9,N0,
                            PAD1 = 89,PAD2,PAD3,PAD4,PAD5,PAD6,PAD7,PAD8,PAD9,PAD0,
                            F1 = 58,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
                            RETURN          = 40, ENTER = RETURN,
                            ESCAPE          = 41,
                            BACKSPACE       = 42,
                            TAB             = 43,
                            SPACEBAR        = 44,
                            MINUS           = 45,
                            EQUAL           = 46,
                            OPEN_SQUARE_BRACKET     = 47,
                            CLOSE_SQUARE_BRACKET    = 48,
                            BACKSLASH   = 49,
                            NUMBER_SIGN = 50,
                            SEMICOLON   = 51,
                            APOSTROPHE  = 52,
                            GRAVE       = 53,
                            COMMA       = 54,
                            PERIOD      = 55, DOT = PERIOD,
                            SLASH       = 56,
                            CAPS_LOCK   = 57,

                            PRINTSCREEN = 70,
                            SCROLL_LOCK = 71,
                            PAUSE       = 72,
                            INSERT      = 73,
                            HOME        = 74,
                            PAGEUP      = 75,
                            DEL         = 76,
                            END         = 77,
                            PAGEDOWN    = 78,
                            RIGHT       = 79,
                            LEFT        = 80,
                            DOWN        = 81,
                            UP          = 82,
                            NUM_LOCK    = 83,
                            PADSLASH    = 84, PADDIV = PADSLASH,
                            PADMUL      = 85,
                            PADMINUS    = 86,
                            PADPLUS     = 87,
                            PADENTER    = 88,
                            PADDOT      = 99,
                            BACKSLASH2  = 100,
                            APPLICATION = 101,

                            INTERNATIONAL1 = 135,

                            LCONTROL    = 224,
                            LSHIFT      = 225,
                            LALT        = 226,
                            LGUI        = 227,
                            RCONTROL    = 228,
                            RSHIFT      = 229,
                            RALT        = 230,
                            RGUI        = 231
                        };
                    private:
                        friend class UI::Window;
                        static uint32 systemToKey(uint32 system);
                        static uint32 keyToSystem(uint32 key);
                        static uint8 translationTable[256];
                        static bool pressmap[256];
                };
            }
        }
    }
}
