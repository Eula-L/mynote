
# space vim
[SpaceVim: 模块化 Vim IDE，支持多种语言开发 (gitee.com)](https://gitee.com/spacevim/SpaceVim?_from=gitee_search)
开发手册-中文版
[开发者文档 | SpaceVim](https://spacevim.org/cn/development/)


# fast和space比较
fast有国内仓库，安装方便，并且足够使用
# wsl/虚拟机中vim无法复制到windows剪贴板
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
`sudo apt-get install vim-gtk`

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1ba3c8c2710c499f454b2dff045c861.jpg)

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/8986cc588d20f1f93ad6db58b1287cb.jpg)