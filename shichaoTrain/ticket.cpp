//
// Created by Shichao on 2022/11/19.
//

#include "ticket.h"
using namespace std;

int TICKETNUM;
int SEATNUM;
int STATIONNUM;

// create��������ڵ�
TicketNode *createTicket(int tId, int sId, int dStation, int tStation){
    auto *pTicketNode = new TicketNode();
//    assert(pTicketNode != nullptr);
    pTicketNode->ticketId = tId;
    pTicketNode->seatId = sId;
    pTicketNode->departureStation = dStation;
    pTicketNode->targetStation = tStation;
    return pTicketNode;
}

// append,���insert����ȷ������
void appendNode(TicketNode *nodeList, TicketNode *pNode) {
    while (nodeList->pNext != nullptr){
        nodeList = nodeList->pNext;
    }
    pNode->pNext = nullptr;
    nodeList->pNext = pNode;
}

// deleteɾ���ڵ�
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

// TicketNode�����һ�ų�Ʊ������ָ����Խ�������Խ�ã���ƫ�����ȳ���
int getTicketScore(TicketNode *pNode, int dStation, int tStation) {
    if (dStation >= tStation || dStation < 1 || tStation > STATIONNUM) {
        cout << "������վ�򵽴ﳵվ��д���������¼�������д��" << endl;
        return -1;
    } else if(pNode->departureStation > dStation || pNode->targetStation < tStation){
        return -2;
    }
    int score = ((dStation - pNode->departureStation) + (pNode->targetStation - tStation));
    return score;
}

/**
 * ��ѯ��ֺö���
 * 1.��ѯ��ǰ���еģ������������Ʊ��
 * 2.��ѯ�ɹ���ģ�����Ʊ���Է�֮���Ʊ��
 * 3.��ѯ�Ѿ��۳��ĳ�Ʊ
 */
// 1.queryAllAvailableTickets
int queryAllAvailableTickets(int dStation, int tStation) {
    int tickets = 0;
    // ��ÿ���Ʊ��ָ��ͷ��pNext��Ҳ���ǵ�һ��Ʊָ��
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
        cout << "����վ��" <<  pNode->departureStation << " --> "
             << "����վ��" <<  pNode->targetStation << " --> "
             << "��λ��" << pNode->seatId << " --> "
             << "��Ʊ����" << pNode->ticketId<< endl;
        pNode = pNode->pNext;
    }
}
//sellTickets
Tickets* sellTickets(int dStation, int tStation) {
    // �趨��ʼscore����Ϊһ���ܴ��������ΪscoreԽСԽ��
    int tmpScore = 0x0FFFFFF;
    // ��ȡ��ǰ����Ʊ����
    TicketNode *pNodes = availableTicketsHead.pNext;
    // ����Ҫ�õ��ı���
    TicketNode *pTmp,*pBefore, *pAfter, *pMid;
    while (pNodes != nullptr) { //  ����һ��
        int score = getTicketScore(pNodes, dStation, tStation);
        if (score > 0 && score < tmpScore) {
            tmpScore = score;
            pTmp = pNodes;
        }else if (score == -1 || score == -2){
        }
        pNodes = pNodes->pNext;
    }
    // ��tmpScoreû�иı䣬Ҳ����û�з��ϵ�score�ڵ�ĵ�ʱ��
    if (tmpScore == 0x0FFFFFF){
        cout << "û�пɹ���ĳ�Ʊ��" << endl;
    }
    // �����������ʵ�൱��else������ǰ��
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
    } cout << "�ɹ���ʼ����Ʊ" << endl;
    cout << "��λ��" << seatsNum << "վ����" << stationNum << endl;
    return availableTicketsHead;
}