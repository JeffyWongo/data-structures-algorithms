#include "Playlist.h"

PlaylistNode::PlaylistNode()
{
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string ID, string name, string artist, int length)
{
    uniqueID = ID;
    songName = name;
    artistName = artist;
    songLength = length;
    nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode* node)
{
    PlaylistNode* tempNode = nextNodePtr;
    nextNodePtr = node;
    node->SetNext(tempNode);
}

void PlaylistNode::SetNext(PlaylistNode* node)
{
    nextNodePtr = node;
}
string PlaylistNode::GetID() const
{
    return uniqueID;
}

string PlaylistNode::GetSongName() const
{
    return songName;
}

string PlaylistNode::GetArtistName() const
{
    return artistName;
}

int PlaylistNode::GetSongLength() const
{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const
{
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const
{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist() 
{
    head = nullptr;
    tail = nullptr;
}

void Playlist::PrintFullPlaylist(string title) const
{
    int count = 1;
    PlaylistNode* currNode = head;
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    if(head == nullptr)
    {
        cout << "Playlist is empty" << endl;
        cout << endl;
    }
    else
    {
        while(currNode != nullptr)
        {
            cout << count << "." << endl;
            currNode->PrintPlaylistNode();
            cout << endl;
            currNode = currNode->GetNext();
            count++;
        }
    }
}

void Playlist::addSong(PlaylistNode* node)
{
    if(head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->InsertAfter(node);
        tail = node;
    }
}

void Playlist::removeSong(string id)
{
    PlaylistNode* tempNode = nullptr;
    PlaylistNode* prevNode = nullptr;
    PlaylistNode* currNode = head;
    while(currNode != nullptr)
    {
        if(id == currNode->GetID())
        {
            if(id == head->GetID())
            {
                tempNode = head;
                head = head->GetNext();
                cout << '"' << currNode->GetSongName() << '"' << " removed." << endl;
                delete tempNode;
                return;
            }
            else if(id == tail->GetID())
            {
                tempNode = tail;
                cout << '"' << currNode->GetSongName() << '"' << " removed." << endl;
                delete tempNode;
                tail = prevNode;
                tail->SetNext(nullptr);
                return;
            }
            else
            {
                tempNode = currNode;
                prevNode->SetNext(currNode->GetNext());
                cout << '"' << currNode->GetSongName() << '"' << " removed." << endl;
                delete tempNode;
                currNode = prevNode->GetNext();
                return;
            }
        }
        else
        {
            prevNode = currNode;
            currNode = currNode->GetNext();
        }
    }
    cout << "ID was not found" << endl;
}

void Playlist::reposition(int current, int desired)
{
    int index = 1;
    PlaylistNode* prevNode = nullptr;
    PlaylistNode* currNode = head;

    if(head == nullptr)
    {
        cout << "Playlist is empty" << endl;
        return;
    }

    if(current < 1)
    {
        cout << "Starting position invalid" << endl;
        return;
    }
    
    while(index < current)
    {
        if(currNode == nullptr) // testing if starting position is more than 2 of list size
        {
            cout << "Starting position invalid" << endl;
            return;
        }
        prevNode = currNode;
        currNode = currNode->GetNext();
        index++;
    }

    if(currNode == nullptr) // testing if starting position is 1 more than list size
    {
        cout << "Starting position invalid" << endl;
        return;
    }

    // now we have the location of current's node
    if(currNode == head) // moving head
    {
        head = currNode->GetNext();
    }
    else if(currNode == tail) // moving tail
    {
        tail = prevNode;
    }

    PlaylistNode* tempNode = currNode;
    if(head != currNode->GetNext())
    {
        prevNode->SetNext(currNode->GetNext());
    }
    currNode = head->GetNext();
    prevNode = head;
    index = 2;
    
    if(desired <= 1) // if node is moved to head
    {
        tempNode->SetNext(head);
        head = tempNode;
        cout << '"' << tempNode->GetSongName() << '"' << " moved to position 1" << endl;
        return;
    }

    while(index < desired)
    {
        if(currNode == nullptr) // if list is empty after removing
        {
            head = tempNode;
            tail = tempNode;
            cout << '"' << tempNode->GetSongName() << '"' << " moved to position 1" << endl;
            return;
        }
        prevNode = currNode;
        currNode = currNode->GetNext();
        index++;
    }

    prevNode->InsertAfter(tempNode);
    
    if(currNode == nullptr) // if node is moved to tail
    {
        tail = tempNode;
    }
    
    cout << '"' << tempNode->GetSongName() << '"' << " moved to position " << index << endl;
}

void Playlist::PrintByArtist(string artist) const
{
    int index = 1;
    PlaylistNode* currNode = head;
    while(currNode != nullptr)
    {
        if(currNode->GetArtistName() == artist)
        {
            cout << index << "." << endl;
            currNode->PrintPlaylistNode();
            cout << endl;
        }
        currNode = currNode->GetNext();
        index++;
    }
}

void Playlist::PrintTotalTime() const
{
    int totalTime = 0;
    PlaylistNode* currNode = head;
    while(currNode != nullptr)
    {
        totalTime += currNode->GetSongLength();
        currNode = currNode->GetNext();
    }
    cout << totalTime;
}