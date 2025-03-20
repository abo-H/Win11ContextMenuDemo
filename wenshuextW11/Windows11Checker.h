#pragma once
#include "pch.h"

namespace wenshuextW11::Windows11Checker
{
    // 检查当前操作系统是否为 Windows 11。
    // Returns true if the current operating system is Windows 11, false otherwise.
    // 此函数通过检查系统注册表中的版本号来判断操作系统版本。
    // This function determines the operating system version by checking the version number in the system registry.
    bool IsWindows11();
}
