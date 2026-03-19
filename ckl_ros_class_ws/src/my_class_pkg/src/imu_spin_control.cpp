#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_datatypes.h> // 用于转换四元数到欧拉角

// 全局变量保存当前姿态
double current_yaw = 0.0;
bool imu_data_ready = false;

// IMU 数据回调函数
void imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
    // 1. 解析四元数
    tf::Quaternion q(
        msg->orientation.x,
        msg->orientation.y,
        msg->orientation.z,
        msg->orientation.w
    );
    
    // 2. 转换为欧拉角（获取 Z 轴方向，即 yaw）
    tf::Matrix3x3 m(q);
    double roll, pitch;
    m.getRPY(roll, pitch, current_yaw); // current_yaw 是弧度制
    
    imu_data_ready = true;
    // ROS_INFO("IMU Yaw: %.2f rad", current_yaw);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "imu_spin_control_node");
    ros::NodeHandle nh;

    // 1. 订阅 IMU 数据
    ros::Subscriber imu_sub = nh.subscribe<sensor_msgs::Imu>("/imu/data", 10, imuCallback);
    
    // 2. 发布运动控制指令
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Rate rate(20); // 20Hz 循环频率

    ROS_INFO("IMU Spin Control Node Started. Waiting for IMU data...");

    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();

        // 等待 IMU 数据初始化
        if (!imu_data_ready) {
            continue;
        }

        // 3. 逻辑判断：是否到达 180度（即 $\pi$ 弧度）
        // 注意：current_yaw 是 -π 到 π 的范围，需要判断是否旋转了半圈
        // 这里简单逻辑：只要旋转角度绝对值 > 3.0 (约172度) 就停
        if (fabs(current_yaw) < M_PI_2 * 1.9) { 
            // 未到达 180度：开始自旋（逆时针旋转，z 轴正方向）
            geometry_msgs::Twist cmd_vel;
            cmd_vel.linear.x = 0.0;
            cmd_vel.angular.z = 0.3; // 旋转速度（可调整）
            cmd_vel_pub.publish(cmd_vel);
            ROS_INFO("Spinning... Current Yaw: %.2f rad (Target: 3.14 rad)", current_yaw);
        } else {
            // 到达 180度：停止
            geometry_msgs::Twist cmd_vel;
            cmd_vel.linear.x = 0.0;
            cmd_vel.angular.z = 0.0; // 停止
            cmd_vel_pub.publish(cmd_vel);
            ROS_WARN("Reached 180 degrees! Stopped.");
            ros::shutdown(); // 完成任务后关闭节点
            return 0;
        }
    }

    return 0;
}

