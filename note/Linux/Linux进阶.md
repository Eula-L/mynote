# git和github

## git

### git结构

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1681570286213.png)

### git三要素

1. 仓库: 仓库是工程存储与管理的基本单位， 工程容器，无论是本地还是云端都有仓库概念

2. Commit: 通过提交记录可以便于开发者回溯代码，随时通过记录找到 删除修改的代码片段，提交功能也可以帮助开发者查看软件开发的流程和逻辑
3. Brach 分支:开发者可以上传数据时默认传到仓库的主分支，但是多人开发不允许并发操作主分支，可以新建分支上传功能数据
    * 上传仓库时，如果本地主分支与云端主分支名一致，则会触发合并关联，不一致在云端创建新分支，保存数报

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

ssh-keygen -t rsa -C邮箱”//生成rsa密钥，和信息数据串

git remote add origin "云端仓库的ssh地址”        //为云端地址添加别名
git remote remove origin                        //删除别名
git add Filename                                //将本地数据 文件或文件夹添加到git缓冲区
git commit -m“提交描述”
git push origin master                          //上传本地仓库主分支到云端,
git status //查看缓冲区状态s
```

#### rm命令的逻辑

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1681570590790.png)

## github

## markdown