// This file is a part of Akel
// Author : @kbz_8
// CREATED : 03/08/2021
// UPDATED : 05/08/2021

#ifndef __AK_OPENAL__
#define __AK_OPENAL__

#include <Akpch.h>

namespace Ak
{
    class OpenAL
    {
        public:
            OpenAL() = default;
            bool initOAL();

            void freeSound(ALuint buffer);
            ALuint loadSound(std::string filename);
            void playSound(ALuint buffer);

            // Sources management
            void newSource();
            void switch_to_source(int index);
            void freeSource(int index);

            void shutdownOAL();

            ~OpenAL() = default;

        private:
            ALCdevice* _device = nullptr;
            ALCcontext* _context = nullptr;
            std::vector<ALuint> _sources;
            ALuint _currentSource = 0;
            std::vector<ALuint*> _buffers;
    };
}

#endif // __AK_OPENAL__
