/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-20 00:46:56
 * @FilePath: \Win11ContextMenuDemo\Win11ContextMenuDemo\MainExplorerCommand.cpp
 */
#include "pch.h"
#include "MainExplorerCommand.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

// 全局变量，用来存储 DLL 模块的句柄。
// Global variable to store the handle of the DLL module.
extern HMODULE g_module; 

MainExplorerCommand::MainExplorerCommand() {
    SetTitleResourceID(ID_WIN11CONTEXTMENUDEMO_MAIN);
    SetIconFileName(L"\\Assets\\MainIcon.ico");
}

IFACEMETHODIMP MainExplorerCommand::Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept try {
    UNREFERENCED_PARAMETER(pbc);

    if (!psiItemArray) {
        return S_OK;
    }

    DWORD itemCount = 0;
    HRESULT hr = psiItemArray->GetCount(&itemCount);
    if (FAILED(hr)) {
        return hr;
    }

    if (itemCount == 0) {
        return S_OK;
    }

    if (itemCount > 10) {
        MessageBoxW(nullptr, L"外发报备不能超过十个文件", L"提示", MB_OK | MB_ICONWARNING);
        return S_OK;
    }

    static std::wstring appPath;
    if (appPath.empty()) {
        wchar_t buf[MAX_PATH] = { 0 };
        GetModuleFileNameW(g_module, buf, MAX_PATH);
        PathRemoveFileSpecW(buf);
        appPath = buf;
        appPath += L"\\wenshu.exe";
    }

    std::wstring fileNames;
    for (DWORD i = 0; i < itemCount; ++i) {
        CComPtr<IShellItem> shellItem;
        hr = psiItemArray->GetItemAt(i, &shellItem);
        if (FAILED(hr)) {
            return hr;
        }

        PWSTR filePath = nullptr;
        hr = shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
        if (SUCCEEDED(hr)) {
            fileNames += L"\"";
            fileNames += filePath;
            fileNames += LR"("|)";
            CoTaskMemFree(filePath);
        }
    }

    if (!fileNames.empty()) {
        fileNames.pop_back();
        
        HINSTANCE hInstance = ShellExecuteW(nullptr, L"open", appPath.c_str(), (L"-f " + fileNames).c_str(), nullptr, SW_SHOWNORMAL);
        if ((INT_PTR)hInstance <= 32) {
            return HRESULT_FROM_WIN32(GetLastError());
        }
    }

    return S_OK;
}
CATCH_RETURN();


IFACEMETHODIMP MainExplorerCommand::GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip) {
    UNREFERENCED_PARAMETER(psiItemArray);
	*ppszInfotip = (LPWSTR)L"test MainExplorerCommand";
	return S_OK;
}

IFACEMETHODIMP MainExplorerCommand::GetCanonicalName(GUID* pguidCommandName) {
	*pguidCommandName = GUID_NULL;
	return S_OK;
}
