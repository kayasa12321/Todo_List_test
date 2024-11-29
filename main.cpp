#include <iostream>
#include <string>
#include "./headers/task.hpp"
#include "./headers/user.hpp"
#include "./headers/taskmanager.hpp"
#include "./headers/reminder.hpp"
#include <cstdlib>

void showLoginMenu() {
    std::cout << "\n请选择操作：" << std::endl;
    std::cout << "1. 注册账户" << std::endl;
    std::cout << "2. 登录" << std::endl;
    std::cout << "3. 退出" << std::endl;
    std::cout << "4. 先不登录" << std::endl;
    std::cout << "请输入操作编号: ";
}

// 显示用户模块选择界面
void showUserModuleMenu(const std::string& username) {
    std::cout << "\n欢迎 " << username << "！请选择操作模块：" << std::endl;
    std::cout << "1. 帐号操作" << std::endl;
    std::cout << "2. 任务操作" << std::endl;
    std::cout << "3. 登出" << std::endl;
    std::cout << "请输入操作编号: ";
}

// 显示帐号操作界面
void showAccountMenu() {
    std::cout << "\n--- 帐号操作 ---" << std::endl;
    std::cout << "1. 查看帐号信息" << std::endl;
    std::cout << "2. 修改密码" << std::endl;
    std::cout << "3. 修改个人信息" << std::endl;
    std::cout << "4. 返回上一级" << std::endl;
    std::cout << "请输入操作编号: ";
}

// 显示任务操作界面
void showTaskMenu() {
    std::cout << "\n--- 任务操作 ---" << std::endl;
    std::cout << "1. 添加任务" << std::endl;
    std::cout << "2. 删除任务" << std::endl;
    std::cout << "3. 查看任务" << std::endl;
    std::cout << "4. 更新任务" << std::endl;
    std::cout << "5. 任务筛选" << std::endl;
    std::cout << "6. 返回上一级" << std::endl;
    std::cout << "请输入操作编号: ";
}

int main() {
    User user;  // 获取默认用户

    // 登录界面
    while (true) {
        ////system("cls");
        showLoginMenu();  // 显示登录菜单

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // 注册
            //system("cls");
            user.registerUser();
            std::cout << "注册成功！" << std::endl;
            break;
        } else if (choice == 2) {
            // 登录
            //system("cls");
            user.login();
            if (user.isLoggedIn) {
                break;
            }
        } else if (choice == 3) {
            std::cout << "退出程序..." << std::endl;
            return 0;
        } else if (choice == 4) {
            user.isLoggedIn == true;
            break;
        } else {
            //system("cls");
            std::cout << "无效操作，请重新选择！" << std::endl;
        }
    }

    // 用户登录成功后，显示帐号操作和任务操作模块
    while (true) {
        //system("cls");
        showUserModuleMenu(user.name);  // 显示用户模块菜单

        int moduleChoice;
        std::cin >> moduleChoice;

        if (moduleChoice == 1) {
            // 帐号操作模块
            while (true) {
                //system("cls");
                showAccountMenu();  // 显示帐号操作菜单

                int accountChoice;
                std::cin >> accountChoice;

                switch (accountChoice) {
                    case 1:
                        //system("cls");
                        user.showUserInfo();  // 显示用户信息
                        break;
                    case 2:
                        //system("cls");
                        user.resetPassword();  // 修改密码
                        break;
                    case 3:
                        //system("cls");
                        user.updateUserInfo();  // 修改个人信息
                        break;
                    case 4:
                        //system("cls");
                        std::cout << "返回上一级..." << std::endl;
                        break;
                    default:
                        //system("cls");
                        std::cout << "无效操作，请重新选择！" << std::endl;
                        break;
                }

                if (accountChoice == 4) { break;} // 返回上一级
            }
        } else if (moduleChoice == 2) {
            // 任务操作模块
            while (true) {
                //system("cls");
                showTaskMenu();  // 显示任务操作菜单
                
                int taskChoice;
                std::cin >> taskChoice;
                user.taskManager.displayAllTasks();
                switch (taskChoice) {
                    case 1:
                        //system("cls");
                        user.operateTASK(add);  // 添加任务
                        break;
                    case 2:
                        //system("cls");
                        user.operateTASK(del);  // 删除任务
                        break;
                    case 3:
                        //system("cls");
                        user.operateTASK(read_task);  // 查看任务
                        break;
                    case 4:
                        //system("cls");
                        user.operateTASK(update);  // 更新任务
                        break;
                    case 5:
                        //system("cls");
                        user.filter_show();  // 显示所有任务
                        break;
                    case 6:
                        //system("cls");
                        std::cout << "返回上一级..." << std::endl;
                        break;
                    default:
                        //system("cls");
                        std::cout << "无效操作，请重新选择！" << std::endl;
                        break;
                }

                if (taskChoice == 6) break;  // 返回上一级
            }
        } else if (moduleChoice == 3) {
            // 用户登出
            user.logout();
            std::cout << "已成功登出！" << std::endl;
            return 0;
        } else {
            std::cout << "无效操作，请重新选择！" << std::endl;
        }
    }

    return 0;
}
