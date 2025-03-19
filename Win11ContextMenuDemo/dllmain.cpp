/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-19 23:30:05
 * @FilePath: \Win11ContextMenuDemo\Win11ContextMenuDemo\dllmain.cpp
 */
// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "InstallContextMenu.h"
#include "MainExplorerCommand.h"
#include "ClassFactory.h"

// 全局变量，用来存储 DLL 模块的句柄。
// Global variable to store the handle of the DLL module.
HMODULE g_module; 

// DLL 的主入口函数。
// Main entry point function for the DLL.
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // 当 DLL 被加载到程序时执行。
        // Executed when the DLL is loaded into a process.
        g_module = hModule;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// 注册 DLL 以便用于上下文菜单扩展。
// Register the DLL for context menu extension.
STDAPI DllRegisterServer()
{
    return Win11ContextMenuDemo::InstallContextMenu::InstallContextMenu();
}

// 注销 DLL。
// Unregister the DLL.
STDAPI DllUnregisterServer()
{
    return Win11ContextMenuDemo::InstallContextMenu::UnInstallContextMenu();
}

// 返回一个类工厂以创建对象的实例。
// Returns a class factory to create an object's instance.
_Use_decl_annotations_ STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) try
{
    *ppv = nullptr;

    if (rclsid == __uuidof(Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand))
    {
        // 如果请求的是 MainExplorerCommand 的类工厂，则创建并返回。
        // Create and return the class factory if MainExplorerCommand is requested.
        return winrt::make<Win11ContextMenuDemo::ClassFactory::COMClassFactory<Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand>>().as(riid, ppv);
    }
    else
    {
        // 如果没有可用的类，则返回错误。
        // Return an error if the class is not available.
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}
catch (...)
{
    // 捕获并处理任何异常。
    // Catch and handle any exceptions.
    return winrt::to_hresult();
}

// 检查是否可以注销 DLL。
// Check whether the DLL can be unloaded.
__control_entrypoint(DllExport) STDAPI DllCanUnloadNow()
{
    // 检查是否有活动的对象或类工厂。
    // Check for active objects or class factories.
    if (winrt::get_module_lock())
    {
        // 如果有，则不能注销。
        // Cannot unload if there are.
        return S_FALSE;
    }
    else
    {
        // 如果没有，则可以注销。
        // Can unload if there are none.
        return S_OK;
    }
}
