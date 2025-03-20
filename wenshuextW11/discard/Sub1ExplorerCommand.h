#pragma once
#include "pch.h"
#include "BaseExplorerCommand.h"

namespace wenshuextW11::ExplorerCommand
{
    // Sub1ExplorerCommand 是一个实现子菜单的类，继承自 BaseExplorerCommand。
    // Sub1ExplorerCommand is a class that implements a submenu, inheriting from BaseExplorerCommand.
    class Sub1ExplorerCommand : public BaseExplorerCommand
    {
    public:
        // 构造函数。
        // Constructor.
        Sub1ExplorerCommand();

        // 执行子菜单的命令逻辑。
        // Execute the command logic of the submenu.
        IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;
    };
}
