//!Broken
//!AL_EXT_float32 not working on Windows

#include <Veritas/Definitions/Definitions.h>
#if defined(WINDOWS) || defined(LINUX)

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "AudioPlayback.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace AudioDevices;

struct ALC {
    ALCdevice *dev;
    ALCcontext *ctx;
    ALuint source,buffers[2];
    ALenum format;
    ALbyte bytesPerFrame;
    uint32 bindex;
};

AudioPlayback::AudioPlayback(uint8 channels, uint8 format, uint32 fps) : AudioDevice(PLAYBACK, channels, format, fps) {
    ALC *alc = new ALC;

    alc->dev = alcOpenDevice(0);
    alc->ctx = alcCreateContext(alc->dev, 0);
    alc->bytesPerFrame = channels;
    alc->bindex = 0;

    switch (format) {
        case FORMAT_UINT8:
            switch (channels) {
                case 1: alc->format = AL_FORMAT_MONO8; break;
                case 2: alc->format = AL_FORMAT_STEREO8; break;
            }
        break;
        case FORMAT_INT16:
            switch (channels) {
                case 1: alc->format = AL_FORMAT_MONO16; break;
                case 2: alc->format = AL_FORMAT_STEREO16; break;
            }

            alc->bytesPerFrame <<= 1;
        break;
        case FORMAT_FLOAT32:
            switch (channels) {
                case 1: alc->format = AL_FORMAT_MONO_FLOAT32; break;
                case 2: alc->format = AL_FORMAT_STEREO_FLOAT32; break;
            }

            alc->bytesPerFrame <<= 2;
        break;
    }

    alcMakeContextCurrent(alc->ctx);
    alDistanceModel(AL_NONE);

    alGenBuffers(sizeof(alc->buffers)/sizeof(ALuint), alc->buffers);
    alGenSources(1, &alc->source);

    id = (Handle) alc;
}

AudioPlayback::~AudioPlayback() {
    ALC *alc = (ALC*) id;

    alSourceStop(alc->source);

    alDeleteSources(1, &alc->source);
    alDeleteBuffers(sizeof(alc->buffers)/sizeof(ALuint), alc->buffers); // Maybe it needs to

    alcDestroyContext(alc->ctx);
    alcCloseDevice(alc->dev);

    delete alc;
}

uint32 AudioPlayback::write(const void *data, uint32 frames) {
    ALC *alc = (ALC*) id;
    if (frames) {
        ALint state; alGetSourcei(alc->source,AL_SOURCE_STATE,&state);
        ALint processed; alGetSourcei(alc->source, AL_BUFFERS_PROCESSED, &processed);
        ALint queued; alGetSourcei(alc->source, AL_BUFFERS_QUEUED, &queued);

        uint32 available = sizeof(alc->buffers)/sizeof(ALuint) - queued;

        if (processed) {
            available += processed;
            for (uint8 i = 0; i < processed; i++) {
                int8 index = alc->bindex - queued + i;
                if (index < 0) index = sizeof(alc->buffers)/sizeof(ALuint) + index;
                alSourceUnqueueBuffers(alc->source, 1, &alc->buffers[index]);
            }
        }

        if (available) {
            uint32 written = frames;

            alBufferData(alc->buffers[alc->bindex], alc->format, data, alc->bytesPerFrame*written, getFPS());
            alSourceQueueBuffers(alc->source, 1, &alc->buffers[alc->bindex]);

            alc->bindex = (alc->bindex + 1) % (sizeof(alc->buffers)/sizeof(ALuint));

            if (state != AL_PLAYING) alSourcePlay(alc->source);

            return written;
        } else return 0;
    } else return 0;
}

#endif
