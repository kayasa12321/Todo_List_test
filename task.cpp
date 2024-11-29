#include "./headers/task.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
// 工具函数：格式化时间为人类可读的字符串
std::string Task::formatTime(std::time_t time) const {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return std::string(buffer);
}
// 构造函数
Task::Task() : taskId(0), updateTime(0), createTime(0), dueTime(0), isCompleted(false), recurrenceType(NONE), nextDueTime(0) {}

Task::Task(int id,  const std::string& name, const std::string& desc, std::time_t due, RecurrenceType recurType)
    : taskId(id),  taskName(name), description(desc), createTime(std::time(nullptr)), 
      updateTime(std::time(nullptr)), dueTime(due), isCompleted(false),  recurrenceType(recurType), nextDueTime(due) {}

// 添加任务
void Task::addTask() {
    std::cout << "添加新任务：" << std::endl;
    std::cout << "请输入任务名称: ";
    std::cin.ignore();
    std::getline(std::cin, taskName);
    std::cout << "请输入任务描述: ";
    std::getline(std::cin, description);
    std::cout << "请输入任务截止时间 (格式：YYYY-MM-DD HH:MM:SS): ";
    std::string dueTimeStr;
    std::cin.ignore();
    std::getline(std::cin, dueTimeStr);
    struct tm dueTimeStruct = {};
    std::istringstream ss(dueTimeStr);
    ss >> std::get_time(&dueTimeStruct, "%Y-%m-%d %H:%M:%S");
    dueTime = std::mktime(&dueTimeStruct);
    createTime = std::time(nullptr);
    updateTime = createTime;
    isCompleted = false;
    // 默认没有循环
    recurrenceType = NONE;
    nextDueTime = dueTime;
    std::cout << "任务已成功添加！" << std::endl;
}
// 删除任务
void Task::deleteTask() {
    std::cout << "任务已删除！ (ID: " << taskId << ")" << std::endl;
    taskId = 0;
    taskName = "";
    description = "";
    createTime = 0;
    updateTime = 0;
    dueTime = 0;
    isCompleted = false;
    recurrenceType = NONE;
    nextDueTime = 0;
}
// 更新任务
void Task::updateTask() {
    //std::cout << "更新任务 (ID: " << taskId << ")" << std::endl;
    std::cout << "请输入新的任务名称 (当前: " << taskName << "): ";
    std::cin.ignore();
    std::getline(std::cin, taskName);
    std::cout << "请输入新的任务描述 (当前: " << description << "): ";
    std::getline(std::cin, description);
    std::cout << "请输入新的截止时间 (格式：YYYY-MM-DD HH:MM:SS，当前: " << formatTime(dueTime) << "): ";
    std::string dueTimeStr;
    std::cin.ignore();
    std::getline(std::cin, dueTimeStr);
    struct tm dueTimeStruct = {};
    std::istringstream ss(dueTimeStr);
    ss >> std::get_time(&dueTimeStruct, "%Y-%m-%d %H:%M:%S");
    dueTime = std::mktime(&dueTimeStruct);
    updateTime = std::time(nullptr);
    std::cout << "任务已成功更新！" << std::endl;
}
// 标记任务为完成
void Task::markComplete() {
    if (!isCompleted) {
        isCompleted = true;
        updateTime = std::time(nullptr);
        std::cout << "任务 (ID: " << taskId << ") 已标记为完成！" << std::endl;
        // 如果是循环任务，更新下一次截止时间
        if (recurrenceType != NONE) {
            updateNextDueTime();
        }
    } else {
        std::cout << "任务 (ID: " << taskId << ") 已经完成，无需再次标记！" << std::endl;
    }
}
// 更新任务的下一次截止时间
void Task::updateNextDueTime() {
    if (recurrenceType == DAILY) {
        addTime(nextDueTime, 1, 0, 0);  // 加1天
    } 
    else if (recurrenceType == WEEKLY) {
        addTime(nextDueTime, 7, 0, 0);  // 加1周
    } 
    else if (recurrenceType == MONTHLY) {
        addTime(nextDueTime, 0, 0, 1);  // 加1月
    }
    std::cout << "下次任务截止时间: " << formatTime(nextDueTime) << std::endl;
}
// 工具函数：根据循环类型加时间
void Task::addTime(std::time_t &time, int days, int weeks, int months) {
    struct tm timeStruct = *std::localtime(&time);

    timeStruct.tm_mday += days + (weeks * 7);  // 增加天数或周
    timeStruct.tm_mon += months;               // 增加月份
    mktime(&timeStruct);                       // 修正日期溢出
    time = std::mktime(&timeStruct);
}
// 显示任务详情
void Task::showTaskDetail(int id) {
    if (id != taskId) {
        std::cout << "未找到任务 (ID: " << id << ")！" << std::endl;
        return;
    }

    std::cout << "任务详情：" << std::endl;
    std::cout << "ID: " << taskId << std::endl;
    std::cout << "名称: " << taskName << std::endl;
    std::cout << "描述: " << description << std::endl;
    std::cout << "创建时间: " << formatTime(createTime) << std::endl;
    std::cout << "更新时间: " << formatTime(updateTime) << std::endl;
    std::cout << "截止时间: " << formatTime(dueTime) << std::endl;
    std::cout << "是否完成: " << (isCompleted ? "是" : "否") << std::endl;
    std::cout << "循环类型: " << (recurrenceType == NONE ? "无" :
                                       recurrenceType == DAILY ? "每日" :
                                       recurrenceType == WEEKLY ? "每周" : "每月") << std::endl;
    std::cout << "下次截止时间: " << formatTime(nextDueTime) << std::endl;
}