#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberCounterNode : public rclcpp::Node
{
    public:
        NumberCounterNode() : Node("number_counter"), counter_(0), timer_(0)
        {
            publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
            subscription_ = this->create_subscription<example_interfaces::msg::Int64>("number", 10, std::bind(&NumberCounterNode::callbackNumberCounter, this, std::placeholders::_1));
            timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&NumberCounterNode::publishCounter, this));
            RCLCPP_INFO(this->get_logger(), "Number Counter has started");
        }

    private:
        void publishCounter(){
            auto msg = example_interfaces::msg::Int64();
            msg.data = counter_;
            publisher_->publish(msg);
        }

        void callbackNumberCounter(const example_interfaces::msg::Int64::SharedPtr msg){
            counter_ += msg->data;
        }

        int counter_;
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscription_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}