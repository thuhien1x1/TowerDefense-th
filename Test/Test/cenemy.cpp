#include "cenemy.h"
#include <queue>
#include <vector>
#include <algorithm>

cenemy::cenemy()
    : _posX(0.f), _posY(0.f), _health(3), _speed(3), _currentTarget(1), _reachedEnd(false), _pathLength(0) {

    // Directions: up, left, down, right for pathfinding
    dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;
    dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;

    // Default positions in grid
    _start = cpoint();
    _end = cpoint();
    _curr = cpoint();

    // Path array initialization
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
        _p[i] = cpoint();
}


cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy() {
    _start = tstart;
    _end = tend;
    _curr = tcurr;
}

void cenemy::setSpeed(int tspeed) { if (tspeed > 0 && tspeed < 10) _speed = tspeed; }
void cenemy::setStart(const cpoint& tstart) { _start = tstart; }
void cenemy::setEnd(const cpoint& tend) { _end = tend; }
void cenemy::setCurr(const cpoint& tcurr) { _curr = tcurr; }


void cenemy::calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e) {
    std::queue<cpoint> q;
    bool visited[cpoint::MAP_ROW][cpoint::MAP_COL] = {};
    cpoint parent[cpoint::MAP_ROW][cpoint::MAP_COL];

    q.push(s);
    visited[s.getRow()][s.getCol()] = true;
    parent[s.getRow()][s.getCol()] = s;

    bool found = false;
    while (!q.empty()) {
        cpoint curr = q.front(); q.pop();
        if (curr.getRow() == e.getRow() && curr.getCol() == e.getCol()) {
            found = true;
            break;
        }
        for (int i = 0; i < 4; i++) {
            int dmoi = dd[i] + curr.getRow(), cmoi = dc[i] + curr.getCol();
            if (dmoi >= 0 && dmoi < cpoint::MAP_ROW && cmoi >= 0 && cmoi < cpoint::MAP_COL
                && !visited[dmoi][cmoi] && a[dmoi][cmoi] == 0) {
                visited[dmoi][cmoi] = true;
                parent[dmoi][cmoi] = curr;
                q.push(cpoint(dmoi, cmoi, 0));
            }
        }
    }

    if (found) {
        std::vector<cpoint> pathList;
        cpoint curr = e;
        while (!(curr.getRow() == s.getRow() && curr.getCol() == s.getCol())) {
            pathList.push_back(curr);
            curr = parent[curr.getRow()][curr.getCol()];
        }
        pathList.push_back(s);
        std::reverse(pathList.begin(), pathList.end());
        int i = 0;
        for (auto& p : pathList) _p[i++] = p;
        _pathLength = i;
    }
    else {
        _pathLength = 0;
    }
}

void cenemy::findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e) {
    int ta[cpoint::MAP_ROW][cpoint::MAP_COL];
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            ta[i][j] = a[i][j].getC();
    calcPath(ta, cpoint::MAP_ROW, s, e);
}

void cenemy::init(const sf::Texture& tex, float x, float y, int hp) {
    _sprite.setTexture(tex);
    _sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f); // Center the sprite origin
    _sprite.setScale(0.5f, 0.5f);
    _posX = x;
    _posY = y;
    _health = hp;
    _reachedEnd = false;
    _currentTarget = 1;  
    updateSprite();
}

void cenemy::updateSprite() {
    _sprite.setPosition(_posX, _posY);
}

void cenemy::setPosition(float x, float y) { 
    _posX = x; 
    _posY = y; 
    updateSprite(); 
}

void cenemy::move(float dx, float dy) { 
    _posX += dx; 
    _posY += dy; 
    updateSprite(); 
}

void cenemy::takeDamage(int damage) {
    _health -= damage;

    if (_health <= 0) {
        _sprite.setColor(sf::Color(255, 255, 255, 0)); // Make enemy disappear
        _reachedEnd = true; 
    }
    else { 
        // Enemy takes damage: color becomes more red as health decreases
        float intensity = static_cast<float>(_health) / 3.f; // Assuming max health is 3 for scaling, adjust based on level setting
        if (intensity < 0.f) intensity = 0.f;
        if (intensity > 1.f) intensity = 1.f;

        int greenBlue = static_cast<int>(255 * intensity);

        // The lower the health, the less green/blue -> more red
        _sprite.setColor(sf::Color(255, greenBlue, greenBlue));
    }
}





