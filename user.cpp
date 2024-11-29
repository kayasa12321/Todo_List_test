#include "./headers/user.hpp"
#include <iostream>
#include <regex>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>

// 静态成员初始化
//User User::defaultUser();

// 初始化
User::User()
    : name("Default User"), emailAddr("default@example.com"), phone("0000000000"), password("default"), isLoggedIn(false),taskManager("Default User") {}
User::User(const std::string& n, const std::string& email, const std::string& p, const std::string& pass)
    : name(n), emailAddr(email), phone(p), password(pass), isLoggedIn(false),taskManager(n) {}
// 帐号相关操作
void User::login() {
    if (!isLoggedIn) {
        std::cout << "请输入用户名: ";
        std::string inputName;
        std::cin >> inputName;

        if (userExists(inputName)) {
            *this = loadFromFile(inputName); // 加载用户信息及任务
            std::cout << "请输入密码: ";
            std::string inputPassword;
            std::cin >> inputPassword;
            if (inputPassword == password) {
                isLoggedIn = true;
                std::cout << "登录成功!" << std::endl;
            } else {
                std::cout << "密码错误!" << std::endl;
            }
        } else {
            std::cout << "用户名不存在!" << std::endl;
        }
    } else {
        std::cout << "用户已登录，无需重复登录。" << std::endl;
    }
}

void User::registerUser() {
    std::cout << "请输入用户名: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    // 检查用户名是否已存在
    while (userExists(name)) {
        std::cout << "该用户名已被使用，请选择一个不同的用户名: ";
        std::getline(std::cin, name);
    }

    std::cout << "请输入邮箱地址: ";
    std::getline(std::cin, emailAddr);
    while (!isValidEmail(emailAddr)) {
        std::cout << "无效的邮箱地址，请重新输入: ";
        std::getline(std::cin, emailAddr);
    }

    std::cout << "请输入电话号码: ";
    std::getline(std::cin, phone);
    while (!isValidPhone(phone)) {
        std::cout << "无效的电话号码，请重新输入: ";
        std::getline(std::cin, phone);
    }

    std::cout << "请输入密码: ";
    std::getline(std::cin, password);
    while (password.length() < 6) { // 密码最小长度
        std::cout << "密码长度不能小于6个字符，请重新输入: ";
        std::getline(std::cin, password);
    }

    // 保存用户信息
    if (saveToFile()) {
        std::cout << "注册成功!" << std::endl;
    } else {
        std::cout << "注册失败，用户信息保存失败!" << std::endl;
    }
}

void User::logout() {
    if (isLoggedIn) {
        isLoggedIn = false;
        std::cout << "注销成功!" << std::endl;
    } else {
        std::cout << "用户未登录，无需注销。" << std::endl;
    }
}

void User::resetPassword() {
    std::cout << "请输入新密码: ";
    std::cin.ignore();
    std::getline(std::cin, password);
    while (password.length() < 6) { // 密码最小长度
        std::cout << "密码长度不能小于6个字符，请重新输入: ";
        std::getline(std::cin, password);
    }
    std::cout << "密码重置成功!" << std::endl;
}

void User::updateUserInfo() {
    std::cout << "请输入新的用户名 (当前: " << name << "): ";
    std::getline(std::cin, name);

    std::cout << "请输入新的邮箱地址 (当前: " << emailAddr << "): ";
    std::getline(std::cin, emailAddr);
    while (!isValidEmail(emailAddr)) {
        std::cout << "无效的邮箱地址，请重新输入: ";
        std::getline(std::cin, emailAddr);
    }

    std::cout << "请输入新的电话号码 (当前: " << phone << "): ";
    std::getline(std::cin, phone);
    while (!isValidPhone(phone)) {
        std::cout << "无效的电话号码，请重新输入: ";
        std::getline(std::cin, phone);
    }

    std::cout << "信息更新成功!" << std::endl;

    // 更新保存
    saveToFile();
}

void User::showUserInfo() const {
    std::cout << "用户信息：" << std::endl;
    std::cout << "用户名: " << name << std::endl;
    std::cout << "邮箱: " << emailAddr << std::endl;
    std::cout << "电话: " << phone << std::endl;
}
// 任务相关操作
void User::getTaskReview() {
    std::cout << "任务回顾：" << std::endl;
    taskManager.displayAllTasks();
}
void User::filter_show(){
    taskManager.interactiveFilterAndDisplay();
}

void User::operateTASK(operate_num opt) {
    switch (opt) {
        case add:
            taskManager.addTask();
            break;
        case del:
            taskManager.deleteTask();
            break;
        case update:
            taskManager.updateTask();
            break;
        case read_task:
            taskManager.readTasks();
            break;
        default:
            std::cout << "无效的操作编号!" << std::endl;
            break;
    }
}
// 辅助函数
bool User::isValidEmail(const std::string& email) {
    // 简单的邮箱验证，正则表达式匹配
    const std::regex pattern(R"((\w+)(\.\w+)*@(\w+\.)+[a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}
bool User::isValidPhone(const std::string& phone) {
    // 简单的电话号码验证：假设为 10 位数字
    return phone.length() == 10 && std::all_of(phone.begin(), phone.end(), ::isdigit);
}
void User::remind(){
    //waiting to do
}
//持久化处理
bool User::saveToFile() {
    std::ofstream userFile(name + ".txt");
    if (!userFile.is_open()) {
        return false;
    }
    
    userFile << name << std::endl;
    userFile << emailAddr << std::endl;
    userFile << phone << std::endl;
    userFile << password << std::endl;

    // 保存任务列表
    taskManager.saveToFile();

    userFile.close();
    allUsernames.push_back(name);  // 添加到用户名列表
    return true;
}

User User::loadFromFile(const std::string& name) {
    std::ifstream userFile(name + ".txt");
    if (!userFile.is_open()) {
        std::cerr << "无法加载用户数据!" << std::endl;
        return User();
    }

    std::string n, email, phone, pass;
    std::getline(userFile, n);
    std::getline(userFile, email);
    std::getline(userFile, phone);
    std::getline(userFile, pass);

    User user(n, email, phone, pass);
    user.isLoggedIn = true;

    // 加载任务列表
    user.taskManager.loadFromFile();

    userFile.close();
    return user;
}

bool User::userExists(const std::string& name) {
    return std::find(allUsernames.begin(), allUsernames.end(), name) != allUsernames.end();
}

bool User::emailExists(const std::string& email) {
    for (const auto& username : allUsernames) {
        User user = loadFromFile(username); // 加载用户
        if (user.emailAddr == email) {
            return true;
        }
    }
    return false;
}

bool User::loadAllUsers() {
    // 加载所有用户的用户名
    std::ifstream userListFile("users.txt");
    if (!userListFile.is_open()) {
        return false;
    }

    std::string username;
    while (std::getline(userListFile, username)) {
        allUsernames.push_back(username);
    }

    userListFile.close();
    return true;
}