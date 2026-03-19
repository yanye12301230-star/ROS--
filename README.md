OS 机器人传感器与通信实验工程
本工程为智行 - W2A 机器人平台的 ROS 实验工程，包含 **ROS 基础通信（主题 / 服务 / 动作）和传感器应用（碰撞 / 超声 TOF/IMU）** 两大核心实验内容，基于 C++/Python 实现 ROS 节点开发，完成消息传递、传感器数据订阅、避障与自旋控制等功能。
实验环境
机器人平台：智行 - W2A 机器人
ROS 版本：Noetic
开发语言：C++、Python3
依赖功能包：roscpp rospy std_msgs sensor_msgs geometry_msgs actionlib actionlib_msgs
工程结构
plaintext
姓名首字母_ros_class_ws/  # ROS工作空间
├── src/
│   └── my_class_pkg/       # 核心功能包
│       ├── action/         # 自定义动作文件
│       │   └── MyAction.action
│       ├── msg/            # 自定义消息文件
│       │   └── MyMessage.msg
│       ├── srv/            # 自定义服务文件
│       │   └── MyServiceMsg.srv
│       ├── launch/         # 启动文件
│       │   └── bringup_topic.launch
│       ├── scripts/        # Python节点文件
│       │   ├── ros_publisher_node.py
│       │   ├── ros_subscriber_node.py
│       │   ├── ros_server.py
│       │   ├── ros_client.py
│       │   ├── ros_action_server.py
│       │   └── ros_action_client.py
│       ├── src/            # C++节点文件
│       │   ├── ros_publisher.cpp
│       │   ├── ros_subscriber.cpp
│       │   ├── msg_publisher.cpp
│       │   ├── msg_subscriber.cpp
│       │   ├── ros_server.cpp
│       │   ├── ros_client.cpp
│       │   ├── ros_action_server.cpp
│       │   ├── ros_action_client.cpp
│       │   ├── ros_bump.cpp
│       │   ├── ros_sonic.cpp
│       │   ├── ros_imu.cpp
│       │   ├── bump_avoidance.cpp
│       │   ├── tof_avoidance.cpp
│       │   └── imu_spin_control.cpp
│       ├── CMakeLists.txt  # 编译配置文件
│       └── package.xml     # 包依赖配置文件
├── build/                  # 编译生成文件（自动生成）
└── devel/                  # 开发环境文件（自动生成）
实验内容分类
一、ROS 基础通信实验（实验一）
实现 ROS 核心通信机制，包含主题 / 消息、服务、动作三种方式，支持 C++/Python 双语言开发，同时完成自定义消息 / 服务 / 动作的创建与调用。
标准消息传递：C++/Python 实现发布者 / 订阅者，基于std_msgs/String完成基础消息通信
自定义消息：创建MyMessage.msg，实现自定义消息的发布与订阅
自定义服务：创建MyServiceMsg.srv，实现服务端 / 客户端的同步请求响应（整数双倍计算）
自定义动作：创建MyAction.action，实现带进度反馈的异步动作通信
Launch 文件：bringup_topic.launch一键启动多个主题节点，无需单独启动roscore
二、传感器应用实验（实验二）
基于智行 - W2A 机器人的三大传感器，完成数据订阅与实际功能开发，实现机器人避障、自旋控制等核心功能。
碰撞传感器：订阅/robot/bump_sensor话题，实现碰撞检测与后退避障
超声 - TOF 传感器：订阅/ul/sensor*//us/tof*话题，获取距离数据并实现距离触发避障
IMU 惯性测量单元：订阅/imu/data话题，解析角速度 / 加速度 / 姿态数据，实现机器人 180° 自旋控制
核心节点说明
C++ 节点（src / 目录下）
表格
节点文件	功能说明	关联话题 / 服务 / 动作
ros_publisher.cpp	标准消息发布者（String）	发布 /my_topic
ros_subscriber.cpp	标准消息订阅者（String）	订阅 /my_topic
msg_publisher.cpp	自定义消息发布者	发布 /my_msg_topic
msg_subscriber.cpp	自定义消息订阅者	订阅 /my_msg_topic
ros_server.cpp	自定义服务端（整数双倍）	提供 /my_service
ros_client.cpp	自定义客户端	调用 /my_service
ros_action_server.cpp	自定义动作服务端（进度反馈）	提供 /my_action
ros_action_client.cpp	自定义动作客户端	调用 /my_action
ros_bump.cpp	碰撞传感器数据订阅	订阅 /robot/bump_sensor
bump_avoidance.cpp	碰撞传感器避障控制	订阅 /robot/bump_sensor
发布 /cmd_vel
ros_sonic.cpp	超声 TOF 传感器数据订阅	订阅 /ul/sensor1/2/3
tof_avoidance.cpp	TOF 传感器避障控制	订阅 /ul/sensor2
发布 /cmd_vel
ros_imu.cpp	IMU 传感器数据订阅	订阅 /imu/data
imu_spin_control.cpp	IMU 自旋控制（180°）	订阅 /imu/data
发布 /cmd_vel
Python 节点（scripts / 目录下）
表格
节点文件	功能说明	关联话题 / 服务 / 动作
ros_publisher_node.py	标准消息发布者（String）	发布 /my_topic
ros_subscriber_node.py	标准消息订阅者（String）	订阅 /my_topic
ros_server.py	自定义服务端（整数双倍）	提供 /my_service
ros_client.py	自定义客户端	调用 /my_service
ros_action_server.py	自定义动作服务端（进度反馈）	提供 /my_action
ros_action_client.py	自定义动作客户端	调用 /my_action
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
