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

        MenuScreen,

        // UI for MenuState
        newGameButton,
        loadGameButton,
        exitButton,

        // UI for SettingState
        settingButton,
        optionsPanelInMenu,
        onButton,
        offButton,
        closeButton,

        // UI for InformationState
        infoPanel,
        infoButton,

        // UI for MapSelectionState
        mapSelectionBackground,
        homeButton,
        miniMap1,
        miniMap2,
        miniMap3,
        miniMap4,
        miniMap2Locked,
        miniMap3Locked,
        miniMap4Locked,

        // UI for GameState
        pauseButton,
        pausePanel,
        restartButton,
        quitButton,
        commingWave,

        // UI for VictoryState & DefeatState
        victory,
        defeat,
        star,
        restartButton2,
        quitButton2,
    };
}

namespace Fonts
{
    enum ID
    {
        BruceForever,
        KnightWarrior,
        RobotTraffic,
    };
}

// Type aliases for easy access
using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;