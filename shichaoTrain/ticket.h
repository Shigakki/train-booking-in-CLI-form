//
// Created by Shichao on 2022/11/19.
//

#ifndef TICKET_H
#define TICKET_H

#include <iostream>
class ticket {};
/**
 * �ṹ����������
 */
// ��Ʊ�ṹ������

typedef struct Ticket {
    int ticketId; // ��ʵûɶ��
    int seatId; // ��λ��
    int departureStation; // ������վ����ʼ��Ϊ1
    int targetStation; // ���ﳵվ����ʼ��Ϊ12

    Ticket(){}
    Ticket(int tId, int sId, int dStation, int tStation)
     :ticketId(tId),seatId(sId),departureStation(dStation),targetStation(tId){}
}Ticket;

typedef struct Tickets {
    int ticketId; // ��ʵûɶ��
    int seatId; // ��1��ʼ��M����λ��
    int departureStation; // ������վ
    int targetStation; // ���ﳵվ
    struct Tickets *pNext = nullptr;
}TicketNode;
// ��ʼ����������,����ע��ʹ��static���ö�γ�ʼ������
static TicketNode availableTicketsHead = {0, 0,
                               0, 0,
                               nullptr};
static TicketNode soldTicketsHead = {0, 0,
                          0, 0,
                          nullptr};
/**
 * ��������
 * @param tId
 * @param sId
 * @param dStation
 * @param tStation
 * @return
 */
// create��������ڵ�
TicketNode *createTicket(int tId, int sId, int dStation, int tStation);
// append,���insert����ȷ������
void appendNode(TicketNode *nodeList, TicketNode *pNode);
// deleteɾ���ڵ�
void deleteNode(TicketNode *nodeList, TicketNode *pNode);
// TicketNode�����һ�ų�Ʊ������ָ����Խ�������Խ�ã���ƫ�����ȳ���
int getTicketScore(TicketNode *pNode, int dStation, int tStation);
/**
 * ��ѯ��ֺö���
 * 1.��ѯ��ǰ���еģ������������Ʊ��
 * 2.��ѯ�ɹ���ģ�����Ʊ���Է�֮���Ʊ��
 * 3.��ѯ�Ѿ��۳��ĳ�Ʊ
 */
// 1.queryAllAvailableTickets
int queryAllAvailableTickets(int dStation, int tStation);
// 2.querySoldTickets
int querySoldTickets();
// ��Ʊ���൱������Ʊ,�����۳���Ʊ�Ľڵ�
Tickets* sellTickets(int dStation, int tStation);
// ��ʼ��ϵͳ������ָ������λ���ͳ�վ��
Tickets initTickets(int stationNum,int seatsNum);
#endif //TICKET_H