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

### git命令

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
git status //查看缓冲区状态s
```

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685616102812.png)

## 分支
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1685619232938.png)

