 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663676811971.png)​
 ```sql
 -- DDL
desc advisor;
desc classroom;

show create  table classroom;

show databases ;


create database itcast;
use  itcast;

create  table emp(
    id int,
    workno varchar(10) comment '工号',
    name varchar(10),
    gender char(1),
    age tinyint unsigned,
    idcard char(18) ,
    entrydata date comment  '入职时间'

)comment '员工表';

alter table  emp  add nickname varchar(20);




alter table emp change nickname username varchar(30) comment  '用户名';

alter  table emp modify username varchar(35);

alter  table  emp drop username;

desc employee;

alter table emp rename to  employee;

drop  table  if exists  mytable;

show databases ;

show  tables ;
 ```