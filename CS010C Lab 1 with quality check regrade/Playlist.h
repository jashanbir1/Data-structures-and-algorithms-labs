
#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include <string>
using namespace std;

class PlaylistNode {

    public:

    PlaylistNode();
    PlaylistNode(string, string, string, int); // add parameters
    void InsertAfter(PlaylistNode* );
    void SetNext(PlaylistNode* );
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode() const;

    private:

    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;


};

class Playlist {

    private:
    PlaylistNode* head;
    PlaylistNode* tail;

    public:
    Playlist();
    ~Playlist();
    void PlaylistCopy(const Playlist& );
    void operator=(const Playlist& );
    void removeSong(string );
    void addSong(PlaylistNode* );
    void OutputPlayList(string );
    void changePos();
    void playlistLength();
    void specificArtistSong(string );

};
#endif