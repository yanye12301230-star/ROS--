#include "ros/ros.h"
#include "std_msgs/Int16MultiArray.h"

// 碰撞传感器回调函数，接收并打印传感器状态
void bumpCallback(const std_msgs::Int16MultiArray::ConstPtr& msg)
{
    ROS_INFO("=========碰撞传感器数据=========");
    for (int i = 0; i < msg->data.size(); ++i)
    {
        // 打印每个传感器ID的状态（Triggered=触发，Not Triggered=未触发）
        ROS_INFO("传感器ID%d: %s", i, msg->data[i] ? "Triggered(碰撞)" : "Not Triggered(无碰撞)");
    }
}

int main(int argc, char **argv)
{
    // 初始化ROS节点，命名为bump_sensor_subscriber
    ros::init(argc, argv, "bump_sensor_subscriber");
    ros::NodeHandle n;
    // 订阅碰撞传感器话题，队列大小1000，回调函数bumpCallback
    ros::Subscriber sub = n.subscribe("/robot/bump_sensor", 1000, bumpCallback);
    // 循环等待回调，持续接收数据
    ros::spin();
    return 0;
}
