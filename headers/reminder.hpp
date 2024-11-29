#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include <ctime>
#include "taskmanager.hpp"

class Reminder {
public:
    // 构造函数，接受 TaskManager 引用，遍历任务列表
    Reminder(TaskManager& taskManager);

    // 检查任务的截止时间并提醒
    void checkAndRemind() const;
    bool isDueTomorrow(std::time_t dueTime) const; // 判断任务是否在明天截止
    void sendReminder(const Task& task) const; // 发送提醒
    void sendEmail(const Task&task)const;
    std::time_t getCurrentTime() const; // 获取当前时间
    

private:
    TaskManager& taskManager; // 任务管理器引用
    
    
};

#endif
