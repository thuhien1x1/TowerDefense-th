#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "ResourceHolder.h"

namespace Textures
{
    enum ID
    {
        Background,
        Tower,
        Enemy,
        Bullet,
        MainTower,
        TitleScreen,
        // Add any additional textures here
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
        // Add any additional fonts here
    };
}

// Type aliases for easy access
using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;