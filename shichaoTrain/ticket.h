//
// Created by Shichao on 2022/11/19.
//

#ifndef TICKET_H
#define TICKET_H

#include <iostream>
class ticket {};
/**
 * 结构体与链表定义
 */
// 车票结构链表定义

typedef struct Ticket {
    int ticketId; // 其实没啥用
    int seatId; // 座位号
    int departureStation; // 出发车站，初始化为1
    int targetStation; // 到达车站，初始化为12

    Ticket(){}
    Ticket(int tId, int sId, int dStation, int tStation)
     :ticketId(tId),seatId(sId),departureStation(dStation),targetStation(tId){}
}Ticket;

typedef struct Tickets {
    int ticketId; // 其实没啥用
    int seatId; // 从1开始到M的座位号
    int departureStation; // 出发车站
    int targetStation; // 到达车站
    struct Tickets *pNext = nullptr;
}TicketNode;
// 初始化两个链表,这里注意使用static放置多次初始化报错
static TicketNode availableTicketsHead = {0, 0,
                               0, 0,
                               nullptr};
static TicketNode soldTicketsHead = {0, 0,
                          0, 0,
                          nullptr};
/**
 * 函数声明
 * @param tId
 * @param sId
 * @param dStation
 * @param tStation
 * @return
 */
// create创建链表节点
TicketNode *createTicket(int tId, int sId, int dStation, int tStation);
// append,相比insert更精确的描述
void appendNode(TicketNode *nodeList, TicketNode *pNode);
// delete删除节点
void deleteNode(TicketNode *nodeList, TicketNode *pNode);
// TicketNode代表的一张车票的评价指数，越低则代表越好，更偏向首先出售
int getTicketScore(TicketNode *pNode, int dStation, int tStation);
/**
 * 查询会分好多种
 * 1.查询当前所有的，包含此区间的票数
 * 2.查询可购买的，即分票策略分之后的票数
 * 3.查询已经售出的车票
 */
// 1.queryAllAvailableTickets
int queryAllAvailableTickets(int dStation, int tStation);
// 2.querySoldTickets
int querySoldTickets();
// 售票，相当于买卖票,返回售出的票的节点
Tickets* sellTickets(int dStation, int tStation);
// 初始化系统变量，指的是座位数和车站数
Tickets initTickets(int stationNum,int seatsNum);
#endif //TICKET_H