//
// Created by Shichao on 2022/11/20.
//

#ifndef TRAINCACHE_FILES_H
#define TRAINCACHE_FILES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "files.h"
#include "order.h"
#include "matchTransform.h"

using namespace std;

int stringToInt(const std::string& s);
vector<vector<std::string>> readFile(const std::string& fileName);
vector<StationTuple> initStations(const string& fileName);
void initWriteToFile(const string& fileName, const vector<string>& head);
void updateFiles(const string& fileName, const vector<order>& tuple);
vector<Ticket> recoverTickets (const string& trainId, const string& fileName);
int readFileIfExists(const string& fileName);
int writeFileIfExists(const string& fileName);
void insertFile(const string& fileName, order o);
vector<Order> filesToOrders(const string& fileName);
void deleteOrder(const string& fileName, int ticketId);
vector<User> filesToUsers(const string& fileName);
void insertUsers(const string& fileName, const User& user);
#endif //TRAINCACHE_FILES_H
