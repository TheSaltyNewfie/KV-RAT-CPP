#include <iostream>
#include "../Networking/Networking.h"
#include "../Commands/CommandHandler.h"
#include "Utils.h"
#define SDL_MAIN_HANDLED
#include <../../external/SDL2/SDL.h>
#include <../../external/SDL2/SDL_image.h>
#include <../../external/SDL2/SDL_mixer.h>
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_opengl2.h"
#include "../../external/imgui/imgui_impl_sdl2.h"
#include "../../external/imgui/imgui_stdlib.h"
#include "../../external/SDL2/SDL_opengl.h"

class Debug 
{
    public:
        std::string ip;
        int port;

        Debug();
        ~Debug();
        int init();

    private:
        SDL_Window* window;
        SDL_WindowFlags window_flags;
        SDL_GLContext gl_context;
        bool done = false;
        int height;
        int width;
        Network client;
        CommandHandler commandHandler;
        std::string DebugLog;

        void Gui();
        void EmulatedServer();
        void HandleClient(SOCKET clientSocket);

};