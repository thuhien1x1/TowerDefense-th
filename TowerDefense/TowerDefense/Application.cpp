#include "Application.h"
#include "StateIdentifiers.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "VictoryState.h"
#include "DefeatState.h"
#include "SettingState.h"
#include "InformationState.h"
#include "SaveManagement.h"
#include "MapSelectionState.h"

Application::Application()
    : mWindow(sf::VideoMode(1920, 1080), "Tower Defense", sf::Style::Close)
    , mTextures()
    , mFonts()
    , mPlayer()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mVictoryStars))
{
    mWindow.setVerticalSyncEnabled(true); // Smoother rendering

    registerStates();
    mStateStack.pushState(States::Menu); // Start with menu screen

    // Load fonts
    mFonts.load(Fonts::BruceForever, "Media/Fonts/BruceForeverRegular-X3jd2.ttf");
    mFonts.load(Fonts::KnightWarrior, "Media/Fonts/KnightWarrior-w16n8.otf");
    mFonts.load(Fonts::RobotTraffic, "Media/Fonts/RobotTrafficDemo-BLPlw.ttf");

    // Load map textures
    mTextures.load(Textures::Map1, "Media/Textures/map 1.png");
    mTextures.load(Textures::Map2, "Media/Textures/map 2.png");
    mTextures.load(Textures::Map3, "Media/Textures/map 3.png");
    mTextures.load(Textures::Map4, "Media/Textures/map 4.png");

    // Load tower & tower shoot effect textures
    mTextures.load(Textures::MainTower, "Media/Textures/mainTower.png");
    mTextures.load(Textures::Tower1, "Media/Textures/tower1.png");
    mTextures.load(Textures::Tower2, "Media/Textures/tower2.png");
    mTextures.load(Textures::Tower3, "Media/Textures/tower3.png");
    mTextures.load(Textures::Tower1plus, "Media/Textures/tower1+.png");
    mTextures.load(Textures::Tower2plus, "Media/Textures/tower2+.png");
    mTextures.load(Textures::Tower3plus, "Media/Textures/tower3+.png");
    mTextures.load(Textures::ShootEffect, "Media/Textures/shootEffect.png");

    // Load tower Infos
    mTextures.load(Textures::Info1, "Media/Textures/infotower1.png");
    mTextures.load(Textures::Info2, "Media/Textures/infotower2.png");
    mTextures.load(Textures::Info3, "Media/Textures/infotower3.png");
    mTextures.load(Textures::Info1plus, "Media/Textures/infotower1+.png");
    mTextures.load(Textures::Info2plus, "Media/Textures/infotower2+.png");
    mTextures.load(Textures::Info3plus, "Media/Textures/infotower3+.png");

    // Load bullet textures
    mTextures.load(Textures::Bullet1, "Media/Textures/bomb_sprite_sheet.png");
    mTextures.load(Textures::Bullet2, "Media/Textures/bomb_sprite_sheet.png");
    mTextures.load(Textures::Bullet3, "Media/Textures/bomb_sprite_sheet.png");
    mTextures.load(Textures::Bomb, "Media/Textures/bomb_sprite_sheet.png");
   

    // Load enemy's animation textures
    mTextures.load(Textures::Enemy1_Walk, "Media/Textures/enemy_1_walk_126_123_6.png");
    mTextures.load(Textures::Enemy1_Attack, "Media/Textures/enemy_1_attack_125_125_6.png");
    mTextures.load(Textures::Enemy1_Death, "Media/Textures/enemy_1_death_125_125_6.png");
    mTextures.load(Textures::Enemy2_Fly, "Media/Textures/enemy_2_fly_209_203_4.png");
    mTextures.load(Textures::Enemy2_Attack, "Media/Textures/enemy_2_attack_209_203_6.png");
    mTextures.load(Textures::Enemy2_Death, "Media/Textures/enemy_2_death_209_203_6.png");
    mTextures.load(Textures::Enemy3_Walk, "Media/Textures/enemy_3_walk_213_211_6.png");
    mTextures.load(Textures::Enemy3_Attack, "Media/Textures/enemy_3_attack_212_210_6.png");
    mTextures.load(Textures::Enemy3_Death, "Media/Textures/enemy_3_death_212_210_6.png");

    // Load Upgrade button
    mTextures.load(Textures::upgradeButton, "Media/UI/buttons/upgradeButton.png");

    // Load UI in MenuState
    mTextures.load(Textures::MenuScreen, "Media/Textures/menuScreen.png");
    mTextures.load(Textures::newGameButton, "Media/UI/buttons/newGameButton.png");
    mTextures.load(Textures::loadGameButton, "Media/UI/buttons/loadGameButton.png");
    mTextures.load(Textures::exitButton, "Media/UI/buttons/exitButton.png");

    // Load UI in SettingState
    mTextures.load(Textures::settingButton, "Media/UI/buttons/settingButton.png");
    mTextures.load(Textures::optionsPanelInMenu, "Media/UI/optionsPanel.png");
    mTextures.load(Textures::onButton, "Media/UI/buttons/onButton.png");
    mTextures.load(Textures::offButton, "Media/UI/buttons/offButton.png");
    mTextures.load(Textures::closeButton, "Media/UI/buttons/xButton.png");

    // Load UI in InformationState
    mTextures.load(Textures::infoButton, "Media/UI/buttons/informationButton.png");
    mTextures.load(Textures::infoPanel, "Media/UI/informationPanelInMenuState.png");

    // Load UI in MapSelectionState
    mTextures.load(Textures::mapSelectionBackground, "Media/UI/MapSelectionStateBackground.png");
    mTextures.load(Textures::homeButton, "Media/UI/buttons/homeButton.png");
    mTextures.load(Textures::miniMap1, "Media/UI/miniMapUnlocked/miniMap1.png");
    mTextures.load(Textures::miniMap2, "Media/UI/miniMapUnlocked/miniMap2.png");
    mTextures.load(Textures::miniMap3, "Media/UI/miniMapUnlocked/miniMap3.png");
    mTextures.load(Textures::miniMap4, "Media/UI/miniMapUnlocked/miniMap4.png");
    mTextures.load(Textures::miniMap2Locked, "Media/UI/miniMapLocked/miniMap2Locked.png");
    mTextures.load(Textures::miniMap3Locked, "Media/UI/miniMapLocked/miniMap3Locked.png");
    mTextures.load(Textures::miniMap4Locked, "Media/UI/miniMapLocked/miniMap4Locked.png");

    // Load UI in PauseState 
    mTextures.load(Textures::pauseButton, "Media/UI/buttons/pauseButton.png");
    mTextures.load(Textures::pausePanel, "Media/UI/pausePanel.png");
    mTextures.load(Textures::restartButton, "Media/UI/buttons/restartButton.png");
    mTextures.load(Textures::quitButton, "Media/UI/buttons/quitButton.png");

    // Load UI in GameState
    mTextures.load(Textures::commingWave, "Media/UI/icons/commingWave.png");

    // Load UI in VictoryState
    mTextures.load(Textures::victory, "Media/UI/icons/victory.png");
    mTextures.load(Textures::star, "Media/UI/icons/star.png");

    // Load UI in DefeatState
    mTextures.load(Textures::defeat, "Media/UI/icons/defeat.png");
    mTextures.load(Textures::restartButton2, "Media/UI/buttons/restartButton2.png");
    mTextures.load(Textures::quitButton2, "Media/UI/buttons/quitButton2.png");
}

void Application::run()
{
    sf::Clock clock;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        processInput();
        update(dt);
        render();
    }
}

void Application::registerStates()
{
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingState>(States::Setting);
    mStateStack.registerState<InformationState>(States::Information);
    mStateStack.registerState<SaveManagement>(States::Load);
    mStateStack.registerState<MapSelectionState>(States::MapSelection);
    mStateStack.registerState<VictoryState>(States::Victory);
    mStateStack.registerState<DefeatState>(States::Defeat);
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);

    if (mStateStack.isEmpty())
        mWindow.close();
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}