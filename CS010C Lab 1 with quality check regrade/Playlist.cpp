#include <iostream>
#include <string>
using namespace std;

#include "Playlist.h"

PlaylistNode:: PlaylistNode()
{
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode:: PlaylistNode(string _uniqueID, string _songName, string _artistName, int _songLength)
{
    uniqueID = _uniqueID;
    songName = _songName;
    artistName = _artistName;
    songLength = _songLength;
    nextNodePtr = nullptr;;
}

void PlaylistNode:: InsertAfter(PlaylistNode* newNode) // NEED HELP
{
    PlaylistNode* temp = nextNodePtr;
    nextNodePtr = newNode;
    newNode->SetNext(temp);
}
void PlaylistNode:: SetNext(PlaylistNode* next)
{
    nextNodePtr = next;
}

string PlaylistNode:: GetID() const
{
    return uniqueID;
}

string PlaylistNode:: GetSongName() const
{
    return songName;
}

string PlaylistNode:: GetArtistName() const
{
    return artistName;
}

int PlaylistNode:: GetSongLength() const
{
    return songLength;
}

PlaylistNode* PlaylistNode:: GetNext() const
{
    return nextNodePtr;
}

void PlaylistNode:: PrintPlaylistNode() const
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
Playlist::~Playlist()
{
    while(head)// list is not empty
    {
        PlaylistNode* deltVal = head->GetNext();// set val to delete to head next to assist in deleting head
        delete head;// delete val in head
        deltVal = head;// set deltVal to the new head
    }
}
void Playlist:: PlaylistCopy(const Playlist& deepCopy) // copy constructor performs deep Copy, RULE OF THREE
{
    PlaylistNode* valCopy = deepCopy.head;
    while(valCopy != nullptr)// while list is not empty
    {
        PlaylistNode* newVal = new PlaylistNode(valCopy->GetID(), valCopy->GetSongName(), valCopy->GetArtistName(), valCopy->GetSongLength());// set node to be copied with its right contents
        addSong(newVal);//add song to list 
        valCopy = valCopy->GetNext();// get next song to copy
    }
}
void Playlist:: operator=(const Playlist& valAssign)// RULE OF THREE
{
    PlaylistCopy(valAssign);
}
void Playlist:: removeSong(string ID)
{
    if(head == 0) //if list is empty
    {
        cout << "Playlist is empty" << endl;
        return;
    }
    else if (head->GetID() == ID)// if first node ID matches
    {
        string removeSong = head->GetSongName();
        head = head->GetNext();// assign song to be song after the one being removed
        cout << removeSong << " removed" << endl;
        return;
    }
    else 
    {
        PlaylistNode* prev = head;// first song
        PlaylistNode* curr = head->GetNext();// second song
        while(curr != nullptr && curr->GetID() != ID) //gets loop to loop through list,while current node is not null and and the ID does not match
        {
            prev = curr;// go from first node in list to next node
            curr = curr->GetNext();// get next node after the previous next node. after achieving last step, go to the next node
        }
            if(curr != nullptr)// if the next song is not null
            {
                string removeSong = curr->GetSongName();
                prev->SetNext(curr->GetNext());// set the next song to the one after the curr song.
                if(curr->GetNext() == nullptr)//if it is last node
                {
                    tail = prev;// set tail to prev song not next one
                    cout <<'"' << removeSong <<'"' << " removed." << endl;
                    return;
                }
            }
    }
}

void Playlist:: addSong(PlaylistNode* newSong)// function to add song to list
{
    if(head == 0)// if playlist is empty
    {
        head = newSong;//make the newSong the head
        tail = newSong;//make the newSong the tail
    }
    else //if not empty
    {
        tail->SetNext(newSong);//add newSong after tail
        tail = newSong;// set tail to newSong
    }
}

void Playlist:: OutputPlayList(string title)// output the playlist of songs
{
    PlaylistNode* list;
    int num = 1;
    list = head;
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    if (head == 0)// if playlist is empty
    {
        cout << "Playlist is empty" << endl;// playlist is empty, nothing to output
        cout << endl;
        return;
    }
    else// if playlist is not empty
    {
        while (list != nullptr)// list is not empty
        {
            cout << num << "." << endl;
            list->PrintPlaylistNode();// print playlist with all its contents
            cout << endl;
            ++num;// increment num to next number
            list = list->GetNext();// get next song in list
        }
    }
}

void Playlist:: changePos()// change position of songs
{
    int nodeCount = 1;
    PlaylistNode* current;
    PlaylistNode* previous;
    int initPos;
    int newPosition;
    cout << "Enter song's current position:" << endl;
    cin >> initPos;
    cout << "Enter new position for song:" << endl;
    cin >> newPosition;

    current = head;
    previous = nullptr;
    if (initPos < 1)//position must be at least 1
    {
        cout << "invalid position," << endl;
        return;
    }
    while (nodeCount < initPos)
    {
        if (current)// head equals something
        {
            previous = current;
            current = current->GetNext();
            ++nodeCount;

            if(current == nullptr)
            {
                cout << "Invalid position" << endl;
                return;
            }
        }
        else
        {
            cout << "Invalid position" << endl;
            return;
        }
    }
    if (previous)
    {
        previous->SetNext(current->GetNext());// set previous's song to the song after current

    }
    else
    {
        head = current->GetNext();
    }
    if (current == tail)
    {
        tail = previous;
    }
    if (newPosition <= 1)
    {
        if(head == 0)
        {
            tail = current;
        }
        current->SetNext(head);
        head = current;
        cout << '"' << current->GetSongName() << '"' << "moved to position 1" << endl;
        cout << endl;

    }
    else
    {
        if(head == 0)
        {
            head = current;
            cout << '"' << current->GetSongName() << " moved to position 1" << endl;
        }
        else
        {

        int nodeCount1 = 2;
        PlaylistNode* previous1 = head;
        PlaylistNode* current1 = head->GetNext();
        while (nodeCount1 < newPosition && current1 != nullptr)
        {
            previous1 = current1;
            current1 = current1->GetNext();
            nodeCount1++;
        }
        previous1->InsertAfter(current);
        if (current1 == nullptr)
        {
            tail = current;
        }
        cout << current->GetSongName() << " moved to position " << nodeCount << endl;

        }
    }
}

void Playlist::specificArtistSong(string artist)// output song for specified artist
{
    int num;
    num = 1;
    PlaylistNode* artistSong;
    artistSong = head;
    while (artistSong != 0)//artistSong is not null and list isnt empty
    {
        if (artistSong->GetArtistName() == artist)// if artists name matches the name of the artist passed in
        {
            cout << num << "." << endl;
            artistSong->PrintPlaylistNode();// print artists details
            cout << endl;
        }
        ++num;
        artistSong = artistSong->GetNext();// get next artist and loop repeats to see if artist has another song in the list
    }
}
void Playlist:: playlistLength()//output playlists length
{
    int num = 0;
    PlaylistNode* curr;
    curr = head;
    while (curr != nullptr)//while list is not empty
    {
        num += curr->GetSongLength();//increment num to each song's length
        curr = curr->GetNext();// get next song to get length
    }
    cout << "Total time: " << num << " seconds" << endl;
}
