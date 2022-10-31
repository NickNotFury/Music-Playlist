#include "song.h"
Song::Song(){}
Song::Song(std::string songName){
    this->songName=songName;
}
std::string Song::getSongName(){
    return songName;
}