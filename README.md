# DD_Engine

一个用 C++20 和 Vulkan 构建的渲染引擎。Sandbox 是引擎功能的运行入口，每完成一项功能，就能在这里独立验证它。

## 构建与运行

Windows 的 `vs2026` 预设使用 Visual Studio 2026 的 C++ 工具链、Vulkan SDK 1.3 或更新版本，以及 CMake 4.2 或更新版本。如果 `PATH` 里的 CMake 版本更旧，可以在仓库根目录用 PowerShell 调用 Visual Studio 自带的 CMake。

```powershell
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$vsInstall = & $vswhere -latest -version '[18.0,19.0)' -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
$vsCmake = Join-Path $vsInstall 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'

& $vsCmake --preset vs2026
& $vsCmake --build --preset debug
.\out\build\vs2026\apps\sandbox\Debug\dd_sandbox.exe
```

Sandbox 会打印 Vulkan Loader 版本，用于验证 CMake 找到 SDK、程序完成链接，以及当前环境可以调用 Vulkan。后续的设备探测会单独检查 GPU 的 Vulkan 版本和功能支持。

## 目录与职责

| 目录 | 职责 |
| --- | --- |
| `apps/sandbox/` | 组装引擎模块，运行开发中需要验证的功能。 |
| `engine/vulkan/` | 直接调用 Vulkan。实例、设备、交换链、命令提交和 GPU 资源的生命周期在这里实现。 |

当前依赖方向为 `dd_sandbox` → `dd::vulkan` → `Vulkan::Vulkan`。引擎模块各自提供 CMake target，跨模块依赖通过 `target_link_libraries` 声明。调用方可用的头文件放在 `include/dd/<模块名>/`，模块的实现和内部头文件放在 `src/`。

## 后续模块的落点

| 目录 | 启用时机与职责 |
| --- | --- |
| `engine/platform/` | 开始窗口清屏时加入。负责窗口、事件循环和 Vulkan Surface 创建所需的窗口系统接入。 |
| `engine/renderer/` | 开始绘制时加入。负责帧渲染流程和绘制组织，通过 `dd::vulkan` 使用 GPU。 |
| `shaders/` | 加入第一个图形管线时创建。存放 shader 源码，编译产物进入构建目录。 |

Sandbox 负责组装窗口和渲染所需的模块。Vulkan 模块独立于 Sandbox 和窗口库，平台接入时由调用方提供实例所需的扩展及创建 Surface 所需的窗口信息。
