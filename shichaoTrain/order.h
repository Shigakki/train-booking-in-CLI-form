//
// Created by Shichao on 2022/11/20.
//

#ifndef TRAINCACHE_ORDER_H
#define TRAINCACHE_ORDER_H

#include <utility>

#include "User.h"
#include "ticket.h"


typedef struct order{
    std::string orderId;
    std::string trainId;
    std::string userId;
    Ticket ticket;
    int departureStation;
    int targetStation;
    std::string dStationName;
    std::string tStationName;
    int fare;

    // 无参构造
    order(){}
    // 列表初始化
    order(std::string orderId, std::string trainId, std::string userId,
          Ticket ticket, int dStation, int tStation)
     :orderId(std::move(orderId)),trainId(std::move(trainId)),userId(std::move(userId)),
      ticket(ticket),departureStation(dStation),targetStation(tStation){}
}Order;

#endif //TRAINCACHE_ORDER_H
