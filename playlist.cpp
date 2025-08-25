#include<bits/stdc++.h>
using namespace std;

class song{
    private:
    string songTitle;
    string singer;
    song *next;

    public:
    song(string title, string singer){
        songTitle = title;
        this->singer = singer;
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

    void addSong(string songTitle, string singer){
        song* newSong = new song(songTitle, singer);
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

};
int main() {
    songManager manager;
    int choice;
    string title, artist;

    do {
        cout << "\n\n====== Music Playlist Menu ======\n";
        cout << "1. Add Song\n";
        cout << "2. Display Playlist\n";
        cout << "3. Search Song\n";
        cout << "4. Delete Song\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // to ignore newline character after choice

        switch(choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter singer name: ";
                getline(cin, artist);
                manager.addSong(title, artist);
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
                cout << "Exiting... Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 5);

    return 0;
}
