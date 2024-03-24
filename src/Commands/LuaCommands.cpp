#include "LuaCommands.h"

int SDLWindow(lua_State *L)
{
    const int WINDOW_WIDTH = luaL_checknumber(L, 1);
    const int WINDOW_HEIGHT = luaL_checknumber(L, 2);
    const std::string WindowName = luaL_checkstring(L, 3);
    const std::string WindowMessage = luaL_checkstring(L, 4);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // You need to provide a font file
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a surface and texture for the text
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, WindowMessage.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "TTF_RenderText_Solid error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_FreeSurface(textSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the text
    SDL_Rect textRect;
    textRect.x = (WINDOW_WIDTH - textSurface->w) / 2;
    textRect.y = (WINDOW_HEIGHT - textSurface->h) / 2;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay for a few seconds
    SDL_Delay(3000);

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int moveMouse(lua_State *L)
{
    int newX = luaL_checkinteger(L, 1);
    int newY = luaL_checkinteger(L, 2);
    int durationMillis = luaL_checkinteger(L, 3);

    POINT currentPos;
    GetCursorPos(&currentPos);

    int deltaX = newX - currentPos.x;
    int deltaY = newY - currentPos.y;

    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    int numSteps = durationMillis /10;

    double stepX = static_cast<double>(deltaX) / numSteps;
    double stepY = static_cast<double>(deltaY) / numSteps;

    for (int i = 0; i < numSteps; ++i)
    {
        currentPos.x += static_cast<int>(stepX);
        currentPos.y += static_cast<int>(stepY);

        SetCursorPos(currentPos.x, currentPos.y);
        Sleep(10);
    }

    SetCursorPos(newX, newY);
}