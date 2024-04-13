#pragma once

#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <glm/vec2.hpp>


cv::Mat getScreenMatrix(HWND hWND, int fov) {

    HDC deviceContext = GetDC(hWND);
    HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

    RECT windowRect;
    GetClientRect(hWND, &windowRect);

    int height = windowRect.bottom;
    int width = windowRect.right;

    // Calculate center of the screen
    int centerX = width / 2;
    int centerY = height / 2;

    // Calculate top-left corner of the 500x500 square
    int startX = centerX - fov / 2;
    int startY = centerY - fov / 2;

    HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, fov, fov);
    SelectObject(memoryDeviceContext, bitmap);

    BitBlt(memoryDeviceContext, 0, 0, fov, fov, deviceContext, startX, startY, SRCCOPY);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = fov;
    bi.biHeight = -fov;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 1;
    bi.biYPelsPerMeter = 2;
    bi.biClrUsed = 3;
    bi.biClrImportant = 4;

    cv::Mat mat = cv::Mat(fov, fov, CV_8UC4);

    GetDIBits(memoryDeviceContext, bitmap, 0, fov, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    DeleteObject(bitmap);
    DeleteDC(memoryDeviceContext);
    ReleaseDC(hWND, deviceContext);
   
    return mat;
}
