#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "./taskmanager.hpp"

enum operate_num {
    add,
    del,
    update,
    read_task
};

class User {
public:
    std::string name;
    std::string emailAddr;
    std::string phone;
    std::string password;
    bool isLoggedIn;
    TaskManager taskManager; // 用 TaskManager 管理任务

    // User defaultUser();

    User();
    User(const std::string& n, const std::string& email, const std::string& p, const std::string& pass);

    void login();
    void registerUser();
    void logout();
    void resetPassword();
    void updateUserInfo();
    void getTaskReview();
    static User& getDefaultUser();
    void showUserInfo() const;
    bool isValidEmail(const std::string& email);
    bool isValidPhone(const std::string& phone);
    void operateTASK(operate_num opt); // 调用 TaskManager 的操作
    void filter_show();
    void remind();
    bool saveToFile(); // 保存用户信息到文件
     User loadFromFile(const std::string& name); // 根据用户名从文件加载用户
     bool userExists(const std::string& name); // 检查用户名是否存在
     bool emailExists(const std::string& email); // 检查邮箱是否已被注册
     bool loadAllUsers(); // 加载所有用户的用户名信息
    std::vector<std::string> allUsernames; // 存储所有用户名
};

#endif
