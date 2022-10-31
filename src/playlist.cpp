#include "playlist.h"

Playlist::Playlist(std::string playlistName)
{
    this->playlistName = playlistName;
    songListIterator = songList.begin();
}

void Playlist::addInMap(std::map<Playlist *, std::list<Song *>> &musicPlaylists, Playlist *playlist)
{
    musicPlaylists[playlist] = songList;
}

std::string Playlist::getPlaylistName()
{
    return playlistName;
}

std::string Playlist::inputPlaylistName()
{
    std::string nameOfPlaylist;
    std::cout << "Enter Playlist Name: ";
    std::cin >> nameOfPlaylist;
    return nameOfPlaylist;
}
std::string Playlist::inputSongName()
{
    std::string songName;
    std::cout << "Enter Song Name: ";
    std::cin >> songName;
    return songName;
}

void Playlist::playlistMenu()
{
    char choiceToOpenMenuAgain;
    do
    {
        std::cout << "----------Playlist Menu----------\n";
        std::cout << "1. Add song\n"
                  << "2. Delete Song\n"
                  << "3. Show All Songs\n"
                  << "4. Play Song\n"
                  << "5. Pause/Resume Song\n"
                  << "6. Play next song\n"
                  << "7. Play previous song\n"
                  << "8. Move Song Up\n"
                  << "9. Move Song Down\n";
        int menuOption;
        std::cin >> menuOption;
        if (menuOption < 0 || std::cin.fail())
        {
            std::cin.clear();
            throw "Invalid Input !!";
        }
        switch (menuOption)
        {
        case 1:
            addSong(inputSongName());
            break;
        case 2:
            deleteSong();
            break;
        case 3:
            displaySongList(getSongList());
            break;
        case 4:
            playSong(inputSongName());
            break;
        case 5:
            pauseSong();
            break;
        case 6:
            playNextSong();
            break;
        case 7:
            playPreviousSong();
            break;
        case 8:
            moveSongUp(inputSongName());
            break;
        case 9:
            moveSongDown(inputSongName());
            break;

        default:
            break;
        }
        std::cout << "Want to open Playlist Menu Again? y/Y || n/N: ";
        std::cin >> choiceToOpenMenuAgain;
        if (std::cin.fail())
        {
            std::cin.clear();
            throw "Invalid Input !!";
        }
    } while (choiceToOpenMenuAgain == 'y' || choiceToOpenMenuAgain == 'Y');
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
}

void Playlist::addSong(std::string songName)
{
    Song *s = new Song(songName);
    songList.push_back(s);
    std::cout << "Song added successfully...\n";
}

std::list<Song *>::iterator Playlist::lookupSong(std::string name)
{
    for (std::list<Song *>::iterator itr = songList.begin(); itr != songList.end(); ++itr)
    {
        if ((*itr)->getSongName() == name)
        {
            return itr;
        }
    }
    return songList.end();
}

void Playlist::deleteSong()
{
    std::string songName = inputSongName();
    std::list<Song *>::iterator it = lookupSong(songName);
    if (it != songList.end())
    {
        songList.remove(*it);
        std::cout << "Song deleted...\n";
    }
    else
    {
        std::cout << "Song not found...\n";
    }
}

std::list<Song *> Playlist::getSongList()
{
    return songList;
}

void Playlist::displaySongList(std::list<Song *> songListToDisplay)
{
    std::cout << "All the songs present in playlist are: \n";
    std::list<Song *>::iterator it;
    for (it = songListToDisplay.begin(); it != songListToDisplay.end(); ++it)
        std::cout << ' ' << (*it)->getSongName() << std::endl;
    std::cout << '\n';
}

void Playlist::moveSongUp(std::string songName)
{
    songListIterator = lookupSong(songName);
    if (songListIterator == songList.begin())
    {
        std::cout << "Cannot move song up...\n";
        return;
    }
    if (songListIterator != songList.end())
    {
        Song *tempSong;
        std::list<Song *>::iterator songIterator = songList.begin();
        while (songIterator != songListIterator)
        {
            songIterator++;
        }
        songIterator--;
        tempSong = (*songIterator);
        (*songIterator) = (*songListIterator);
        (*songListIterator) = tempSong;
        songListIterator = songList.begin();
        std::cout << "Song Moved Up.\n";
    }
    else
    {
        songListIterator = songList.begin();
        std::cout << "Song not found...\n";
        return;
    }
}

void Playlist::moveSongDown(std::string songName)
{
    songListIterator = lookupSong(songName);
    if (songListIterator == --songList.end())
    {
        std::cout << "Cannot move song down...\n";
        return;
    }
    if (songListIterator != songList.end())
    {
        Song *tempSong;
        std::list<Song *>::iterator songIterator = songList.begin();
        while (songIterator != songListIterator)
        {
            songIterator++;
        }
        songIterator++;
        tempSong = (*songIterator);
        (*songIterator) = (*songListIterator);
        (*songListIterator) = tempSong;
        songListIterator = songList.begin();
        std::cout << "Song Moved Down.\n";
    }
    else
    {
        songListIterator = songList.begin();
        std::cout << "Song not found...\n";
        return;
    }
}

void Playlist::playSong(std::string songName)
{
    songListIterator = lookupSong(songName);
    if (songListIterator != songList.end())
    {
        std::cout << "Song found in Playlist...\n";
    }
    else
    {
        songListIterator = songList.begin();
        std::cout << "Song not found...\n";
        return;
    }
    libvlc_media_t *media;

    // load the vlc engine
    inst = libvlc_new(0, NULL);

    // create a new item
    media = libvlc_media_new_path(inst, songName.c_str());

    // create a media play playing environment
    mediaPlayer = libvlc_media_player_new_from_media(media);

    // no need to keep the media now
    libvlc_media_release(media);

    // play the media_player
    libvlc_media_player_play(mediaPlayer);
}

void Playlist::pauseSong()
{
    libvlc_media_player_pause(mediaPlayer);
}

void Playlist::playNextSong()
{
    // stop playing
    libvlc_media_player_stop(mediaPlayer);

    // free the media_player
    libvlc_media_player_release(mediaPlayer);

    libvlc_release(inst);

    if (songList.empty())
    {
        std::cout << "Song list is empty...\n";
        return;
    }
    std::cout << "Next Song Playing...\n";
    songListIterator++;
    if (songListIterator != songList.end())
    {
        std::string songName = (*songListIterator)->getSongName();
        playSong(songName);
    }
    else
    {
        songListIterator = songList.begin();
        std::string songName = (*songListIterator)->getSongName();
        playSong(songName);
    }
}
void Playlist::playPreviousSong()
{
    // stop playing
    libvlc_media_player_stop(mediaPlayer);

    // free the media_player
    libvlc_media_player_release(mediaPlayer);

    libvlc_release(inst);

    if (songList.empty())
    {
        std::cout << "Song list is empty...\n";
        return;
    }
    std::cout << "Previous Song Playing...\n";
    // songListIterator--;
    if (songListIterator == songList.begin())
    {
        songListIterator = songList.end();
        songListIterator--;
        std::string songName = (*songListIterator)->getSongName();
        playSong(songName);
    }
    else
    {
        songListIterator--;
        std::string songName = (*songListIterator)->getSongName();
        playSong(songName);
    }
}