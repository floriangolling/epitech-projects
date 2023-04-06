/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Created by dmitry,
*/

#include "Sdl.hpp"

void __attribute__((constructor)) ctor()
{
}

void __attribute__((destructor)) dtor()
{
}

extern "C" Arcade::LibType getLibType()
{
    return Arcade::GRAPHIC;
}

extern "C" Arcade::IGraphic *getLib()
{
    return new Arcade::SDL();
}

Arcade::SDL::SDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 850, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
    TTF_Init();
}

Arcade::SDL::~SDL()
{
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

std::string Arcade::SDL::getName()
{
    return std::string("sdl");
}

void Arcade::SDL::drawPixel(Arcade::Pixel *pixel)
{
    SDL_Rect rect = {.x = (pixel->getXPos() * 15),
                     .y = (pixel->getYPos() * 15),
                     .w = (pixel->getSize() * 15),
                     .h = (pixel->getSize() * 15)};

    SDL_SetRenderDrawColor(_renderer, getSdlColorRed(pixel->getColor()), getSdlColorGreen(pixel->getColor()), getSdlColorBlue(pixel->getColor()), 255);
    SDL_RenderFillRect(_renderer, &rect);
    SDL_RenderDrawRect(_renderer, &rect);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void Arcade::SDL::drawText(Arcade::Text *text)
{
    TTF_Font *font = TTF_OpenFont("./GraphicalLib/Sfml/arial.ttf", text->getSize());
    if (font == nullptr) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(84);
    }
    if (text->getHighlight())
        TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);
    SDL_Color Color = getSdlColor(text->getColor());
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, text->getStr().c_str(), Color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = text->getXPos() * 15;
    Message_rect.y = text->getYPos() * 15;
    Message_rect.w = 0;
    Message_rect.h = 0;
    SDL_QueryTexture(Message, nullptr, nullptr, &Message_rect.w, &Message_rect.h);
    SDL_RenderCopy(_renderer, Message, nullptr, &Message_rect);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(font);
}

void Arcade::SDL::myClear() {
    SDL_RenderClear(_renderer);
}

void Arcade::SDL::myRefresh() {
    SDL_RenderPresent(_renderer);
}

//Get SDL input :
//std::cout << SDL_GetKeyName(_event.key.keysym.sym) << ":" << _event.key.keysym.sym << std::endl;
Arcade::CommandType Arcade::SDL::getInput()
{
    Uint32 windowID = SDL_GetWindowID(_window);
    while (SDL_PollEvent(&_event))
    {
        switch (_event.type) {
            case SDL_WINDOWEVENT: {
                if (_event.window.windowID == windowID) {
                    switch (_event.window.event) {
                        case SDL_WINDOWEVENT_CLOSE: {
                            return CLOSE_WINDOW;
                        }
                    }
                }
                break;
            }
            case SDL_KEYDOWN:
                for (const auto& myPair : keysdlMap) {
                    if (_event.key.keysym.sym == (int)myPair.first) {
                        return myPair.second;
                    }
                }
                break;
        }
    }
    return (NO_EVENT);
}

SDL_Color Arcade::SDL::getSdlColor(Arcade::Color color)
{
    if (color == BLACK)
        return (SDL_Color{0, 0, 0, 0});
    if (color == WHITE)
        return (SDL_Color{255,255,255, 255});
   if (color == RED)
        return (SDL_Color{255,0,0, 255});
    if (color == GREEN)
        return (SDL_Color{0, 255, 0, 255});
    if (color == BLUE)
        return (SDL_Color{0,0,255, 255});
    if (color == YELLOW)
        return (SDL_Color{255, 255, 0, 255});
    if (color == MAGENTA)
        return (SDL_Color{255, 0, 255, 255});
    if (color == CYAN)
        return (SDL_Color{0, 255, 255, 255});
    if (color == TRANSPARENT)
        return (SDL_Color{255, 255, 255, 100});
    return (SDL_Color{0, 0, 0, 255});
}

Uint8 Arcade::SDL::getSdlColorRed(Arcade::Color color)
{
    if (color == BLACK)
        return (0);
    if (color == WHITE)
        return (255);
    if (color == RED)
        return (255);
    if (color == GREEN)
        return (0);
    if (color == BLUE)
        return (0);
    if (color == YELLOW)
        return (255);
    if (color == MAGENTA)
        return (255);
    if (color == CYAN)
        return (0);
    if (color == TRANSPARENT)
        return (255);
    return 0;
}

Uint8 Arcade::SDL::getSdlColorBlue(Arcade::Color color)
{
    if (color == BLACK)
        return (0);
    if (color == WHITE)
        return (255);
    if (color == RED)
        return (0);
    if (color == GREEN)
        return (0);
    if (color == BLUE)
        return (255);
    if (color == YELLOW)
        return (0);
    if (color == MAGENTA)
        return (255);
    if (color == CYAN)
        return (255);
    if (color == TRANSPARENT)
        return (255);
    return 0;
}

Uint8 Arcade::SDL::getSdlColorGreen(Arcade::Color color)
{
    if (color == BLACK)
        return (0);
    if (color == WHITE)
        return (255);
    if (color == RED)
        return (0);
    if (color == GREEN)
        return (255);
    if (color == BLUE)
        return (0);
    if (color == YELLOW)
        return (255);
    if (color == MAGENTA)
        return (0);
    if (color == CYAN)
        return (255);
    if (color == TRANSPARENT)
        return (255);
    return 0;
}