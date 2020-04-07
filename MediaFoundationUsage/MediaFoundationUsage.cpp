// MediaFoundationUsage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <ks.h>
#include <ksmedia.h>
#include <mfapi.h>
#include <mfidl.h>
#include <windows.h>
#include <windowsx.h>

#include <iostream>

#pragma comment(lib, "Mfplat.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "User32.lib")

int main()
{
    CoInitializeEx(0, COINIT_MULTITHREADED);
    // Initialize MF
    MFStartup(MF_VERSION);

    IMFAttributes* pAttributes;
    IMFActivate** ppDevices = nullptr;
    UINT32 count = 0;

    if (FAILED(MFCreateAttributes(&pAttributes, 1))) {
        goto done;
    }

    if (FAILED(pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID))) {
        goto done;
    }

    if (FAILED(MFEnumDeviceSources(pAttributes, &ppDevices, &count))) {
        goto done;
    }

    if (count == 0) {
        goto done;
    }

    for (UINT32 i = 0; i < count; i++) {
        WCHAR buf[512];
        ppDevices[i]->GetString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, buf, sizeof(buf) / sizeof(WCHAR), NULL);
        std::wcout << buf << std::endl;
    }

    done:
    if (pAttributes) pAttributes->Release();
    if (ppDevices) {
        for (UINT32 i = 0; i < count; i++) {
            if (ppDevices[i]) {
                ppDevices[i]->Release();
                ppDevices[i] = nullptr;
            }
        }
        CoTaskMemFree(ppDevices);
    }
    MFShutdown();
    CoUninitialize();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
