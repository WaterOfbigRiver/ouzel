// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#pragma once

#include <string>
#include "graphics/ImageData.hpp"

namespace ouzel
{
    namespace graphics
    {
        class ImageDataSTB: public ImageData
        {
        public:
            ImageDataSTB() {}

            ImageDataSTB(const std::vector<uint8_t>& newData,
                         PixelFormat newPixelFormat = PixelFormat::RGBA8_UNORM);

            void writeToFile(const std::string& filename);
        };
    } // namespace graphics
} // namespace ouzel
