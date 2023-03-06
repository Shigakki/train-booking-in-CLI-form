//
// Created by Shichao on 2022/11/20.
//

#ifndef TRAINCACHE_USER_H
#define TRAINCACHE_USER_H

#include <string>
#include <utility>
#include <vector>

class User {
public:
    // 列表初始化
    User(std::string userId, std::string userName, std::string userSex)
     :userId(std::move(userId)),
      userName(std::move(userName)),
      userSex(std::move(userSex)){}
    User(){};
    std::string userId;
    std::string userName;
    std::string userSex;
};

#endif //TRAINCACHE_USER_H
