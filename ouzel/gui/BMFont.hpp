// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GUI_BMFONT_HPP
#define OUZEL_GUI_BMFONT_HPP

#include "Font.hpp"

namespace ouzel
{
    namespace gui
    {
        class BMFont final: public Font
        {
        public:
            BMFont() = default;
            explicit BMFont(const std::vector<uint8_t>& data);

            RenderData getRenderData(const std::string& text,
                                     Color color,
                                     float fontSize,
                                     const Vector2F& anchor) const final;

            float getStringWidth(const std::string& text) const;

        private:
            int16_t getKerningPair(char32_t, char32_t) const;

            struct CharDescriptor final
            {
                int16_t x = 0;
                int16_t y = 0;
                int16_t width = 0;
                int16_t height = 0;
                int16_t xOffset = 0;
                int16_t yOffset = 0;
                int16_t xAdvance = 0;
                int16_t page = 0;
            };

            uint16_t lineHeight = 0;
            uint16_t base = 0;
            uint16_t width = 0;
            uint16_t height = 0;
            uint16_t pages = 0;
            uint16_t outline = 0;
            uint16_t kernCount = 0;
            std::unordered_map<char32_t, CharDescriptor> chars;
            std::map<std::pair<char32_t, char32_t>, int16_t> kern;
            std::shared_ptr<graphics::Texture> fontTexture;
        };
    } // namespace gui
} // namespace ouzel

#endif // OUZEL_GUI_BMFONT_HPP
