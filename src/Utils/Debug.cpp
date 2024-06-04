#include "Debug.h"

Debug::Debug() : client(ip, port)
{
    device::print("[+] Debugging class created!\n");
    ip = "127.0.0.1";
    port = 4560;
}

Debug::~Debug()
{
    device::print("[-] Debugging Disabled\n");
}

int Debug::init() 
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        device::print("[-] SDL2 failed to initialize: %s\n", SDL_GetError());
        return -1;
    }

    window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("KV-RAT Debug Tools", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);
    if (window == nullptr)
    {
        device::print("[-] SDL2 failed to create window: %s\n", SDL_GetError());
        return -1;
    }

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    io.Fonts->AddFontFromFileTTF("Arial.ttf", 15.0f);

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    while(!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        SDL_GetWindowSize(window, &width, &height);

        Gui();

        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    return 0;
}

void Debug::Gui()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("KV-RAT Debug Tools", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowSize(ImVec2(width, height));
    {
        ImGui::BeginTabBar("DebugTabs");

        if (ImGui::BeginTabItem("Network"))
        {
            // Code for Tab 1
            ImGui::InputText("IP", &ip);
            ImGui::InputInt("Port", &port);
            ImGui::Button("Connect");
            if(ImGui::Button("Enable Emulated Server")) {emulatedServer();}
            ImGui::SameLine();
            ImGui::Text("(runs at 127.0.0.1:4560)");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Commands"))
        {
            // Code for Tab 2
            ImGui::Text("This is Tab 2");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Settings"))
        {
            // Code for Tab 3
            ImGui::Text("This is Tab 3");
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Debug Log"))
        {
            ImGui::Text("Debug Log");
            ImGui::BeginChild("DebugLog", ImVec2(0, 0), true);

            ImGui::Text("Emulated Server Started on %s:%d", ip.c_str(), port);

            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();

    ImGui::Render();
}

void Debug::EmulatedServer()
{
    device::InformationWindow("This will start an emulated server on the specified IP and Port. This is for debugging purposes only!");

    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to init winsock.\n";
    }

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET)
    {
        std::cerr << "Failed to create server socket.\n";
        WSACleanup();
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddress.sin_port = htons(port);

    if(bind(server, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to bind server socket.\n";
        closesocket(server);
        WSACleanup();
    }

    if(listen(server, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Failed to listen on server socket.\n";
        closesocket(server);
        WSACleanup();
    }

    while(true)
    {
        SOCKET clientSocket = accept(server, NULL, NULL);
        if(clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Failed to accept client connection.\n";
            closesocket(server);
            WSACleanup();
        }

        HandleClient(clientSocket);

        closesocket(clientSocket);
    }

    closesocket(server);
    WSACleanup();
}

void Debug::HandleClient(SOCKET clientSocket)
{
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
    if(bytesReceived == SOCKET_ERROR)
    {
        std::cerr << "Failed to receive data from client.\n";
        closesocket(clientSocket);
        WSACleanup();
    }

    if(bytesReceived == 0)
    {
        std::cerr << "Client disconnected.\n";
        closesocket(clientSocket);
        WSACleanup();
    }

    std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;

    std::string response = "Server received: ";
    response += std::string(buffer, 0, bytesReceived);

    send(clientSocket, response.c_str(), response.size() + 1, 0);
}