#include "Utils.h"

const int BUFFER_SIZE = 4096;

using json = nlohmann::json;

std::string compressData(const std::vector<char>& data)
{
    /*
    std::stringstream compressedDataStream;

    if(!gzip::compress(data.data(), data.size(), compressedDataStream))
    {
        std::cerr << "[!] Compression of data has failed\n";
        return "";
    }

    std::string compressedData = compressedDataStream.str();

    std::cout << "[+] Data compressed successfully!\n";

    return compressedData;
    */
   return "";
}

json networking::recvData(SOCKET clientSocket)
{
	char buffer[BUFFER_SIZE];
    std::string jsonData;

    while(true)
    {
        int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(bytesRead <= 0)
        {
            return json(nullptr);
        }

        jsonData.append(buffer, bytesRead);

        try
        {
            json data = json::parse(jsonData.begin(), jsonData.end());
            return data;
        } catch (const json::parse_error& e)
        {
            //std::cout << "Error happen: " << e.what();
            //break;
        }
    }
}

void networking::sendData(SOCKET clientSocket, const json data)
{
	std::string sdata = data.dump();
	int bytesSent = send(clientSocket, sdata.c_str(), static_cast<int>(sdata.length()), 0);
}

void capture::SaveScreenshotToWorkingDirectory(IWICBitmapSource* bitmap)
{
    HRESULT hr;

    // Create a WIC factory
    IWICImagingFactory* pFactory = nullptr;
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pFactory)
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create WIC Imaging Factory." << std::endl;
        return;
    }

    // Create an encoder to save the screenshot as PNG image
    IWICBitmapEncoder* pEncoder = nullptr;
    hr = pFactory->CreateEncoder(
        GUID_ContainerFormatPng,
        nullptr,
        &pEncoder
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create PNG encoder." << std::endl;
        pFactory->Release();
        return;
    }

    // Create a stream to write image data
    IStream* pStream = nullptr;
    hr = SHCreateStreamOnFileW( // Notice the "W" suffix for wide-character version
        L"screenshot.png", // File name for the screenshot
        STGM_CREATE | STGM_WRITE,
        &pStream
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create stream for saving screenshot." << std::endl;
        pFactory->Release();
        pEncoder->Release();
        return;
    }

    // Initialize the encoder with the stream
    hr = pEncoder->Initialize(pStream, WICBitmapEncoderNoCache);
    if (FAILED(hr))
    {
        std::cout << "Failed to initialize the encoder." << std::endl;
        pFactory->Release();
        pEncoder->Release();
        pStream->Release();
        return;
    }

    // Create a new frame and use the bitmap as the image source
    IWICBitmapFrameEncode* pFrame = nullptr;
    hr = pEncoder->CreateNewFrame(&pFrame, nullptr);
    if (FAILED(hr))
    {
        std::cout << "Failed to create new frame for encoding." << std::endl;
        pFactory->Release();
        pEncoder->Release();
        pStream->Release();
        return;
    }

    hr = pFrame->Initialize(nullptr);
    if (FAILED(hr))
    {
        std::cout << "Failed to initialize the frame." << std::endl;
        pFactory->Release();
        pEncoder->Release();
        pStream->Release();
        pFrame->Release();
        return;
    }

    // Copy the bitmap to the frame
    hr = pFrame->WriteSource(bitmap, nullptr);
    if (FAILED(hr))
    {
        std::cout << "Failed to write the bitmap to the frame." << std::endl;
        pFactory->Release();
        pEncoder->Release();
        pStream->Release();
        pFrame->Release();
        return;
    }

    // Commit the frame to the encoder
    hr = pFrame->Commit();
    if (FAILED(hr))
    {
        std::cout << "Failed to commit the frame." << std::endl;
    }

    // Commit the encoder to save the image
    hr = pEncoder->Commit();
    if (FAILED(hr))
    {
        std::cout << "Failed to commit the encoder." << std::endl;
    }

    // Release resources
    pFactory->Release();
    pEncoder->Release();
    pStream->Release();
    pFrame->Release();
}

void capture::screenshot()
{
    // Take a screenshot of the entire screen
    HWND hDesktopWnd = GetDesktopWindow();
    HDC hDesktopDC = GetDC(hDesktopWnd);
    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, screenWidth, screenHeight);
    SelectObject(hCaptureDC, hCaptureBitmap);
    BitBlt(hCaptureDC, 0, 0, screenWidth, screenHeight, hDesktopDC, 0, 0, SRCCOPY);

    // Convert the screenshot to a WIC bitmap
    IWICImagingFactory* pFactory = nullptr;
    CoInitialize(nullptr);
    CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pFactory)
    );

    IWICBitmap* pBitmap = nullptr;
    pFactory->CreateBitmapFromHBITMAP(hCaptureBitmap, nullptr, WICBitmapUseAlpha, &pBitmap);

    // Save the screenshot to the working directory as PNG
    SaveScreenshotToWorkingDirectory(pBitmap);

    // Release resources
    DeleteDC(hCaptureDC);
    DeleteObject(hCaptureBitmap);
    ReleaseDC(hDesktopWnd, hDesktopDC);
    pFactory->Release();
    pBitmap->Release();

    CoUninitialize();
}

std::vector<char> file::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if(!file.is_open())
    {
        std::cerr << "File open failed" << std::endl;
        return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if(!file.read(buffer.data(), size))
    {
        std::cerr << "File read failed" << std::endl;
        return {};
    }
    return buffer;
}