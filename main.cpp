#include <iostream>
#include <cstring>
#include "playlist.h"
#include "song.h"
void displayPlaylists(std::map<Playlist *, std::list<Song *>> &playlists)
{
    std::cout << "----------Music Playlist----------\n";
    int i = 0;
    if (playlists.empty())
    {
        std::cout << "No playlists are present..\n";
        return;
    }
    for (std::map<Playlist *, std::list<Song *>>::iterator playlistMapIterator = playlists.begin(); playlistMapIterator != playlists.end(); playlistMapIterator++)
    {
        Playlist *playlistIterator = playlistMapIterator->first;
        std::cout << ++i << ": " << (*playlistIterator).getPlaylistName() << std::endl;
    }
}

std::string inputPlaylistName()
{
    std::string nameOfPlaylist;
    std::cout << "Enter Playlist Name: ";
    std::cin >> nameOfPlaylist;
    return nameOfPlaylist;
}

std::map<Playlist *, std::list<Song *>>::iterator searchPlaylist(std::map<Playlist *, std::list<Song *>> &musicPlaylists)
{
    std::string playlistName = inputPlaylistName();
    std::map<Playlist *, std::list<Song *>>::iterator playlistMapIterator = musicPlaylists.begin();
    while (playlistMapIterator != musicPlaylists.end())
    {
        Playlist *playlistIterator = playlistMapIterator->first;
        if (playlistIterator->getPlaylistName() == playlistName)
        {
            break;
        }
        playlistMapIterator++;
    }
    return playlistMapIterator;
}

int main()
{
    std::map<Playlist *, std::list<Song *>> musicPlaylists;
    char choiceToOpenMenuAgain, choiceToAddSong;
    std::string playlistName;
    Playlist *playlist = nullptr;
    std::map<Playlist *, std::list<Song *>>::iterator playlistIterator;

    do
    {
        std::cout << "----------Music Playlist----------\n";
        std::cout << "1. Create a new playlist\n"
                  << "2. Delete a playlist\n"
                  << "3. Display all playlists\n"
                  << "4. Get into playlist\n";
        try
        {
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
                // Create Playlist
                playlistName = inputPlaylistName();
                playlist = new Playlist(playlistName);
                playlist->addInMap(musicPlaylists, playlist);
                std::cout << "Do you want to add songs? y/Y || n/N: ";
                std::cin >> choiceToAddSong;
                if (choiceToAddSong == 'y' || choiceToAddSong == 'Y')
                {   
                    playlist->addSong(playlist->inputSongName());
                }
                break;
            case 2:
                // Delete Playlist
                playlistIterator = searchPlaylist(musicPlaylists);
                if (musicPlaylists.empty() || playlistIterator == musicPlaylists.end())
                {
                    std::cout << "No playlist to show !!\n";
                }
                else
                {
                    musicPlaylists.erase(playlistIterator);
                    std::cout << "Playlist deleted...\n";
                }
                break;
            case 3:
                // Display Playlists
                displayPlaylists(musicPlaylists);
                break;
            case 4:
                // Get into playlist
                playlistIterator = searchPlaylist(musicPlaylists);
                if (musicPlaylists.empty() || playlistIterator == musicPlaylists.end())
                {
                    std::cout << "No playlist to show !!\n";
                }
                else
                {
                    playlist = playlistIterator->first;
                    playlist->playlistMenu();
                }
                break;

            default:
                std::cout << "Invalid Input...\n";
                break;
            }
        }
        catch (const char *exception)
        {
            std::cerr << exception << std::endl;
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

        std::cout << "Want to open Main Menu Again? y/Y || n/N: ";
        std::cin >> choiceToOpenMenuAgain;
    } while (choiceToOpenMenuAgain == 'y' || choiceToOpenMenuAgain == 'Y');

    return 0;
}