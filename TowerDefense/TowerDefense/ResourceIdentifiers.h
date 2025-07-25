#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "ResourceHolder.h"

namespace Textures
{
    enum ID
    {
        // Maps
        Map1,
        Map2,
        Map3,
        Map4,

        // Enemy 1
        Enemy1_Walk,
        Enemy1_Attack,
        Enemy1_Death,

        // Enemy 2
        Enemy2_Fly,
        Enemy2_Attack,
        Enemy2_Death,

        // Enemy 3
        Enemy3_Walk,
        Enemy3_Attack,
        Enemy3_Death,

        // Bullet
        Bomb,
        Fire,
        Laser,

        // Effect
        ShootEffect,

        Tower,
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