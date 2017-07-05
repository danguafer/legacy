#pragma once

#include "AudioDevice.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices {
                namespace AudioDevices {
                    class AudioPlayback : public AudioDevice {
                        public:
                            AudioPlayback(uint8 channels, uint8 format = FORMAT_INT16, uint32 fps = 44100);
                            ~AudioPlayback();

                            uint32 write(const void* buffer, uint32 frames);
                            uint32 error() const;
                        private:
                            void systemCreateAudioPlayback(uint8 channels, uint8 bps, uint32 fps);

                            Handle id;
                    };
                }
            }
        }
    }
}
