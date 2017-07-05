//!Complete

#ifndef SILEXARS_MANAGERS_DEVICEMANAGERS_GRAPHICSMANAGER_H_
#define SILEXARS_MANAGERS_DEVICEMANAGERS_GRAPHICSMANAGER_H_

#include "../../IO/Devices/GraphicsDevice.h"
#include <list>

namespace Silexars {
    namespace System {
        namespace Managers {
            namespace DeviceManagers {
                class GraphicsManager {
                    private:
                        typedef std::list<IO::Devices::GraphicsDevice*> List;
                    public:
                        typedef List::iterator iterator;

                        iterator begin();
                        iterator end();
                        uint32 size() const;

                        IO::Devices::GraphicsDevice* getDefaultDisplay() const;
                    private:
                        void manage();

                        friend class Managers::DeviceManager;
                        List devices;

                        GraphicsManager();
                        ~GraphicsManager();                        
                };
            }
        }
    }
}

#endif
