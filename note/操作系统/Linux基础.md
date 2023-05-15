# 设备

## 本地wsl

普通用户：beichen
密码：2002
普通用户：liuhao
密码：2002
root用户：root
root密码：LiuHao2002

## vmware
虚拟机：ubuntu22

用户：beichen
密码：2002

用户：root
密码：LiuHao2002

用户：liuhao
密码：2002

## 配置
zsh+oh-my-zsh（主题），vim+spaceVim

C/C++环境

## 腾讯云
账号：微信
密码LiuHao2002

## 云服务器
普通用户：lighthouse（腾讯云面板登录用户），ubuntu（默认普通用户）
root用户：root
密码2002
登录密码：LiuHao2002
### 配置
#### 旧的配置 
vim+spacevim(c++,)
C/C++环境，Rust环境
#### 新的配置
由于在服务器上一般没有root权限，所以只能进行简单的配置
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1676107785468.png)
## 新云服务器

华为云

创建普通用户
[(61条消息) linux创建新用户_linux创建用户_普通网友的博客-CSDN博客](https://blog.csdn.net/web13170611647/article/details/126423088?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167772261316800211586526%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167772261316800211586526&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-126423088-null-null.142^v73^control,201^v4^add_ask,239^v2^insert_chatgpt&utm_term=linux%E6%96%B0%E5%BB%BA%E6%99%AE%E9%80%9A%E7%94%A8%E6%88%B7&spm=1018.2226.3001.4187)
root LiuHao2002
beichen 2002

# ssh软件

## FinaShell（基于java，性能不行）
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1674258863989.png)
用户名是ubuntu
密码是LiuHao2002
## xshell

# vi

## space vim
[SpaceVim: 模块化 Vim IDE，支持多种语言开发 (gitee.com)](https://gitee.com/spacevim/SpaceVim?_from=gitee_search)
开发手册-中文版
[开发者文档 | SpaceVim](https://spacevim.org/cn/development/)


## fast和space比较
fast有国内仓库，安装方便，并且足够使用
## wsl/虚拟机中vim无法复制到windows剪贴板
解决办法
```$ vim --version | grep "clipboard"
-clipboard         +keymap            +printer           +vertsplit
+emacs_tags        +mouse_gpm         -sun_workshop      -xterm_clipboard
```

```No +clipboard?
Vim requires the +clipboard feature flag for any of this to work; you can check if your Vim has this by using :echo has('clipboard') from within Vim (if the output is 0, it's not present, if it's 1, it is), or checking the output of vim --version for +clipboard.

Most Linux distributions ship with a "minimal" Vim build by default, which doesn't have +clipboard, but you can usually install it:

Debian & Ubuntu: Install vim-gtk3.

```

安装vim-gtk3
`sudo apt-get install vim-gtk`

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1ba3c8c2710c499f454b2dff045c861.jpg)

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/8986cc588d20f1f93ad6db58b1287cb.jpg)


# 工作流程
windows ob(vim模式)笔记git到gitee

vm本地操作，编码，调试等(vscode、vim)

ssh 到云服务器部署(vim)



# gcc、make、cmake区别

[关于gcc、make和CMake的区别 - 我得去图书馆了 - 博客园 (cnblogs.com)](https://www.cnblogs.com/xuelisheng/p/9988626.html)
程序员写：CMakeLists.txt

CMake：CMakeLists.txt -> makefile

make:   makefile + gcc + 代码 ->运行程序

# 更新命令

sudo apt-get update: 升级安装包相关的命令,刷新可安装的软件列表(但是不做任何实际的安装动作)

sudo apt-get upgrade: 进行安装包的更新(软件版本的升级)

sudo apt-get dist-upgrade: 进行系统版本的升级(Ubuntu版本的升级)

sudo do-release-upgrade: Ubuntu官方推荐的系统升级方式,若加参数-d还可以升级到开发版本,但会不稳定

sudo apt-get autoclean: 清理旧版本的软件缓存

sudo apt-get clean: 清理所有软件缓存

sudo apt-get autoremove: 删除系统不再使用的孤立软件

# git
## gitee账号
gitee
账号1（团队）
beichen2002
13644524465
密码
LiuHao2002
为了区分，使用edge登录gitee

不需要登录的linux
只需要对master分支进行维护

账号2（私人）
19904662993
liuhao-hub

密码
LiuHao2002
为了区分，使用谷歌浏览器登录gitee

linux配置
刘昊的vm/刘昊的wsl
1522375287@qq.com

## git基础操作

```shell
git config --global user.name “github’s Name”
git config --global user.email "github@xx.com"
git config --list
//切换到main分支
git checkout main
//拉取
git pull
//暂存
git add .
//添加到缓冲区
git commit -m "注释"
//推送
git push
```

### 查看当前状态
使用这个命令查看你都做了那些修改
` git status `
### 将工作区的修改提交到缓存区 
`git add .` 或者
` git add XXX `
### 提交缓存区代码到本地git库
`git commit -m "提交说明" `
### 取回主机某个分支的更新，与本地的指定更新分支合并
` git pull <远程主机名> <远程分支> ``
### 提交代码到云存储
` git push `



## 修改git配置文件的方法

`vi ~/.gitconfig`

## git冲突

遇到了下面的问题：

```
Please, commit your changes or stash them before you can merge.
```
这是因为本地代码和远程代码有冲突，解决方法如下:
### 方法1：stash

```
git stash
git pull
git stash pop
```

**git stash:**

备份当前的工作区的内容，从最近的一次提交中读取相关内容，让工作区保证和上次提交的内容一致。同时，将当前的工作区内容保存到Git栈中。  
也就是说能够将所有未提交的修改（工作区和暂存区）保存至堆栈中，用于后续恢复。

**git pull：**

将远程代码更新下来

**git stash pop:**

从Git栈中读取最近一次保存的内容，恢复工作区的相关内容。由于可能存在多个Stash的内容，所以用栈来管理，pop会从最近的一个stash中读取内容并恢复。

接下来diff一下此文件看看自动合并的情况，并对有冲突的代码进行选择并作出相应修改。

修改完后再将代码提交到远程仓库。

备注：

**git stash list:**

显示Git栈内的所有备份，可以利用这个列表来决定从那个地方恢复。

**git stash clear:**

清空Git栈。此时使用gitg等图形化工具会发现，原来stash的哪些节点都消失了。

### 方法2：

放弃本地修改的代码，直接覆盖为远程的代码。

```
git reset --hard
git pull
```
# linux和windows的区别
## Socket

[socket编程在windows和linux下的区别 - jlins - 博客园 (cnblogs.com)](https://www.cnblogs.com/dyllove98/archive/2013/06/23/3151162.html)

## 静态库



以一下文件结构为例
a.h 
a.cpp
staticlib.cpp
### 首先编译源文件
注意：只需要编译源文件，头文件不需要包含
code：` g++ -c a.cpp staticlib.cpp `
### 将汇编语言创建为库
#### 方法一
命名格式：以lib开头
' ar crv libmystaticlib.a a.o staticlib.o '
### 查看库中的符号(函数、全局变量）
` nm libmystaticlib.a `

### 创建main.cpp使用
1. 将a.h和libmystaticlib.a放到目录中（可以不复制过来，只不过包含比较麻烦）
2. 包含头文件 ` a.h `
3. 导入依赖库 ` #pragma comment (lib,"libmystaticlib.a") `

### 链接，运行
1. -L指定库所在的存储位置
2. -l指定库的名称，不用写前面的lib和后面的.a
` g++ -o main main.cpp -L. -lmystaticlib `