#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<limits>
using namespace std;

class song{
    private:
    string songTitle;
    string singer;
    string album;
    int year;
    song *next;

    public:
    song(string title, string singer, string album, int year){
        songTitle = title;
        this->singer = singer;
        this->album = album;
        this->year = year;
        next = nullptr;
    }
    friend class songManager;
};

class songManager{
    private:
    song *head;
    song *tail; //to point to the last song
    public:
    songManager(){
        head = nullptr;
        tail = nullptr;
    }
    ~songManager(){
        song *temp = head;
        while(temp!=nullptr){
            song *nextSong = temp->next;
            delete temp;
            temp = nextSong;
        }
        head = nullptr;
        tail = nullptr;
    //    Playlist is removed to prevent the memory leak
    }

    void addSong(string songTitle, string singer, string album, int year){
        song* newSong = new song(songTitle, singer, album, year);
        if(head == nullptr){
            head = newSong;
            tail = newSong;
        }else{
            tail->next = newSong;
            tail = newSong;
        }
        cout << "\nSong Added in the playlist";
    }

    void displayPlaylist(){
        if(head == nullptr){
            cout << "\nPlaylist is empty.\n";
            return;
        }
        song *temp = head;
        while(temp){
            cout << "\n---";
            cout << "\nSong:   " << temp->songTitle;
            cout << "\nSinger: " << temp->singer;
            cout << "\nAlbum: " << temp->album;
            cout << "\nYear: " << temp->year;
            cout << "\n----";
            temp = temp->next;
        }
    }
    
    void searchSong(string songTitle){
        if(head == nullptr){
            cout << "\nNo song to search";
            return;
        }
        song *temp = head;
        int count = 0;
        while(temp){
            if(temp->songTitle == songTitle){
                cout << "\n---";
                cout << "\nSong: " << temp->songTitle;
                cout << "\nSinger: " << temp->singer;
                cout << "\n----";
                count++;
            }
            temp = temp->next;
        }
        if(count == 0){
            cout << "\nCouldn't find the song" << songTitle;
            return;
        }
    }

    void deleteSong(string songTitle){
        if(head == nullptr){
            cout << "\nNo song to delete";
            return;
        }
        song *temp = head, *prev = nullptr;
        bool found = false;
        while(temp){
            if(temp->songTitle == songTitle){
                found=true;
                if(prev){
                    prev->next = temp->next;
                }else{
                    head = head->next;
                } 
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        if(!found){
            cout << "\ncouldn't find the song";
            return;
        }
        
    }

    void savePlaylistToFile(string filename);
    void loadPlaylistFromFile(string filename);

};

void songManager::savePlaylistToFile(string filename){
    ofstream file(filename);
    if(!file.is_open()){
        cout << "Error opening file for writing." << endl;
        return;
    }

    song *temp = head;
    while(temp){
        file << "song=" << temp->songTitle << ",singer=" << temp->singer << ",album=" << temp->album << ",year=" << temp->year << endl;
        temp = temp->next;
    }

    file.close();
    cout << "Playlist saved to " << filename << endl;
}

void songManager::loadPlaylistFromFile(string filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "No saved playlist found." << endl;
        return;
    }

    string line, title, singer, album, year_str;
    int year;

    while(getline(file, line)){
        stringstream ss(line);
        string segment;
        
        getline(ss, segment, ',');
        title = segment.substr(segment.find("=") + 1);

        getline(ss, segment, ',');
        singer = segment.substr(segment.find("=") + 1);

        getline(ss, segment, ',');
        album = segment.substr(segment.find("=") + 1);

        getline(ss, segment, ',');
        year_str = segment.substr(segment.find("=") + 1);
        year = stoi(year_str);

        addSong(title, singer, album, year);
    }

    file.close();
    cout << "Playlist loaded from " << filename << endl;
}
int main() {
    songManager manager;
    manager.loadPlaylistFromFile("playlist.csv");
    int choice, year;
    string title, artist, album;

    do {
        cout << "\n\n====== Music Playlist Menu ======\n";
        cout << "1. Add Song\n";
        cout << "2. Display Playlist\n";
        cout << "3. Search Song\n";
        cout << "4. Delete Song\n";
        cout << "5. Save Playlist\n";
        cout << "6. Load Playlist\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }
        cin.ignore(); // to ignore newline character after choice

        switch(choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter singer name: ";
                getline(cin, artist);
                cout << "Enter album name: ";
                getline(cin, album);
                cout << "Enter year of release: ";
                cin >> year;
                cin.ignore();
                manager.addSong(title, artist, album, year);
                break;

            case 2:
                manager.displayPlaylist();
                break;

            case 3:
                cout << "Enter song title to search: ";
                getline(cin, title);
                manager.searchSong(title);
                break;

            case 4:
                cout << "Enter song title to delete: ";
                getline(cin, title);
                manager.deleteSong(title);
                break;

            case 5:
                manager.savePlaylistToFile("playlist.csv");
                break;

            case 6:
                manager.loadPlaylistFromFile("playlist.csv");
                break;

            case 7:
                cout << "Saving playlist and exiting... Goodbye!\n";
                manager.savePlaylistToFile("playlist.csv");
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 7);

    return 0;
}
