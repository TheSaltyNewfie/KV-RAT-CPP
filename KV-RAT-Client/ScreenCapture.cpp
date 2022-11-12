#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include <thread>
#include <chrono>

HBITMAP GetScreenShot(void)
{
    int x1, y1, x2, y2, w, h;

    // get screen dimensions

    //Debug values
    int xx = GetSystemMetrics(SM_CXSCREEN);
    int yy = GetSystemMetrics(SM_CYSCREEN);

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    w = x2 - x1;
    h = y2 - y1;

    // copy screen to bitmap
    HDC     hScreen = GetDC(NULL);
    HDC     hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);
    /*
    // save bitmap to clipboard
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();
    */

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(bitmap), &bitmap);
    return hBitmap;

    // clean up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
}



void StreamBuffer()
{
    auto framerate = round(1000 / 45); // locked framerate for now




}