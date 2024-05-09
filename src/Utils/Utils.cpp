#include "Utils.h"

const int BUFFER_SIZE = 8196;

using json = nlohmann::json;

void device::ErrorWindow(const std::string& message)
{
    MessageBoxA(nullptr, message.c_str(), "Error", MB_OK | MB_ICONERROR);
}

void device::InformationWindow(const std::string& message)
{
    MessageBoxA(nullptr, message.c_str(), "Information", MB_OK | MB_ICONINFORMATION);
}

// Made for screenshot function mainly
std::string networking::compressData(const std::vector<char>& data)
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
            
        }
    }
}

void networking::sendData(SOCKET clientSocket, const json data)
{
	std::string sdata = data.dump();
	send(clientSocket, sdata.c_str(), static_cast<long long>(sdata.length()), 0);
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
        device::print("[SSTWD] [!] Failed to create WIC factory.");
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
        device::print("[SSTWD] [!] Failed to create PNG encoder.");
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
        device::print("[SSTWD] [!] Failed to create stream for writing.");
        pFactory->Release();
        pEncoder->Release();
        return;
    }

    // Initialize the encoder with the stream
    hr = pEncoder->Initialize(pStream, WICBitmapEncoderNoCache);
    if (FAILED(hr))
    {
        device::print("[SSTWD] [!] Failed to initialize the encoder.");
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
        device::print("[SSTWD] [!] Failed to create a new frame.");
        pFactory->Release();
        pEncoder->Release();
        pStream->Release();
        return;
    }

    hr = pFrame->Initialize(nullptr);
    if (FAILED(hr))
    {
        device::print("[SSTWD] [!] Failed to initialize the frame.");
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
        device::print("[SSTWD] [!] Failed to write the source to the frame.");
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
        device::print("[SSTWD] [!] Failed to commit the frame.");
    }

    // Commit the encoder to save the image
    hr = pEncoder->Commit();
    if (FAILED(hr))
    {
        device::print("[SSTWD] [!] Failed to commit the encoder.");
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

    // Create a new bitmap with lower resolution
    int newWidth = screenWidth / 2; // adjust as needed
    int newHeight = screenHeight / 2; // adjust as needed
    HBITMAP hLowResBitmap = CreateCompatibleBitmap(hDesktopDC, newWidth, newHeight);
    HDC hLowResDC = CreateCompatibleDC(hDesktopDC);
    SelectObject(hLowResDC, hLowResBitmap);

    // Copy the original bitmap to the new bitmap with scaling
    SetStretchBltMode(hLowResDC, COLORONCOLOR);
    StretchBlt(hLowResDC, 0, 0, newWidth, newHeight, hCaptureDC, 0, 0, screenWidth, screenHeight, SRCCOPY);

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
    pFactory->CreateBitmapFromHBITMAP(hLowResBitmap, nullptr, WICBitmapUseAlpha, &pBitmap);
    
    // Save the screenshot to the working directory as PNG
    SaveScreenshotToWorkingDirectory(pBitmap);
    
    // Release resources
    DeleteDC(hCaptureDC);
    DeleteDC(hLowResDC);
    DeleteObject(hLowResBitmap); // delete hLowResBitmap first
    DeleteObject(hCaptureBitmap); // then delete hCaptureBitmap
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