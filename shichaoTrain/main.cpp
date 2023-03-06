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
    // 起始初始化可以顺便做这个，初始化实质上为不断增加
    for(auto & vectorStation : t.vectorStations){
        vectorStation.trainId = trainId;
    }
    // 返回t，相当于返回了一堆东西，stations定义为有了train才是有意义的车站
    return t;
    // 这之后的工作就是订票，为订单
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
            cout << "查询到相关订单信息" << endl;
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
        cout << "没有找到相关用户的订单。" << endl;
    }
}

void searchTheOrderByStations(const string& fileName, int dStation, int tStaion){
    vector<Order> orders;
    orders = filesToOrders(fileName);
    for(auto & order : orders) {
        if (order.departureStation == dStation && order.targetStation == tStaion){
            cout << "找到查询的车次" << endl;
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
    cout << "当前总收入为:" << sum << endl;
}

User registerUser(const string& filePath){
    vector<User> users;
    users = filesToUsers(filePath);
    cout << "\n请输入您的个人信息" << endl;
    // string userId, userName, userSex;
    cout << "请输入您的用户编号、姓名、性别" << endl;
    string uId,uName,uSex;
    cout << "您的编号" << endl;
    cin >> uId;

    cout << "您的姓名" << endl;
    cin >> uName;
    cout << "您的性别" << endl;
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
    cout << "输入车站编号:" << endl;
    trainId = "海克斯科技-GGBB886";
    cout << "输入车站数目:" << endl;
    stationNum = 11;
    cout << "输入座位数目:" << endl;
    seatsNum = 12;
    STATIONNUM = stationNum;
    SEATNUM = seatsNum;
    TICKETNUM = seatsNum;
    cout << "车站数目:" << STATIONNUM << endl;
    cout << "座位数目:" << TICKETNUM << endl;
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
        cout << "\n请注册或者登录" << "输入数字 1登录，0进行注册" << endl;
        cin >> flag;
        if (flag){
            cout << "请输入您的用户姓名" << endl;
            cin >> userName;
            if (judgeUser(userPath,userName)){
                tips = 1;
                u = searchUser(userPath, userName);
            } else {
                cout << "未找到此用户名用户，请重试。" << endl;
            }
        } else {
            cout << "请输入您要注册的用户姓名" << endl;
            cin >> userName;
            if (!judgeUser(userPath,userName)){
                tips = 1;
                u = registerUser(userPath);
            } else {
                cout << "此用户名称已经被占领！" << endl;
            }
        }
    }

    vector<Order> orders;
    Tickets *soldTicket;
    int ticketId;
    string uname;
    while(true){
        cout << "\n=============================================" << endl;
        cout << "欢迎您, " << u.userName << " 先生" << endl;
        cout << "0 站点查询" << endl;
        cout << "1 根据起始站点和目的站点查询剩余车票" << endl;
        cout << "2 购买车票" << endl;
        cout << "3 查询已售出的所有车票" << endl;
        cout << "4 查询已售出的车票-根据起止车站" << endl;
        cout << "5 查询已售出的车票-根据用户姓名" << endl;
        cout << "6 退票-根据车票编号" << endl;
        cout << "7 查询当前所有已售车票收益" << endl;
        cout << "8 查询所有的用户" << endl;
        cout << "9 退出" << endl;
        cout << "请输入你的选择:" << endl;
        cin >> choice;
        printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        switch(choice){
            case 0:
                searchStations(stationFile);
                break;
            case 1:
                printf("出发车站:");
                scanf("%d",&dStation);
                printf("到达车站:");
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
                printf("出发车站:");
                scanf("%d",&dStation);
                printf("到达车站:");
                scanf("%d",&tStation);
                soldTicket = sellTickets(dStation, tStation);
                if(soldTicket == nullptr){
                    printf("无余票！\n");
                } else {
                    // 购票成功，生成一张车票，用ticket和seatId包装住
                    Ticket t(soldTicket->ticketId,soldTicket->seatId,
                               soldTicket->departureStation,soldTicket->targetStation);
                    // 把生成的票、起始终止车站、用户联系起来，形成order
                    order o(train.trainId+to_string(t.ticketId), train.trainId, u.userId,
                            t, dStation, tStation);
                    o.fare = (train.vectorStations[tStation-1].stationFare-train.vectorStations[dStation-1].stationFare);
                    o.dStationName = train.vectorStations[dStation-1].stationName;
                    o.tStationName = train.vectorStations[tStation-1].stationName;
                    orders.push_back(o);
                    insertFile(filePath, o);
                    printf("售票成功，生成售出车票与订单。\n");
                }
                break;
            case 3:
                querySoldTickets();
                break;
            case 4:
                printf("出发车站:");
                scanf("%d",&dStation);
                printf("到达车站:");
                scanf("%d",&tStation);
                searchTheOrderByStations(filePath, dStation, tStation);
                break;
            case 5:
                cout << "输入要查询的用户名称:" << endl;
                cin >> uname;
                searchTheOrderByName(filePath,uname);
                break;
            case 6:
                cout << "退票界面" << endl;
                cout << "根据ticketId进行删除" << endl;
                cin >> ticketId;
                deleteOrder(filePath, ticketId);
                initTickets(train.stationNum, train.seatsNum);
                updateTickets(train.trainId, filePath);
                break;
            case 7:
                searchSum(filePath);
                break;
            case 8:
                cout << "所有的用户:" << endl;
                searchAllusers(userPath);
                break;
            case 9:
                exit(0);
            default:
                cout << "命令输入错误，请输入 help 进行命令查询" << endl;
                break;
        }
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    }
}
