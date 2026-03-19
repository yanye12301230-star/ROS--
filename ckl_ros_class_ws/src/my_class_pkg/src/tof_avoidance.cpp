#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>

// 全局变量：保存最前方 TOF 传感器的距离数据
float front_distance = 1.0;  // 初始化为安全距离

// 回调函数：订阅最前方 TOF 传感器（/ul/sensor2）的数据
void frontRangeCallback(const sensor_msgs::Range::ConstPtr& msg) {
    front_distance = msg->range;
    ROS_INFO("Front TOF distance: %.2f m", front_distance);
}

int main(int argc, char** argv) {
    // 1. 初始化 ROS 节点
    ros::init(argc, argv, "tof_avoidance_node");
    ros::NodeHandle nh;

    // 2. 订阅最前方 TOF 传感器话题（修正笔误：senser → sensor）
    ros::Subscriber front_range_sub = nh.subscribe<sensor_msgs::Range>(
        "/ul/sensor2", 10, frontRangeCallback
    );

    // 3. 发布控制指令（控制小车运动的话题）
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>(
        "/cmd_vel", 10
    );

    // 4. 设置循环频率（10Hz）
    ros::Rate rate(10);

    while (ros::ok()) {
        // 处理回调函数，更新 front_distance
        ros::spinOnce();

        // 5. 按流程图判断：距离 < 0.4m 则后退
        geometry_msgs::Twist cmd_vel;
        if (front_distance < 0.4) {
            // 距离过近：后退（线速度为负）
            cmd_vel.linear.x = -0.1;   // 后退速度（可调整）
            cmd_vel.angular.z = 0.0;    // 不转向
            ROS_WARN("Obstacle too close! Backing up...");
        } else {
            // 距离安全：停止
            cmd_vel.linear.x = 0.0;
            cmd_vel.angular.z = 0.0;
            ROS_INFO("Safe distance, no obstacle.");
        }

        // 6. 发布控制指令
        cmd_vel_pub.publish(cmd_vel);
        rate.sleep();
    }

    return 0;
}
