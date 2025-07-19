#include "cmenu.h"
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

cmenu::cmenu()
    : _state(ENTER_NAME), _hoverIdx(-1)
{
    _font.loadFromFile("arial.ttf");

    _titleTxt.setFont(_font);
    _titleTxt.setCharacterSize(36);
    _titleTxt.setString("Tower-Defense");
    _titleTxt.setPosition(40.f, 40.f);

    _inputTxt.setFont(_font);
    _inputTxt.setCharacterSize(28);
    _inputTxt.setPosition(60.f, 140.f);

    _hintTxt.setFont(_font);
    _hintTxt.setCharacterSize(20);
    _hintTxt.setFillColor(sf::Color::Yellow);

    _cursor.setSize({ 2.f,28.f });
    _cursor.setFillColor(sf::Color::White);

    scanSaveFolder();
}

void cmenu::scanSaveFolder()
{
    _saveNames.clear();
    if (!fs::exists("saves")) fs::create_directory("saves");
    for (auto& p : fs::directory_iterator("saves"))
        if (p.is_regular_file() && p.path().extension() == ".txt")
            _saveNames.push_back(p.path().stem().string());
}

std::string cmenu::runMenu(bool& isContinue)
{
    sf::RenderWindow win(sf::VideoMode(600, 400), "Menu");
    win.setKeyRepeatEnabled(false);

    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) win.close();

            // TEXT ENTRY -------------------------------------------
            if (_state == ENTER_NAME) {
                if (e.type == sf::Event::TextEntered) {
                    char ch = static_cast<char>(e.text.unicode);
                    if (std::isprint(ch) && _typedName.size() < 15) _typedName.push_back(ch);
                    else if (ch == 8 && !_typedName.empty()) _typedName.pop_back(); // backspace
                }
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
                    if (!_typedName.empty()) {
                        isContinue = fs::exists("saves/" + _typedName + ".txt");
                        win.close();
                    }
                }
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Tab) {
                    _state = SELECT_SAVE;
                }
            }
            // SAVE LIST -------------------------------------------
            else if (_state == SELECT_SAVE) {
                if (e.type == sf::Event::MouseMoved) {
                    _hoverIdx = -1;
                    for (size_t i = 0; i < _saveNames.size(); ++i) {
                        sf::FloatRect rect(60.f, 120.f + i * 32.f, 300.f, 30.f);
                        if (rect.contains((float)e.mouseMove.x, (float)e.mouseMove.y))
                            _hoverIdx = (int)i;
                    }
                }
                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && _hoverIdx != -1) {
                    _typedName = _saveNames[_hoverIdx];
                    isContinue = true;
                    win.close();
                }
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                    _state = ENTER_NAME;
                }
            }
        }

        // drawing -------------------------------------------
        win.clear(sf::Color(30, 30, 30));
        win.draw(_titleTxt);

        if (_state == ENTER_NAME)       drawEnterName(win);
        else if (_state == SELECT_SAVE) drawSelectSave(win);

        win.display();
    }
    return _typedName;
}

void cmenu::drawEnterName(sf::RenderWindow& win)
{
    _inputTxt.setString("Player name: " + _typedName);
    _hintTxt.setString("Press <Enter> to start   |   <Tab> to view saves");
    _hintTxt.setPosition(60.f, 220.f);

    _cursor.setPosition(_inputTxt.findCharacterPos(_typedName.size()).x + 2.f,
        _inputTxt.getPosition().y + 2.f);

    win.draw(_inputTxt);
    win.draw(_cursor);
    win.draw(_hintTxt);
}
void cmenu::drawSelectSave(sf::RenderWindow& win)
{
    _hintTxt.setString("ESC back");
    _hintTxt.setPosition(60.f, 90.f);
    win.draw(_hintTxt);

    for (size_t i = 0; i < _saveNames.size(); ++i) {
        sf::Text t(_saveNames[i], _font, 28);
        t.setPosition(60.f, 120.f + i * 32.f);
        if ((int)i == _hoverIdx) t.setFillColor(sf::Color::Cyan);
        win.draw(t);
    }
}
