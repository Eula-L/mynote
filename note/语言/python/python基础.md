# 目标



python是一个胶水语言，不需要学的多么高深，只需要作为一个工具去学习就可以了。

写算法题还是使用c++

# 序列

## 切片

切片操作可以访问一定范围内的元素，语法如下所示：
sname[start : end : step]

sname：表示序列的名称；
start：开始索引位置（包括该位置），默认为 0；
end：表示切片的结束索引位置（不包括该位置），默认为序列的长度；
step：步长。
以字符串为例，如下所示：

```python
str = 'Python'
print(str[:3])
print(str[3:])
print(str[:])
```

输出结果：
`Pyt`
`hon`
`Python`

## 字符串[]

## 列表list

功能更强的数组，元素必须要统一类型

创建：列表中所有元素都放在一个中括号 [] 中，相邻元素之间用逗号

添加：`.append()`

删除：`del list1[1]`

### 常用方法

`.count()` 统计列表中某个元素出现的次数

`.index()` 查找某个元素在列表中首次出现的位置（即索引）

`.remove()` 移除列表中某个值的首次匹配项

`.sort()` 对列表中元素进行排序

`.copy()` 复制列表

## 元组tuple()

元组（tuple）与列表类似，但元组不可变，可简单将其看作是不可变的列表，元组常用于保存不可修改的内容。

元组中所有元素都放在一个小括号 () 中，相邻元素之间用逗号

### 修改

元组中元素不能被修改，我们要用重新赋值的方式操作

```python
t = (1024, 0.5, 'Python')
t = (1024, 0.5, 'Python', 'Hello')
print('t -->', t)
```

### 删除

元组中的元素不能被删除，我们只能删除整个元组

```python
t = (1024, 0.5, 'Python')
del t
print('t -->', t)
```

### 常用方法

`len()` 计算元组中元素的个数

`max()和 min()` 返回元组中元素的最大、最小值

`tuple()` 将列表转化为元组

```python
t = tuple(l)
```

# 字典dict{}

key-value（键值对）

字典的内容在花括号 `{}` 内，键-值（key-value）之间用冒号 `:` 分隔，键值对之间用逗号 `,` 分隔，

## 创建

比如创建字典 d，如下所示：

```python
# 默认方式
d = {'name':'小明', 'age':'18'}

# 使用 dict 函数
## 方式一
l = [('name', '小明'), ('age', 18)]
d = dict(l)
## 方式二
d = dict(name='小明', age='18')

# 空字典
d = dict()
d = {}
```

## 访问

* 下标 `d['name']`
* get方法 `.get('name')`

## 修改

直接下标修改

## 清除

* clear方法  `.clear`

## 常用函数

`len()获取字典的长度`

# 集合set{}

集合（set）与字典相同均存储 key，但也只存储 key，因 key 不可重复，所以 `set 的中的值不可重复`，也是`无序的`。

## 创建

集合使用花括号 `{}` 或者 `set()` 函数创建，如果创建空集合只能使用 `set()` 函数，以创建集合 s 为例，如下所示：

```python
#基本创建方法
s = {'a', 'b', 'c'}

# 使用 set 函数
s = set(['a', 'b', 'c'])

# 空集合
s = set()
```



## 添加

添加元素可以使用 `add` 或 `update` 方法

## 删除

删除元素使用 `remove` 方法

# 和时间有关的模块

##  time 模块

time 模块提供了很多与时间相关的类和函数

## datetime 模块

datatime 模块重新封装了 time 模块，提供了更多接口，变得更加直观和易于调用。

## calendar 模块

calendar 模块提供了很多可以处理日历的函数。

# 函数

## 声明函数

Python 使用 def 关键字来声明函数，格式如下所示：

```python
def 函数名(参数):
	函数体
	return 返回值
```

如果要定义一个无任何功能的空函数，函数体只写 `pass` 即可。格式如下所示：

```python
def 函数名():
	pass
```

当我们不确定参数的个数时，可以使用不定长参数，在参数名前加 `*` 进行声明，格式如下所示：

```python
def 函数名(*参数名):
	函数体
```

## 匿名函数

我们还可以使用 `lambda` 定义匿名函数，格式如下所示：

```python
lambda 参数 : 表达式
```

```python
# 空函数
def my_empty():
    pass


# 无返回值
def my_print(name):
    print('Hello', name)


# 有返回值
def my_sum(x, y):
    s = x + y
    print('s-->', s)
    return s


# 不定长参数
def my_variable(*params):
    for p in params:
        print(p)


# 匿名函数
my_sub = lambda x, y: x - y
```

# 模块和包

## 模块

Python 中一个以 `.py` 结尾的文件就是一个模块，模块中定义了变量、函数等来实现一些类似的功能。Python 有很多自带的模块（标准库）和第三方模块，一个模块可以被其他模块引用，实现了代码的复用性。

## 包

包是存放模块的文件夹，包中包含 `__init__.py` 和其他模块，`__init__.py` 可为空也可定义属性和方法，在 Python3.3 之前的版本，一个文件夹中只有包含 `__init__.py`，其他程序才能从该文件夹引入相应的模块、函数等，之后的版本没有 `__init__.py` 也能正常导入，简单来说就是 Python3.3 之前的版本，`__init__.py` 是包的标识，是必须要有的，之后的版本可以没有。

## 引用

从包中引入模块有如下两种方式：

### import ...

```python
import 包名1.包名2...模块名
```

### from ... import ...

```python
from 包名1.包名2... import 模块名from 包名1.包名2...模块名 import 变量名/函数名
```



# 面向对象

## 类

### 创建一个类

```python
class Cat:
	# 属性
    color = 'black'
    # 构造方法
    def __init__(self, name):
        self.name = name
    # 自定义方法
    def eat(self, food):
        self.food = food
        print(self.name, '正在吃'+food)
```

### 构造方法

 `__init__()` 会在类实例化时自动调用。无论构造方法还是其他方法都需要将 `self` 作为第一个参数，它代表类的实例。

### 私有属性和方法

定义私有属性和方法，声明方式为：在属性名或方法名前加两条下划线

### 类名访问

可以通过类名访问属性，格式为：`类名.属性名`
比如我们访问 Cat 类的 color 属性，如下所示：

```python
print('color-->', Cat.color)
```

外部不能访问私有方法

## 对象

### 创建对象

```python
# 创建对象
c = Cat('Tom')
```

### 对象访问属性和方法

```python
# 访问属性
print('name-->', c.name)
print('color-->', c.color)
# 调用方法
c.eat('鱼')
```

同样，对象也不能访问私有

## 继承

Python 支持类的`继承`，而且支持`多继承`，语法格式为：

```python
class 基类(子类1, 子类2 ...):
		...
```

子类可以`直接重新`父类方法，可以添加自己独有的方法

```python
# 类的创建
class Cat:
    # 属性
    color = 'black'
    __cid = '1'

    # 构造方法
    def __init__(self, name):
        self.food = None
        self.name = name

    # 自定义方法
    def eat(self, food):
        self.food = food
        print(self.name, '正在吃' + food)

    # 私有方法
    def __run(self):
        pass


# 继承的子类
# 波斯猫类
class PersianCat(Cat):  # 继承
    def __init__(self, name):
        self.name = name

    def eat(self, food):
        print(self.name, '波斯猫！正在吃' + food)


# 加菲猫类
class GarfieldCat(Cat):
    def __init__(self, name):
        self.name = name

    def run(self, speed):
        print(self.name, '加菲猫！！正在以' + speed + '的速度奔跑')


# 单继承
class SingleCat(PersianCat):
    # 重写父类方法
    def eat(self, food):
        print(self.name, '正在吃' + food, '十分钟后', self.name + '吃饱了')


# 多继承
class MultiCat(PersianCat, GarfieldCat):
    pass


# 调用
ps = PersianCat('波斯猫0号')
ps.eat('老鼠')

gf = GarfieldCat('加菲猫0号')
gf.eat('蛋糕')
gf.run('100')

sc = SingleCat('波斯猫1号')
sc.eat('鱼')

mc = MultiCat('波斯加菲猫1号')
mc.eat('鱼')
mc.run('50迈')

```

