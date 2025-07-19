#include "cgame.h"
#include <iostream>

using namespace sf;
using namespace std;

cgame::cgame() :
    window(),
    isGameOver(false),
    mainTowerHealth(20),
    enemySpeed(100.f),
    TOWER_RANGE(200.f)
{
    // Load resources
    if (!backgroundTexture[0].loadFromFile("map1.png") ||
        !backgroundTexture[1].loadFromFile("map2.png") ||
        !backgroundTexture[2].loadFromFile("map3.png") ||
        !backgroundTexture[3].loadFromFile("map4.png") ||
        !towerTexture[0].loadFromFile("tower1.png") ||
        !towerTexture[1].loadFromFile("tower2.png") ||
        !towerTexture[2].loadFromFile("tower3.png") ||
        !enemyTexture[0].loadFromFile("blockbott1.png") ||
        !enemyTexture[1].loadFromFile("ballred1.png") ||
        !enemyTexture[2].loadFromFile("botzred1.png") ||
        !bulletTexture[0].loadFromFile("bullet1.png") ||
        !bulletTexture[1].loadFromFile("bullet2.png") ||
        !bulletTexture[2].loadFromFile("bullet3.png") ||
        !mainTowerTexture.loadFromFile("mainTower.png") ||
        !explosionTexture.loadFromFile("explosion.png") ||
        !infoTexture[0].loadFromFile("infotower1.png") ||
        !infoTexture[1].loadFromFile("infotower2.png") ||
        !infoTexture[2].loadFromFile("infotower3.png") ||
        !font.loadFromFile("arial.ttf"))
    {
        cerr << "Failed to load resources!\n";
        exit(EXIT_FAILURE);
    }
    //window.create(VideoMode(backgroundTexture.getSize().x, backgroundTexture.getSize().y), "Tower Defense");
    backgroundSprite.setTexture(backgroundTexture[0]);

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
    gameOverText.setPosition(backgroundTexture[0].getSize().x / 2.f, backgroundTexture[0].getSize().y / 2.f);

    //spawnEnemies();

    // Set up for choosing towers
    for (int i = 0; i < 3; ++i) {
        towerIcons[i].setTexture(towerTexture[i]);
        towerIcons[i].setScale(0.6f, 0.6f); // Tower icon size
    }

    // Set up for info tower
    for (int i = 0; i < 3; ++i) {
        infoSprite[i].setTexture(infoTexture[i]);
    }

    attacks = 0;
}

void cgame::levelManagement()
{
    if (this->level == 0) // level 1
    {
        if (enemies.empty() && attacks < 2) {
            spawnEnemies(10, attacks, 3);
            attacks++;
        }
    }
    if (this->level == 1) // level 2
    {
        if (enemies.empty() && attacks < 3) {
            spawnEnemies(15, attacks, 5);
            attacks++;
        }
    }
    if (this->level == 2) // level 3
    {
        if (enemies.empty() && attacks < 4) {
            spawnEnemies(20, attacks, 8);
            attacks++;
        }
    }
    if (this->level == 3) // level 4
    {
        if (enemies.empty() && attacks < 5) {
            spawnEnemies(25, attacks, 12);
            attacks++;
        }
    }
}

void cgame::run() {
    Clock clock;
    this->level = 0; // level 1 (this is temporary)
    //this->mainTowerHealth += level * 10; // cannot update mainTowerHealth in the loop below || mainTowerHealth been init 20 in constructor
    updateMap(0);
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds(); // Delta time for smooth movement
        handleEvents();
        updateEnemies(dt);
        updateTower(dt);
        updateTest(dt);
        render(dt);

        this->levelManagement();
    }
}

// get number of towers and location (row, col) of each tower
static void writeTowers(ofstream& out, const vector<ctower>& towers)
{
    out << towers.size() << endl;
    for (auto t : towers) {
        out << t.getType() << ' ';
        auto location = t.getLocation();
        out << location.getRow() << ' ' << location.getCol() << endl;
    }
}

// get towers from file
static void readTowers(ifstream& in, vector<ctower>& towers, const Texture tex[], cpoint(&map)[cpoint::MAP_ROW][cpoint::MAP_COL])
{
    size_t n; in >> n; // number of towers
    towers.clear();
    while (n--) {
        int type; in >> type;
        int r, c; in >> r >> c;

        ctower t;
        t.init(tex[type], map[r][c].getPixelX(), map[r][c].getPixelY());
        t.setLocation(map[r][c]);
        t.setMapForBullet(map);
        t.getBullet().setSpeed(8);
        towers.push_back(t);
    }
}

// create file to save
void cgame::processSaveFile()
{
    ofstream out("saves/" + playerName + ".txt");
    if (!out) return;
    for (int i = 0; i < 4; i++)
    {
        out << p.get_score(i) << endl;
    }
    //out << mainTowerHealth << '\n';
    //writeTowers(out, towers);
    // ...
}

bool cgame::processLoadFile(const string& player)
{
    ifstream in("saves/" + player + ".txt");
    if (!in) return false;
    for (int i = 0; i < 4; i++)
    {
        int s; in >> s;
        p.set_score(i, s);
    }
    //in >> mainTowerHealth;
    //readTowers(in, towers, towerTexture, map.getMap());
    // ...
    return true;
}

void cgame::playContinue()
{
    // ...
    hpText.setString("Main Tower HP: " + to_string(mainTowerHealth));
}

void cgame::spawnEnemies(int number, int type, int health) {
    cenemy& ce = map.getEnemy();
    for (int i = 0; i < number; i++) {
        cenemy enemy;
        enemy.setStart(ce.getStart());
        enemy.setEnd(ce.getEnd());
        enemy.findPath(map.getMap(), ce.getStart(), ce.getEnd());

        // Offset enemies so they don't overlap
        cpoint startPoint = ce.getP()[0];
        float pixelX = startPoint.getPixelX() - i * 80.f;
        float pixelY = startPoint.getPixelY();

        if (type == 0)  enemy.init(enemyTexture[0], pixelX, pixelY, health); // Start with 3 health (level 1), adjust based on level setting
        else if (type == 1)  enemy.init(enemyTexture[1], pixelX, pixelY, health * 2); // Start with 3 health (level 1), adjust based on level setting
        else if (type == 2)  enemy.init(enemyTexture[2], pixelX, pixelY, health * 3); // Start with 3 health (level 1), adjust based on level setting
        enemy.setCurr(startPoint);  // Store current grid position

        enemies.push_back(enemy);
    }
}

void cgame::render(float dt) {
    window.clear();

    window.draw(backgroundSprite);
    window.draw(mainTowerSprite);
    window.draw(hpText);
    window.draw(gold);

    if (isGameOver) window.draw(gameOverText);
    if (enemies.empty()) window.draw(gameWin);

    for (const auto& t : towers) window.draw(t.getSprite());
    for (const auto& e : enemies) window.draw(e.getSprite());
    for (const auto& b : bullets) window.draw(b.getSprite());
    for (auto& e : explosions) window.draw(e.sprite);

    if (isChoosingTower) {
        for (int i = 0; i < 3; ++i)
            window.draw(towerIcons[i]);
    }
    if (showInfo) {
        window.draw(infoSprite[selectedinfo - 3]);
    }

    // Set time to erase explosions
    for (auto& e : explosions)
        e.timer += dt;
    explosions.erase
    (
        remove_if
        (
            explosions.begin(), explosions.end(), [](const explosion& e) { return e.timer > 0.12f; }
        ),
        explosions.end()
    );

    window.display();
}

void cgame::updateEnemies(float dt)
{
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

                    // Explosion effect
                    Sprite exp;
                    exp.setTexture(explosionTexture);
                    exp.setOrigin(explosionTexture.getSize().x / 2.f, explosionTexture.getSize().y / 2.f);
                    exp.setPosition(mainTowerSprite.getPosition());
                    exp.setScale(0.6f, 0.6f);
                    explosions.push_back({ exp, 0.f });


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

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (it->isDead() || it->hasReachedEnd()) {
            if (it->isDead()) p.in_score(level, 1);
            it = enemies.erase(it); // erase returns the next valid iterator
        }
        else {
            ++it;
        }
    }
}

void cgame::updateTower(float dt)
{
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
            b.init(bulletTexture[tower.getType()], tower.getSprite().getPosition().x, tower.getSprite().getPosition().y);
            b.setTargetIdx(tower.getTargetEnemyIdx());
            b.setSpeed(5);

            // Set damgage
            if (tower.getType() == 1) b.setDamage(2);
            else if (tower.getType() == 2) b.setDamage(3);

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
            //Set damage


            enemies[idx].takeDamage(b.getDamage());


            // Explosion effect
            Sprite exp;
            exp.setTexture(explosionTexture);
            exp.setOrigin(explosionTexture.getSize().x / 2.f, explosionTexture.getSize().y / 2.f);

            // Get enemy position to place explosion
            float ex = enemies[idx].getX();
            float ey = enemies[idx].getY();
            exp.setPosition(ex, ey);
            exp.setScale(0.15f, 0.15f);
            explosions.push_back({ exp, 0.f });

            // When enemy dies, move it off-screen and mark as reached end
            //if (enemies[idx].isDead()) {
            //    enemies[idx].setPosition(-100.f, -100.f);
            //    enemies[idx].reachEnd();
            //}
            bullets.erase(remove_if(bullets.begin(), bullets.end(), [](cbullet& b) { return !b.isActive(); }), bullets.end());
        }
        else {
            b.trackEnemy(enemies[idx], dt);
        }
    }

    // Remove inactive bullets
}

void cgame::updateTest(float dt)
{
    hpText.setString("Main Tower HP: " + to_string(mainTowerHealth));
    gold.setString("GOLD: " + to_string(p.get_gold()));
}

void cgame::updateMap(int index)
{
    window.create(VideoMode(backgroundTexture[index].getSize().x, backgroundTexture[index].getSize().y), "Tower Defense");
    backgroundSprite.setTexture(backgroundTexture[index]);

    // Setup map & path
    map.ChooseMap(index);
    cenemy& ce = map.getEnemy();
    ce.findPath(map.getMap(), ce.getStart(), ce.getEnd());

    // Set up main tower
    cpoint endTile = ce.getEnd();
    float endX = map.getMap()[endTile.getRow()][endTile.getCol()].getPixelX();
    float endY = map.getMap()[endTile.getRow()][endTile.getCol()].getPixelY();
    // Move up 1 tile

    mainTowerSprite.setTexture(mainTowerTexture);
    mainTowerSprite.setOrigin(mainTowerTexture.getSize().x / 2.f, mainTowerTexture.getSize().y / 2.f);
    mainTowerSprite.setPosition(endX, endY);

    // Set up text to display main tower hp (demo)
    hpText.setFont(font);
    hpText.setCharacterSize(20);
    hpText.setFillColor(Color::Black);
    hpText.setPosition(10.f, 10.f);

    // Set up text to display gold (demo)
    gold.setFont(font);
    gold.setCharacterSize(20);
    gold.setFillColor(Color::Green);
    gold.setPosition(10.f, 50.f);

    // Set up text to notify game loss (demo)
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(Color::Red);
    string loseGame = "Main tower destroyed! Game over!" + to_string(p.get_score(level));
    gameOverText.setString(loseGame);
    FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    gameOverText.setPosition(backgroundTexture[index].getSize().x / 2.f, backgroundTexture[index].getSize().y / 2.f);

    // Ser up text to notify game win
    gameWin.setFont(font);
    gameWin.setCharacterSize(30);
    gameWin.setFillColor(Color::Blue);
    string winGame = "You win!" + to_string(p.get_score(level));
    gameWin.setString(winGame);
    textRect = gameWin.getLocalBounds();
    gameWin.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    gameWin.setPosition(backgroundTexture[index].getSize().x / 2.f, backgroundTexture[index].getSize().y / 2.f);
}

void cgame::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            window.close();
            processSaveFile();
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            int mx = event.mouseButton.x, my = event.mouseButton.y;

            if (isChoosingTower) {
                // Click to choose tower
                for (int i = 0; i < 3; ++i) {
                    FloatRect bounds = towerIcons[i].getGlobalBounds();
                    if (bounds.contains(mx, my)) {
                        // Choose tower i
                        int gold = p.get_gold(); // remaining gold
                        int cost = p.get_cost(i); // cost of tower i
                        if (towers.size() < 3 && (gold - cost) >= 0) {
                            p.de_gold(p.get_cost(i));
                            ctower t;
                            t.init(towerTexture[i],
                                map.getMap()[selectedTile.getRow()][selectedTile.getCol()].getPixelX(),
                                map.getMap()[selectedTile.getRow()][selectedTile.getCol()].getPixelY());

                            t.setLocation(selectedTile);
                            t.setMapForBullet(map.getMap());
                            t.getBullet().setSpeed(8);
                            t.setType(i);
                            towers.push_back(t);
                            // choosen
                            map.getMap()[selectedTile.getRow()][selectedTile.getCol()].setC(i + 3);
                        }
                        isChoosingTower = false;
                        return;
                    }
                }

                // Click outside => close the menu
                isChoosingTower = false;
            }
            else {
                // First click
                cpoint clicked = cpoint::fromXYToRowCol(mx, my);
                if (clicked.getRow() >= 0 && clicked.getRow() < cpoint::MAP_ROW &&
                    clicked.getCol() >= 0 && clicked.getCol() < cpoint::MAP_COL)
                {
                    int c = map.getMap()[clicked.getRow()][clicked.getCol()].getC();

                    if (c == 2 && towers.size() < 3) {
                        selectedTile = clicked;
                        isChoosingTower = true;

                        for (int i = 0; i < 3; ++i)
                            towerIcons[i].setPosition(mx + i * 50.f, my);  // range 50 pixel
                    }
                    else if (c >= 3) {
                        int TILE_SIZE = cpoint::TILE_SIZE;
                        int x = clicked.getCol() * TILE_SIZE;
                        int y = clicked.getRow() * TILE_SIZE;

                        infoSprite[c - 3].setPosition(x + TILE_SIZE, y - TILE_SIZE * 4);  // Info board
                        showInfo = true;
                        selectedinfo = c;
                    }
                    else {
                        showInfo = false;
                    }
                }
            }

        }
    }
}