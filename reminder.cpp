#include "./headers/reminder.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include<windows.h>

Reminder::Reminder(TaskManager& taskManager) : taskManager(taskManager) {}

std::time_t Reminder::getCurrentTime() const {
    // 获取当前时间
    return std::time(nullptr);
}

bool Reminder::isDueTomorrow(std::time_t dueTime) const {
    // 获取当前时间
    std::time_t now = getCurrentTime();

    // 获取当前时间的日期（年-月-日）
    std::tm* currentTime = std::localtime(&now);
    currentTime->tm_hour = 0;
    currentTime->tm_min = 0;
    currentTime->tm_sec = 0;
    std::time_t currentDate = std::mktime(currentTime);

    // 获取明天的日期
    std::tm* tomorrowTime = std::localtime(&currentDate);
    tomorrowTime->tm_mday += 1; // 明天的日期
    std::time_t tomorrowDate = std::mktime(tomorrowTime);

    // 任务的截止时间
    std::tm* taskTime = std::localtime(&dueTime);
    taskTime->tm_hour = 0;
    taskTime->tm_min = 0;
    taskTime->tm_sec = 0;
    std::time_t taskDate = std::mktime(taskTime);

    // 如果任务截止时间是明天的日期
    return (taskDate == tomorrowDate);
}

// void Reminder::sendReminder(const Task& task) const {
//     // 提醒消息
//     std::cout << "提醒: 任务 '" << task.taskName << "' 截止时间即将到来，明天就是截止日期!" << std::endl;
//     std::cout << "任务详情: " << task.description << std::endl;
//     std::cout << "截止时间: " << std::asctime(std::localtime(&task.dueTime)) << std::endl;
// }

void Reminder::sendReminder(const Task& task) const {
    // 弹窗提醒
    std::string reminderMessage = "提醒: 任务 '" + task.taskName + "' 截止时间即将到来，明天就是截止日期!\n";
    reminderMessage += "任务详情: " + task.description + "\n";
    reminderMessage += "截止时间: " + std::string(std::asctime(std::localtime(&task.dueTime)));

    // 转换 std::string 为 wchar_t* 类型
    int len = MultiByteToWideChar(CP_ACP, 0, reminderMessage.c_str(), -1, NULL, 0);
    if (len > 0) {
        // 为 wchar_t 数组分配内存
        wchar_t* wideMessage = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, reminderMessage.c_str(), -1, wideMessage, len);

        // 使用 MessageBoxW 来显示 Unicode 字符串
        MessageBoxW(NULL, wideMessage, L"任务提醒", MB_OK | MB_ICONINFORMATION);

        // 清理分配的内存
        delete[] wideMessage;
    }
}
void Reminder::sendEmail(const Task&task)const{/*等待完成*/};
void Reminder::checkAndRemind() const {
    // 遍历所有任务并检查是否需要提醒
    for (const auto& task : taskManager.getTasks()) {
        if (isDueTomorrow(task.dueTime)) {
            sendReminder(task);
        }
    }
}