//
// Created by Shichao on 2022/11/20.
//

#ifndef TRAINCACHE_TRAIN_H
#define TRAINCACHE_TRAIN_H

#include <string>
#include <utility>
#include <vector>

#include "matchTransform.h"


class Train {
public:
    // 列表初始化
    Train(std::string tId, int staNum, int seNum)
     :trainId(std::move(tId)),stationNum(staNum),seatsNum(seNum){}

    std::string trainId;
    int stationNum;
    int seatsNum;

    std::vector<StationTuple> vectorStations;
};

#endif //TRAINCACHE_TRAIN_H
