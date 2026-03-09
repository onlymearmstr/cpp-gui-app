# C++ GUI Application

一个使用Qt框架开发的C++图形用户界面应用程序，支持通过GitLab CI/CD进行云编译。

## 功能特性

- 现代化的图形用户界面
- 文本输入和处理功能
- 字符串反转功能
- 点击计数器
- 清空功能
- 美观的UI设计

## 技术栈

- **C++17**
- **Qt 6.6.1**
- **CMake 3.16+**
- **GitLab CI/CD** (用于云编译)

## 本地编译

### 前置要求

- CMake 3.16 或更高版本
- Qt 6.6.1 或更高版本
- C++17 兼容的编译器 (MSVC 2022, GCC, Clang)

### 编译步骤

#### Windows (使用 Visual Studio)

```bash
# 1. 安装Qt
# 下载并安装Qt 6.6.1: https://www.qt.io/download

# 2. 配置环境变量
# 设置 Qt6_DIR 指向 Qt 安装路径，例如：
# set Qt6_DIR=C:\Qt\6.6.1\msvc2022_64\lib\cmake\Qt6

# 3. 生成项目
cmake -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:\Qt\6.6.1\msvc2022_64"

# 4. 编译
cmake --build build --config Release

# 5. 运行
.\build\Release\CppGuiApp.exe
```

#### Linux / macOS

```bash
# 1. 安装依赖
# Ubuntu/Debian:
sudo apt-get update
sudo apt-get install qt6-base-dev cmake build-essential

# macOS (使用 Homebrew):
brew install qt@6 cmake

# 2. 生成项目
cmake -B build -DCMAKE_PREFIX_PATH="/path/to/Qt/6.6.1/gcc_64"

# 3. 编译
cmake --build build

# 4. 运行
./build/CppGuiApp
```

## 云编译 (GitLab CI/CD)

### 前置要求

在GitLab中使用CI/CD，需要配置GitLab Runner。参考教程：[GitLab CI/CD配置指南](https://www.cnblogs.com/newton/p/14035169.html)

### Runner配置

#### 获取GitLab Runner认证Token

GitLab 15.6+版本使用新的认证方式：

1. **登录GitLab**并进入您的项目
2. **导航到** Settings > CI/CD > Runners
3. **点击** "New project runner" 按钮
4. **选择** Runner的操作系统和标签
5. **点击** "Create runner" 按钮
6. **复制**显示的认证token（**重要**：token必须以 `glrt-` 开头，不是 `glpat-`）
7. **注意**：不要使用Personal Access Token（glpat-开头），那个不适用于Runner注册

**正确的token格式示例**：`glrt-xxxxxxxxxxxx`
**错误的token格式**：`glpat-xxxxxxxxxxxx`（这是Personal Access Token，不能用于Runner注册）

#### 安装GitLab Runner (Docker方式)

```powershell
# 1. 拉取并运行GitLab Runner容器
docker run -d --name gitlab-runner --restart always -v /srv/gitlab-runner/config:/etc/gitlab-runner -v /var/run/docker.sock:/var/run/docker.sock gitlab/gitlab-runner:latest

# 2. 注册Runner（使用上面获取的token）
docker exec -it gitlab-runner gitlab-runner register

# 按提示输入：
# - GitLab instance URL: https://gitlab.com/
# - Authentication token: 粘贴上面复制的token（glrt-xxxxxxxxxxxx）
# - Runner description: Docker Runner for CppGuiApp
# - Tags: windows,docker
# - Executor: docker
# - Default Docker image: mcr.microsoft.com/windows/servercore:ltsc2022
```

#### 安装GitLab Runner (Windows本地方式)

```powershell
# 1. 下载并安装GitLab Runner
# 从 https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-windows-amd64.exe 下载
# 将文件重命名为 gitlab-runner.exe 并放到 C:\GitLab-Runner\ 目录

# 2. 注册Runner
cd C:\GitLab-Runner
.\gitlab-runner.exe register

# 按提示输入：
# - GitLab instance URL: https://gitlab.com/
# - Authentication token: 从GitLab项目设置中获取（glrt-xxxxxxxxxxxx）
# - Runner description: Windows Runner for CppGuiApp
# - Tags: windows,shell
# - Executor: shell
```

#### 安装GitLab Runner (Linux)

```bash
# 1. 添加GitLab Runner仓库
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash

# 2. 安装GitLab Runner
sudo apt-get install gitlab-runner

# 3. 注册Runner
sudo gitlab-runner register
```

### 自动编译

将代码推送到GitLab仓库后，GitLab CI/CD会自动触发编译流程：

1. **触发条件**:
   - 推送到 `main` 或 `master` 分支
   - 创建标签 (tag)
   - 合并请求

2. **查看构建状态**:
   - 进入GitLab仓库的 "CI/CD" -> "Pipelines" 标签页
   - 查看各个阶段的构建状态

3. **下载编译产物**:
   - 在Pipeline页面点击对应的构建任务
   - 在右侧 "Job artifacts" 部分下载 `CppGuiApp-Windows.zip`

### Pipeline说明

CI/CD流程包含两个阶段：

1. **build阶段**: 编译C++程序
   - Windows: 使用MSVC 2022编译器
   - Linux: 使用GCC 11编译器

2. **package阶段**: 打包应用程序
   - 复制所有Qt依赖DLL
   - 创建可分发的zip压缩包

### 创建发布版本

如果需要创建发布版本：

```bash
# 1. 创建并推送标签
git tag v1.0.0
git push origin v1.0.0

# 2. GitLab CI/CD会自动构建并上传产物
# 3. 可以手动创建Release并关联编译产物
```

## 项目结构

```
.
├── main.cpp              # 主程序源代码
├── CMakeLists.txt        # CMake构建配置
├── .gitlab-ci.yml        # GitLab CI/CD配置文件
└── README.md             # 项目说明文档
```

## 使用说明

1. **启动程序**: 双击运行 `CppGuiApp.exe`
2. **输入文字**: 在输入框中输入任意文字
3. **点击按钮**: 点击"点击我"按钮查看处理结果
4. **清空内容**: 点击"清空"按钮重置所有内容

## 功能演示

程序会显示：
- 输入的文字内容
- 字符数量统计
- 反转后的字符串
- 点击次数统计

## 许可证

MIT License

## 贡献

欢迎提交Issue和Pull Request！

## 联系方式

如有问题，请提交Issue。