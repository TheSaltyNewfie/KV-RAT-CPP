#include "Networking.h"

using json = nlohmann::json;

Network::Network(char ip[], int port)
{
    this->port = port;
    this->ip = ip;
	this->bufferSize = 1024;
	device::print("[Network] [+] Created Instance!");
}

Network::~Network()
{
	this->ip = nullptr;
	this->port = 0;
	this->bufferSize = 0;
	device::print("[Network] [+] Destroying Instance!");
}

struct Network::ClientPacket
{
	std::string resp;
	std::vector<char> screenData;

	void clear()
	{
		resp = "";
		screenData.clear();
	}

	json create()
	{
		json data;
		data["response"] = resp;
		data["screenData"]["binaryData"] = compress(screenData);
		return data;
	}
};

struct Network::ServerPacket
{
	std::string command;
	std::string information;
	int mx;
	int my;

	void clear()
	{
		command = "";
		information = "";
		mx = 0;
		my = 0;
	}

    void parse(json data)
    {
        command = data["command"].get<std::string>();
		information = data["information"].get<std::string>();
	    mx = data["mouseData"]["x"].get<int>();
	    my = data["mouseData"]["y"].get<int>();
    }
};

void Network::start()
{
	device::print("[Network] [+] Connecting to %s:%d...", ip, port);

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "Failed to init winsock.\n";
	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to create client socket.\n";
		WSACleanup();
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(ip);
	serverAddress.sin_port = htons(port);

	if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to connect to the server.\n";
		closesocket(clientSocket);
		WSACleanup();
	}

	device::print("[Network] [+] Connected to %s:%d!", ip, port);

	CommandHandler commandHandler;

	while(true)
	{
		json data = this->recv_(clientSocket);

		device::print("[Network] [+] Server: %s", data.dump());

		if(data == NULL)
		{
			device::ErrorWindow("Connection lost!");
		}

		ServerPacket serverPacket;
		serverPacket.parse(data);

		if(serverPacket.information == "Shutdown")
		{
			closesocket(clientSocket);
			WSACleanup();
			exit(0);
		}

		commandHandler.setInput(serverPacket.command);

		data.clear();
		serverPacket.clear();

		ClientPacket clientPacket;
		clientPacket.resp = "handled";
		clientPacket.screenData = commands::Screenshot_C();
		json clientData = clientPacket.create();

		commandHandler.callFunction();
		commandHandler.clear();

		device::print("[Network] [+] Sending data...");
		this->send_(clientSocket, clientData);
		device::print("[Network] [+] Data sent!\n");
	}

	closesocket(clientSocket);
	WSACleanup();
}

json Network::recv_(SOCKET clientSocket)
{
	buffer = new char[bufferSize];

    std::string jsonData;

    while(true)
    {
        int bytesRead = recv(clientSocket, buffer, 1024, 0);
        if(bytesRead <= 0)
        {
            return json(nullptr);
        }

        jsonData.append(buffer, bytesRead);

        try
        {
            json data = json::parse(jsonData.begin(), jsonData.end());
			delete[] buffer; // I think this is in the right spot?
            return data;
        } catch (const json::parse_error& e){}
    }
}

void Network::send_(SOCKET clientSocket, const json data)
{
	std::string sdata = data.dump();
	send(clientSocket, sdata.c_str(), static_cast<long long>(sdata.length()), 0);
}

std::string Network::compress(const std::vector<char>& data)
{
	z_stream deflate_s;

    deflate_s.zalloc = Z_NULL;
    deflate_s.zfree = Z_NULL;
    deflate_s.opaque = Z_NULL;
    deflate_s.avail_in = data.size(); // size of input
    deflate_s.next_in = (Bytef *)data.data(); // input char array

    if(deflateInit(&deflate_s, Z_BEST_COMPRESSION) != Z_OK)
    {
        device::ErrorWindow("Failed to initialize zlib");
        return "";
    }

    std::vector<char> compressedData;
    const size_t BUFSIZE = 128 * 1024;
    Bytef temp_buffer[BUFSIZE];

    do 
    {
        deflate_s.avail_out = BUFSIZE;
        deflate_s.next_out = temp_buffer;
        deflate(&deflate_s, Z_FINISH);
        size_t compressed_size = BUFSIZE - deflate_s.avail_out;
        for(size_t i = 0; i < compressed_size; i++)
        {
            compressedData.push_back(temp_buffer[i]);
        }
    } while(deflate_s.avail_out == 0);

    deflateEnd(&deflate_s);

    std::string encodedString = base64::encode(compressedData.data(), compressedData.size());

    return encodedString;
}