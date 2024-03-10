机器寿命预测系统
===

[![Build status](https://ci.appveyor.com/api/projects/status/uro8lrsvb9q57326?svg=true)](https://ci.appveyor.com/project/WinterSquire/lifepredictionsystem)

---
### 一. 项目概要
该项目系统利用Qt构造交互界面和图学习、深度学习、大数据挖掘等前沿方法，以实现设备全生命周期的在线运行监测、分析、预测、预警、报警，重点锁定设
备的“健康和亚健康”阶段，保障设备的稳定健康运行，可大幅减少故障停机时间、提高设备寿命、降低维修成本。

### 二. 如何构建

#### 所需环境
- Python 3.9.x
- Cmake 3.26 and above
- Visual Studio 17 2022 | MSVC
- Qt 6.x | MSVC 2019 64-bit | Qt Charts

#### 环境变量
前两项变量根据自己的具体情况填写，最后一项的版本不要随意变更，否则会产生Python API兼容问题。
```
set QT6_PATH=C:\Qt\6.5.3\msvc2019_64
set PYTHON_PATH=C:\Python39-x64
set PYTHON_VERSION=39
```

#### 构建命令
在项目根目录下执行以下命令
```
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -D CMAKE_PREFIX_PATH=%QT6_PATH% -D PYTHON_DIR=%PYTHON_PATH% -D PYTHON_VER=%PYTHON_VERSION%
```
然后运行``./build/*.sln``项目进行编译即可

### 三. 如何运行
如果你是从[Appveyor](https://ci.appveyor.com/project/WinterSquire/lifepredictionsystem)中下载的，
在运行前检查一下是否有安装``vc_redist.x64``，然后在第一次运行前执行``install_package.bat``来安装Python Package。

> install_package.bat 一定要执行成功，如果执行失败，请检查运行路径是否超过了[最大路径长度限制](https://learn.microsoft.com/zh-cn/windows/win32/fileio/maximum-file-path-limitation?tabs=registry)。

如果你是自行构建的，还需在上面的基础上提前执行一次``install_python.ps1``来安装Python解释器。