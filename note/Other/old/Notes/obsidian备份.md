obsidian通过git向gitee备份
#win
# git
## 下载git
根据提示安装完毕
win+r进入cmd，输入git，出现如下为成功
![[git安装成功.png]]
## 配置git
### 配置基本信息
```bash
# 配置用户名
git config --global user.name "username"    //（ "username"是自己的账户名，）
# 配置邮箱
git config --global user.email "username@email.com"     //("username@email.com"注册账号时用的邮箱)
git config --global --list//检查配置的是否成功
```
### 生成ssh
```bash
ssh-keygen -t rsa
```
然后连敲三次回车键，结束后去系统盘目录下（一般在 C:\Users\你的用户名.ssh）(mac: /Users/用户/.ssh）查看是否有。ssh文件夹生成，此文件夹中以下两个文件
![[ssh公钥.png]]
将ssh文件夹中的公钥（ id_rsa.pub）添加到Gitee管理平台中，在Gitee的个人账户的设置中找到如下界面![[gitee设置ssh公钥.png]]
测试一下配置是否成功，在Git Bush命令框（就是刚才配置账号和邮箱的命令框）中继续输入以下命令，回车
```
ssh -T git@gitee.com
```
# 在gitee创建私有仓库
![[gitee新建私有库.png]]
根据自动生成的建库代码在本地建立存储库，建立完成后，在这个目录下会出现.git目录
## 使用obsidian打开这个存储库
使用ob打开之后，这个目录回出现.ob目录
在.ob目录下创建plugins目录，然后将插件放入这个目录当中
进入ob设置这个插件
# 完成

# git可视化软件
[Sourcetree | Free Git GUI for Mac and Windows (sourcetreeapp.com)](https://www.sourcetreeapp.com/)
安装教程[(22条消息) 【Git可视化工具】Sourcetree的初始化与使用_慕雪华年的博客-CSDN博客_git可视化工具](https://blog.csdn.net/muxuen/article/details/123130926?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166832429916800186526429%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166832429916800186526429&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-2-123130926-null-null.142^v63^control,201^v3^control_1,213^v2^t3_esquery_v3&utm_term=git%E5%8F%AF%E8%A7%86%E5%8C%96&spm=1018.2226.3001.4187)
远端红色感叹号[(22条消息) sourcetree远端 红色叹号_划水小将军的博客-CSDN博客_sourcetree远端有感叹号](https://blog.csdn.net/qq_44309969/article/details/122937148?ops_request_misc=&request_id=&biz_id=102&utm_term=sourcetree%20%E8%BF%9C%E7%AB%AF%E6%84%9F%E5%8F%B9%E5%8F%B7&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-122937148.142^v63^control,201^v3^control_1,213^v2^t3_esquery_v3&spm=1018.2226.3001.4187)

# gitee到手机端
https://forum-zh.obsidian.md/t/topic/7152
手机端下载mgit
clone下来gitee对应的库，注意：用户名是
![[gitee到手机_登录环节.png]]
## 但是这个手机端有问题

# linux 

