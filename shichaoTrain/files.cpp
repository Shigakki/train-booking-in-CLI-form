//
// Created by Shichao on 2022/11/20.
//
#include "files.h"
using namespace std;

// string类型转到int类型
int stringToInt(const string& s){
    int x;
    stringstream ss;
    ss << s;
    ss >> x;
    return x;
}

// 检测read读取的文件是否存在
int readFileIfExists(const string& fileName){
    string url = "../Files/" + fileName;
    ifstream readFile(url, ios::in);
    if (!readFile.is_open()){
        cout << "读取文件不存在哟" << endl;
        return 0;
    }
    readFile.close();
    return 1;
}

int writeFileIfExists(const string& fileName) {
    string url = "../Files/" + fileName;
    ofstream writeFile(url, ios::in);
    if (!writeFile.is_open()){
        cout << "写入文件不存在哦" << endl;
        return 1;
    }
    writeFile.close();
    return 0;
}

vector<vector<std::string>> readFile(const string& fileName){
    string url = "../Files/" + fileName;
    ifstream readFile(url, ios::in);
    if (!readFile.is_open()){
        cout << "读取文件" << url << "失败,请重试。" << endl;
        exit(0);
    }
    istringstream sin; //将整行字符串line读入到字符串istringstream中
    vector<vector<std::string>> lines;
    vector<std::string> words; //声明一个字符串向量
    string line;
    string word;

    cout << "\n" <<"开始阅读文件: " << url << endl;
    // 读取标题行
    std::getline(readFile, line);
    cout << line << endl;
    // 读取数据
    while (std::getline(readFile, line)){
        sin.clear();
        sin.str(line);
        words.clear();
        //将字符串流sin中的字符读到field字符串中，以逗号为分隔符
        while (std::getline(sin, word, ',')) {
            words.push_back(word); //将每一格中的数据逐个push
            cout << word << " ";
        } cout << "\n";
        lines.push_back(words);
    }
    cout << "\n" <<"当前文件存储在: " << url << endl;
    readFile.close();
    return lines;
}

void initWriteToFile(const string& fileName, const vector<string>& head){
    ofstream writeFile;
    string url = "../Files/" + fileName;

    writeFile.open(url, ios::app);


    if (!writeFile.is_open()){
        cout << "读取文件" << url << "失败,请重试。" << endl;
        writeFile.close();
        exit(1);
    } cout << "打开文件成功。" << endl;
    for (int i = 0; i < head.size(); i++ ){
        writeFile << head.at(i);
        if (i != head.size()-1 ) {
            writeFile << ",";
        }
    } writeFile << "\n";
    writeFile.close();
    cout << "初始化写入文件成功，当前文件存储在" << url <<endl;
}

void insertFile(const string& fileName, order o){
    ofstream writeFile;
    string url = "../Files/" + fileName;
    writeFile.open(url, ios::app);

    if (!writeFile.is_open()){
        cout << "读取文件" << url << "失败,请重试。" << endl;
        writeFile.close();
        exit(1);
    } cout << "打开文件成功。" << endl;

    writeFile << o.orderId << ',';
    writeFile << o.trainId << ',';
    writeFile << o.userId << ',';
    writeFile << o.ticket.seatId<< ',';
    writeFile << o.ticket.ticketId << ',';
    writeFile << o.ticket.departureStation << ',';
    writeFile << o.targetStation << ',';
    writeFile << o.dStationName << ',';
    writeFile << o.tStationName << ',';
    writeFile << o.fare << '\n';

    writeFile.close();
    cout << "写入文件成功，当前文件存储在" << url <<endl;
}

void updateFiles(const string& fileName, const vector<order>& tuple) {
    ofstream writeFile;
    string url = "../Files/" + fileName;

    writeFile.open(url, ios::app);


    if (!writeFile.is_open()){
        cout << "读取文件" << url << "失败,请重试。" << endl;
        writeFile.close();
        exit(1);
    } cout << "打开文件成功。" << endl;

    for (const auto & i : tuple){
        writeFile << i.orderId << ',';
        writeFile << i.trainId << ',';
        writeFile << i.userId << ',';
        writeFile << i.ticket.seatId<< ',';
        writeFile << i.ticket.ticketId << ',';
        writeFile << i.ticket.departureStation << ',';
        writeFile << i.targetStation << ',';
        writeFile << i.dStationName << ',';
        writeFile << i.tStationName << ',';
        writeFile << i.fare << '\n';
    }
    writeFile.close();
    cout << "写入文件成功，当前文件存储在" << url <<endl;
}

vector<StationTuple> initStations(const string& fileName){
    vector<StationTuple> stationsTuple;
    StationTuple stationTuple;
    vector<vector<std::string>> lines = readFile(fileName);
    for(auto & line : lines) {
        stationTuple.stationId = stringToInt(line[0]);
        stationTuple.stationName = line[1];
        stationTuple.stationFare = stringToInt(line[2]);
        stationsTuple.push_back(stationTuple);
    }
    cout << "\n" << "成功初始化车站" << endl;
    return stationsTuple;
}

vector<Ticket> recoverTickets (const string& trainId, const string& fileName) {
    vector<Ticket> ticketsRecovery;
    Ticket ticket;
    vector<vector<std::string>> lines = readFile(fileName);
    for(auto & line : lines) {
        ticket.ticketId = stringToInt(line[4]);
        ticket.seatId = stringToInt(line[3]);
        ticket.departureStation = stringToInt(line[5]);
        ticket.targetStation = stringToInt(line[6]);
        ticketsRecovery.push_back(ticket);
    }
    cout << "成功恢复列车" << trainId << "的历史车票记录!" << endl;
    return ticketsRecovery;
}

vector<Order> filesToOrders(const string& fileName) {
    vector<vector<std::string>> lines = readFile(fileName);
    vector<Order> orders;
    // 这里记得首先做一个空的构造函数
    Order order;

    for(auto & line :  lines){
        order.orderId = line[0];
        order.trainId = line[1];
        order.userId = line[2];
        order.ticket.seatId = stringToInt(line[3]);
        order.ticket.ticketId = stringToInt(line[4]);
        order.departureStation = stringToInt(line[5]);
        order.targetStation = stringToInt(line[6]);
        order.dStationName = line[7];
        order.tStationName = line[8];
        order.fare = stringToInt(line[9]);
        orders.push_back(order);
    }
    cout << "得到整个订单数据并封装成了向量！"<< endl;
    return orders;
}

void deleteOrder(const string& fileName, int ticketId) {
    vector<Order> orders;
    orders = filesToOrders(fileName);

    ofstream writeFile;
    string url = "../Files/" + fileName;

    writeFile.open(url, ios::out);

    if (!writeFile.is_open()){
        cout << "读取文件" << url << "失败,请重试。" << endl;
        writeFile.close();
        exit(1);
    } cout << "打开文件成功。" << endl;

    vector<string> head = {"orderId","trainId","userId","seatId","ticketId",
                           "departureStation","targetStation","dStationName","tStationName","fare"};

    for (int i = 0; i < head.size(); i++ ){
        writeFile << head.at(i);
        if (i != head.size()-1 ) {
            writeFile << ",";
        }
    } writeFile << "\n";
    for (const auto & i : orders){
        if (i.ticket.ticketId != ticketId) {
            writeFile << i.orderId << ',';
            writeFile << i.trainId << ',';
            writeFile << i.userId << ',';
            writeFile << i.ticket.seatId<< ',';
            writeFile << i.ticket.ticketId << ',';
            writeFile << i.departureStation << ',';
            writeFile << i.targetStation << ',';
            writeFile << i.dStationName<< ',';
            writeFile << i.tStationName << ',';
            writeFile << i.fare << '\n';
        }
    }
    writeFile.close();
    cout << "写入文件成功，当前文件存储在" << url <<endl;

}

vector<User> filesToUsers(const string& fileName){
    vector<vector<std::string>> lines = readFile(fileName);
    vector<User> users;
    // 这里记得首先做一个空的构造函数
    User user;

    for (auto & line: lines){
        user.userId = line[0];
        user.userName = line[1];
        user.userSex = line[2];
        users.push_back(user);
    }
    cout << "得到整个用户数据都封装成了向量！"<< endl;
    return users;
}

void insertUsers(const string& fileName, const User& user){
    ofstream writeFile;
    string url = "../Files/" + fileName;
    writeFile.open(url, ios::app);

    if (!writeFile.is_open()){
        cout << "读取文件" << url << "失败,请重试。" << endl;
        writeFile.close();
        exit(1);
    } cout << "打开文件成功。" << endl;

    writeFile << user.userId << ',';
    writeFile << user.userName << ',';
    writeFile << user.userSex << '\n';

    writeFile.close();
    cout << "写入文件成功，当前文件存储在" << url <<endl;
}