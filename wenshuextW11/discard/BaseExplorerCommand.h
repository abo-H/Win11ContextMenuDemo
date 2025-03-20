/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: HB
 * @LastEditTime: 2025-03-20 15:46:15
 * @FilePath: /wenshuextW11/wenshuextW11/discard/BaseExplorerCommand.h
 */
#pragma once
#include "pch.h"
#include "resource.h"

namespace wenshuextW11::ExplorerCommand
{
    // BaseExplorerCommand 是一个基础类，用于实现 IExplorerCommand 接口。
    // BaseExplorerCommand is a base class for implementing the IExplorerCommand interface.
    class BaseExplorerCommand : public winrt::implements<BaseExplorerCommand, IExplorerCommand, IObjectWithSite>
    {
    protected:
       // 获取当前 Explorer 路径的方法。
       // This method retrieves the current Explorer path.
       virtual wstring GetCurrentExplorerPath();

        // 获取多语言标题的方法。
        // Method for obtaining the multi-language title.
        virtual const wstring GetMultiLanguageTitle();

        // 获取图标路径的方法。
        // Method for obtaining the icon path.
        virtual const wstring GetIconPath();

        // 用于存储标题资源 ID 的成员变量。
        // Member variable to store the title resource ID.
        UINT titleResourceID = ID_wenshuextW11_DEFAULT;

        // 用于存储图标文件名的成员变量。
        // Member variable to store the icon file name.
        wstring iconFileName = L"";

        // 用于存储 site 对象的 COM 指针。
        // COM pointer to store the site object.
        winrt::com_ptr<IUnknown> m_Site;
    public:
        // 设置 site 对象的方法。
        // Method to set the site object.
        virtual HRESULT SetSite(IUnknown* pUnkSite);

        // 获取 site 对象的方法。
        // Method to get the site object.
        virtual HRESULT GetSite(REFIID riid, void** ppvSite);

        // 设置标题资源 ID 的方法。
        // Method to set the title resource ID.
        virtual void SetTitleResourceID(UINT id);

        // 设置图标文件名的方法。
        // Method to set the icon file name.
        virtual void SetIconFileName(wstring fileName);

        // 获取命令的标题。
        // Get the title of the command.
        virtual IFACEMETHODIMP GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName);

        // 获取命令的图标。
        // Get the icon of the command.
        virtual IFACEMETHODIMP GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon);

        // 获取命令的工具提示。
        // Get the tooltip of the command.
        virtual IFACEMETHODIMP GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip);

        // 获取命令的状态。
        // Get the state of the command.
        virtual IFACEMETHODIMP GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState);

        // 获取命令的标志。
        // Get the flags of the command.
        virtual IFACEMETHODIMP GetFlags(EXPCMDFLAGS* flags);

        // 获取命令的标准名称。
        // Get the canonical name of the command.
        virtual IFACEMETHODIMP GetCanonicalName(GUID* pguidCommandName);

        // 枚举子命令。
        // Enumerate sub-commands.
        virtual IFACEMETHODIMP EnumSubCommands(IEnumExplorerCommand** ppEnum);

        // 执行命令的方法，必须由派生类实现。
        // The method to execute the command, which must be implemented by derived classes.
        IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;
    };
}
