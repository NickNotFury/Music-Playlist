#ifndef SONG_H
#define SONG_H
#include <iostream>
class Song
{
private:
    std::string songName;

public:
    Song();
    Song(std::string);
    std::string getSongName();
};

#endif