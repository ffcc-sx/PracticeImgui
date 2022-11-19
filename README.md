# Imgui 编辑测试

- ### 1 测试环境
- 确保已经安装 python;
- 在当前目录下执行指令 python -m http.server; (或者是python3 -m http.server)
- 在浏览器中输入地址 localhost:8000/debug.html

- ### 2 当前功能测试
- 左侧 Toolbox 展开 Basic;
- 鼠标左键将 button 拖入中间的 Canvas layout 工作区；
- 鼠标左键拖动工作区的 button 改变位置；
- 将工作区的 button 拖出工作区 左/上/右 边界，自动修改按钮位置，实现位置限制。

- ### 3 未实现功能：
- “文档区”与“显示区”交/并集控制；
- 文档栅格控制；
- 文档栅格对齐控制；
- 显示区刷新控件可视范围控制；
- 工作区和显示区使用 Dummy 控制；
- 布局数据结构定义、存储和载入等；
- ...
