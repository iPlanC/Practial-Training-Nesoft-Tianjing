<!--
 * @Author: PlanC
 * @Date: 2020-09-08 14:01:02
 * @LastEditTime: 2020-09-08 18:10:03
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.8\notepad.md
-->

**可能有误**

# 原理图与PCB
- 先画原理图再画PCB图
    - 原理图库
    - PCB图库

## 新建图纸
<kbd>File -> New -> Project -> PCB Project</kbd>
工程文件以`.PrjPCB`拓展名保存

### 创建原理图
<kbd>Project -> Add New to Project -> Schematic</kbd>
原理图以`.SchDoc`拓展名保存

### 添加已经存在的库
<kbd>Project -> Add Existing to Project</kbd>
库拓展名为`.IntLib`
会添加原理图库和PCB库

------

## 绘制原理图
```
place
    n. 地点, 位置.
    v. 放置.
```
### 基础操作
`Place Wire`放置连线
`Rxx`即为电阻
`Cxx`即为电容
`VCC`即为电源输入
`GND`即为接地

缩放：<kbd>ctrl</kbd> + <kbd>scroll</kbd>
旋转：<kbd>space</kbd>
