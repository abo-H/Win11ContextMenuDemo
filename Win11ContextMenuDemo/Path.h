/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-19 23:40:36
 * @FilePath: \Win11ContextMenuDemo\Win11ContextMenuDemo\Path.h
 */
#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::Path
{
    // 获取应用程序所在目录的路径。
    // Retrieves the path of the directory where the application is located.
    const wstring GetAppDirectoryPath();

    // 获取上下文菜单相关文件所在目录的路径。
    // Retrieves the path of the directory where context menu related files are located.
    const wstring GetContextMenuDirectoryPath();

    // 获取上下文菜单可执行
    // Retrieves the full path of the context menu executable.
    const wstring GetContextMenuExecutableFullPath();

    // 获取当前执行模块的文件名。
    // Retrieves the file name of the currently executing module.
    const wstring GetCurrentExecutableName();
}
