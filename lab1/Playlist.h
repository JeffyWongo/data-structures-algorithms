#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <string>
#include <iostream>

using namespace std;

class PlaylistNode
{
    public:
        PlaylistNode();
        PlaylistNode(string ID, string name, string artist, int length);
        void InsertAfter(PlaylistNode* node);
        void SetNext(PlaylistNode* node);
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

class Playlist
{
    public:
        Playlist();
        void PrintFullPlaylist(string title) const;
        void addSong(PlaylistNode* node);
        void removeSong(string id);
        void reposition(int current, int desired);
        void PrintByArtist(string artist) const;
        void PrintTotalTime() const;

    private:
        PlaylistNode* head;
        PlaylistNode* tail;
};
#endif