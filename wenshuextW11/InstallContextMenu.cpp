/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-19 23:41:42
 * @FilePath: \wenshuextW11\wenshuextW11\InstallContextMenu.cpp
 */
#include "pch.h"
#include "InstallContextMenu.h"
#include "Windows11Checker.h"
#include "Path.h"
#include "RegistryController.h"
#include "MainExplorerCommand.h"

using namespace wenshuextW11::RegistryController;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;


const wstring CONTEXTMENUNAME = L"wenshuextW11";
const wstring REGISTRYSHELLPATH = L"Software\\Classes\\*\\shell\\";
const wstring REGISTRYSHELLEXTENSIONPATH = L"Software\\Classes\\*\\shellex\\ContextMenuHandlers\\";
const wstring REGISTRYCLSIDPATH = L"Software\\Classes\\CLSID\\";
const wstring REGISTRYFILESHELLEXPATH = L"_file\\shellex";

// 获取特定的 Sparse Package。
// Gets a specific Sparse Package.
Package GetSparsePackage(PackageManager& packageManager)
{
	try
	{
		auto packages = packageManager.FindPackagesForUser(L"");

		for (const auto& package : packages)
		{
			if (package.Id().Name() == CONTEXTMENUNAME)
			{
				return package;
			}
		}
	}
	catch (const winrt::hresult_error& e)
	{
		throw runtime_error("Failed to find sparse package: " + winrt::to_string(e.message()));
	}

	return nullptr;
}

// 取消注册 Sparse Package。
// Unregisters the Sparse Package.
HRESULT UnRegisterSparsePackage()
{
	PackageManager packageManager;
	auto package = GetSparsePackage(packageManager);
	if (!package)
	{
		return S_FALSE;
	}

	winrt::hstring fullName = package.Id().FullName();
	auto deploymentOperation = packageManager.RemovePackageAsync(fullName, RemovalOptions::None);
	auto deployResult = deploymentOperation.get();

	if (!SUCCEEDED(deployResult.ExtendedErrorCode()))
	{
		return deployResult.ExtendedErrorCode();
	}

	return S_OK;
}

// 注册 Sparse Package。
// Registers the Sparse Package.
HRESULT RegisterSparsePackage()
{
	const wstring contextMenuDirectoryPath = wenshuextW11::Path::GetContextMenuDirectoryPath();
	const wstring sparsePackageFullPath = contextMenuDirectoryPath + L"\\" + CONTEXTMENUNAME + L".msix";

	Uri externalLocationUri(contextMenuDirectoryPath);
	Uri packageUri(sparsePackageFullPath);

	AddPackageOptions options;
	options.ExternalLocationUri(externalLocationUri);
	options.AllowUnsigned(true);

	PackageManager packageManager;
	auto deploymentOperation = packageManager.AddPackageByUriAsync(packageUri, options);
	auto deployResult = deploymentOperation.get();

	if (!SUCCEEDED(deployResult.ExtendedErrorCode()))
	{
		return deployResult.ExtendedErrorCode();
	}

	return S_OK;
}

// 执行注册 Sparse Package 的程序。
// Executes the procedure for registering the Sparse Package.
void RegisterSparsePackageProgram()
{
	winrt::init_apartment();
	UnRegisterSparsePackage();
	RegisterSparsePackage();
}

// 执行取消注册 Sparse Package 的程序。
// Executes the procedure for unregistering the Sparse Package.
void UnRegisterSparsePackageProgram()
{
	winrt::init_apartment();
	UnRegisterSparsePackage();
}

// 获取 COM 类别的 CLSID 字符串。
// Gets the CLSID string for a COM class.
wstring GetCLSIDString()
{
	const auto uuid = __uuidof(wenshuextW11::ExplorerCommand::MainExplorerCommand);
	LPOLESTR clsidString = nullptr;
	HRESULT result = StringFromCLSID(uuid, &clsidString);
	if (FAILED(result))
	{
		throw runtime_error("Failed to parse GUID to string");
	}
	wstring clsid(clsidString);
	CoTaskMemFree(clsidString);
	return clsid;
}

// 注册上下文菜单。
// Registers the context menu.
HRESULT RegisterContextMenu()
{
	const wstring clsid = GetCLSIDString();
	RegistryControllerClass regExtController(HKEY_LOCAL_MACHINE, REGISTRYSHELLPATH + CONTEXTMENUNAME, KEY_READ | KEY_WRITE, true);
	regExtController.SetStringValue(L"", CONTEXTMENUNAME + L" - Context menu Demo");
	regExtController.SetStringValue(L"ExplorerCommandHandler", clsid);
	regExtController.SetStringValue(L"NeverDefault", L"");

	RegistryControllerClass regClsidController(HKEY_LOCAL_MACHINE, REGISTRYCLSIDPATH + clsid, KEY_READ | KEY_WRITE, true);
	regClsidController.SetStringValue(L"", CONTEXTMENUNAME);

	RegistryControllerClass regInProcController = regClsidController.GetSubKey(L"InProcServer32", true);
	regInProcController.SetStringValue(L"", wenshuextW11::Path::GetContextMenuExecutableFullPath());
	regInProcController.SetStringValue(L"ThreadingModel", L"Apartment");

	return S_OK;
}

// 取消注册上下文菜单。
// Unregisters the context menu.
HRESULT UnRegisterContextMenu()
{
	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, REGISTRYSHELLPATH + CONTEXTMENUNAME))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, REGISTRYSHELLPATH + CONTEXTMENUNAME, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, REGISTRYSHELLEXTENSIONPATH + CONTEXTMENUNAME))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, REGISTRYSHELLEXTENSIONPATH + CONTEXTMENUNAME, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, CONTEXTMENUNAME + REGISTRYFILESHELLEXPATH))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, CONTEXTMENUNAME + REGISTRYFILESHELLEXPATH, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	const wstring clsid = GetCLSIDString();
	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, REGISTRYCLSIDPATH + clsid))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, REGISTRYCLSIDPATH + clsid, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	return S_OK;
}

HRESULT wenshuextW11::InstallContextMenu::InstallContextMenu()
{
	HRESULT result;

	if (wenshuextW11::Windows11Checker::IsWindows11())
	{
		UnRegisterContextMenu();

		thread registerSparsePackageProgramThread(RegisterSparsePackageProgram);
		registerSparsePackageProgramThread.join();
	}

	result = RegisterContextMenu();

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);

	return S_OK;
}

HRESULT wenshuextW11::InstallContextMenu::UnInstallContextMenu()
{
	HRESULT result;

	result = UnRegisterContextMenu();

	if (result != S_OK)
	{
		return result;
	}

	if (wenshuextW11::Windows11Checker::IsWindows11())
	{
		thread unRegisterSparsePackageThread(UnRegisterSparsePackageProgram);
		unRegisterSparsePackageThread.join();
	}

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);

	return S_OK;
}
