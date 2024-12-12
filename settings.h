#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

struct Settings
{
    std::map<std::string, std::vector<float>> constantMap;
    int track_length;
    int seed;
    std::vector<std::string> StatObjs;
    std::vector<std::string> MovObjs;
    int StatObjs_freq;
    int MovObjs_freq;
};

#endif
