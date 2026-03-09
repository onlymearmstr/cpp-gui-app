# GitLab Runner配置指南

## 问题说明

您遇到的错误是因为使用了错误的token类型：
- ❌ **错误**：`glpat-fbkd983bqJxm1xUOIPClrm86MQp1Omt5MnNhCw.01.121p1nj5u`
- ✅ **正确**：`glrt-xxxxxxxxxxxx`

## Token类型说明

### 1. Personal Access Token (glpat-开头)
- 用于API访问、Git操作等
- **不能**用于GitLab Runner注册
- 在 User Settings > Access Tokens 中创建

### 2. Runner Authentication Token (glrt-开头)
- 专门用于GitLab Runner注册
- 在 Project Settings > CI/CD > Runners 中创建
- **这是注册Runner必须使用的token**

## 获取正确的Runner Token步骤

### 步骤1：登录GitLab并进入项目
```
https://gitlab.com/
```

### 步骤2：进入Runner设置
1. 点击左侧菜单 **Settings**
2. 选择 **CI/CD**
3. 向下滚动到 **Runners** 部分
4. 点击 **New project runner** 按钮

### 步骤3：配置Runner
1. **Select platform**: 选择您的操作系统（如 Linux, Windows, macOS）
2. **Tags**: 输入标签（如 `windows,docker` 或 `linux,shell`）
3. **Run untagged jobs**: 如果需要运行没有特定标签的job，可以勾选
4. **Protected**: 如果只允许在protected分支运行，可以勾选

### 步骤4：创建Runner
点击 **Create runner** 按钮

### 步骤5：复制Token
页面会显示一个以 `glrt-` 开头的token，例如：
```
glrt-abc123def456ghi789jkl012mno345pqr678
```

**复制这个token**（不要复制其他内容）

## 注册GitLab Runner

### 方法1：使用Docker（推荐）

```powershell
# 1. 运行GitLab Runner容器
docker run -d --name gitlab-runner --restart always `
  -v /srv/gitlab-runner/config:/etc/gitlab-runner `
  -v /var/run/docker.sock:/var/run/docker.sock `
  gitlab/gitlab-runner:latest

# 2. 注册Runner
docker exec -it gitlab-runner gitlab-runner register
```

注册时输入：
```
Enter the GitLab instance URL: https://gitlab.com/
Enter the authentication token: glrt-abc123def456ghi789jkl012mno345pqr678
Enter a description for the runner: My Windows Runner
Enter tags for the runner: windows,docker
Enter optional maintenance note for the runner: [直接回车]
Enter an executor: docker
Enter the default Docker image: mcr.microsoft.com/windows/servercore:ltsc2022
```

### 方法2：使用Windows本地安装

```powershell
# 1. 下载GitLab Runner
# 访问：https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-windows-amd64.exe
# 保存到：C:\GitLab-Runner\gitlab-runner.exe

# 2. 注册Runner
cd C:\GitLab-Runner
.\gitlab-runner.exe register
```

注册时输入：
```
Enter the GitLab instance URL: https://gitlab.com/
Enter the authentication token: glrt-abc123def456ghi789jkl012mno345pqr678
Enter a description for the runner: My Windows Runner
Enter tags for the runner: windows,shell
Enter optional maintenance note for the runner: [直接回车]
Enter an executor: shell
```

## 验证Runner注册

### 在GitLab中查看
1. 进入项目 > Settings > CI/CD > Runners
2. 在 "Project runners" 部分应该能看到您的Runner
3. Runner状态应该是绿色圆点（表示在线）

### 在本地查看
```powershell
# 查看Runner状态
docker exec -it gitlab-runner gitlab-runner verify

# 查看Runner列表
docker exec -it gitlab-runner gitlab-runner list
```

## 常见问题

### Q: 为什么不能用Personal Access Token？
A: Personal Access Token (glpat-) 用于API访问，而Runner注册需要专门的Runner Authentication Token (glrt-)，这是GitLab的安全机制。

### Q: Runner注册后显示为离线？
A: 检查以下几点：
1. Docker容器是否正在运行：`docker ps`
2. 网络连接是否正常
3. GitLab URL是否正确（https://gitlab.com/）

### Q: 如何删除已注册的Runner？
A: 在GitLab项目 > Settings > CI/CD > Runners 中，找到Runner并点击编辑图标，然后选择"Delete runner"

### Q: 如何重新注册Runner？
A:
1. 在GitLab中删除旧的Runner
2. 在GitLab中创建新的Runner并获取新的token
3. 在本地运行 `docker exec -it gitlab-runner gitlab-runner register` 重新注册

## 下一步

Runner注册成功后：
1. 将代码推送到GitLab仓库
2. CI/CD Pipeline会自动触发
3. 在 CI/CD > Pipelines 中查看构建状态
4. 构建完成后下载编译产物