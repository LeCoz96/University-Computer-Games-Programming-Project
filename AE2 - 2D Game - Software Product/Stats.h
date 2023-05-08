#pragma once
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Player;

class Stats
{
private:
    Player* m_player{ nullptr };
public:
    Stats(Player* player);
    ~Stats();

    TTF_Font* m_statsText{ nullptr };

    void UpdateText(std::string message, int x, int y, SDL_Renderer* renderer, TTF_Font* font, SDL_Color colour);
};
