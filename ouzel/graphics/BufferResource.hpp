// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#pragma once

#include <vector>
#include "graphics/RenderResource.hpp"
#include "graphics/Buffer.hpp"

namespace ouzel
{
    namespace graphics
    {
        class BufferResource: public RenderResource
        {
        public:
            virtual ~BufferResource();

            inline uint32_t getFlags() const { return flags; }
            inline Buffer::Usage getUsage() const { return usage; }
            inline uint32_t getSize() const { return static_cast<uint32_t>(data.size()); }

        protected:
            BufferResource(RenderDevice& initRenderDevice);

            Buffer::Usage usage;
            uint32_t flags = 0;
            std::vector<uint8_t> data;
        };
    } // namespace graphics
} // namespace ouzel
