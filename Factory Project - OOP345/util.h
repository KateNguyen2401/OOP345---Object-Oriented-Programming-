#include <string>
#include <iostream>
#include <fstream>
#include <vector>


void trimSpace(std::string& s);

void csvprint(std::vector<std::vector<std::string>> & csvdata);

void csvread(std::string& filename, char seperator, std::vector<std::vector<std::string>> & csvdata);

bool validtaskName(std::string s);

bool validSlot(std::string s);
bool validItemName(std::string s);
bool validSequence(std::string s);



#pragma once
