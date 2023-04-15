# Data Control Language​ 
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1663721984367.png)​
# 权限
## 授权 
grant
```sql
grant<授权列表> on <关系的名称>to <用户/角色列表>
```
角色：可以理解为用户的不同身份
### 权限列表
	select
	insert
	update
	delete

例如：
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1664496900651.png)​​
​
```sql
grant select on instructor to U1,U2,U3​
```
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1664497051410.png)
## 收权
​revoke
```sql
revoke<授权列表>
on <关系的名称>from <用户/角色列表>
```
## 级联
级联收回权限（默认）：
`revoke select on-department from Amit,Satoshi cascade; `

不级联收回权限： 
`revoke select on department from Amit,Satoshi restrict;`



在授予权限时将授权人设置为一个会话所关联的当前角色，且当前角色不为空，可在授权语句后加上（表示授权人的身份）
`granted by current role`

​

​
# 角色
角色就是一直身份，角色是权限的集合。例如：用户张三，成为了老师，就是张三拥有了老师这个角色，就获得了对应的权限的集合

创建角色： ​create role instructor:​ 角色授予权限： ​grant select on takes to instructor;​ 角色可以授予给用户，也可以授予给其他角色 ​create role teaching assistant grant teaching assistant to instructor;​ 角色链： ​create role dean; grant instructor to dean; grant dean to Satoshi;​

一个用户或一个角色的权限包括：
所有直接授予用户/角色的权限；（单个授予）

所有授予给用户/角色所拥有角色的权限（以集合形式，批量授予）

​

​
# 权限的转移​
获得了某些形式权限的用户被允许将此权限授权传递给其他用户 默认方式下，被授予权限的用户/角色无权把得到的权限再授予给另外的用户/角色
`​grant select on department to Amit with grant option;​​`
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1664498295873.png)​
 