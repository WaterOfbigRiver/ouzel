// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_SOURCE_HPP
#define OUZEL_AUDIO_SOURCE_HPP

#include <memory>
#include <vector>
#include "audio/Effect.hpp"

namespace ouzel
{
    namespace audio
    {
        class Source
        {
        public:
            virtual ~Source() = default;

            virtual void play() {}
            virtual void stop(bool shouldReset) { (void)shouldReset; }
            virtual void getSamples(uint32_t frames, uint32_t channels, uint32_t sampleRate, std::vector<float>& samples) = 0;

            auto& getEffects() const noexcept { return effects; }

        private:
            std::vector<std::unique_ptr<Effect>> effects;
        };
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_SOURCE_HPP
