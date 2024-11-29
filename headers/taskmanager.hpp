#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include"./task.hpp"
class TaskManager {
private:
    std::string owner;
    std::vector<Task> tasks; // 任务列表

public:
    // 获取任务列表
    TaskManager(std::string a):owner(a){};
    const std::vector<Task>& getTasks() const;
    // 添加任务
    void addTask(const Task& task);
    // 显示所有任务
    void displayAllTasks() const;
    // 筛选任务方法
    std::vector<Task> filterTasksByDateRange(std::time_t startDate, std::time_t endDate) const;
    std::vector<Task> filterTasksByToday() const;
    std::vector<Task> filterTasksByThisWeek() const;
    std::vector<Task> filterTasksByThisMonth() const;
    // 交互式任务筛选
    void interactiveFilterAndDisplay() const;
    // 打印任务列表
    static void printTasks(const std::vector<Task>& tasks);
    void addTask();         // 添加任务
    void deleteTask();      // 删除任务
    void updateTask();      // 更新任务
    void readTasks() ; // 查看任务
    //持久化保存
    void saveToFile();
    void loadFromFile();
};
#endif 