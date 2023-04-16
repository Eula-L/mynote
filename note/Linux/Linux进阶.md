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

这是第一行
这是第二行

这是第一行
这还是第一行

这才是第二行

斜体效果 *avx*

粗体效果 **asad**

粗斜体 ***adasdsad***

~~删除线效果~~

+ 无序列表

1. 有序列表
    1. 子级
        * 有序中包含无序

> 一级引用
>> 二级引用
>>> 三级引用

超链接
[github官网](htttp://github.com "这是鼠标悬停信息")

插入图片链接

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662348926027.png)

插入代码块

```cpp
#include<iostream>
using namespace std;
int main ()
{
    return 0;
}
```

`高亮`

# 正则表达式

作用：主要用于数据处理，对于数据的匹配和提取

特点:

* 模糊查询很强

* 各个语言和平台都有对正则的支持与实现

## 使用方法

Linux平台

### 命令

Grep

```bash

grep '正则语句' file

grep 'a*' test  # *表示以前一个表达式为参照物，默认情况下表达式为一个字符，该表达式出现次数>=0

grep 'aa*' test # *表示以前一个表达式为参照物，默认情况下表达式为一个字符，该表达式出现次数>=1

grep 'a\+' test # +以前一个表达式为参照，默认情况下表达式为一个字符，该表达式出现1次或多次（需要转义）
grep '^a' test #^以后一个为参照，表示以a开头的

grep 'a$' test #$以前一个为参照，表示以a结尾的

grep '.ood' test #.表示任意一个字符

grep '?ood' test #?表示数据出现0次或1次

grep '[abcd]ood' test #[]表示字符集合，使用时只表示集合中的某个字符
常用模板有[a-z][A-Z][0-9]

grep '[^abcd]ood' test #[^abcd]表示字符集合取非

() # 可以将字符表达式变为整体，形成字符串表达式，以字符串为单位匹配数据（需要转义）

| # 自由字符集合中无需转义，其他位置需要转义

a{n} # 以前一个表达式为参照，表示该表达式出现的频率，需要转义
# 出现两次{2}、至少出现两次{2,}、出现两到五次{2，5}

```

Awk

Sed

>>>除了这三个命令，其他命令使用特殊符号都是 `通配符`

### 正则函数

```cpp
#include<regex.h>//正则表达式需要的头文件

```
