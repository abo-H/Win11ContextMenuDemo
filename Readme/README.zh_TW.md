# Win11 Context Menu Demo
这是一个用于演示 Win11 右键现代菜单的项目，通过 IExplorerCommand 和 IEnumExplorerCommand 接口，结合 Sparse package 实现自定义的上下文菜单。
<br>
<br>

## 相关文章
 - [Windows 11 - 自定义右键菜单（IExplorerCommand 程序实现）](https://www.momochenisme.com/2023/12/windows11-custom-contextmenu-with-iexplorercommand-and-sparsepackage.html)
 - [Windows 11 - 自定义右键菜单（Sparse Package 实现）](https://www.momochenisme.com/2023/12/windows11-custom-contextmenu-with-iexplorercommand-and-sparsepackage-part2.html)
<br>
<br>

## 准备工具
为了开发此项目，需要准备以下工具：
- [Visual Studio 2022](https://visualstudio.microsoft.com/zh-hans/vs/whatsnew/)
- [Windows SDK](https://developer.microsoft.com/zh-cn/windows/downloads/windows-sdk/)
<br>
<br>

## 安装 NuGet 包
Visual Studio 2022 需要安装以下 NuGet 包：
- [Microsoft.Windows.CppWinRT](https://github.com/Microsoft/cppwinrt)
- [Microsoft.Windows.ImplementationLibrary](https://github.com/Microsoft/wil)
<br>
<br>

## 生成 Sparse package 流程
以下是生成 Sparse package 的步骤：

1. **准备好 Win11 自定义菜单 DLL**：
    确保您的 DLL 已经构建并准备好。

2. **准备 AppxManifest.xml**：
    创建并配置 AppxManifest.xml 文件，这是生成 Sparse package 的重要部分。

3. **生成 Sparse package**：
    使用以下命令生成 Sparse package：
     ```
     makeappx.exe pack /d <Your AppxPath> /p <Your AppxPath>\Win11ContextMenuDemo.msix
     ```

4. **创建自签名证书**：
使用 PowerShell 命令创建一个自签名的数字证书：
     ```
     New-SelfSignedCertificate -Type Custom -Subject "CN=MomoChenIsMe, C=CN" -KeyUsage DigitalSignature -FriendlyName "MomoChenIsMe" -CertStoreLocation "Cert:\CurrentUser\My" -TextExtension @("2.5.29.37={text}1.3.6.1.5.5.7.3.3", "2.5.29.19={text}")
     ```

5. **查看所有证书**：
通过以下命令查看所有证书：
     ```
     Set-Location Cert:\CurrentUser\My
     Get-ChildItem
     ```

6. **删除证书（如有需要）**：
如需删除某个证书，可使用以下命令：
     ```
     Remove-Item Cert:\CurrentUser\My\<Your Thumbprint>
     ```

7. **导出自签名证书**：
将自签名证书导出为 .pfx 文件：
     ```
     $password = ConvertTo-SecureString -String <Your Password> -Force -AsPlainText
     Export-PfxCertificate -cert "Cert:\CurrentUser\My\<Your Thumbprint>" -FilePath <Certificate FilePath>.pfx -Password $password
     ```

8. **签署 Sparse package**：
使用以下命令签署 Sparse package： 
     ```
     signtool.exe sign /fd SHA256 /a /f <Your AppxPath>\Win11ContextMenu.pfx /t http://timestamp.digicert.com /p <Your Password> <Your AppxPath>\Win11ContextMenuDemo.msix
     ```
     如果需要进入 debug 模式可以添加 `/debug` 参数。
<br>
<br>

## 注册 DLL
使用以下命令来注册 DLL：
```
regsvr32.exe <Your DLL Path>
```

使用以下命令来注销 DLL：
```
regsvr32.exe /u <Your DLL Path>
```
