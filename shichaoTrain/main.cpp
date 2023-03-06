//
// Created by Shichao on 2022/11/19.
//

#include <utility>
#include <cstdio>

#include "ticket.h"
#include "Train.h"
#include "User.h"
#include "order.h"
#include "files.h"

using namespace std;

extern int TICKETNUM;
extern int SEATNUM;
extern int STATIONNUM;


Train initSystem(string trainId, const string& stationsFile, int stationsNum, int seatsNum) {
    Train t = Train(std::move(trainId), stationsNum, seatsNum);
    t.vectorStations = initStations(stationsFile);
    // ��ʼ��ʼ������˳�����������ʼ��ʵ����Ϊ��������
    for(auto & vectorStation : t.vectorStations){
        vectorStation.trainId = trainId;
    }
    // ����t���൱�ڷ�����һ�Ѷ�����stations����Ϊ����train����������ĳ�վ
    return t;
    // ��֮��Ĺ������Ƕ�Ʊ��Ϊ����
}

vector<Ticket> updateTickets(const string& trainId, const string& fileName) {
    Tickets *soldTicket;
    vector<Ticket> ticketsUpdate = recoverTickets(trainId, fileName);
    vector<Ticket> ticketsUpdated;
    for (auto & i : ticketsUpdate){
        int d = i.departureStation, t = i.targetStation;
        soldTicket = sellTickets(d, t);
        Ticket ticket(soldTicket->ticketId,soldTicket->seatId,
                 soldTicket->departureStation,soldTicket->targetStation);
        ticketsUpdated.push_back(ticket);
    }
    return ticketsUpdated;
}

void searchAllusers(const string& fileName){
    vector<User> users;
    users = filesToUsers(fileName);

    cout << "userId,userName,userSex" << endl;
    for(auto & user: users){
        cout << user.userId << ',';
        cout << user.userName << ',';
        cout << user.userSex<< endl;
    }
}

User searchUser(const string& fileName, const string& uName){
    vector<User> users;
    users = filesToUsers(fileName);
    User u;
    cout << "userId,userName,userSex" << endl;
    for(auto & user: users){
        if (user.userName == uName){
            u.userName = user.userName;
            u.userId = user.userId;
            u.userSex = user.userSex;
            cout << user.userId << ',';
            cout << user.userName << ',';
            cout << user.userSex<< endl;
        }
    }
    return u;
}

void searchStations(const string& fileName){
    readFile(fileName);
}

void searchTheOrderByName(const string& fileName, const string& userName){
    int flag = 0;
    string userId;

    vector<User> users;
    users = filesToUsers("user.csv");
    for(auto & user : users) {
        if (user.userName == userName){
            userId = user.userId;
            flag = 1;
        }
    }

    vector<Order> orders;
    orders = filesToOrders(fileName);
    for(auto & order : orders) {
        if (order.userId == userId){
            cout << "��ѯ����ض�����Ϣ" << endl;
            cout << "orderId,trainId,userId,seatId,ticketId,departureStation,targetStation,dStationName,tStationName,fare" << endl;
            cout << order.orderId << ',';
            cout << order.trainId << ',';
            cout << order.userId << ',';
            cout << order.ticket.seatId << ',';
            cout << order.ticket.ticketId << ',';
            cout << order.departureStation << ',';
            cout << order.targetStation << ',';
            cout << order.dStationName << ',';
            cout << order.tStationName << ',';
            cout << order.fare << endl;
        }
    }
    if (!flag){
        cout << "û���ҵ�����û��Ķ�����" << endl;
    }
}

void searchTheOrderByStations(const string& fileName, int dStation, int tStaion){
    vector<Order> orders;
    orders = filesToOrders(fileName);
    for(auto & order : orders) {
        if (order.departureStation == dStation && order.targetStation == tStaion){
            cout << "�ҵ���ѯ�ĳ���" << endl;
            cout << "orderId,trainId,userId,seatId,ticketId,departureStation,targetStation,fare" << endl;
            cout << order.orderId << ',';
            cout << order.trainId << ',';
            cout << order.ticket.seatId << ',';
            cout << order.ticket.ticketId << ',';
            cout << order.departureStation << ',';
            cout << order.targetStation << ',';
            cout << order.fare << endl;
        }
    }
}

void searchSum(const string& fileName){
    vector<Order> orders;
    int sum =0;
    orders = filesToOrders(fileName);
    for(auto & order : orders) {
        sum += order.fare;
    }
    cout << "��ǰ������Ϊ:" << sum << endl;
}

User registerUser(const string& filePath){
    vector<User> users;
    users = filesToUsers(filePath);
    cout << "\n���������ĸ�����Ϣ" << endl;
    // string userId, userName, userSex;
    cout << "�����������û���š��������Ա�" << endl;
    string uId,uName,uSex;
    cout << "���ı��" << endl;
    cin >> uId;

    cout << "��������" << endl;
    cin >> uName;
    cout << "�����Ա�" << endl;
    cin >> uSex;

    User u = User(uId, uName, uSex);

    insertUsers( filePath, u);

    users.push_back(u);

    return u;
}

int judgeUser(const string& filePath, const string& uName){
    int flag = 0;
    vector<User> users;
    users = filesToUsers(filePath);
    for (auto & user: users){
        if(user.userName == uName){
            flag = 1;
        }
    }
    return flag;
}

int main()
{
    string userPath = "user.csv";
    string filePath = "order.csv";
    string trainId, stationFile = "stations.csv";
    int stationNum, seatsNum, choice;
    int dStation, tStation, ticketsNum;
    cout << "���복վ���:" << endl;
    trainId = "����˹�Ƽ�-GGBB886";
    cout << "���복վ��Ŀ:" << endl;
    stationNum = 11;
    cout << "������λ��Ŀ:" << endl;
    seatsNum = 12;
    STATIONNUM = stationNum;
    SEATNUM = seatsNum;
    TICKETNUM = seatsNum;
    cout << "��վ��Ŀ:" << STATIONNUM << endl;
    cout << "��λ��Ŀ:" << TICKETNUM << endl;
    if(stationNum < 2 || seatsNum < 1)
    {
        printf("system param error\n");
        return 0;
    }
    Train train = initSystem(trainId, stationFile, stationNum, seatsNum);
    initTickets(train.stationNum, train.seatsNum);

    int flagRead = readFileIfExists(filePath);
    if (flagRead == 1){
        updateTickets(train.trainId, filePath);
    }

    vector<string> head = {"orderId","trainId","userId","seatId","ticketId",
                           "departureStation","targetStation","dStationName","tStationName","fare"};

    int flagWrite = writeFileIfExists(filePath);
    if (flagWrite == 1 ){
        initWriteToFile(filePath, head);
    }

    User u;
    int flag = 0, tips = 0;
    string userName;

    while (tips == 0){
        cout << "\n��ע����ߵ�¼" << "�������� 1��¼��0����ע��" << endl;
        cin >> flag;
        if (flag){
            cout << "�����������û�����" << endl;
            cin >> userName;
            if (judgeUser(userPath,userName)){
                tips = 1;
                u = searchUser(userPath, userName);
            } else {
                cout << "δ�ҵ����û����û��������ԡ�" << endl;
            }
        } else {
            cout << "��������Ҫע����û�����" << endl;
            cin >> userName;
            if (!judgeUser(userPath,userName)){
                tips = 1;
                u = registerUser(userPath);
            } else {
                cout << "���û������Ѿ���ռ�죡" << endl;
            }
        }
    }

    vector<Order> orders;
    Tickets *soldTicket;
    int ticketId;
    string uname;
    while(true){
        cout << "\n=============================================" << endl;
        cout << "��ӭ��, " << u.userName << " ����" << endl;
        cout << "0 վ���ѯ" << endl;
        cout << "1 ������ʼվ���Ŀ��վ���ѯʣ�೵Ʊ" << endl;
        cout << "2 ����Ʊ" << endl;
        cout << "3 ��ѯ���۳������г�Ʊ" << endl;
        cout << "4 ��ѯ���۳��ĳ�Ʊ-������ֹ��վ" << endl;
        cout << "5 ��ѯ���۳��ĳ�Ʊ-�����û�����" << endl;
        cout << "6 ��Ʊ-���ݳ�Ʊ���" << endl;
        cout << "7 ��ѯ��ǰ�������۳�Ʊ����" << endl;
        cout << "8 ��ѯ���е��û�" << endl;
        cout << "9 �˳�" << endl;
        cout << "���������ѡ��:" << endl;
        cin >> choice;
        printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        switch(choice){
            case 0:
                searchStations(stationFile);
                break;
            case 1:
                printf("������վ:");
                scanf("%d",&dStation);
                printf("���ﳵվ:");
                scanf("%d",&tStation);
                ticketsNum = queryAllAvailableTickets(dStation, tStation);
                if( ticketsNum  < 0){
                    printf("no tickets \n");
                }
                else{
                    printf("has %d tickets\n", ticketsNum);
                }
                break;
            case 2:
                printf("������վ:");
                scanf("%d",&dStation);
                printf("���ﳵվ:");
                scanf("%d",&tStation);
                soldTicket = sellTickets(dStation, tStation);
                if(soldTicket == nullptr){
                    printf("����Ʊ��\n");
                } else {
                    // ��Ʊ�ɹ�������һ�ų�Ʊ����ticket��seatId��װס
                    Ticket t(soldTicket->ticketId,soldTicket->seatId,
                               soldTicket->departureStation,soldTicket->targetStation);
                    // �����ɵ�Ʊ����ʼ��ֹ��վ���û���ϵ�������γ�order
                    order o(train.trainId+to_string(t.ticketId), train.trainId, u.userId,
                            t, dStation, tStation);
                    o.fare = (train.vectorStations[tStation-1].stationFare-train.vectorStations[dStation-1].stationFare);
                    o.dStationName = train.vectorStations[dStation-1].stationName;
                    o.tStationName = train.vectorStations[tStation-1].stationName;
                    orders.push_back(o);
                    insertFile(filePath, o);
                    printf("��Ʊ�ɹ��������۳���Ʊ�붩����\n");
                }
                break;
            case 3:
                querySoldTickets();
                break;
            case 4:
                printf("������վ:");
                scanf("%d",&dStation);
                printf("���ﳵվ:");
                scanf("%d",&tStation);
                searchTheOrderByStations(filePath, dStation, tStation);
                break;
            case 5:
                cout << "����Ҫ��ѯ���û�����:" << endl;
                cin >> uname;
                searchTheOrderByName(filePath,uname);
                break;
            case 6:
                cout << "��Ʊ����" << endl;
                cout << "����ticketId����ɾ��" << endl;
                cin >> ticketId;
                deleteOrder(filePath, ticketId);
                initTickets(train.stationNum, train.seatsNum);
                updateTickets(train.trainId, filePath);
                break;
            case 7:
                searchSum(filePath);
                break;
            case 8:
                cout << "���е��û�:" << endl;
                searchAllusers(userPath);
                break;
            case 9:
                exit(0);
            default:
                cout << "����������������� help ���������ѯ" << endl;
                break;
        }
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    }
}
