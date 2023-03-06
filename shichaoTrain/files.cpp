//
// Created by Shichao on 2022/11/20.
//
#include "files.h"
using namespace std;

// string����ת��int����
int stringToInt(const string& s){
    int x;
    stringstream ss;
    ss << s;
    ss >> x;
    return x;
}

// ���read��ȡ���ļ��Ƿ����
int readFileIfExists(const string& fileName){
    string url = "../Files/" + fileName;
    ifstream readFile(url, ios::in);
    if (!readFile.is_open()){
        cout << "��ȡ�ļ�������Ӵ" << endl;
        return 0;
    }
    readFile.close();
    return 1;
}

int writeFileIfExists(const string& fileName) {
    string url = "../Files/" + fileName;
    ofstream writeFile(url, ios::in);
    if (!writeFile.is_open()){
        cout << "д���ļ�������Ŷ" << endl;
        return 1;
    }
    writeFile.close();
    return 0;
}

vector<vector<std::string>> readFile(const string& fileName){
    string url = "../Files/" + fileName;
    ifstream readFile(url, ios::in);
    if (!readFile.is_open()){
        cout << "��ȡ�ļ�" << url << "ʧ��,�����ԡ�" << endl;
        exit(0);
    }
    istringstream sin; //�������ַ���line���뵽�ַ���istringstream��
    vector<vector<std::string>> lines;
    vector<std::string> words; //����һ���ַ�������
    string line;
    string word;

    cout << "\n" <<"��ʼ�Ķ��ļ�: " << url << endl;
    // ��ȡ������
    std::getline(readFile, line);
    cout << line << endl;
    // ��ȡ����
    while (std::getline(readFile, line)){
        sin.clear();
        sin.str(line);
        words.clear();
        //���ַ�����sin�е��ַ�����field�ַ����У��Զ���Ϊ�ָ���
        while (std::getline(sin, word, ',')) {
            words.push_back(word); //��ÿһ���е��������push
            cout << word << " ";
        } cout << "\n";
        lines.push_back(words);
    }
    cout << "\n" <<"��ǰ�ļ��洢��: " << url << endl;
    readFile.close();
    return lines;
}

void initWriteToFile(const string& fileName, const vector<string>& head){
    ofstream writeFile;
    string url = "../Files/" + fileName;

    writeFile.open(url, ios::app);


    if (!writeFile.is_open()){
        cout << "��ȡ�ļ�" << url << "ʧ��,�����ԡ�" << endl;
        writeFile.close();
        exit(1);
    } cout << "���ļ��ɹ���" << endl;
    for (int i = 0; i < head.size(); i++ ){
        writeFile << head.at(i);
        if (i != head.size()-1 ) {
            writeFile << ",";
        }
    } writeFile << "\n";
    writeFile.close();
    cout << "��ʼ��д���ļ��ɹ�����ǰ�ļ��洢��" << url <<endl;
}

void insertFile(const string& fileName, order o){
    ofstream writeFile;
    string url = "../Files/" + fileName;
    writeFile.open(url, ios::app);

    if (!writeFile.is_open()){
        cout << "��ȡ�ļ�" << url << "ʧ��,�����ԡ�" << endl;
        writeFile.close();
        exit(1);
    } cout << "���ļ��ɹ���" << endl;

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
    cout << "д���ļ��ɹ�����ǰ�ļ��洢��" << url <<endl;
}

void updateFiles(const string& fileName, const vector<order>& tuple) {
    ofstream writeFile;
    string url = "../Files/" + fileName;

    writeFile.open(url, ios::app);


    if (!writeFile.is_open()){
        cout << "��ȡ�ļ�" << url << "ʧ��,�����ԡ�" << endl;
        writeFile.close();
        exit(1);
    } cout << "���ļ��ɹ���" << endl;

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
    cout << "д���ļ��ɹ�����ǰ�ļ��洢��" << url <<endl;
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
    cout << "\n" << "�ɹ���ʼ����վ" << endl;
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
    cout << "�ɹ��ָ��г�" << trainId << "����ʷ��Ʊ��¼!" << endl;
    return ticketsRecovery;
}

vector<Order> filesToOrders(const string& fileName) {
    vector<vector<std::string>> lines = readFile(fileName);
    vector<Order> orders;
    // ����ǵ�������һ���յĹ��캯��
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
    cout << "�õ������������ݲ���װ����������"<< endl;
    return orders;
}

void deleteOrder(const string& fileName, int ticketId) {
    vector<Order> orders;
    orders = filesToOrders(fileName);

    ofstream writeFile;
    string url = "../Files/" + fileName;

    writeFile.open(url, ios::out);

    if (!writeFile.is_open()){
        cout << "��ȡ�ļ�" << url << "ʧ��,�����ԡ�" << endl;
        writeFile.close();
        exit(1);
    } cout << "���ļ��ɹ���" << endl;

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
    cout << "д���ļ��ɹ�����ǰ�ļ��洢��" << url <<endl;

}

vector<User> filesToUsers(const string& fileName){
    vector<vector<std::string>> lines = readFile(fileName);
    vector<User> users;
    // ����ǵ�������һ���յĹ��캯��
    User user;

    for (auto & line: lines){
        user.userId = line[0];
        user.userName = line[1];
        user.userSex = line[2];
        users.push_back(user);
    }
    cout << "�õ������û����ݶ���װ����������"<< endl;
    return users;
}

void insertUsers(const string& fileName, const User& user){
    ofstream writeFile;
    string url = "../Files/" + fileName;
    writeFile.open(url, ios::app);

    if (!writeFile.is_open()){
        cout << "��ȡ�ļ�" << url << "ʧ��,�����ԡ�" << endl;
        writeFile.close();
        exit(1);
    } cout << "���ļ��ɹ���" << endl;

    writeFile << user.userId << ',';
    writeFile << user.userName << ',';
    writeFile << user.userSex << '\n';

    writeFile.close();
    cout << "д���ļ��ɹ�����ǰ�ļ��洢��" << url <<endl;
}