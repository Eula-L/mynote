# 数据库基础
## 一、相关概念
  ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663518003104.png)
MySQL中的数据模型  ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663518095684.png)
[[基本概念-键]]
## 二、SQL

### 1、SQL通用语法
	SQL语句可以单行或多行书写，以分号结尾。
	SQL语句可以使用空格/缩进来增强语句的可读性。
	MySQL数据库的SQL语句不区分大小写，关键字建议使用大写。
	注释： 
		单行注释：-- 注释内容或 # 注释内容(MySQL特有) 
		多行注释：/ * 注释内容 * /
### 2、SQL语句的分类
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663518368734.png)
[[DDL——数据库操作]]

[[DML——修改表内容]]

[[DQL——数据库查询]]

[[DQL——执行顺序]]

[[DCL——管理数据库用户和用户权限]]















# 视图
## 创建  
```sql
create view myview as(select student.s,Sname,avg(sc.score) from student inner join sc on sc.S=student.S  
group by student.S having avg(sc.score)>=60);  
```
## 使用  
select * from myview;  
## 删除  
drop view myview;
## 优缺点
### 优点：sql语句在网络中传输，使用视图可以减少流量，保证sql语句不会有问题，更安全
节省流量、安全
### 缺点：执行效率不会提高，因为还是执行原来的语句
# 函数
## 创建自定义函数
```sql
delimiter //                        # 声明//为结束标志
create function 函数名(参数名 类型,参数名 类型,参数名 类型)
returns 返回值类型
begin
函数内容1;
函数内容2;
end //
delimiter ;                              # 重新声明;为结束标志，不影响别人，不影响别的sql函数
```
## 启用创建函数功能
SET GLOBAL log_bin_trust_function_creators = 1;

```sql
## 定义一个加法函数

delimiter //
create function addFun(a int,b int)
returns int
begin
    declare c int  default  0;
    set c = a + b;
    return c;
end //
delimiter ;
```
## 调用函数
select addFun(1,2);

## 删除函数
drop function if exists addFun;
想要修改函数，只能删除旧的，并创建新的

# 变量  
## 局部（临时）变量  
```sql
drop function if exists  myadd;  
  
delimiter //  
create function myadd(a int,b int)  
returns int  
begin  
    declare c int  default  0; # 这个c是局部（临时）变量  
    set c = a + b;  
    return c;  
end //  
delimiter ;
```
## 会话变量  
-- 本次会话有效，可以直接使用  
set @xx = addFun(100,9);  
select @xx;  
## 系统变量（全局变量）  
select @@sql_mode;  
### 显示所有系统变量  
show global variables;
# 选择  
## if选择  
if(条件成立)then 执行语句，可以是多条;  
elseif(条件成立) then 执行语句，可以是多条;  
else 执行语句，可以是多条;  
end if;  

-- 定义一个函数，判断是正、负还是0  
drop function if exists myfun;  
delimiter  //  
create function myfun(a int)  
returns varchar(45)  
begin  
    declare result varchar(45) default '';  

    if(a>0) then set result = '是正数';  
    elseif(a<0) then set result = '是负数';  
    else  set result ='是0';  
    end if;  
    return result;  
end //  
delimiter ;  

select myfun (1);  

  

## case  
### 第一种  
case 变量 when 值1 then 执行语句;  
         when 值2 then 执行语句;  
         when 值3 then 执行语句;  
end case;  
-- 练习  
drop function if exists myfun;  
delimiter  //  
create function myfun(a int)  
returns varchar(45)  
begin  
    declare result varchar(45) default '';  

   case a when 10 then set result='值是10';  
          when 0 then set result='值是0';  
          when -10 then set result='值是-10';  
    end case ;    return result;  
end //  
delimiter ;  

select myfun(-10);  

### 第二种  
case  when  条件1 then 执行语句;  
	     when 条件2 then 执行语句;  
         when 条件3 then 执行语句;  
	     else    执行语句;
end case;  

-- 练习  
drop function if exists myfun;  
delimiter  //  
create function myfun(a int)  
returns varchar(45)  
begin  
    declare result varchar(45) default '';  

   case  when a>0 then set result='值是正数';  
          when a<0 then set result='值是负数';  
          when a=0 then set result='值是0';  
    end case ;    
    return result;  
end //  
delimiter ;  

select myfun(0);
# 循环  
## while  
while 循环条件  
do  
    执行语句  
end while;  

### 定义一个函数，计算1到n的累加和  
drop function if exists mysum;  
delimiter  //  
create function mysum(n int)  
returns int  
begin  
    declare i int default 1;  
    declare nSum int default 0;  

    while i<=n  
    do  
        set nSum =nSum+i;  
        set i=i+1;  
      
    end while ;  
      
    return nSum;  
end //  
delimiter ;  

select mysum(10);  

## 其他循环  
mysql中没有for循环，有repeat和loop循环，自行学习即可。
# 存储过程  
存储过程是大型数据库系统中，一组为了完成指定功能的sql语句集。 存储在数据库中，一次编译吗，永久有效。用户通过指定的存储过程名和参数来执行。  
## 优点  
### 1、减少网络流量：存储过程直接在数据库服务器上运行，减少了与客户机的交流。  
### 2、增强代码的通用性和共享性  
### 3、加快系统运行速度  
### 4、使用灵活  
## 创建存储过程  
```sql
delimiter //  
create procedure  存储过程名(参数1 类型,参数2 类型,....)  
begin  
    执行语句;  
end //  
delimiter ;  
```

### 注意：存储过程没有返回值，如果需要返回数据，可以把参数定义为OUT|INOUT,默认IN  
## 调用存储过程  
call 存储过程名(参数列表)  
## 删除存储过程  
`drop procedure if exists  存储过程名;  `

## test  
```sql
drop procedure  if exists  mypro;  
delimiter //  
create procedure mypro()  
begin  
    select student.S,Sname,avg(score)  
    from student inner join sc on student.S=sc .S  
    group by student.S having avg(score)>=60;  
end //  
delimiter ;  
  
call mypro();  
```

## 存储过程和函数区别  
### 1、函数只能操作数据，是在select里执行的，不能有sql语句；存储过程是可以有sql语句 ，存储过程里可以调用函数
### 2、函数有返回值，存储过程没有返返回值，需要OUT|INOUT声明参数来返回数据


# 触发器  
是一种特殊的存储过程  
当指定事件（增删改）发生的时候，系统自动调用触发器  
在控制多个表的是时候，如果一个表涉及删除，与之相关的表也需要删除，否则就会有垃圾数据产生。触发器就能完成自动删除的操作  

## 创建触发器  

```sql
delimiter //  
create trigger 触发器名字  
after/before  操作 on 表名  for each row  
    begin    end//  
delimiter ;  
```



## 删除触发器  
drop trigger  if exists  触发器名字;  

## test  
### 定义一个触发器，删除student表时，删除对应的sc表中的数据  
## 创建触发器  
drop trigger if exists  mydel;  
delimiter //  
create trigger mydel  
after delete on student  for each row  
    begin        delete            from sc  
                where sc.S=OLD.S;  
    end//  
delimiter ;  

delete from student where S ='03';  

## 创建一个增加的触发器，当stu表增加同学时，sc表添加对应同学的01，02课程的成绩  
drop trigger if exists  myadd;  
delimiter //  
create trigger myadd  
    after insert on student for each row  
    begin        
	    insert into  sc(S,C) values (new.S,'01');  
        insert into  sc(S,C) values (new.S,'02');  
    end //  
delimiter ;  

insert into student (S,Sname) values (20,'beichen');  

## 定义一个修改的触发器  
当teacher表中的学号更改，course中也进行更改  
drop trigger if exists  myupdate;  
delimiter //  
create trigger myupdate  
    after update on teacher for each row  
    begin        update course set T=NEW.T where T=OLD.T;  
    end //  
delimiter ;  

update teacher set T='05' where Tname='王五';
# 事务  
## 作为当逻辑单元，一系列sql语句操作，要么都执行，要么都不执行。  
## 事务的特性（ACID）  
### A:atom原子性，事务不可再分  
### C:consistency一致性，数据库的完整性约束不会被破坏  
### I:isolusion隔离性，多个事务并行执行，相互之间不影响  
### D:durability持久性，持久保存在本地commit数据持久保存  
## 语法  
start transaction;         # 开启事务  
执行语句；  

commit;或者 rollback;       

commit:提交结果到数据库持久保存,   
rollback:回滚到start transaction状态  

  


create table bank(  
   name varchar(45),  
   money double not null ,  
   check ( money>=0 )  
) ;  

insert into bank values ('张三',100);  
insert into bank values ('李四',0;  

update  bank set money = money-50 where name='张三';  
update  bank set money = money+50 where name='李四';  


### test  

start transaction ;  
select * from bank;  
update  bank set money = money-20 where name='张三';  
update  bank set money = money+20 where name='李四';  

commit ;  

# 数据库复习

```sql
-- 查询平均成绩大于等于60的学生的编号,姓名和平均成绩
-- 把两个表连接起来
select * from student inner join sc on stident.S=sc.S
-- 查询每个学生的平均成绩
select student.S,Sname,avg(score) from student inner join sc on stident.S=sc.S
group by student.S;
-- 加条件，平均成绩大于等于60
select student.S,Sname,avg(score) from student inner join sc on student.S=sc.S
group by student.S having avg(score) >= 60;

#视图
-- 视图是为了简化复杂的sql查询语句而提出的概念
-- 视图是一个表或者是多个表导出的虚拟表
-- 不是真实存在的，不需要满足范式的要求

-- 创建视图：create view 视图名 as (sql语句)
create view myview as(
select student.S,Sname,avg(score) from student inner join sc on student.S=sc.S
group by student.S having avg(score) >= 60)



-- 使用视图：视图是表
select * from myview;

-- 删除视图：drop view 视图名
drop view myview;

-- 视图优缺点
-- 优点：sql语句在网络中传输，使用视图可以减少流量，更安全
-- 缺点：执行效率并不会提高，因为还是原来的语句

-- 函数
-- delimiter //(//为一条sql语句的结束标志)
-- create function 函数名(参数1 参数类型,参数2 参数类型, ...)
-- returns 返回值类型 
-- begin
-- 函数内容1;
-- 函数内容2;
-- end
-- delimiter ; (重新声明";"为一条sql语句的结束标志：为了不影响其他人使用数据库)

-- 定义一个加法函数
delimiter //
create function addFun(a int,b int)
returns int
begin 
	declare c int default 0;
	set c = a+b;
	return c;
end //
delimiter ;

-- 调用函数
select addFun(2,3)

-- 删除函数：drop function 函数名;
-- 先判断是否存在再删除：drop function if exists 函数名;

-- 变量
-- 局部变量

-- 会话变量：本次会话有效，可以直接使用
set @xx=addFun(3,4)
select @xx;

-- 系统变量(全局变量)
select @@sql_mode;

-- 选择

-- if选择
-- if(条件) then 执行语句(可以是多条)
-- elseif(条件) then 执行语句
-- else 执行语句
-- end if;

-- 定义一个函数，判断输入的值是正数，负数还是0
drop function if exists myfun;
delimiter //
create function myfun(a int)
returns varchar(45)
begin 
	declare result varchar(45) default '';
	if(a>0) then set result = '输入的值是正数';
	elseif(a<0) then set result = '输入的值是负数';
	else set result = '输入的值是0';
	end if;
	return result;
end //
delimiter ;

select myfun(0);

-- case选择
-- 1>
-- case 变量 when 值1 then 执行语句;
--           when 值1 then 执行语句;
--           when 值1 then 执行语句;
-- end case 

-- 定义一个函数，判断输入的值是10，0还是-10
drop function if exists myfun;
delimiter //
create function myfun(a int)
returns varchar(45)
begin 
	declare result varchar(45) default '';
	case a when 10  then set result = '输入的值是10';
	       when 0 then set result = '输入的值是0';
	       when -10 then set result = '输入的值是-10';
	end case;
	return result;
end //
delimiter ;

select myfun(10);

-- case第二种
drop function if exists myfun;
delimiter  //
create function myfun(a int)
returns varchar(45)
begin
    declare result varchar(45) default '';

   case  when a>0 then set result='值是正数';
          when a<0 then set result='值是负数';
          when a=0 then set result='值是0';
    end case ;
    return result;
end //
delimiter ;

select myfun(0);


-- 循环
-- while循环
-- while 循环条件
-- do
-- 执行语句
-- end while;

-- 定义一个函数，计算1+2+3+...+n
drop function if exists mysum;
delimiter //
create function mysum(n int)
returns int
begin 
	declare i int default 1;
	declare nSum int default 0;

	while i<=n
	do
    set nSum = nSum+i;
		set i=i+1;
	end while;
	return nSum;
end //
delimiter ;

select mysum(10);

-- 其他循环: mysql没有for循环，有repeat和loop循环，自行学习即可。





-- 作业:
-- 青蛙爬井，白天向上5m，晚上向下4m，问多少天出井。
-- 使用函数实现，传入采纳数是井的高度(high int),返回值是需要的天数(nDay int)

drop function if exists climb;
delimiter //
create function climb(high int)
returns int
begin 
	declare nDay int default 1;
	while high>5
	do
		set high=high-1;
    set nDay=nDay+1;
	end while;
	return nDay;
end //
delimiter ;

select climb(7);

-- 存储过程：是大型数据库系统中，一组为了完成指定功能的SQL语句集
-- 存储在数据库中，一次编译永久有效。用户通过指定的存储过程名和参数来执行。
-- 优点：
-- 1、减少网络流量：存储过程直接在数据库服务器上运行，减少了与客户机的交流。
-- 2、增强代码的重用性和共享性
-- 3、加快系统的运行速度
-- 4、使用灵活

-- 创建存储过程
-- delimite //
-- create procedure 过程名(参数1 类型,参数2 类型,...)
-- begin
-- 	执行语句；
-- end //
-- delimiter ;

-- 注意：存储过程没有返回值，如果需要返回数据，可以把参数定义成OUT|INOUT，默认是IN类型

-- 调用存储过程: call 存储过程名(参数列表);
-- 删除存储过程: drop procedure if exists存储过程名;

-- 创建一个存储过程
drop procedure if exists mypro;
delimiter //
create procedure mypro()
begin
	select student.S,Sname,avg(score) from student inner join sc on student.S=sc.S
	group by student.S having avg(score) >= 60;
end //
delimiter ;

call mypro();

-- 存储过程和函数的区别
-- 1、函数只能操作数据，是在select里面执行的，不能有sql语句：存储过程是可以有sql语句
-- 2、函数有返回值，存储过程没有返回值

-- 触发器：是一种特殊的存储过程，当指定事件(增删改)，系统自动调用。
-- 在控制多个表的时候，如果一个表涉及到删除，那么与之相关的表，也需要删除
-- 不然就会有垃圾数据产生，触发器就可以完成自动删除的操作。

-- 创建触发器
-- delimiter //
-- create trigger 触发器名字
-- after/before 操作          产生触发的操作
-- on 表名                    产生触发的表
-- for each row               影响每一行
-- begin 
-- 	执行操作
-- end//
-- delimiter ;

-- 定义一个删除的触发器
drop trigger if exists mydel;
delimiter //
create trigger mydel
after delete
on student
for each row 
begin
	-- 同时删除sc表中的对应数据
	delete from sc where sc.S = old.S;
	-- old表:删除的数据，或者是修改前的数据
	-- new表:新增加的数据，或者是修改以后的数据
end //
delimiter ;

delete from student where S = '03';

-- 定义一个增加的触发器，当student表增加一个同学时，同时sc表里面增加这个同学选修01和02课程
drop trigger if exists myadd;
delimiter //
create trigger myadd
after insert
on student
for each row 
begin
	-- 同时sc表里面增加这个同学选修01和02课程
  insert into sc(S,C) values(new.S,'01');
	insert into sc(S,C) values(new.S,'02');
end //
delimiter ;

insert into Student(S,Sname) values('20','啊啊啊');

-- 定义一个修改的触发器，修改teacher表里面的T列，同时修改course表中对应行的T列
drop trigger if exists myupdate;
delimiter //
create trigger myupdate
after update
on teacher
for each row 
begin
	-- 同时修改course表中对应行的T列
	update course set T = new.T where T = old.T;
end //
delimiter ;

update teacher set T = '05' where Tname = '王五';

-- 事务
create table bank(
name varchar(45),
money double not null,
check(money >=0)-- 约束条件检查，在mysql中不支持
);

insert into bank values('一一',100);
insert into bank values('二二',0);

select * from bank;

update bank set money = money-50 where name = '一一';
update bank set money = money+50 where name = '二二';

-- 什么是事务：作为单个逻辑工作单元的一些列sql语句操作，要么都执行成功，要么都执行失败。
-- 事务的四个特性（ACID）
-- A atom 原子性，事务是最小工作单元，不可再分，要么都执行，要么都不执行
-- C consistency 一致性，数据库的完整性约束不会被破坏
-- I isolusion 隔离性，并行执行的多个事务之间是隔离的，不互相影响
-- D durabiity 持久性，持久保存在数据库中，commit数据持久保存

-- 语法：
-- start transaction;    开启事务
-- 执行语句;
-- commit;或者rollback;
-- commit：提交结果到数据库持久化保存
-- rollback：回滚到start transaction前的状态

start transaction;    开启事务

select * from bank;

update bank set money = money-50 where name = '一一';
update bank set money = money+50 where name = '二二';

rollback;

commit;

-- 作业：写一个分页(limit a,b)的存储过程。
-- 查student表，传入参数当前是第几页(nPage int)，每页显示多少行(nCount int)。

-- 1、简单写

-- 2、进行参数校验:页数超过最大页数，显示最后一页的数据;页数是负数，显示第一页的数据
drop procedure if exists limitPro;
delimiter //
create procedure limitPro(nPage int,nCount int)
begin
	declare n int default 0; -- 总行数
	declare page int default 0; 
	select count(*) into n from student ;
	-- 页数是负数，显示第一页的数据
	if (nPage < 1) then set nPage=1;
	end if;
	-- 页数超过最大页数，显示最后一页的数据
	if (nPage > floor(n/nCount)) then set nPage = ceil(n/nCount);
	end if;
	set page=(nPage-1)*nCount;
	select * from student limit page,nCount;
end //
delimiter ;

call limitPro(3,3);

-- 3、表名作为参数传入


```