编译与运行步骤
一、工程编译
进入工作空间根目录
bash
运行
cd ~/ckl_ros_class_ws
编译整个工作空间
bash
运行
catkin_make
加载环境变量（已配置到~/.bashrc，新终端可直接使用）
bash
运行
source devel/setup.bash
二、硬件启动（所有传感器实验必备）
启动智行 - W2A 机器人硬件通信，建立 ROS 与机器人控制器的连接：
bash
运行
roslaunch upros_bringup bringup_w2a.launch
该命令需保持运行，单独打开一个终端执行。
三、分实验运行指令
（一）ROS 基础通信实验
标准消息通信（C++）
bash
运行
# 终端1：启动发布者
rosrun my_class_pkg ros_publisher_node
# 终端2：启动订阅者
rosrun my_class_pkg ros_subscriber_node
# 或一键启动（Launch文件）
roslaunch my_class_pkg bringup_topic.launch
自定义消息通信（C++）
bash
运行
rosrun my_class_pkg msg_publisher_node
rosrun my_class_pkg msg_subscriber_node
自定义服务通信（C++/Python）
bash
运行
# C++版
rosrun my_class_pkg ros_server_node
rosrun my_class_pkg ros_client_node
# Python版
rosrun my_class_pkg ros_server.py
rosrun my_class_pkg ros_client.py
自定义动作通信（C++/Python）
bash
运行
# C++版
rosrun my_class_pkg ros_action_server
rosrun my_class_pkg ros_action_client
# Python版
rosrun my_class_pkg ros_action_server.py
rosrun my_class_pkg ros_action_client.py
（二）传感器应用实验
碰撞传感器实验
bash
运行
# 仅订阅数据
rosrun my_class_pkg ros_bump_node
# 碰撞避障功能
rosrun my_class_pkg bump_avoidance_node
超声 - TOF 传感器实验
bash
运行
# 仅订阅超声数据
rosrun my_class_pkg ros_sonic_node
# TOF避障功能
rosrun my_class_pkg tof_avoidance_node
IMU 传感器实验
bash
运行
# 仅订阅IMU数据
rosrun my_class_pkg ros_imu_node
# IMU自旋控制（180°）
rosrun my_class_pkg imu_spin_control_node
