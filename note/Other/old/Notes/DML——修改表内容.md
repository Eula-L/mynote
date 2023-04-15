![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672747586656.png)

```sql
-- DEL
-- 增
insert  into  employee(id, workno, name, gender, age, idcard, entrydata)
values (1,'010','张三','男',20,123456123456123456,'2022-01-01');


select *
from employee;

insert into employee values (2,'011','李四','女','19','111111222222333333','2022-09-20');

insert into employee
values (3,'011','李四','女','19','111111222222333333','2022-09-20'),(4,'011','李四','女','19','111111222222333333','2022-09-20');

-- 改
-- 修改表中数据
-- 修改id为1的数据中的name为itheima
update employee set name='itheima'
where id=1;

-- 修改id为1的字段中的name为 ‘小昭’，gender为‘女’
update employee set name='小昭',gender='女'
where id=1;

-- 修改所以员工的入职日期改为 ‘2020-01-01’
-- 对所有信息修改，只需要不写where就好了
update employee
set entrydata='2020-01-01';


-- 删
delete from employee
where id=1;

-- 删除所有员工
delete from employee;
```