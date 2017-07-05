#pragma once

#include "../Device.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices {
                namespace AudioDevices {
                    class AudioDevice : public Device {
                        public:
                            uint8 getChannels() const;
                            uint8 getFormat() const;
                            uint32 getFPS() const;
                            uint32 getBufferFrames() const;

                            uint8 getDeviceType() const;

                            enum TYPES { PLAYBACK, CAPTURE };
                            enum FORMATS { FORMAT_UINT8, FORMAT_INT16, FORMAT_FLOAT32 };
                        protected:
                            AudioDevice(uint8 type, uint8 channels, uint8 format, uint32 fps);
                            virtual ~AudioDevice();
                            uint8 type;
                            uint32 fps;
                            uint8 channels, format;
                    };
                }
            }
        }
    }
}
