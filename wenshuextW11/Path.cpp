#include "pch.h"
#include "Path.h"

using namespace wenshuextW11::Path;

extern HMODULE g_module;

static const path GetModulePath(HMODULE moduleHandle)
{
    wchar_t pathBuffer[MAX_PATH] = { 0 };
    GetModuleFileNameW(moduleHandle, pathBuffer, MAX_PATH);
    return path(pathBuffer);
}

const wstring wenshuextW11::Path::GetAppDirectoryPath()
{
    return GetModulePath(g_module).parent_path().parent_path().wstring();
}

const wstring wenshuextW11::Path::GetContextMenuDirectoryPath()
{
    return GetModulePath(g_module).parent_path().wstring();
}

const wstring wenshuextW11::Path::GetContextMenuExecutableFullPath()
{
    return GetModulePath(g_module).wstring();
}

const wstring wenshuextW11::Path::GetCurrentExecutableName()
{
    wchar_t pathBuffer[FILENAME_MAX] = { 0 };
    GetModuleFileNameW(NULL, pathBuffer, FILENAME_MAX);
    PathStripPathW(pathBuffer);
    wstring moduleName(pathBuffer);
    transform(moduleName.begin(), moduleName.end(), moduleName.begin(), towlower);
    return moduleName;
}
