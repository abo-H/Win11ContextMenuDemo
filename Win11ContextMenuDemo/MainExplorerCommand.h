/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-19 23:13:23
 * @FilePath: \Win11ContextMenuDemo\Win11ContextMenuDemo\MainExplorerCommand.h
 */
#pragma once
#include "pch.h"
#include "BaseExplorerCommand.h"

namespace Win11ContextMenuDemo::ExplorerCommand {
    // MainExplorerCommand 是用于实现主菜单的类，继承自 BaseExplorerCommand。
    // MainExplorerCommand is a class used to implement the main menu, inheriting from BaseExplorerCommand.
    class __declspec(uuid("15589FA6-768B-4826-97B8-D12DE265B3BB")) MainExplorerCommand : public BaseExplorerCommand {
    public:
        // 构造函数。
        // Constructor.
        MainExplorerCommand();

        IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;

        IFACEMETHODIMP GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip) override;

        IFACEMETHODIMP GetCanonicalName(GUID* pguidCommandName) override;
    };
}
