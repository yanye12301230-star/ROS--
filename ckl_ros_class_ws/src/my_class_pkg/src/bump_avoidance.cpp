#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <geometry_msgs/Twist.h>

// 全局变量：记录碰撞传感器状态 & 上一帧状态
int front_bump_triggered = 0;
int last_front_bump_triggered = 0;  // 上一帧状态，用于判断是否是新触发

// 碰撞传感器回调函数
void bumpCallback(const std_msgs::Int16MultiArray::ConstPtr& msg) {
    // 假设最前方碰撞传感器是数组第0个元素（根据实际硬件调整索引）
    if (msg->data.size() > 0) {
        front_bump_triggered = msg->data[0];
    }
    ROS_INFO("Front bump sensor: %d", front_bump_triggered);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "bump_avoidance_node");
    ros::NodeHandle nh;

    // 1. 订阅碰撞传感器话题
    ros::Subscriber bump_sub = nh.subscribe<std_msgs::Int16MultiArray>(
        "/robot/bump_sensor", 10, bumpCallback
    );

    // 2. 发布控制指令
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Rate rate(10);  // 10Hz 循环

    ROS_INFO("Bump Avoidance Node Started.");

    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();

        geometry_msgs::Twist cmd_vel;
        // 流程图逻辑：
        // 1. 查询最前方碰撞传感器
        // 2. 是否触发？
        if (front_bump_triggered == 1) {
            // 3. 上一帧是否触发？
            if (last_front_bump_triggered == 0) {
                // 新触发：发送后退速度
                cmd_vel.linear.x = -0.1;  // 后退速度
                cmd_vel.angular.z = 0.0;
                cmd_vel_pub.publish(cmd_vel);
                ROS_WARN("Bump detected! Backing up...");
            } else {
                // 持续触发：保持后退（或根据需求调整为停止/转向）
                cmd_vel.linear.x = -0.1;
                cmd_vel.angular.z = 0.0;
                cmd_vel_pub.publish(cmd_vel);
            }
        } else {
            // 未触发：停止（或保持前进）
            cmd_vel.linear.x = 0.0;
            cmd_vel.angular.z = 0.0;
            cmd_vel_pub.publish(cmd_vel);
        }

        // 更新上一帧状态
        last_front_bump_triggered = front_bump_triggered;
    }

    return 0;
}
