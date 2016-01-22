// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "Application.h"

ouzel::AppPtr ouzelMain(const std::vector<std::string>& args)
{
    std::shared_ptr<ouzel::Application> application(new ouzel::Application());
    
    return application;
}
