#include "Playlist.h"

Playlist* playlist;

void PrintMenu(string title)
{
    string input;
    while(input != "q")
    {
        cout << title << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl << endl;
        cout << "Choose an option:" << endl;
        getline(cin, input);
        
        if(input == "a")
        {
            string id;
            string name;
            string artist;
            int length;
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            getline(cin, id);
            cout << "Enter song's name:" << endl;
            getline(cin, name);
            cout << "Enter artist's name:" << endl;
            getline(cin, artist);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> length;
            cin.ignore();

            PlaylistNode* node = new PlaylistNode(id, name, artist, length);
            playlist->addSong(node);
            cout << endl;
        }
        else if(input == "d") 
        {
            string id;
            cout << "REMOVE SONG" << endl
            << "Enter song's unique ID:" << endl;
            getline(cin, id);
            playlist->removeSong(id);
            cout << endl;
        }
        else if(input == "c")
        {
            int current;
            int desired;
            cout << "CHANGE POSITION OF SONG" << endl
            << "Enter song's current position:" << endl;
            cin >> current;
            cout << "Enter new position for song:" << endl;
            cin >> desired;
            cin.ignore();

            playlist->reposition(current, desired);
            cout << endl;
        }
        else if(input == "s")
        {
            string artist;
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl
            << "Enter artist's name:" << endl;
            getline(cin, artist);
            cout << endl;
            playlist->PrintByArtist(artist);
        }
        else if(input == "t")
        {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl
            << "Total time: ";
            playlist->PrintTotalTime();
            cout << " seconds" << endl;
            cout << endl;
        }
        else if(input == "o")
        {
            playlist->PrintFullPlaylist(title);
        }
        else if(input == "q")
        {
            return;
        }
        else
        {
            cout << "Invalid selection" << endl;
        }
    }
}

int main()
{
    string playlistTitle;
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    cout << endl;
    playlist = new Playlist();
    PrintMenu(playlistTitle);
    return 0;
}