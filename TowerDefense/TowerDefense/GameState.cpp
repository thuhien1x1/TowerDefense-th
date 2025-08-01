#include "GameState.h"
#include "MapSelectionState.h"
#include <iostream>

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context),
    TOWER_RANGE(500.f),
    currentLevelIndex(MapSelectionState::levelID),
    waveIndex(0),
    mainTowerMaxHealth(0),
    levels(),
    isGameOver(false),
    isGameWin(false),
    hasPressedPlay(false),
    isWaitingForNextLevel(false),
    showEndButtons(false)
{
    // Load textures
    backgroundTexture[0] = &getContext().textures->get(Textures::Map1);
    backgroundTexture[1] = &getContext().textures->get(Textures::Map2);
    backgroundTexture[2] = &getContext().textures->get(Textures::Map3);
    backgroundTexture[3] = &getContext().textures->get(Textures::Map4);

    mainTowerTexture = &getContext().textures->get(Textures::MainTower);

    // Load Tower textures
    towerTexture[0] = &getContext().textures->get(Textures::Tower1);
    towerTexture[1] = &getContext().textures->get(Textures::Tower2);
    towerTexture[2] = &getContext().textures->get(Textures::Tower3);
    towerTexture[3] = &getContext().textures->get(Textures::Tower1plus);
    towerTexture[4] = &getContext().textures->get(Textures::Tower2plus);
    towerTexture[5] = &getContext().textures->get(Textures::Tower3plus);

    // Load Tower Infos
    infoTexture[0] = &getContext().textures->get(Textures::Info1);
    infoTexture[1] = &getContext().textures->get(Textures::Info2);
    infoTexture[2] = &getContext().textures->get(Textures::Info3);
    infoTexture[3] = &getContext().textures->get(Textures::Info1plus);
    infoTexture[4] = &getContext().textures->get(Textures::Info2plus);
    infoTexture[5] = &getContext().textures->get(Textures::Info3plus);

    // Set up for info tower
    for (int i = 0; i < 6; ++i) {
        infoSprite[i].setTexture(*infoTexture[i]);
    }

    // Set up for choosing towers
    for (int i = 0; i < 3; ++i) {
        towerIcons[i].setTexture(*towerTexture[i]);
        towerIcons[i].setScale(0.6f, 0.6f); // Tower icon size
    }

    // Load Bullet textures
    bulletTexture[0] = &getContext().textures->get(Textures::Bomb);
    bulletTexture[1] = &getContext().textures->get(Textures::Bullet2);
    bulletTexture[2] = &getContext().textures->get(Textures::Bullet3);
    bulletTexture[3] = &getContext().textures->get(Textures::Bullet1);
    bulletTexture[4] = &getContext().textures->get(Textures::Bullet2);
    bulletTexture[5] = &getContext().textures->get(Textures::Bullet3);
    shootEffectTexture = &getContext().textures->get(Textures::ShootEffect);
    font = getContext().fonts->get(Fonts::BruceForever);

    // Load Upgrade
    upgradeButton.setTexture(context.textures->get(Textures::upgradeButton));

    // Load UI texture 
    pauseButton.setTexture(context.textures->get(Textures::pauseButton));
    pauseButton.setPosition(1880.f, 50.f);
    centerOrigin(pauseButton);

    commingWave.setTexture(context.textures->get(Textures::commingWave));
    if (currentLevelIndex == 3)
        commingWave.setPosition(60.f, 690.f);
    else
        commingWave.setPosition(60.f, 770.f);
    centerOrigin(commingWave);

    // Initialize 4 levels (levelID, enemyCount, waveCount, towerMaxCount, startGold) 
    clevel level1(1, 45, 3, 5, 200);
    level1.setWaves({ {FAST_SCOUT, 20}, {FAST_SCOUT, 1}, {RANGED_MECH, 1} }); // 10, 15, 20
    level1.loadMap(mainTowerTexture, backgroundTexture[0], 1);

    clevel level2(2, 65, 3, 6, 400);
    level2.setWaves({ {HEAVY_WALKER, 1}, {FAST_SCOUT, 1}, {RANGED_MECH, 1} }); // 15, 20, 30
    level2.loadMap(mainTowerTexture, backgroundTexture[1], 2);

    clevel level3(3, 100, 4, 6, 700);
    level3.setWaves({ {HEAVY_WALKER, 1}, {FAST_SCOUT, 1}, {RANGED_MECH, 1}, {HEAVY_WALKER, 1} }); // 20, 25, 30, 25
    level3.loadMap(mainTowerTexture, backgroundTexture[2], 3);

    clevel level4(4, 175, 5, 7, 1000);
    level4.setWaves({ {HEAVY_WALKER, 1}, {FAST_SCOUT, 1}, {RANGED_MECH, 1}, {FAST_SCOUT, 1}, {HEAVY_WALKER, 1} }); // 25, 30, 35, 40, 45
    level4.loadMap(mainTowerTexture, backgroundTexture[3], 4);

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);
    levels.push_back(level4);

    // Setup enemy data
    enemyData[RANGED_MECH] = {
        &getContext().textures->get(Textures::Enemy1_Walk),
        &getContext().textures->get(Textures::Enemy1_Attack),
        &getContext().textures->get(Textures::Enemy1_Death),
        6, 6, 6, // frames walk, attack, death
        0.1f, 0.1f, 0.1f, // animation speeds
        126, 123, // frame width, frame height of walk sprite sheet
        125, 125, // frame width, frame height of attack sprite sheet
        125, 125, // frame width, frame height of death sprite sheet
        1.f, 1.f, // set scale
    };

    enemyData[FAST_SCOUT] = {
        &getContext().textures->get(Textures::Enemy2_Fly),
        &getContext().textures->get(Textures::Enemy2_Attack),
        &getContext().textures->get(Textures::Enemy2_Death),
        4, 6, 6,
        0.1f, 0.1f, 0.1f,
        209, 203,
        209, 203,
        209, 203,
        0.5f, 0.5f,
    };

    enemyData[HEAVY_WALKER] = {
        &getContext().textures->get(Textures::Enemy3_Walk),
        &getContext().textures->get(Textures::Enemy3_Attack),
        &getContext().textures->get(Textures::Enemy3_Death),
        6, 6, 6,
        0.1f, 0.1f, 0.1f,
        213, 211,
        212, 210,
        212, 210,
        0.5f, 0.5f,
    };

    loadLevel(currentLevelIndex);
}

void GameState::draw()
{
    RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.clear(sf::Color::Black);

    window.draw(backgroundSprite);
    window.draw(curMap->getMainTower().getMainTowerSprite());

    window.draw(hpText);
    window.draw(gold);

    Text levelInfo("LEVEL: " + to_string(currentLevelIndex + 1), font, 20);
    levelInfo.setFillColor(Color::Black);
    levelInfo.setPosition(10.f, 80.f);
    window.draw(levelInfo);

    clevel& level = levels[currentLevelIndex];
    Text waveText("WAVE: " + to_string(level.getCurrentWaveIndex() + 1) + "/" + to_string(level.getWaveCount()), font, 20);
    waveText.setFillColor(Color::Black);
    waveText.setPosition(10.f, 110.f);
    window.draw(waveText);

    if (!hasPressedPlay && !isGameOver && !isGameWin) {
        if (commingWave.getGlobalBounds().contains(mousePos))
            commingWave.setScale(0.15f, 0.15f);
        else
            commingWave.setScale(0.1f, 0.1f);
        window.draw(commingWave);
    }

    // Pause button
    if (hasPressedPlay) {
        if (pauseButton.getGlobalBounds().contains(mousePos))
            pauseButton.setScale(1.1f, 1.1f);
        else
            pauseButton.setScale(1.f, 1.f);
        window.draw(pauseButton);
    }

    // Update: Add enemy's hp bar
    for (const auto& e : enemies) {
        if (!e.hasReachedEnd() || e.getState() == DEATH) {

            // Draw enemy
            window.draw(e.getSprite());

            // Draw enemy's hp bar
            float spriteHeight = e.getSprite().getGlobalBounds().height;
            float barWidth = 50.f;
            float barHeight = 6.f;
            float barX = e.getX() - barWidth + 15.f;
            float barY = e.getY() - spriteHeight / 2.f - 45.f;

            // Black outline
            RectangleShape hpOutline(Vector2f(barWidth, barHeight));
            hpOutline.setPosition(barX, barY);
            hpOutline.setFillColor(Color::Black);
            window.draw(hpOutline);

            // Green hp bar, decrease gradually
            float hpPercent = static_cast<float>(e.getHealth()) / cenemy::getHealthByType(e.getType());
            hpPercent = max(0.f, min(1.f, hpPercent));

            RectangleShape hpBar(Vector2f(barWidth * hpPercent, barHeight));
            hpBar.setPosition(barX, barY);
            hpBar.setFillColor(Color::Green);
            window.draw(hpBar);
        }
    }

    for (const auto& tower : towers)
        window.draw(tower.getSprite());

    for (const auto& tower : towers)
        if (tower.isEffectPlaying())
            window.draw(tower.getEffectSprite());

    for (int i = 0; i < bullets.size(); ++i) {
        if (!bullets[i].isActive()) continue;

        if (bullets[i].isLaserBullet())
            window.draw(bullets[i].getLaserSprite());
        else
            window.draw(bullets[i].getSprite());
    }

    // draw TowerIcons
    if (isChoosingTower) {
        for (int i = 0; i < 3; ++i)
            window.draw(towerIcons[i]);
    }
    
    // draw Tower Infos
    if (showInfo && selectedinfo >= 3) {
        window.draw(infoSprite[selectedinfo - 3]);
        if (selectedinfo - 3 < 3)
            window.draw(upgradeButton);
    }
}
bool GameState::handleEvent(const sf::Event& event)
{
    RenderWindow& window = *getContext().window;

    if (event.type == Event::Closed)
        window.close();

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        // Add pause button
        sf::Vector2f mousePos = getContext().window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        // Click commingWave icon to spawn enemies
        if (commingWave.getGlobalBounds().contains(mousePos) && !hasPressedPlay) {
            hasPressedPlay = true;
            spawnEnemies();
            return false;
        }

        // Request pushing pause state when click pause button
        if (pauseButton.getGlobalBounds().contains(mousePos)) {
            requestStackPush(States::Pause);
            return false;
        }

        // Check if mouse is over UI elements (avoid placing tower in these cases)
        if (commingWave.getGlobalBounds().contains(mousePos) || pauseButton.getGlobalBounds().contains(mousePos))
            return false;

        pair<int, int> td;
        int mx = event.mouseButton.x;
        int my = event.mouseButton.y;

        // If player is currently choosing a tower to place on a tile
        if (isChoosingTower) {
            for (int i = 0; i < 3; ++i) {
                if (towerIcons[i].getGlobalBounds().contains(mx, my)) {
                    if (towers.size() < 3) {
                        ctower t;
                        // Get the designated tile to place tower from selected tile
                        td = MapHandle::getTowerdes(currentLevelIndex, selectedTile.getRow(), selectedTile.getCol());

                        // Initialize tower with texture and position on map
                        t.init(*towerTexture[i],
                            curMap->getMap()[td.first][td.second].getPixelX(),
                            curMap->getMap()[td.first][td.second].getPixelY());
                        t.setLocation(cpoint(td.first, td.second, 1));
                        t.setMapForBullet(curMap->getMap());
                        t.getBullet().setSpeed(8);
                        t.setType(i);

                        towers.push_back(t);

                        // Set the map C value to indicate a tower is placed (C = 3/4/5)
                        MapHandle::setCmap(currentLevelIndex, *curMap, selectedTile.getRow(), selectedTile.getCol(), i + 3);
                    }
                    isChoosingTower = false;
                    return false;
                }
            }
            isChoosingTower = false;
            return false;
        }

        // Handle tower upgrade button click
        if (showInfo && upgradeButton.getGlobalBounds().contains(mx, my)) {
            int tileC = selectedinfo;
            if (tileC >= 3 && tileC <= 5) {
                // Find current tower's position based on C value
                int row = -1, col = -1;
                for (int i = 0; i < cpoint::MAP_ROW && row == -1; ++i) {
                    for (int j = 0; j < cpoint::MAP_COL; ++j) {
                        if (curMap->getMap()[i][j].getC() == tileC) {
                            row = i;
                            col = j;
                            break;
                        }
                    }
                }

                // Get the designated tile and upgrade C value
                td = MapHandle::getTowerdes(currentLevelIndex, row, col);
                row = td.first;
                col = td.second;

                if (row != -1 && col != -1) {
                    int newC = tileC + 3;
                    MapHandle::setCmap(currentLevelIndex, *curMap, row, col, newC); // Update map C value for upgraded tower

                    // Update the tower's type and texture
                    for (auto& t : towers) {
                        if (t.getLocation().getRow() == row && t.getLocation().getCol() == col) {
                            t.setType(newC - 3);
                            t.init(*towerTexture[newC - 3],
                                curMap->getMap()[row][col].getPixelX(),
                                curMap->getMap()[row][col].getPixelY());
                            break;
                        }
                    }
                }

                showInfo = false;
                selectedinfo = -1;
                return false;
            }
        }

        // Handle click on map tiles
        cpoint clicked = cpoint::fromXYToRowCol(mx, my);
        if (clicked.getRow() >= 0 && clicked.getRow() < cpoint::MAP_ROW &&
            clicked.getCol() >= 0 && clicked.getCol() < cpoint::MAP_COL) {

            int c = curMap->getMap()[clicked.getRow()][clicked.getCol()].getC();

            // If clicked on a tile with C = 2 (candidate tower tile)
            if (c == 2 && towers.size() < 3) {
                selectedTile = clicked;
                isChoosingTower = true;

                // Display tower options at click location
                for (int i = 0; i < 3; ++i)
                    towerIcons[i].setPosition((float)mx + i * 50.f, (float)my);

                return false;
            }
            // If clicked on a tile that already has a tower (C >= 3)
            else if (c >= 3) {
                selectedinfo = c;

                // Get fixed display tile for showing info panel
                pair<int, int> fixed = MapHandle::getTowerdes(currentLevelIndex, clicked.getRow(), clicked.getCol());
                float fx = (float)fixed.second * cpoint::TILE_SIZE;
                float fy = (float)fixed.first * cpoint::TILE_SIZE;

                // Display tower info panel and upgrade button if upgradeable
                infoSprite[c - 3].setPosition((float)fx + cpoint::TILE_SIZE, (float)fy - 4 * cpoint::TILE_SIZE);
                if (c >= 3 && c <= 5) {
                    upgradeButton.setPosition((float)fx + cpoint::TILE_SIZE, (float)fy - 5.5f * cpoint::TILE_SIZE);
                }

                showInfo = true;
                return false;
            }
        }

        // Hide info panel if clicked outside
        showInfo = false;
        selectedinfo = -1;



        // Press "Enter" to load the next level (after winning) (demo version, adjust based on Game State Management &  UI graphics)
        if (isWaitingForNextLevel && event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
            if (currentLevelIndex + 1 < levels.size()) {
                loadLevel(currentLevelIndex + 1);
                hasPressedPlay = false;
            }

            // Reset state flags after transition
            isWaitingForNextLevel = false;
            isGameWin = false;
            isGameOver = false;
        }

        // Press "R" to restart the current level if the player loss (demo version, adjust based on Game State Management & UI graphics)
        if ((isGameOver || isGameWin) && event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
            isGameOver = false;
            isGameWin = false;
            isWaitingForNextLevel = false;
            loadLevel(currentLevelIndex); // Reload current level
        }

        // Press "Q" to exit (demo version, adjust based on Game State Management & UI graphics)
        if ((isGameOver || isGameWin || showEndButtons) && event.type == Event::KeyPressed && (event.key.code == Keyboard::Q))
            window.close(); // Exit

        return true;
    }

}

bool GameState::update(sf::Time dt)
{
    // Retrieve mainTower position in pixels
    cpoint towerTile = curMap->getMainTowerTile();
    float towerX = curMap->getMap()[towerTile.getRow()][towerTile.getCol()].getPixelX();
    float towerY = curMap->getMap()[towerTile.getRow()][towerTile.getCol()].getPixelY();

    // Enemy movement & Wave management
    for (auto& e : enemies) {
        if (!e.hasReachedEnd() && e.getCurrentTarget() < e.getPathLength() && e.getState() == WALK) {

            float targetX = e.getP()[e.getCurrentTarget()].getPixelX();
            float targetY = e.getP()[e.getCurrentTarget()].getPixelY();

            float dx = targetX - e.getX();
            float dy = targetY - e.getY();
            float len = sqrt(dx * dx + dy * dy);

            if (len < 1.f) {
                e.incrementTarget();

                if (e.getCurrentTarget() >= e.getPathLength()) {
                    // Enemy automatically switches to ATTACK state when close to the main tower
                    e.setPosition(targetX, targetY);
                    e.triggerAttack(towerX, towerY);

                    curMap->getMainTower().decreaseHealth();

                    if (curMap->getMainTower().getHealth() <= 0) {
                        isGameOver = true;
                        isGameWin = false;
                    }
                }
            }

            else {
                dx /= len;
                dy /= len;

                // Rotate enemies's sprite sheet when they turn left 
                if (dx < -0.1f)
                    e.faceLeft(e.getType());

                else if (dx > 0.1f || dy < -0.1f)
                    e.faceRight(e.getType());

                e.move(dx * e.getSpeedByType(e.getType()) * dt.asSeconds(), dy * e.getSpeedByType(e.getType()) * dt.asSeconds());
            }
        }

        e.updateAnimation(dt.asSeconds());

        if (e.isDead() && e.getState() == DEATH && e.hasFinishedDeathAnim() && !e.hasReachedEnd()) {
            e.setPosition(-2000.f, -2000.f);
            e.reachEnd();
        }

        // Remove enemy if dead AND death anim done OR has reached end
        for (int i = enemies.size() - 1; i >= 0; --i)
            if ((enemies[i].isDead() && enemies[i].getState() == DEATH && enemies[i].hasFinishedDeathAnim()) || enemies[i].hasReachedEnd())
                enemies.erase(enemies.begin() + i);
    }

    // The wave must be the last wave
    if (!isGameOver && !isGameWin && curMap->getMainTower().getHealth() > 0 && enemies.empty() && hasPressedPlay) {
        clevel& level = levels[currentLevelIndex];

        if (!level.isLastWave()) {
            level.nextWave();
            spawnEnemies();
        }

        else {
            isGameWin = true;
            isWaitingForNextLevel = true;
        }
    }

    if (isGameWin && currentLevelIndex == levels.size() - 1) {
        if (currentLevelIndex == levels.size() - 1)
            showEndButtons = true; // Only show Exit and Restart buttons on last level
        else
            isWaitingForNextLevel = true; // Go to the next level
    }

    if (isGameOver) {
        requestStackPush(States::Defeat);
        isGameOver = false;
    }

    // Push VictoryState
    if (isGameWin) {
        *getContext().victoryStars = calStars();
        requestStackPush(States::Victory);
        isGameWin = false;
    }

    // Tower attack logic: target enemies and shoot
    for (auto& tower : towers) {
        tower.addShootTimer(dt.asSeconds());
        tower.updateEffect(dt.asSeconds());
        bool validTarget = false;
        int idx = tower.getTargetEnemyIdx();

        // Check current target still valid
        if (idx >= 0 && idx < enemies.size() && !enemies[idx].hasReachedEnd() && !enemies[idx].isDead()) {
            float dist = hypot(tower.getSprite().getPosition().x - enemies[idx].getX(),
                tower.getSprite().getPosition().y - enemies[idx].getY());
            if (dist <= TOWER_RANGE)
                validTarget = true;
        }

        // Find new target if needed
        if (!validTarget) {
            tower.setTargetEnemyIdx(-1);
            for (int i = 0; i < enemies.size(); i++) {
                if (enemies[i].hasReachedEnd() || enemies[i].isDead()) continue;
                float dist = hypot(tower.getSprite().getPosition().x - enemies[i].getX(),
                    tower.getSprite().getPosition().y - enemies[i].getY());
                if (dist <= TOWER_RANGE) {
                    tower.setTargetEnemyIdx(i);
                    break;
                }
            }
        }

        // Trigger VFX
        if (tower.getTargetEnemyIdx() != -1 && tower.getShootTimer() > 0.8f)
            tower.startEffect();

        // Shoot bullet when cooldown is over
        if (tower.getTargetEnemyIdx() != -1 && tower.getShootTimer() > 1.f) {
            tower.startEffect();
            tower.resetShootTimer();

            cbullet b;
            b.init(*bulletTexture[0], tower.getSprite().getPosition().x, tower.getSprite().getPosition().y, 16, 15, 7, 0.05f);
            b.setTargetIdx(tower.getTargetEnemyIdx());
            b.setSpeed(5);
            if (tower.getType() == 1) b.setDamage(2);
            else if (tower.getType() == 2) b.setDamage(3);
            else if (tower.getType() == 3) b.setDamage(4);
            else if (tower.getType() == 4) b.setDamage(5);
            else if (tower.getType() == 5) b.setDamage(6);
            else b.setDamage(1);
            bullets.push_back(b);

            // Test laser
            /*int enemyIdx = tower.getTargetEnemyIdx();
            Vector2f towerPos = tower.getSprite().getPosition();
            Vector2f enemyPos(enemies[enemyIdx].getX(), enemies[enemyIdx].getY());

            cbullet laser;
            laser.initLaser(laserTexture, towerPos.x, towerPos.y, enemyPos.x, enemyPos.y, 0.2f);
            laser.setTargetIdx(enemyIdx);
            laser.setDamage(1);

            bullets.push_back(laser);*/
        }
    }

    // Bullet logic: track and hit enemies
    for (auto& b : bullets) {
        if (!b.isActive()) continue;

        if (b.isLaserBullet()) {
            b.updateLaser(dt.asSeconds());

            int idx = b.getTargetIdx();
            if (idx >= 0 && idx < enemies.size() && !enemies[idx].isDead() && !enemies[idx].hasReachedEnd()) {
                enemies[idx].takeDamage(b.getDamage());

                if (enemies[idx].isDead()) {
                    enemies[idx].setPosition(-100.f, -100.f);
                    enemies[idx].reachEnd();
                }
            }
        }
        else {
            int idx = b.getTargetIdx();
            if (idx < 0 || idx >= enemies.size() || enemies[idx].hasReachedEnd() || enemies[idx].isDead()) {
                b.deactivate();
                continue;
            }

            if (b.checkCollision(enemies[idx])) {
                b.deactivate();
                enemies[idx].takeDamage(b.getDamage());

                // Add collision effect
                /*float impactX = (b.getSprite().getPosition().x + enemies[idx].getX()) / 2.f;
                float impactY = (b.getSprite().getPosition().y + enemies[idx].getY()) / 2.f;

                cimpact impact(impactTexture, impactX, impactY, 500, 360, 8, 0.02f);
                impacts.push_back(impact);*/
            }
            else {
                b.trackEnemy(enemies[idx], dt.asSeconds());
                b.updateAnimation(dt.asSeconds());
            }
        }

    }

    // Remove inactive bullets
    bullets.erase(remove_if(bullets.begin(), bullets.end(), [](cbullet& b) { return !b.isActive(); }), bullets.end());

    // Update mainTower hp & gold
    hpText.setString("MAIN TOWER HP: " + to_string(curMap->getMainTower().getHealth()));
    gold.setString("GOLD: " + to_string(levels[currentLevelIndex].getStartGold()));

    return true;
}

void GameState::loadLevel(int index) {
    RenderWindow& window = *getContext().window;

    if (index < 0 || index >= levels.size()) return;

    currentLevelIndex = index;

    // Load map & pathfinding
    curMap = &levels[currentLevelIndex].getMap();
    cenemy& ce = curMap->getEnemy();
    ce.findPath(curMap->getMap(), ce.getStart(), ce.getEnd());

    // Load map data & texture & mainTowerMaxHealth for the current level
    mainTowerMaxHealth = curMap->getMainTower().getHealth();
    backgroundSprite.setTexture(*backgroundTexture[currentLevelIndex]);
    levels[currentLevelIndex].loadMap(mainTowerTexture, backgroundTexture[index], currentLevelIndex + 1);
    window.setSize(backgroundTexture[currentLevelIndex]->getSize());

    // Reset enemy, tower, bullet...
    enemies.clear();
    towers.clear();
    bullets.clear();

    // Reset game flags and wave index
    isGameOver = false;
    isGameWin = false;
    hasPressedPlay = false; // Reset play state for new level
    waveIndex = 0;
    levels[currentLevelIndex].resetWave(); // Start from wave 0

    /*
    // Set up start gold of each level for player
    p.setGold(levels[currentLevelIndex].getStartGold());
    */

    // Set up text to display main tower hp (demo)
    hpText.setFont(font);
    hpText.setCharacterSize(20);
    hpText.setFillColor(Color::Black);
    hpText.setPosition(10.f, 10.f);
    hpText.setString("MAIN TOWER HP: " + to_string(curMap->getMainTower().getHealth()));

    // Set up text to display gold (demo)
    gold.setFont(font);
    gold.setCharacterSize(20);
    gold.setFillColor(Color::Green);
    gold.setPosition(10.f, 50.f);
    gold.setString("GOLD: " + to_string(levels[currentLevelIndex].getStartGold()));
}

void GameState::spawnEnemies() {
    // Get the current level and its wave information
    const auto& waves = levels[currentLevelIndex].getWaves();
    if (waveIndex >= waves.size()) return;

    clevel& level = levels[currentLevelIndex];

    pair<EnemyType, int> info = level.getCurrentWaveInfo();
    EnemyType type = info.first;
    int count = info.second;
    cenemy& ce = curMap->getEnemy();

    for (int i = 0; i < count; i++) {
        cenemy enemy;
        enemy.loadFromData(enemyData[type]);

        enemy.setStart(ce.getStart());
        enemy.setEnd(ce.getEnd());
        enemy.findPath(curMap->getMap(), ce.getStart(), ce.getEnd());

        // Offset enemies so they don't overlap
        cpoint startPoint = ce.getP()[0];
        float pixelX = startPoint.getPixelX() - i * 120.f;
        float pixelY = startPoint.getPixelY();

        enemy.init(type, pixelX, pixelY, enemy.getHealthByType(type), enemyData[type]);
        enemy.setCurr(startPoint);
        enemies.push_back(enemy);
    }

    waveIndex++; // Update wave
}

int GameState::calStars() {
    int curHealth = curMap->getMainTower().getHealth();
    float healthRatio = static_cast<float>(curHealth) / mainTowerMaxHealth;

    // If gamwWin()
    // If currentMainTowerHealth >= 80% mainTowerMaxHealth -> 3 stars
    if (healthRatio >= 0.8f)
        return 3;
    // If currentMainTowerHealth >= 50% mainTowerMaxHealth -> 2 stars
    else if (healthRatio >= 0.5f)
        return 2;
    // If currentMainTowerHealth > 1 -> 1 star
    else if (curHealth > 0)
        return 1;
    // GameOver = true
    else
        return 0;
}

