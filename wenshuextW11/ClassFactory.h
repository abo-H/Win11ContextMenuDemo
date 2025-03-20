#pragma once
#include "pch.h"

namespace wenshuextW11::ClassFactory
{
    // COMClassFactory 是一个模板类，用于实现 IClassFactory 接口。
    // COMClassFactory is a template class for implementing the IClassFactory interface.
    template<class T>
    struct COMClassFactory : winrt::implements<COMClassFactory<T>, IClassFactory>
    {
        // CreateInstance 用于创建 COM 对象的实例。
        // CreateInstance is used to create an instance of a COM object.
        IFACEMETHODIMP CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override try
        {
            *ppvObject = nullptr;

            // 如果 pUnkOuter 不是 null，则表示请求聚合，COM 规范不允许这样做。
            // If pUnkOuter is not null, it indicates a request for aggregation, which is not allowed in COM.
            if (pUnkOuter)
            {
                return CLASS_E_NOAGGREGATION;
            }

            // 使用 winrt::make 创建 COM 对象并返回相应的接口。
            // Use winrt::make to create the COM object and return the requested interface.
            return winrt::make<T>().as(riid, ppvObject);
        }
        catch (...)
        {
            // 捕获所有异常，并将它们转换为合适的 HRESULT。
            // Catch all exceptions and convert them to an appropriate HRESULT.
            return winrt::to_hresult();
        }

        // LockServer 用于增加或减少服务器的锁定计数。
        // LockServer is used to increment or decrement the lock count of the server.
        IFACEMETHODIMP LockServer(BOOL) noexcept override
        {
            // 通常用于控制 DLL 是否可以被注销，这里简单返回 S_OK。
            // Usually used to control whether the DLL can be unloaded, here we simply return S_OK.
            return S_OK;
        }
    };
}
