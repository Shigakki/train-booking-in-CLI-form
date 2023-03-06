//
// Created by Shichao on 2022/11/19.
//

#include "ticket.h"
using namespace std;

int TICKETNUM;
int SEATNUM;
int STATIONNUM;

// create创建链表节点
TicketNode *createTicket(int tId, int sId, int dStation, int tStation){
    auto *pTicketNode = new TicketNode();
//    assert(pTicketNode != nullptr);
    pTicketNode->ticketId = tId;
    pTicketNode->seatId = sId;
    pTicketNode->departureStation = dStation;
    pTicketNode->targetStation = tStation;
    return pTicketNode;
}

// append,相比insert更精确的描述
void appendNode(TicketNode *nodeList, TicketNode *pNode) {
    while (nodeList->pNext != nullptr){
        nodeList = nodeList->pNext;
    }
    pNode->pNext = nullptr;
    nodeList->pNext = pNode;
}

// delete删除节点
void deleteNode(TicketNode *nodeList, TicketNode *pNode) {
    while (nodeList != nullptr){
        if (nodeList->pNext != pNode){
            nodeList = nodeList->pNext;
            continue;
        }
        nodeList->pNext = pNode->pNext;
        free(pNode);
        break;
    }
}
void insertNode(TicketNode *nodeList, TicketNode *pNode){

}

// TicketNode代表的一张车票的评价指数，越低则代表越好，更偏向首先出售
int getTicketScore(TicketNode *pNode, int dStation, int tStation) {
    if (dStation >= tStation || dStation < 1 || tStation > STATIONNUM) {
        cout << "出发车站或到达车站填写错误！请重新检查后再填写。" << endl;
        return -1;
    } else if(pNode->departureStation > dStation || pNode->targetStation < tStation){
        return -2;
    }
    int score = ((dStation - pNode->departureStation) + (pNode->targetStation - tStation));
    return score;
}

/**
 * 查询会分好多种
 * 1.查询当前所有的，包含此区间的票数
 * 2.查询可购买的，即分票策略分之后的票数
 * 3.查询已经售出的车票
 */
// 1.queryAllAvailableTickets
int queryAllAvailableTickets(int dStation, int tStation) {
    int tickets = 0;
    // 获得可用票的指针头的pNext，也就是第一个票指针
    TicketNode *pNodes = availableTicketsHead.pNext;
    while (pNodes != nullptr){
        int score = getTicketScore(pNodes, dStation, tStation);
        if(score >= 0){
            tickets++;
        } else if (score == -1){
        }
        pNodes = pNodes->pNext;
    }
    return tickets;
}
// 2.querySoldTickets
int querySoldTickets() {
    TicketNode *pNode = soldTicketsHead.pNext;
    while (pNode != nullptr){
        cout << "出发站点" <<  pNode->departureStation << " --> "
             << "到达站点" <<  pNode->targetStation << " --> "
             << "座位号" << pNode->seatId << " --> "
             << "车票编码" << pNode->ticketId<< endl;
        pNode = pNode->pNext;
    }
}
//sellTickets
Tickets* sellTickets(int dStation, int tStation) {
    // 设定初始score分数为一个很大的数，因为score越小越好
    int tmpScore = 0x0FFFFFF;
    // 获取当前可用票链表
    TicketNode *pNodes = availableTicketsHead.pNext;
    // 以下要用到的变量
    TicketNode *pTmp,*pBefore, *pAfter, *pMid;
    while (pNodes != nullptr) { //  遍历一遍
        int score = getTicketScore(pNodes, dStation, tStation);
        if (score > 0 && score < tmpScore) {
            tmpScore = score;
            pTmp = pNodes;
        }else if (score == -1 || score == -2){
        }
        pNodes = pNodes->pNext;
    }
    // 当tmpScore没有改变，也就是没有符合的score节点的的时候
    if (tmpScore == 0x0FFFFFF){
        cout << "没有可购买的车票！" << endl;
    }
    // 下面的内容其实相当于else，即当前的
    pBefore = pAfter = pMid = nullptr;

    if (pTmp->departureStation < dStation){
        pBefore = createTicket(++TICKETNUM,pTmp->seatId,pTmp->departureStation, dStation);
        appendNode(&availableTicketsHead, pBefore);
    }
    if (pTmp->targetStation > tStation) {
        pAfter = createTicket(++TICKETNUM, pTmp->seatId, tStation, pTmp->targetStation);
        appendNode(&availableTicketsHead, pAfter);
    }
    pMid = createTicket(pTmp->ticketId,pTmp->seatId, dStation,tStation);

    appendNode(&soldTicketsHead, pMid);
    deleteNode(&availableTicketsHead, pTmp);

    return pMid;
}

//refundTickets
void refundTicket(Ticket* t){

}


// initTickets
Tickets initTickets(int stationNum,int seatsNum) {
     availableTicketsHead = {0, 0,
                                       0, 0,
                                       nullptr};
    soldTicketsHead = {0, 0,
                       0, 0,
                       nullptr};
    for (int i =1; i <= seatsNum; i++){
        appendNode(&availableTicketsHead,
                   createTicket(i, i,
                                1, stationNum));
    } cout << "成功初始化车票" << endl;
    cout << "座位数" << seatsNum << "站点数" << stationNum << endl;
    return availableTicketsHead;
}