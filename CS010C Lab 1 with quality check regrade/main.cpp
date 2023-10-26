#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h"

Playlist* pPtr;

void PrintMenu(string title1)
{
    char option;

    string ID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* newSong;

    cout << title1 << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;

    cout << "Choose an option:";
    cout << endl;
    cin >> option;
    if(cin.fail())
    {
        throw runtime_error("Error unable to input");
    }

    cin.ignore();

    
    if (option == 'q')
    {
        return;
    }
    else if(option == 'a')
    {
        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        getline(cin,ID);
        cout << "Enter song's name:" << endl;
        getline(cin,songName);
        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);
        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;
        cin.ignore();


        newSong = new PlaylistNode(ID,songName, artistName,songLength);
        pPtr->addSong(newSong);
        cout << endl;
        PrintMenu(title1);

    }
    else if (option == 'd')
    {

        cout << "REMOVE SONG" << endl;
        cout << "Enter Song's unique ID: " << endl;
        getline(cin,ID);
        pPtr->removeSong(ID);
        cout << endl;
    }
    else if (option == 'o')
    {
        pPtr->OutputPlayList(title1);
        PrintMenu(title1);
    
    }
    else if (option == 's')
    {
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        cout << endl;
        string name;
        getline(cin,name);
        pPtr->specificArtistSong(name);
        PrintMenu(title1);
    }
    else if (option == 't')
    {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        pPtr->playlistLength();
        cout << endl;
        PrintMenu(title1);
    }
    else if (option == 'c')
    {
        cout << "CHANGE POSITION OF SONG" << endl;
        pPtr->changePos();
        PrintMenu(title1);
    }
    else
    {
        throw runtime_error("no option available for user input");

    }

}
int main() {

    string playTitle;

    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin,playTitle);
    pPtr = new Playlist();
    PrintMenu(playTitle);

}
