#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <map>
#include <list>
#include <libvlcpp-master/vlcpp/vlc.hpp>

#include "song.h"
#include <iostream>
#include <cstring>

class Playlist
{
private:
    std::list<Song *> songList;
    std::list<Song *>::iterator songListIterator;
    std::string playlistName;
    libvlc_instance_t *inst;
    libvlc_media_player_t *mediaPlayer;

public:
    Playlist(std::string);
    void addInMap(std::map<Playlist *, std::list<Song *>> &, Playlist *);
    std::string getPlaylistName();
    std::string inputPlaylistName();
    std::string inputSongName();
    void playlistMenu();
    void addSong(std::string);
    std::list<Song *>::iterator lookupSong(std::string);
    void deleteSong();
    void playSong(std::string);
    std::list<Song *> getSongList();
    void displaySongList(std::list<Song *>);
    void pauseSong();
    void playNextSong();
    void playPreviousSong();
    void moveSongUp(std::string);
    void moveSongDown(std::string);
};

#endif