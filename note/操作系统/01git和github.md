# git和github

（2023/05/31）

## github的使用

github是工程托管网站，大量的企业项目工程和开源工程托管在这个网站中，开发者聚集地，大量的开源项目可以很好的帮助用户学习，或开发github是工程托管网站。

### 常用标签

Explore 探索标签

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542115604.png)

Topics 分类标签

Trending 推送

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542210197.png)

### 搜索关键词

绝对查询，通过特定的关键字搜索网站内容

- python *awesome*,检索有趣的内容
- socket *sample*,查找技术相关的样例
- go *tutorial*,查找资料相关

### 仓库

一个用户可以创建多个仓库，因为单一原则每个仓库保存一个工程。

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542508762.png)

#### 仓库里的标签

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542474498.png)

#### README.md

阅读文档，快速帮助用户了解工程和使用方式。

#### LICENSE-许可证

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542623715.png)

给使用者最大的权限以及最少的限制，高权限许可证常见的有
GPL 3.0
MIT许可证
APACHE 2.0
*企业使用开源项目一定要注意许可问题，避免法务问题*

## git

Gt软件，全称为分布式版本控制系统，用户使用此软件来访问和编辑仓库内容.
git的大致流程

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685543148394.png)

### git配置

#### 0.创建本地仓库

```bash
// 创建本地仓库
git init 

//查看配置文件
git config --list 

git config --global 键值

```

#### 1.账号关联，使用本地Git配置关联github的某个账号

原理：采用单向/认证双向认证与云端完成关联，本地生成身份数据串， 将其复制，粘贴到云端账号中 RSA(非对称加密算法)

1. 生成本地RSA密钥串

    ```bash
    ssh-keygen -t rsa -C 1522375287@qq.com
    ```

2. 按生成位置，打开id_rsa.pub文件，复制其中的密钥字符串

3. 打开网站头像下拉列表->Settings->SSH and GPG key->New ssh key,为密钥编写title标题，将刚刚拷贝的密钥串粘贴到下面空白位置，保存即可

4. 修改配置文件，查看配置文件

    ```bash
    git config --list
    ```

5. 添加修改配置文件

     ```bash
    git config --global user.name "用户名"  
    
    git config --global user.email "邮箱"
    ```

#### 2.为仓库起别名，将数据上传到指定仓库

1. 从网站中拷贝云端仓库的SSH地址

2. 将云端地址重命名
将云端地址重命名为origin，方便之后使用

    ```bash
    git remote add origin "云端仓库的ssh地址" 
    ```

3. 删除别名

    ```bash
    git remote remove origin
    ```

4. 测试是否连通

    ```bash
    ssh -T git@github.com
    ```

### git上传资源的过程

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685698679507.png)

### git结构（之前学的）

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1681570286213.png)

### git常用命令

```bash
//将本地数据、文件或文件夹添加到git缓冲区
git add Filename      
//提交到本地仓库                        
git commit -m "提交描述"

//上传本地仓库主分支到云端
//一次push可以推上去多个积压得commit
git push [remote] [branch]
//例如
git push origin master

//查看缓冲区状态
git status 

//在仓库中使用常规的rm只是删除本地

//可以从本地仓库找回，commit过的且rm了的
git restore filename
//删除本地文件，并删除本地仓库
git rm filename

git clone "想要下载的项目的http地址"
```

要删除云端数据
要先从本地删除，
本地删除后，同步到云端，
云端也就被删除

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685616102812.png)

同一文件不同时间的提交，时间戳不同
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685716537452.png "时间戳不同")

## git三要素

### 1.仓库

仓库：在github中仓库是项目的基本单位，是工程容器，每个开发者将自己的项目保存管理在一个仓库中，所有工程都是在仓库中管理编辑和发布

### 2.commit提交

因为某些原因导致云端仓库内容与本地仓库内容版本不一致，出现push失败，可以尝试先拉再推

```bash
git pull -rebase origin branchname
```
拉取云端分支与本地合并，保证一致性，而后尝试推

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685698997133.png)

#### commit的作用

1. 可以备份开发者关于代码的操作和统计修改。便于开发者回溯代码，只要开发者有良好的提交习惯，那么就可以找到任何时间节点的任何代码统计修改。
2. 可以通过提交观察一个项目的开发流程，便于了解开发者的思想，学习开发技术。

### branch分支

分支概念用于工程管理，便于多人协作开发

当创建一个仓库时，会默认生成一个主分支(master)或者是(main),默认情况下向仓库上传数据或代码都是存储在主分支中的

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685699222914.png)

#### 分支命令

```bash
// 创建分支
git branch branchname

// 切换分支
git checkout branchname

// 显示所有本地分支
git branch

// 显示所有分支
git branch -a

// 合并分支
git merge branchname

// 删除分支
git branch -d branchname
```

创建新分支，并推到云端，会自动创建新的分支，并且会在此分支把主分支复制过来。相当于在主分支这一个节点复制分出的一支。


# git和github
（2023/05/31）
## github的使用
github是工程托管网站，大量的企业项目工程和开源工程托管在这个网站中，开发者聚集地，大量的开源项目可以很好的帮助用户学习，或开发github是工程托管网站。

### 常用标签
Explore 探索标签
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542115604.png)
Topics 分类标签
    
Trending 推送

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542210197.png)

### 搜索关键词
绝对查询，通过特定的关键字搜索网站内容
- python *awesome*,检索有趣的内容
- socket *sample*,查找技术相关的样例
- go *tutorial*,查找资料相关

### 仓库
一个用户可以创建多个仓库，因为单一原则每个仓库保存一个工程。
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542508762.png)
#### 仓库里的标签

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542474498.png)

#### README.md 
阅读文档，快速帮助用户了解工程和使用方式。

#### LICENSE-许可证
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685542623715.png)

给使用者最大的权限以及最少的限制，高权限许可证常见的有
GPL 3.0
MIT许可证
APACHE 2.0
*企业使用开源项目一定要注意许可问题，避免法务问题*

## git

Gt软件，全称为分布式版本控制系统，用户使用此软件来访问和编辑仓库内容.
git的大致流程

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685543148394.png)
### git配置

#### 1.账号关联，使用本地Git配置关联github的某个账号

1. ssh-keygen-trsa-CIiu88777@126.com/生成本地RSA密钥串

2. 按生成位置，打开id rsa.pub文件，复制其中的密钥字符串

3. 打开网站头像下拉列表->Settings->SSH and GPG key->New ssh key,为密钥编写title标题，将刚刚拷贝的密钥串粘贴到下面空白位置，保存即可

4. 修改配置文件，查看配置文件git config-list

5. 添加修改配置文件，git config-global user.name "用户名"  git config-global user.email"邮箱"

#### 2.为仓库起别名，将数据上传到指定仓库

1. 从网站中拷贝云端仓库的SSH地址

2. git remote add origin"地址"

3. git remote remove origin    //删除别名

### git上传资源的过程

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685541646114.png)

### git结构（之前学的）

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1681570286213.png)

### git基本命令

```bash
git init // 常见本地仓库

ssh -T git@github.com

账号关联， 让Git软件与某个账号绑定， 并且定位某个仓库

git config --list //查看配置文件

在配置文件中两项， 
user.email = "邮箱"
user.name = "用户名"

git config --global 键值

采用单向/认证双向认证与云端完成关联，本地生成身份数据串， 将其复制，粘贴到云端账号中 RSA(非对称加密算法)

ssh-keygen -t rsa -C "邮箱"//生成rsa密钥，和信息数据串

git remote add origin "云端仓库的ssh地址”        //为云端地址添加别名
git remote remove origin                        //删除别名
git add Filename                                //将本地数据 文件或文件夹添加到git缓冲区
git commit -m“提交描述”
git push origin master                          //上传本地仓库主分支到云端,
git status //查看缓冲区状态
```
