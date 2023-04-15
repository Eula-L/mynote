 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663682248017.png)​创建表并存入数据​
 ```sql
 
-- 删除原来的表
-- drop table employee;
-- 创建一个新表
create table emp
(
    id int comment '编号',
    workno varchar(10) comment '工号',
    name varchar(10) comment '姓名',
    gender char(1) comment '性别',
    age tinyint unsigned comment '年龄',
    idcard char(18) comment '身份证号',
    workaddress varchar(50) comment '工作地址',
    entrydate date comment '入职时间'
)comment'员工表';


-- 导入数据
insert into emp(id, workno, name, gender, age, idcard, workaddress, entrydate)
VALUES (1, '1', '柳岩', '女', 20, '123456789012345678', '北京', '2000-01-01'),
       (2, '2', '张无忌', '男', 18, '123456789012345670', '北京', '2005-09-01'),
       (3, '3', '韦一笑', '女', 38, '123456789012345670', '上海', '2005-08-01'),
       (4, '4', '赵敏', '女', 18, '123456789012345670', '北京', '2009-12-01'),
       (5, '5', '小昭', '女', 16, '123456789012345678', '上海', '2007-07-01'),
       (6, '6', '杨逍', '男', 28, '12345678901234567X', '北京', '2006-01-01'),
       (7, '7', '范瑶', '男', 40, '123456789012345670', '北京', '2005-05-01'),
       (8, '8', '黛绮丝', '女', 38, '123456789012345670', '天津', '2015-05-01'),
       (9, '9', '范凉凉', '女', 45, '123456789012345678', '北京', '2010-04-01'),
       (10, '10', '陈友谅', '男', 53, '123456789012345670', '上海', '2011-01-01'),
       (11, '11', '张士诚', '男', 55, '123456789012345670', '江苏', '2015-05-01'),
       (12, '12', '常遇春', '男', 32, '123456789012345670', '北京', '2004-02-01'),
       (13, '13', '张三丰', '男', 88, '123456789012345678', '江苏', '2020-11-01'),
       (14, '14', '灭绝', '女', 65, '123456789012345670', '西安', '2019-05-01'),
       (15, '15', '胡青牛', '男', 70, '12345678901234567X', '西安', '2018-04-01'),
       (16, '16', '周芷若', '女', 18, null, '北京', '2012-06-01');
```
基本查询
```sql
-- 基本查询
-- 1. 查询指定字段
select name,workno,age
from emp;
-- 2. 查询所有字段
select * -- 实际开发中，尽量不要写 *
from emp;
-- 3.查询所有员工的工作地址，起别名
select workaddress as '工作地址'
from emp;
-- as 可以省略
select workaddress  '工作地址'
from emp;

-- 4.员工的上班地址，不要重复 distinct
select distinct workaddress
from emp;
```
条件查询
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663684236147.png)​
```sql
-- 1.查询年龄等于88的员工
select *
from emp
where age=88;
-- 2.查询年龄小于20的员工信息
select *
from emp
where age<20;
-- 3.查询年龄小于等于20的员工信息
select *
from emp
where age<=20;
-- 4.查询没有身份证号的员工信息
select *
from emp
where idcard is null; -- 判空
-- 5.查询有身份证号的员工信息
select *
from emp
where idcard is not null;  -- not 取反
-- 6.查询年龄不等于88的员工信息
select *
from emp
where age != 88;
-- 7.查询年龄在15岁（包含）到20岁（包含）之间的员工信息
select *
from emp
where age>=15 and age <=20; -- 也可以 between 15 and 20
-- 8.查询性别为女且年龄小于25岁的员工信息
select *
from emp
where gender='女' and age <25;
-- 9.查询年龄等于18或20或40的员工信息
select *
from emp
where age=18 or age=20 or age=40;
-- 用 in 替换 or，后面列表中只需要满足其一就可以
select *
from emp
where age in(18,20,40);
-- 10.查询姓名为两个字的员工信息
select *
from emp
where name like '__'; -- 模糊查找，一个下划线代表一个模糊字符  __
-- 11.查询身份证号最后一位是X的员工信息
select *
from emp
where idcard like '%X'; -- 模糊查找，%代表无限长的模糊查找
```
聚合函数​
```sql
-- 聚合函数
-- 1.统计该企业员工数量
select count(*)
from emp;
select count(id)
from emp;
select count(idcard)
from emp;-- 不统计null值

-- 2.统计该企业员工的平均年龄
select avg(age)
from emp;
-- 3.统计该企业员工的最大年龄
select max(age)
from emp;

-- 4.统计该企业员工的最小年龄
select min(age)
from emp;

-- 5.统计西安地区员工的年龄之和
select sum(age)
from emp
where workaddress='西安';
```
分组查询
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663693974050.png)​
 ```sql
 -- 分组查询
-- 1.根据性别分组，统计男性员工和女性员工的数量
select gender,count(*)
from emp
group by gender;
-- 2.根据性别分组，统计男性员工和女性员工的平均年龄
select gender,avg(age)
from emp
group by gender;
-- 3.查询年龄小于45的员工，并根据工作地址分组，获取员工数量大于等于3的工作地址
select workaddress,count(*)
from emp
where age<45 group by workaddress having count(*)>=3;

select workaddress,count(*) address_count
from emp
where age<45 group by workaddress having address_count>=3;
```
排序查询​
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663694484680.png)​
 ```sql
 -- 排序查询
-- 1.根据年龄对公司的员工进行升序排序
select *
from emp
order by age desc;  -- 升序（默认可以省略） asc  降序 desc

-- 2.根据入职时间，对员工进行降序排序
select *
from emp
order by entrydate desc;

-- 3.根据年龄对公司的员工进行升序排序，年龄相同，再按照入职时间进行降序排序
select *
from emp
order by age ,entrydate desc;
```
分页查询​
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663694861483.png)​
```sql
-- 分页查询
-- 1.查询第1页员工数据，每页展示10条记录
select *
from emp
limit 0,10;

select *
from emp
limit 10;
-- 2.查询第2页员工数据，每页展示10条记录
select *
from emp
limit 10,10;
```