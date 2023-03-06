//
// Created by Shichao on 2022/11/19.
//

#ifndef MATCHTRANSFORM_H
#define MATCHTRANSFORM_H

#include <iostream>

typedef struct theStation {
    std::string trainId;
    int stationId;
    std::string stationName;
    int stationFare; // 实际上是每个站点给个值，最后的票价就是两个站点之间的Fare差值
}StationTuple;

int transformStationToNo(const std::string& station);
std::string transformNoToStation(int stationNo);
StationTuple transformStationToNo(const std::string& station, std::vector<StationTuple> stationsTuple);
StationTuple transformNoToStation(int stationNo, std::vector<StationTuple> stationsTuple);

#endif //MATCHTRANSFORM_H