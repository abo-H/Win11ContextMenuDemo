/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: HB
 * @LastEditTime: 2025-03-20 11:16:39
 * @FilePath: /wenshuextW11/wenshuextW11/MainExplorerCommand.h
 */
#pragma once
#include "pch.h"
#include "BaseExplorerCommand.h"

namespace wenshuextW11::ExplorerCommand {
    // MainExplorerCommand 是用于实现主菜单的类，继承自 BaseExplorerCommand。
    // MainExplorerCommand is a class used to implement the main menu, inheriting from BaseExplorerCommand.
    class __declspec(uuid("5E2121EE-0300-11D4-8D3B-444553540000")) MainExplorerCommand : public BaseExplorerCommand {
    public:
        // 构造函数。
        // Constructor.
        MainExplorerCommand();

        IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;

        IFACEMETHODIMP GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip) override;

        IFACEMETHODIMP GetCanonicalName(GUID* pguidCommandName) override;
    };
}
