#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

enum RecurrenceType {
    NONE,    // 没有循环
    DAILY,   // 每天循环
    WEEKLY,  // 每周循环
    MONTHLY  // 每月循环
};
class Task {
public:
    // 成员变量
    int taskId;
    std::string taskName;        // 任务名称
    std::time_t updateTime;      // 更新时间
    std::time_t createTime;      // 创建时间
    std::string description;     // 描述
    std::time_t dueTime;         // 截止时间
    bool isCompleted;            // 是否完成 
    RecurrenceType recurrenceType;  // 循环类型
    std::time_t nextDueTime;         // 下一次截止时间

    // 构造函数
    Task();
    Task(int id, const std::string& name, const std::string& desc, std::time_t due,  RecurrenceType recurType = NONE);

    // 成员函数
    void addTask();                // 添加任务
    void deleteTask();             // 删除任务
    void updateTask();             // 更新任务
    void markComplete();           // 标记任务为完成
    void showTaskDetail(int taskId); // 显示任务详情
    void updateNextDueTime();      // 更新任务的下一次截止时间

private:
    // 工具函数
    std::string formatTime(std::time_t time) const; // 格式化时间
    void addTime(std::time_t &time, int days, int weeks, int months); // 添加指定的时间
};

#endif
