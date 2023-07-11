# archLinux安装记录

<!--按照知乎 南风璇 的教程操作--> 

## 基于wsl的arch

### 启用wsl

首先，按Win + S搜索启用或关闭Windows功能（Turn Windows features on or off）,打开虚拟机平台和WSL，并重启Windows。

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662364285892.png)

重启后，进入Windows设置，检查更新。

更新完成后，进入Power Shell，执行：

```bash
wsl --set-default-version 2
```

这样可以将默认WSL版本设置为WSL2。

### 下载Arch Linux

到清华大学TUNA开源镜像站下载Arch Linux：

[Index of /archlinux/iso/latest/ | 清华大学开源软件镜像站 | Tsinghua Open Source Mirror](https://mirrors.tuna.tsinghua.edu.cn/archlinux/iso/latest/)

下载archlinux-bootstrap-xxxx.xx.xx-x86_64.tar.gz，注意是**tar.gz**文件。

### 安装Arch Linux

在GitHub下载LxRunOffline，[Releases · DDoSolitary/LxRunOffline](https://link.zhihu.com/?target=https%3A//github.com/DDoSolitary/LxRunOffline/releases)，选mingw或msvc版本均可。

1. 在你想要安装Linux的位置**创建一**个目录，我这里选择D:\Arch。

2. 将刚才**下载好的tar.gz放进D:\Arch**

3. 将**LxRunOffline解压好也放进D:\Arch**

4. 在D:\Arch文件夹空白位置，右击，**打开Power Shell**。

5. 在Power Shell中，输入：

   ```bash
   .\LxRunOffline i -n Arch -f archlinux-bootstrap-2022.05.01-x86_64.tar.gz -d D:\Arch -r root.x86_64
   ```

   -n后面跟一个系统名称，可自取。

   -f后面跟上你下载的Arch Linux压缩包，注意日期。

   -d后面跟上你的安装目录。

6. 在Power Shell中，输入：

```bash
wsl --set-version Arch 2
```

​	Arch是你起的系统名，将Arch设为WSL2。

### 进入Arch Linux

1. 进入Power Shell，输入

```bash
wsl -d Arch
```

2. 删除/etc/resolv.conf

```bash
rm /etc/resolv.conf
```

3. 退出，回到Power Shell

```bash
exit
```

4. 重启Arch Linux

```bash
wsl --shutdown Arch
wsl -d Arch
```

5. 添加清华Tuna源,打开pacman配置

```bash
cd /etc/
explorer.exe .
```

​		打开pacman.conf，在文件末尾添加：

```bash
[archlinuxcn]
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
```

6. cd到下一级目录pacman.d，编辑mirrorlist，取消注释掉China的两个清华Tuna源链接，当然也可以取消注释所有链接。

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662364313906.png)

7. 回到Arch Linux，执行

```bash
pacman -Syy
pacman-key --init
pacman-key --populate
pacman -S archlinuxcn-keyring
```

8. 安装基础软件

```bash
pacman -S base base-devel vim git wget curl
```

### 创建Linux账号

在Arch Linux中

1. 给root加密码：

```bash
passwd
```

2. 新建普通用户

```bash
useradd -m -G wheel -s /bin/bash 用户名
passwd 用户名
```

3. 给用户提权。编辑/etc/sudoers

```bash
vim /etc/sudoers
```

​	将`wheel ALL=(ALL) ALL`取消注释，保存并退出。

4. 查看当前id

```bash
id -u 用户名
```

​	记录下账号id

5. 退出Arch Linux，回到Power Shell

```bash
exit
```

6. 执行

```bash
.\LxRunOffline su -n Arch -v 账户id
```

​	-n后面跟WSL虚拟机的名字，我的是Arch。

​	这样，下一次登录会自动进入刚创建的用户。

### 语言本地化   方法一

1. 编辑/etc/locale.gen

```bash
vim /etc/locale.gen
```

​	将en_US.UTF8 UTF-8和zh_CN.UTF8 UTF-8取消注释，如果需要其他语言，请一并取消注释。

2. 执行

```bash
locale-gen 
locale
locale -a
```

3. 编辑/etc/locale.conf

```bash
vim /etc/locale.conf
```

​	添加如下内容

```bash
# /etc/locale.conf
LANG=en_US.UTF-8
```

重启Arch Linux，即可完成配置

### 语言本地化   方法二（设置 Locale 进行本地化）

Locale 决定了地域、货币、时区日期的格式、字符排列方式和其他本地化标准。

1. 编辑 /etc/locale.gen，去掉en_US.UTF-8 所在行以及 zh_CN.UTF-8 所在行的注释符号（#）。

2. 然后使用如下命令生成 locale。

​		`locale-gen`

3. 向 /etc/locale.conf 导入内容

​		`echo 'LANG=en_US.UTF-8'  > /etc/locale.conf`

#### 终端显示中文！！

在 `~/.bashrc`里单独设置中文 locale，即添加下面两行到文件的**最开头**

```
export LANG=zh_CN.UTF-8
export LANGUAGE=zh_CN:en_US
```

### 安装Neovim

1. 进入Arch Linux，执行：

```bash
sudo pacman -S neovim
```

2. 安装配套软件：gcc/g++/gdb

```bash
sudo pacman -S gcc gdb
```

3. Python

```bash
sudo pacman -S python
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
pip install neovim
```

4. Node.js

```bash
sudo pacman -S nodejs npm
npm install neovim
```

5. 用Neovim替代Vim,如果你装了zsh，编辑~/.zshrc，若没装，编辑~/.bashrc。

```bash
alias vi='vim'
alias vim='nvim'
```



## Neovim

 ### 配置Neovim基本选项

1. 在Arch Linux的用户根目录~中，建立如下目录结构：

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662364333540.png)

```bash
cd ~
mkdir .config && cd .config
mkdir nvim && cd nvim
mkdir lua && cd lua
mkdir user && cd user
mkdir conf dap lsp
```

2. 在nvim文件夹下新建init.lua，在user文件夹下新建options.lua。

编辑init.lua，编写加载程序：

```bash
require "user.options"
```

​	保存并退出。

3. 编辑options.lua，编写基本配置：

```
local options = {
    cmdheight = 1,
    showmode = true, --右下角显示模式
    conceallevel = 0,
    termguicolors = true, --如果安装第三方主题，必须设置为true
    mouse = 'a', --允许鼠标
    fileencoding = 'utf-8', --utf8编码
    ignorecase = true, --查找时忽略大小写
    smartcase = true, --智能大小写
    smartindent = true, --智能锁进
    cindent = true,
    autoindent = true, --自动缩进
    tabstop = 4, --Tab宽度
    shiftwidth = 4, --每次Shift调整的缩进
    number = true, --行号
    relativenumber = true, --相对行号
    showtabline = 2,
    wrap = false, --不自动换行
    cursorline = true, --高亮当前行
    cursorcolumn = false, --不高亮当前列
    showcmd = true, --右下角显示命令
}
--这里只列举基础的配置，更多选项可以在Vim中:set all查询

--应用上面配置
vim.opt.shortmess:append 'c'
for k, v in pairs(options) do
    vim.opt[k] = v
end

vim.cmd "set whichwrap+=<,>,[,],h,l"

--WSL与Windows同步剪贴板
vim.cmd([[
let g:clipboard = {
	\   'name': 'win32yank-wsl',
	\   'copy': {
	\      '+': 'win32yank.exe -i --crlf',
	\      '*': 'win32yank.exe -i --crlf',
	\    },
	\   'paste': {
	\      '+': 'win32yank.exe -o --lf',
	\      '*': 'win32yank.exe -o --lf',
	\   },
	\   'cache_enabled': 0,
	\ }
]])
```

### 按键映射

由于我的键盘可以更改键位，所以我选择不进行按键映射，如果需要设置按键映射，可以进入南风璇的文章

[现代Neovim配置-(2)-按键映射 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/532486519)

### 插件管理

在Neovim中，推荐使用基于Lua的[Packer](https://link.zhihu.com/?target=https%3A//github.com/wbthomason/packer.nvim)作为插件管理器。

1.安装Packer

```bash
git clone --depth 1 https://github.com/wbthomason/packer.nvim\
 ~/.local/share/nvim/site/pack/packer/start/packer.nvim
```

2. 安装插件

​	在~/.config/nvim/lua/user下创建plugins.lua。

​	编辑~/.config/nvim/init.lua，追加：`require 'user.plugins'`

​	编辑plugins.lua，添加：

```
return require('packer').startup(function()
    	use 'wbthomason/packer.nvim'
	
end)
```

​	在function()和end之间添加你需要的插件：

​	比如安装One Dark主题：

```
return require('packer').startup(function()
    use 'wbthomason/packer.nvim'
    use "navarasu/onedark.nvim"

end)
```

保存并退出，重新进入Neovim，执行命令：`:PackerSync`

3. 卸载插件

​	打开plugins.lua，将想要卸载的插件注释掉或删除掉。

退出并重新打开Neovim，执行：`:PackerClean`

4. 设置自动同步

​	我们不希望在安装插件的时候反复重启Neovim，可以在plugins.lua文件头部追加：

```
vim.cmd [[
	augroup packer_user_config
		autocmd!
		autocmd BufWritePost plugins.lua source <afile> | PackerSync
	augroup end
]]
```

​	这样每次保存plugins.lua文件时，Packer会自动同步插件，无需重启Neovim。

5. 浮窗显示Packer（这个功能我没有设置成功）

​	在plugins.lua中添加：

```
packer.init {
	display = {
		open_fn = function()
		    return require('packer.util').float { border = 'rounded' }
		end,
	}
}
```

## zsh（已完成，待编写）

### oh-my-zsh

### 插件

## netofetch

安装Neofetch并使用它在终端中显示系统信息

1. 安装

`sudo pacman -S netofetch`

2. 使用

`neofetch`

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662364363849.png)