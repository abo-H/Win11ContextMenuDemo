#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::RegistryController
{
    // RegistryControllerClass 用于访问和修改 Windows 注册表。
    // RegistryControllerClass is used for accessing and modifying the Windows registry.
    class RegistryControllerClass
    {
    public:
        // 构造函数初始化注册表控制器，可选择创建不存在的键。
        // Constructor initializes the registry controller, with an option to create the key if it does not exist.
        RegistryControllerClass(HKEY hKey, const wstring& subKey = L"", REGSAM access = KEY_READ, bool createIfMissing = false);

        // 析构函数确保注册表键被适当关闭。
        // Destructor ensures the registry key is properly closed.
        ~RegistryControllerClass();

        // 检查指定的注册表键是否存在。
        // Checks if a specified registry key exists.
        static bool KeyExists(HKEY hKey, const wstring& subKey);

        // 检查注册表中是否存在指定的值。
        // Checks if a specified value exists in the registry.
        bool ValueExists(const wstring& valueName) const;

        // 获取指定子键的 RegistryControllerClass 实例。
        // Retrieves a RegistryControllerClass instance for a specified subkey.
        RegistryControllerClass GetSubKey(const wstring& subKey, bool createIfMissing = false) const;

        // 获取 DWORD 类型的注册表值。
        // Retrieves a DWORD type registry value.
        DWORD GetDwordValue(const wstring& valueName);

        // 获取字符串类型的注册表值。
        // Retrieves a string type registry value.
        wstring GetStringValue(const wstring& valueName);

        // 设置 DWORD 类型的注册表值。
        // Sets a DWORD type registry value.
        void SetDwordValue(const wstring& valueName, DWORD value);

        // 设置字符串类型的注册表值。
        // Sets a string type registry value.
        void SetStringValue(const wstring& valueName, const wstring& value);

        // 删除当前操作的注册表键。
        // Deletes the currently operated registry key.
        void DeleteKey();
    private:
        // 打开或创建注册表键。
        // Opens or creates a registry key.
        void OpenOrCreateKey(HKEY hKey, const wstring& subKey, REGSAM access, bool createIfMissing);

        // 关闭注册表键。
        // Closes the registry key.
        void CloseKey();

        // 确保注册表键已打开。
        // Ensures the registry key is open.
        void EnsureKeyIsOpen() const;

        // 抛出 Windows API 最后一个错误的详细信息。
        // Throws detailed information about the Windows API last error.
        void ThrowLastError(const std::string& message) const;

        // 注册表键的句柄。
        // Handle to the registry key.
        HKEY m_hKey;

        // 访问注册表键的权限。
        // Access rights for the registry key.
        REGSAM m_regsam;

        // 原始注册表键的句柄。
        // Handle to the original registry key.
        HKEY m_originalHKey;

        // 原始子键路径。
        // Original subkey path.
        wstring m_originalSubKey;
    };
}
