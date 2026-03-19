#include "ros/ros.h"
#include "my_class_pkg/MyServiceMsg.h"

bool myServiceCallback(my_class_pkg::MyServiceMsgRequest &req,
                       my_class_pkg::MyServiceMsgResponse &res)
{
    // 处理服务请求，返回输入值的两倍
    res.output = req.input * 2;
    ROS_INFO("Request: input = %ld, output = %ld", (long int)req.input, (long int)res.output);
    return true;
}

int main(int argc, char **argv)
{
    // 初始化 ROS 节点
    ros::init(argc, argv, "my_service_node");

    // 创建节点句柄
    ros::NodeHandle nh;

    // 创建服务
    ros::ServiceServer service = nh.advertiseService("my_service", myServiceCallback);
    ROS_INFO("Ready to receive service requests.");

    // 循环处理 ROS 回调函数
    ros::spin();

    return 0;
}

