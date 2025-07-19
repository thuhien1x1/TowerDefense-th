#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class cmenu {
public:
    cmenu();
    /// Shows the menu; returns the chosen player name.
    /// If the name already has a save file, 'isContinue' is set to true.
    std::string runMenu(bool& isContinue);

private:
    void drawEnterName(sf::RenderWindow& win);
    void drawSelectSave(sf::RenderWindow& win);

    enum State { ENTER_NAME, SELECT_SAVE } _state;
    sf::Font      _font;
    sf::Text      _titleTxt, _inputTxt, _hintTxt;
    sf::RectangleShape _cursor;

    std::string   _typedName;                 // keyboard buffer
    std::vector<std::string> _saveNames;      // *.txt in ./saves
    int           _hoverIdx;                  // mouse-over item

    void scanSaveFolder();                    // fill _saveNames
};
