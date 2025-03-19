/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-19 22:56:11
 * @FilePath: \Win11ContextMenuDemo\Win11ContextMenuDemo\MainExplorerCommand.cpp
 */
#include "pch.h"
#include "MainExplorerCommand.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

MainExplorerCommand::MainExplorerCommand() {
    SetTitleResourceID(ID_WIN11CONTEXTMENUDEMO_MAIN);
    SetIconFileName(L"\\Assets\\MainIcon.ico");
}

IFACEMETHODIMP MainExplorerCommand::Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept try {
    UNREFERENCED_PARAMETER(psiItemArray);
    UNREFERENCED_PARAMETER(pbc);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    wstring commandLine = L"cmd.exe /C echo Hello World by Sub1Win11ContextMenu. && pause;";
    if (!CreateProcessW(nullptr, (LPWSTR)commandLine.c_str(), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
    {
        return S_OK;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

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
