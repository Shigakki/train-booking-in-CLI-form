//
// Created by Shichao on 2022/11/19.
//

#include <string>
#include <vector>

#include "matchTransform.h"
using namespace std;

int transformStationToNo(const string& station) {
    int stationNo = 0;

    if (station == "艾欧尼亚") {
        stationNo = 1;
    }
    else if (station == "比尔吉沃特") {
        stationNo = 2;
    }
    else if (station == "皮尔特沃夫与祖安") {
        stationNo = 3;
    }
    else if (station == "以绪塔尔") {
        stationNo = 4;
    }
    else if (station == "暗影岛") {
        stationNo = 5;
    }
    else if (station == "恕瑞玛") {
        stationNo = 6;
    }
    else if (station == "巨神峰") {
        stationNo = 7;
    }
    else if (station == "诺克萨斯") {
        stationNo = 8;
    }
    else if (station == "德玛西亚") {
        stationNo = 9;
    }
    else if (station == "弗雷尔卓德") {
        stationNo = 10;
    }
    else if (station == "虚空") {
        stationNo = 11;
    } else {
        stationNo = -1;
    }

    return stationNo;
}

string transformNoToStation(int stationNo) {
    string station;
    switch (stationNo) {
        case (1):
            station = "艾欧尼亚";
            break;
        case (2):
            station = "比尔吉沃特";
            break;
        case (3):
            station = "皮尔特沃夫与祖安";
            break;
        case (4):
            station = "以绪塔尔";
            break;
        case (5):
            station = "暗影岛";
            break;
        case (6):
            station = "恕瑞玛";
            break;
        case (7):
            station = "巨神峰";
            break;
        case (8):
            station = "诺克萨斯";
            break;
        case (9):
            station = "德玛西亚";
            break;
        case (10):
            station = "弗雷尔卓德";
            break;
        case (11):
            station = "虚空";
            break;
        default:
            break;
    }
    return station;
}

StationTuple transformStationToNo(const string& station, vector<StationTuple> stationsTuple) {
    StationTuple stationTuple;
    if (station == "艾欧尼亚") {
        stationTuple = stationsTuple[0];
    }
    else if (station == "比尔吉沃特") {
        stationTuple = stationsTuple[1];
    }
    else if (station == "皮尔特沃夫与祖安") {
        stationTuple = stationsTuple[2];
    }
    else if (station == "以绪塔尔") {
        stationTuple = stationsTuple[3];
    }
    else if (station == "暗影岛") {
        stationTuple = stationsTuple[4];
    }
    else if (station == "恕瑞玛") {
        stationTuple = stationsTuple[5];
    }
    else if (station == "巨神峰") {
        stationTuple = stationsTuple[6];
    }
    else if (station == "诺克萨斯") {
        stationTuple = stationsTuple[7];
    }
    else if (station == "德玛西亚") {
        stationTuple = stationsTuple[8];
    }
    else if (station == "弗雷尔卓德") {
        stationTuple = stationsTuple[9];
    }
    else if (station == "虚空") {
        stationTuple = stationsTuple[10];
    } else {
        stationTuple = stationsTuple[11];
    }

    return stationTuple;
}

StationTuple transformNoToStation(int stationNo, vector<StationTuple> stationsTuple) {
    StationTuple stationTuple;
    switch (stationNo) {
        case (1):
            stationTuple = stationsTuple[0];
            break;
        case (2):
            stationTuple = stationsTuple[1];
            break;
        case (3):
            stationTuple = stationsTuple[2];
            break;
        case (4):
            stationTuple = stationsTuple[3];
            break;
        case (5):
            stationTuple = stationsTuple[4];
            break;
        case (6):
            stationTuple = stationsTuple[5];
            break;
        case (7):
            stationTuple = stationsTuple[6];
            break;
        case (8):
            stationTuple = stationsTuple[7];
            break;
        case (9):
            stationTuple = stationsTuple[8];
            break;
        case (10):
            stationTuple = stationsTuple[9];
            break;
        case (11):
            stationTuple = stationsTuple[10];
            break;
        default:
            break;
    }
    return stationTuple;
}