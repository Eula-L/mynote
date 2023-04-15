# 表关系
![[java-数据库项目-表关系.png]]
# 用户关系以及读写权限
![[java-数据库项目-用户以及权限.png]]


![[a809e925e17ed6e90f615d895ac5638.png]]



```sql
drop table if exists sell;

drop table if exists buy;

drop table if exists purchaser;

drop table if exists supplier;

drop table if exists item;

drop table if exists user;

  

create table user(-- user存储能进入系统的用户信息

    account     varchar(20) primary key,

    pwdHash     char(64) not null,

    name        varchar(40) not null,

    type        varchar(20) not null,

    index uIndex(type)

);

  

create table item(-- item用于管理仓库内的物品

    ID      varchar(20) primary key,

    name    varchar(40) not null,

    num     numeric(12,0) not null check(num>=0),

    index iIndex(name)

);

  

create table supplier( -- supplier用来管理供货商的库存信息

    name        varchar(40),

    ID          varchar(20),

    price       numeric(12,2) not null check(price>=0),

    num         numeric(12,0) not null check(num>=0),

    primary key (name, ID),

    foreign key (ID) references item(ID) on delete cascade

);

  

create table purchaser(-- purchaser用来管理采购商的求购信息

    name        varchar(40),

    ID          varchar(20),

    price       numeric(12,2) not null check(price>=0),

    num         numeric(12,0) not null check(num>=0),

    primary key (name, ID),

    foreign key (ID) references item(ID) on delete cascade

);

  

create table buy( -- buy用来管理入库记录 即供货商->仓库的物品流动

    time    timestamp default localtimestamp,

    time    timestamp default localtimestamp,

    ID      varchar(20),

    name    varchar(40) not null,

    num     numeric(12,0) not null check(num>0),

    primary key (time, ID),

    foreign key (ID, name) references supplier(ID, name) on delete cascade

);

  

create table sell( -- sell用来管理出库记录 仓库->采购商的物品流动

    time    timestamp default localtimestamp,

    ID      varchar(20),

    name    varchar(40) not null,

    num     numeric(12,0) not null check(num>0),

    primary key (time, ID),

    foreign key (ID, name) references purchaser(ID, name) on delete cascade

);

```


潘红伟 
1，你主要负责哪个部分？ 答：我主要负责数据库部分，数据库建表，建立联系，建立主键，实现我们组的jdbc连接，实现每个组员电脑实现jdbc连接的相关操作，帮助他们了解数据库jdbc的连接含义，实现负责java部分组员的基础代码，与创建弹框的组员合 作完成弹窗。
2，问：数据库部分建立了几个表，他们分别是什么？ 答：一共共建立了三个表格，植物部分的表，僵尸部分的表，用户部分的表。我们组主要侧重游戏方面，数据库这方面，就没有建立太多。下面我就来演示我数据库中存储的植物表，展现表中的植物姓名，功能特点，伤害，攻击范围 等。展现僵尸表里边僵尸姓名，特点，移速及其生命值。我建立的用户表，通过java软件测试jdbc连接插入的一些用户姓名。
3，在接下来的过程中，如何进行改进? 答：我觉得有三个方面， 第一点，正如老师所说，我们这个数据库和游戏进行连接，每个用户在创建完游戏ID之后，每个人挑战的关卡和分数也是不同的，作为一款游戏最重要的就是记录游戏相关的数据，在对其进行排名增加游戏的乐趣，这个以后会进行完 善。 第二点，我们这个数据库图鉴部分，虽说与数据库连接成功了，但是没有贴图成功，我们会积极讨论解决这个问题，让它看起来更像数据库。 第三点：接下来，java和数据库开发人员加强沟通，植物大战僵尸中类定义属性，要分别与数据库中数据建立一一联系。（植物图鉴为后期迭代开发的功能部分） 第四点，数据库部分缺少相关的索引，事务，存储过程等基本数据库的操作，我们组员会根据具体的需求进行添加。