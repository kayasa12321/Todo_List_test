#include<iostream>
#include"./headers/taskmanager.hpp"
#include <iomanip>
#include<fstream>
#include<sstream>

// 添加任务
void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}
// 显示所有任务
void TaskManager::displayAllTasks() const {
    printTasks(tasks);
}
// 筛选任务：根据日期范围
std::vector<Task> TaskManager::filterTasksByDateRange(std::time_t startDate, std::time_t endDate) const {
    std::vector<Task> result;
    for (const auto& task : tasks) {
        if (task.dueTime >= startDate && task.dueTime <= endDate) {
            result.push_back(task);
        }
    }
    return result;
}
// 筛选任务：今日任务
std::vector<Task> TaskManager::filterTasksByToday() const {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::tm startOfDay = *localTime;
    startOfDay.tm_hour = 0;
    startOfDay.tm_min = 0;
    startOfDay.tm_sec = 0;
    std::time_t startDate = std::mktime(&startOfDay);

    std::tm endOfDay = *localTime;
    endOfDay.tm_hour = 23;
    endOfDay.tm_min = 59;
    endOfDay.tm_sec = 59;
    std::time_t endDate = std::mktime(&endOfDay);

    return filterTasksByDateRange(startDate, endDate);
}
// 筛选任务：本周任务
std::vector<Task> TaskManager::filterTasksByThisWeek() const {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    int dayOfWeek = (localTime->tm_wday + 6) % 7; // 将周日设为6，周一设为0
    std::tm startOfWeek = *localTime;
    startOfWeek.tm_mday -= dayOfWeek;
    startOfWeek.tm_hour = 0;
    startOfWeek.tm_min = 0;
    startOfWeek.tm_sec = 0;
    std::time_t startDate = std::mktime(&startOfWeek);

    std::tm endOfWeek = startOfWeek;
    endOfWeek.tm_mday += 6;
    endOfWeek.tm_hour = 23;
    endOfWeek.tm_min = 59;
    endOfWeek.tm_sec = 59;
    std::time_t endDate = std::mktime(&endOfWeek);

    return filterTasksByDateRange(startDate, endDate);
}
// 筛选任务：本月任务
std::vector<Task> TaskManager::filterTasksByThisMonth() const {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::tm startOfMonth = *localTime;
    startOfMonth.tm_mday = 1;
    startOfMonth.tm_hour = 0;
    startOfMonth.tm_min = 0;
    startOfMonth.tm_sec = 0;
    std::time_t startDate = std::mktime(&startOfMonth);

    std::tm endOfMonth = startOfMonth;
    endOfMonth.tm_mon += 1;
    endOfMonth.tm_mday = 1;
    std::time_t endDate = std::mktime(&endOfMonth) - 1;

    return filterTasksByDateRange(startDate, endDate);
}
// 交互式任务筛选和显示
void TaskManager::interactiveFilterAndDisplay() const {
    std::cout << "请选择筛选类型：1=今日任务，2=本周任务，3=本月任务: ";
    int choice;
    std::cin >> choice;

    std::vector<Task> filteredTasks;
    switch (choice) {
        case 1:
            filteredTasks = filterTasksByToday();
            break;
        case 2:
            filteredTasks = filterTasksByThisWeek();
            break;
        case 3:
            filteredTasks = filterTasksByThisMonth();
            break;
        default:
            std::cout << "无效选择！" << std::endl;
            return;
    }

    std::cout << "筛选结果：" << std::endl;
    printTasks(filteredTasks);
}
// 打印任务列表
void TaskManager::printTasks(const std::vector<Task>& tasks) {
    if(tasks.size()==0){std::cout<<"当前没有任务\n";return ;};
    for (const auto& task : tasks) {
        std::cout << "任务 ID: " << task.taskId << "\n"
                  << "任务名: " << task.taskName << "\n"
                  << "截止时间: " << std::put_time(std::localtime(&task.dueTime), "%Y-%m-%d %H:%M:%S") << "\n"
                  << "-------------------------" << std::endl;
    }
}
void TaskManager::addTask() {
    Task newTask;
    newTask.addTask();
    tasks.push_back(newTask);
}
void TaskManager::deleteTask() {
    std::cout << "请输入要删除的任务ID: ";
    int id;
    std::cin >> id;
    std::cin.ignore();

    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.taskId == id; });
    if (it != tasks.end()) {
        tasks.erase(it);
        delete &it;
        std::cout << "任务已删除成功!" << std::endl;
    } else {
        std::cout << "未找到指定ID的任务!" << std::endl;
    }
}
void TaskManager::updateTask() {
    std::cout << "请输入要更新的任务ID: ";
    int id;
    std::cin >> id;
    std::cin.ignore();

    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.taskId == id; });
    if (it != tasks.end()) {
        it->updateTask();
    } else {
        std::cout << "未找到指定ID的任务!" << std::endl;
    }
}
void TaskManager::readTasks()  {
    std::cout << "请输入要展示的任务ID: ";
    int id;
    std::cin >> id;
    std::cin.ignore();
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {return task.taskId == id;});
    if (it != tasks.end()) {
        it->showTaskDetail(id);
    } 
    else {
        std::cout << "未找到指定ID的任务!" << std::endl;
    }
    std::cout << "任务列表: " << std::endl;
    for (const auto& task : tasks) {
        std::cout << "任务ID: " << task.taskId << std::endl;
        std::cout << "标题: " << task.taskName << std::endl;
        std::cout << "描述: " << task.description << std::endl;
        std::cout << "创建时间: " << std::ctime(&task.createTime);
        std::cout << "任务时间: " << std::ctime(&task.dueTime);
    }
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
void TaskManager::saveToFile() {
    std::ofstream outFile(owner + "_tasks.dat", std::ios::binary);
    if (outFile.is_open()) {
        for (const auto& task : tasks) {
            outFile.write(reinterpret_cast<const char*>(&task), sizeof(Task));
        }
        outFile.close();
        std::cout << "任务已保存!" << std::endl;
    } else {
        std::cerr << "无法打开文件进行保存!" << std::endl;
    }
}

// 从文件加载任务
void TaskManager::loadFromFile() {
    std::ifstream inFile(owner + "_tasks.dat", std::ios::binary);
    if (inFile.is_open()) {
        Task task;
        while (inFile.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
            tasks.push_back(task);
        }
        inFile.close();
        std::cout << "任务已加载!" << std::endl;
    } else {
        std::cerr << "无法打开文件进行加载!" << std::endl;
    }
}