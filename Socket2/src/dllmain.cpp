// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "../include/framework.h"
#include "../include/SocketDispatcher.h"
#include "../include/DataStructures.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


__declspec(dllexport) int __stdcall ConnectIF(NetAddressInterop address,int type)
{
    SocketDispatcher& dispatcher = SocketDispatcher::GetInstance(type);
    NetAddress netAddress = { address.ip,address.port };
    dispatcher.Connect(netAddress);
    return 0;
}