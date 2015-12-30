// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "AutoPtr.h"
#include "Node.h"
#include "Size2.h"
#include "MeshBuffer.h"
#include "Rectangle.h"

namespace ouzel
{
    class Engine;
    class Scene;
    class Texture;
    class Shader;
    
    class Sprite: public Node
    {
    public:
        Sprite(const std::string& filename, Scene* scene);
        virtual ~Sprite();
        
        virtual void draw() override;
        virtual void update(float delta) override;
        
        virtual Texture* getTexture() const { return _texture; }
        virtual void setTexture(Texture* texture);
        
        virtual Shader* getShader() const { return _shader; }
        virtual void setShader(Shader* shader);
        
        virtual const Size2& getSize() const { return _size; }
        
        virtual const Color& getColor() const { return _color; }
        virtual void setColor(const Color& color);
        
        virtual bool checkVisibility() const override;
        
        virtual void play(bool repeat = true, float frameInterval = 0.1f);
        virtual void stop(bool reset = true);
        virtual bool isPlaying() const { return _playing; }
        
    protected:
        bool loadSpriteSheet(const std::string& filename);
        void addFrame(const Rectangle& rectangle, Size2 textureSize, bool rotated);
        
        AutoPtr<Texture> _texture;
        AutoPtr<Shader> _shader;
        
        Engine* _engine;
        
        Size2 _size;
        
        std::vector<std::vector<Vertex>> _frameVertices;
        std::vector<AutoPtr<MeshBuffer>> _frameMeshBuffers;
        Color _color = Color(255, 255, 255, 255);
        
        uint32_t _currentFrame = 0;
        float _frameInterval = 0.0f;
        bool _playing = false;
        bool _repeat = false;
        float _timeSinceLastFrame = 0.0f;
        
        uint32_t _uniModelViewProj;
    };
}
