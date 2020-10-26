<!--
 * @Author: PlanC
 * @Date: 2020-10-26 18:02:06
 * @LastEditTime: 2020-10-26 19:35:54
 * @FilePath: \Practical-Training-Neusoft-Tianjin\运维\lesson4.md
-->

# 笔记
## VLan
**虚拟局域网**
https://www.processon.com
交换机原理
- 交换机收到数据帧之后学习数据帧的源MAC地址
- 转发广播（除去源端口）寻找数据帧目标MAC地址
- 当其他主机或设备收到广播时不是这个广播的目标，则丢弃这个数据帧
- 目标主机回应时，数据帧里面的信息源IP与目标互换，源MAC与目标互换
- 把数据帧发送回数据帧
- 交换机转发数据帧
- 如果交换机有源MAC和目标MAC则不必学习和广播

VLan的优点
- VLan可以隔绝网络风暴
- 不同的VLan配置不同的IP地址段
- VLan可以方便管理

VLan口
- 1 默认
- 2 ~ 1024 一般情况下，一个部门一个VLan

创建VLan
- 方法一
  - 在特权模式创建VLan
    - `Switch# vlan databace`
      - 打开VLan数据库
    - `Switch# vlan id [name 名称]`
      - 添加VLan并指定名
    - `show vlan [brief]`
      - 显示所有VLan信息
      - 默认情况所有接口都属于VLan1
  - 在全局模式将接口加入VLan
    - `Switch(config)# int f 0/1`
      - 进入接口
    - `Switch(config-if)# switchport mode access`
      - 将接口模式改为接入链路
    - `Switch(config-if)# switchport access vlan 10`
      - 将接口加入VLan10
- 方法二
  - 在全局模式下创建VLan
    - `Switch(config)# vlan 10`
      - 创建VLan10
    - `Switch(config vlan)# name [名称]`
      - 为VLan命名

`Switch(config)# do show vlan`
`do`命令可以越权操作
### 不同交换机相同VLan通信
`Switch(config-it)# switchport mode trunk`
中继模式
