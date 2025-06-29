#include "cgame.h"
#include <iostream>

using namespace sf;
using namespace std;

cgame::cgame() : window(), isGameOver(false), mainTowerHealth(5), enemySpeed(100.f), TOWER_RANGE(200.f) {
    // Load resources
    if (!backgroundTexture.loadFromFile("background.png") ||
        !towerTexture.loadFromFile("tower.png") ||
        !enemyTexture.loadFromFile("blockbott4.png") ||
        !bulletTexture.loadFromFile("bullet.png") ||
        !mainTowerTexture.loadFromFile("mainTower.png") ||
        !font.loadFromFile("arial.ttf"))
    {
        cerr << "Failed to load resources!\n";
        exit(EXIT_FAILURE);
    }

    window.create(VideoMode(backgroundTexture.getSize().x, backgroundTexture.getSize().y), "Tower Defense");
    backgroundSprite.setTexture(backgroundTexture);

    // Setup map & path
    cenemy& ce = map.getEnemy();
    ce.findPath(map.getMap(), ce.getStart(), ce.getEnd());

    // Set up main tower
    cpoint endTile = ce.getEnd();
    float endX = map.getMap()[endTile.getRow()][endTile.getCol()].getPixelX();
    float endY = map.getMap()[endTile.getRow()][endTile.getCol()].getPixelY();
    endY -= 80.f; // Move up 1 tile

    mainTowerSprite.setTexture(mainTowerTexture);
    mainTowerSprite.setOrigin(mainTowerTexture.getSize().x / 2.f, mainTowerTexture.getSize().y / 2.f);
    mainTowerSprite.setPosition(endX, endY);

    // Set up text to display main tower hp (demo)
    hpText.setFont(font);
    hpText.setCharacterSize(20);
    hpText.setFillColor(Color::Black);
    hpText.setPosition(10.f, 10.f);

    // Set up text to notify game loss (demo)
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(Color::Black);
    gameOverText.setString("Main tower destroyed! Game over!");
    FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    gameOverText.setPosition(backgroundTexture.getSize().x / 2.f, backgroundTexture.getSize().y / 2.f);

    spawnEnemies();
}

void cgame::run() {
    Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds(); // Delta time for smooth movement
        handleEvents();
        update(dt);
        render();
    }
}

void cgame::spawnEnemies() {
    cenemy& ce = map.getEnemy();
    for (int i = 0; i < 10; i++) {
        cenemy enemy;
        enemy.setStart(ce.getStart());
        enemy.setEnd(ce.getEnd());
        enemy.findPath(map.getMap(), ce.getStart(), ce.getEnd());

        // Offset enemies so they don't overlap
        cpoint startPoint = ce.getP()[0];
        float pixelX = startPoint.getPixelX() - i * 80.f;
        float pixelY = startPoint.getPixelY();

        enemy.init(enemyTexture, pixelX, pixelY, 3); // Start with 3 health (level 1), adjust based on level setting
        enemy.setCurr(startPoint);  // Store current grid position

        enemies.push_back(enemy);
    }
}

void cgame::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        // Place tower on valid map tiles by clicking the mouse
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            int mx = event.mouseButton.x, my = event.mouseButton.y;
            cpoint clicked = cpoint::fromXYToRowCol(mx, my);

            if (clicked.getRow() >= 0 && clicked.getRow() < cpoint::MAP_ROW &&
                clicked.getCol() >= 0 && clicked.getCol() < cpoint::MAP_COL &&
                map.getMap()[clicked.getRow()][clicked.getCol()].getC() == -1 && towers.size() < 3) { // Assuming towers is 3 for scaling, adjust based on level setting
                ctower t;
                t.init(towerTexture, map.getMap()[clicked.getRow()][clicked.getCol()].getPixelX(), map.getMap()[clicked.getRow()][clicked.getCol()].getPixelY());
                t.setLocation(clicked);
                t.setMapForBullet(map.getMap());
                t.getBullet().setSpeed(8);
                towers.push_back(t);
            }
        }
    }
}

void cgame::update(float dt) {
    // Enemy movement
    for (auto& e : enemies) {
        if (!e.hasReachedEnd() && e.getCurrentTarget() < e.getPathLength()) {
            float targetX = e.getP()[e.getCurrentTarget()].getPixelX();
            float targetY = e.getP()[e.getCurrentTarget()].getPixelY();

            float dx = targetX - e.getX();
            float dy = targetY - e.getY();
            float len = sqrt(dx * dx + dy * dy);

            if (len < 1.f) {
                e.incrementTarget();
                if (e.getCurrentTarget() >= e.getPathLength()) {
                    e.reachEnd();
                    mainTowerHealth--;
                    if (mainTowerHealth <= 0) {
                        isGameOver = true;
                    }
                }
            }
            else {
                dx /= len;
                dy /= len;
                e.move(dx * enemySpeed * dt, dy * enemySpeed * dt);
            }
        }
    }

    // Tower attack logic: target enemies and shoot
    for (auto& tower : towers) {
        tower.addShootTimer(dt);
        bool validTarget = false;
        int idx = tower.getTargetEnemyIdx();

        // Check current target still valid
        if (idx >= 0 && idx < enemies.size() &&
            !enemies[idx].hasReachedEnd() && !enemies[idx].isDead()) {
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

        // Shoot bullet when cooldown is over
        if (tower.getTargetEnemyIdx() != -1 && tower.getShootTimer() > 1.f) {
            tower.resetShootTimer();
            cbullet b;
            b.init(bulletTexture, tower.getSprite().getPosition().x, tower.getSprite().getPosition().y);
            b.setTargetIdx(tower.getTargetEnemyIdx());
            b.setSpeed(8);
            bullets.push_back(b);
        }
    }

    // Bullet logic: track and hit enemies
    for (auto& b : bullets) {
        if (!b.isActive()) continue;
        int idx = b.getTargetIdx();

        if (idx < 0 || idx >= enemies.size() || enemies[idx].hasReachedEnd() || enemies[idx].isDead()) {
            b.deactivate();
            continue;
        }

        if (b.checkCollision(enemies[idx])) {
            b.deactivate();
            enemies[idx].takeDamage(b.getDamage());

            // When enemy dies, move it off-screen and mark as reached end
            if (enemies[idx].isDead()) {
                enemies[idx].setPosition(-100.f, -100.f);
                enemies[idx].reachEnd();
            }
        }
        else {
            b.trackEnemy(enemies[idx], dt);
        }
    }

    // Remove inactive bullets
    bullets.erase(remove_if(bullets.begin(), bullets.end(), [](cbullet& b) { return !b.isActive(); }), bullets.end());

    hpText.setString("Main Tower HP: " + to_string(mainTowerHealth));
}

void cgame::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(mainTowerSprite);
    window.draw(hpText);
    if (isGameOver) window.draw(gameOverText);
    for (const auto& t : towers) window.draw(t.getSprite());
    for (const auto& e : enemies) window.draw(e.getSprite());
    for (const auto& b : bullets) window.draw(b.getSprite());
    window.display();
}