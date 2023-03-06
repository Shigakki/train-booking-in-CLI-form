# 系统说明-功能要求实现

1.包含一个车次（可自定义，相应接口均已经写好）

2.包含11个站点

3.每个站点之间的距离与费用都均已经定义好，且符合要求

4.出票策略：

```
规则：
	例如:假如要买站点3~站点5 的车票
	规则1：
		(1)假如刚好有3~5的车票则售出，否则按照下面规则。
	规则2：
		(1)选择离3最近的有票的站点(包括<=3)
		(2)选择离5最近的有票的站点(包括>=5)
	规则3：
		(1)在满足规则2中选择一张车票拆分。
实例：
	假如有1，2，3，4，5，6这6个站点，且初始只有一张1到6的票，现在要买一张3~4的车票，根据规则，没有直接从3~4的票出售，离3最近且有票的只有1，离4最近且有票的只有6，则需要拆分这张1~6的车票，拆分成1~3，3~4，4~6，则3~4售出，且多了1~3和4~6各一张.
```

也就是说我们是只拆分比较“散碎”的票，然后我们如果是退票的话，如果是退掉上文所述的3-4的车票的话，其与之相邻的1-3和4-6也会和这个退的票一起复原成1-6。

5.使用的是命令行的界面

6.可根据起始到达站点、用户名称进行查询

# 系统设计说明

## 1.项目结构



![image-20221214174032434](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214174032434.png)

其中包括一个Files用来储存文件；

User.h用来定义User类，Train.h用来定义Train类；order.h用来定义order结构体

ticket类文件定义了ticket结构与相应的购票、退票操作；

files类文件定义了文件相关的读写操作；

matchTransform类文件定义了自己写的string到int的类型转换与stataion车站元组的转换。

## 2.数据结构介绍

### 2.1Train

![image-20221214174448597](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214174448597.png)

### 2.2User

![image-20221214174501943](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214174501943.png)

### 2.3order

![image-20221214174526307](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214174526307.png)

### 2.4ticket

![image-20221214174542822](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214174542822.png)

### 2.5stations三元组

![image-20221214174641055](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214174641055.png)

## 3.数据结构之间的逻辑关系

定义一个具体的Train中包含了一个StationTuple站点元组，其中火车包括trainId作为唯一标识，站点三元组包括stationId站点号、stationName名称与stationFare站点对应的费用，最后的订单费用是两个站点之间的fare值的差值。

然后order是由一个user与一个train（自带station）生成的，其中包含userId、trainId，自己的标识值orderId，还有最重要的出发、到达站点。

最后order中也内嵌一个ticket对象，即一个订单由一个用户的信息、特定火车站点的信息、一个车票组成。

## 4.功能流程

### 4.1系统初始化

在最开始会由火车信息、站点信息进行站点初始化。

![image-20221214175409747](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214175409747.png)

### 4.2恢复历史数据

我们会根据文件order中的数据，读取数据并将历史的购票记录再次恢复。

![image-20221214180521262](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214180521262.png)

### 4.3用户的登录与注册

我们使用一个while循环体进行登录注册的简单实现。

![image-20221214180724455](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214180724455.png)

![image-20221214180741432](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214180741432.png)

![image-20221214180757334](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214180757334.png)

其中还有判定用户是否在user文件中已经注册过

![image-20221214180826432](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214180826432.png)

在这之后我们就会使用返回的User对象。

### 4.4具体功能流程

![image-20221214180925132](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214180925132.png)

我们包括：

所有余票查询、订票、退票、根据起止车站查询已售车票、根据用户名称查询已售车票

还有当前所有已售车票的收益查询、所有的用户查询。

这个我会由一个录制视频进行展示。

# 5提交说明

我在编程完之后才发现程序有4个动态链接库，这也是我当初没法使用QT制作GUI的原因，并且由于其依赖于.dll，没法在Lunix上构建，因而只能提交exe文件了。

这里我附上相关的截图：

(最后手动添加了相关的dll文件，exe文件可直接执行）

![image-20221214195706090](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214195706090.png)

### 5.1登录

![image-20221214200636193](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200636193.png)

并查询当前已卖出的票。

![image-20221214200653427](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200653427.png)

### 5.2查看站点信息

![image-20221214200736830](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200736830.png)

### 5.3购买车票并查询所有已售车票

![image-20221214200800022](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200800022.png)

![image-20221214200832457](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200832457.png)

### 5.4根据起始终止车站查询

![image-20221214200918026](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200918026.png)

### 5.5根据用户名称查询

![image-20221214200958349](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214200958349.png)

### 5.6根据ticketId退票

![image-20221214201103428](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214201103428.png)

### 5.7查看所有收益

![image-20221214201131315](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214201131315.png)

### 5.8查看所有用户

![image-20221214201156903](C:\Users\Shichao\AppData\Roaming\Typora\typora-user-images\image-20221214201156903.png)

### 这段截图对应的日志txt文件也已经提供，请查收。