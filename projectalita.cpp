#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;

enum PlaybackMode { SEQUENTIAL, SHUFFLE, REPEAT };

class Song {
public:
    string name;
    string artistName;
    int releaseYear;
    string genre;

    Song(string n = "", string a = "", int y = 0, string g = "")
        : name(n), artistName(a), releaseYear(y), genre(g) {}

    bool operator==(const Song& other) const {
        return name == other.name && artistName == other.artistName;
    }
};

class Playlist {
public:
    string name;
    vector<Song> songs;
    PlaybackMode playbackMode;
    int currentSongIndex;

    Playlist(string n = "")
        : name(n), playbackMode(SEQUENTIAL), currentSongIndex(0) {}

    void addSong(const Song& song) {
        songs.push_back(song);
    }

    void removeSong(const Song& song) {
        songs.erase(remove(songs.begin(), songs.end(), song), songs.end());
        if (currentSongIndex >= (int)songs.size())
            currentSongIndex = 0;
    }

    int getNumberOfSongs() const {
        return (int)songs.size();
    }

    void nextSong() {
        if (songs.empty()) return;
        if (playbackMode == SHUFFLE) {
            currentSongIndex = rand() % songs.size();
        }
        else if (playbackMode == REPEAT) {
            currentSongIndex = (currentSongIndex + 1) % songs.size();
        }
        else {
            if (currentSongIndex < (int)songs.size() - 1)
                ++currentSongIndex;
            else
                currentSongIndex = 0;
        }
    }

    void previousSong() {
        if (songs.empty()) return;
        if (playbackMode == SHUFFLE) {
            currentSongIndex = rand() % songs.size();
        }
        else if (playbackMode == REPEAT) {
            if (currentSongIndex == 0)
                currentSongIndex = (int)songs.size() - 1;
            else
                --currentSongIndex;
        }
        else {
            if (currentSongIndex > 0)
                --currentSongIndex;
            else
                currentSongIndex = (int)songs.size() - 1;
        }
    }

    Song currentSong() {
        if (songs.empty())
            return Song();
        return songs[currentSongIndex];
    }

    void setPlaybackMode(PlaybackMode mode) {
        playbackMode = mode;
    }

    void displaySongs() {
        cout << "Playlist: " << name << " (" << getNumberOfSongs() << " songs)\n";
        for (size_t i = 0; i < songs.size(); ++i) {
            cout << i + 1 << ". " << songs[i].name
                << " by " << songs[i].artistName
                << " (" << songs[i].releaseYear << ", " << songs[i].genre << ")\n";
        }
    }
};

class Artist {
public:
    string name;
    int numberOfAlbums;
    int numberOfReleasedSongs;
    vector<Song> releasedSongs;

    Artist(string n = "", int albums = 0)
        : name(n), numberOfAlbums(albums), numberOfReleasedSongs(0) {}

    void addSong(const Song& song) {
        releasedSongs.push_back(song);
        numberOfReleasedSongs = (int)releasedSongs.size();
    }

    void editArtist(int albums) {
        numberOfAlbums = albums;
    }

    void displayInfo() {
        cout << "Artist: " << name << "\nAlbums: " << numberOfAlbums
            << "\nReleased Songs: " << numberOfReleasedSongs << '\n';
        for (const auto& s : releasedSongs) {
            cout << "- " << s.name << "\n";
        }
    }
};

class User {
public:
    string username;
    string password;
    vector<Song> savedSongs;
    vector<Song> favoriteSongs;
    vector<Playlist> favoritePlaylists;
    vector<Playlist> personalPlaylists;

    User(string u = "", string p = "") : username(u), password(p) {}

    bool checkPassword(const string& p) {
        return password == p;
    }

    void addToSavedSongs(const Song& song) {
        if (find(savedSongs.begin(), savedSongs.end(), song) == savedSongs.end())
            savedSongs.push_back(song);
    }

    void removeFromSavedSongs(const Song& song) {
        savedSongs.erase(remove(savedSongs.begin(), savedSongs.end(), song), savedSongs.end());
    }

    void addToFavoriteSongs(const Song& song) {
        if (find(favoriteSongs.begin(), favoriteSongs.end(), song) == favoriteSongs.end())
            favoriteSongs.push_back(song);
    }

    void removeFromFavoriteSongs(const Song& song) {
        favoriteSongs.erase(remove(favoriteSongs.begin(), favoriteSongs.end(), song), favoriteSongs.end());
    }

    void addPlaylist(const Playlist& playlist) {
        personalPlaylists.push_back(playlist);
    }

    void deletePlaylist(const string& playlistName) {
        personalPlaylists.erase(remove_if(personalPlaylists.begin(), personalPlaylists.end(),
            [&](const Playlist& p) { return p.name == playlistName; }), personalPlaylists.end());
    }

    Playlist* findPlaylist(const string& playlistName) {
        for (auto& playlist : personalPlaylists) {
            if (playlist.name == playlistName) return &playlist;
        }
        return nullptr;
    }

    void displaySavedSongs() {
        cout << "Saved Songs:\n";
        for (size_t i = 0; i < savedSongs.size(); ++i) {
            cout << i + 1 << ". " << savedSongs[i].name << " by " << savedSongs[i].artistName << '\n';
        }
    }

    void displayFavoriteSongs() {
        cout << "Favorite Songs:\n";
        for (size_t i = 0; i < favoriteSongs.size(); ++i) {
            cout << i + 1 << ". " << favoriteSongs[i].name << " by " << favoriteSongs[i].artistName << '\n';
        }
    }

    void displayFavoritePlaylists() {
        cout << "Favorite Playlists:\n";
        for (size_t i = 0; i < favoritePlaylists.size(); ++i) {
            cout << i + 1 << ". " << favoritePlaylists[i].name << " (" << favoritePlaylists[i].getNumberOfSongs() << " songs)\n";
        }
    }

    void displayPersonalPlaylists() {
        cout << "Personal Playlists:\n";
        for (size_t i = 0; i < personalPlaylists.size(); ++i) {
            cout << i + 1 << ". " << personalPlaylists[i].name << " (" << personalPlaylists[i].getNumberOfSongs() << " songs)\n";
        }
    }
};

class Admin {
public:
    string username;
    string password;

    Admin(string u = "admin", string p = "password") : username(u), password(p) {}

    bool login(const string& u, const string& p) {
        return (username == u && password == p);
    }
};

class MusicSystem {
public:
    vector<User> users;
    Admin admin;
    vector<Song> songs;
    vector<Playlist> playlists;
    map<string, Artist> artists;

    MusicSystem() {
        srand((unsigned int)time(NULL));
    }

    User* findUser(const string& username) {
        for (auto& user : users) {
            if (user.username == username) return &user;
        }
        return nullptr;
    }

    Artist* findArtist(const string& artistName) {
        auto it = artists.find(artistName);
        if (it != artists.end()) return &it->second;
        return nullptr;
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void addSong(const Song& song) {
        songs.push_back(song);
        if (artists.find(song.artistName) == artists.end()) {
            artists[song.artistName] = Artist(song.artistName, 0);
        }
        artists[song.artistName].addSong(song);
    }

    void createPlaylist(const string& name) {
        playlists.push_back(Playlist(name));
    }

    Playlist* findPlaylist(const string& name) {
        for (auto& playlist : playlists) {
            if (playlist.name == name) return &playlist;
        }
        return nullptr;
    }

    void displaySongs(const vector<Song>& list) {
        for (size_t i = 0; i < list.size(); ++i) {
            const auto& s = list[i];
            cout << i + 1 << ". Song: " << s.name << ", Artist: " << s.artistName << ", Year: " << s.releaseYear << ", Genre: " << s.genre << endl;
        }
        if (list.empty()) {
            cout << "No songs to display.\n";
        }
    }

    void displayPlaylists(const vector<Playlist>& list) {
        for (size_t i = 0; i < list.size(); ++i) {
            const auto& p = list[i];
            cout << i + 1 << ". Playlist: " << p.name << " (" << p.getNumberOfSongs() << " songs)" << endl;
        }
        if (list.empty()) {
            cout << "No playlists to display.\n";
        }
    }

    vector<Song> searchSongs(const string& keyword) {
        vector<Song> results;
        for (const auto& s : songs) {
            string lowerName = s.name, lowerArtist = s.artistName;
            transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
            transform(lowerArtist.begin(), lowerArtist.end(), lowerArtist.begin(), ::tolower);
            string lowerKeyword = keyword;
            transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
            if (lowerName.find(lowerKeyword) != string::npos || lowerArtist.find(lowerKeyword) != string::npos) {
                results.push_back(s);
            }
        }
        return results;
    }

    void filterSongsByArtist(const string& artistName) {
        vector<Song> filtered;
        for (const auto& s : songs) {
            if (s.artistName == artistName) filtered.push_back(s);
        }
        displaySongs(filtered);
    }

    void filterSongsByYear(int year) {
        vector<Song> filtered;
        for (const auto& s : songs) {
            if (s.releaseYear == year) filtered.push_back(s);
        }
        displaySongs(filtered);
    }

    void filterSongsByGenre(const string& genre) {
        vector<Song> filtered;
        for (const auto& s : songs) {
            if (s.genre == genre) filtered.push_back(s);
        }
        displaySongs(filtered);
    }

    void sortSongsAlphabetically() {
        vector<Song> sorted = songs;
        sort(sorted.begin(), sorted.end(), [](const Song& a, const Song& b) {
            return a.name < b.name;
            });
        displaySongs(sorted);
    }

    void displayArtistPage(const string& artistName) {
        Artist* artist = findArtist(artistName);
        if (artist) {
            artist->displayInfo();
        }
        else {
            cout << "Artist not found." << endl;
        }
    }
};

void adminMenu(MusicSystem& system);
void userMenu(MusicSystem& system, User* user);

int main() {
    MusicSystem system;

    cout << "Welcome to Music Player\n";
    while (true) {
        cout << "\n1. Admin login\n2. User login\n3. Register new user\n4. Exit\nChoose option: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            string u, p;
            cout << "Admin username: ";
            cin >> u;
            cout << "Admin password: ";
            cin >> p;
            if (system.admin.login(u, p)) {
                cout << "Admin logged in successfully.\n";
                adminMenu(system);
            }
            else {
                cout << "Invalid admin credentials.\n";
            }
        }
        else if (choice == 2) {
            string u, p;
            cout << "User username: ";
            cin >> u;
            cout << "User password: ";
            cin >> p;
            User* user = system.findUser(u);
            if (user && user->checkPassword(p)) {
                cout << "User logged in successfully.\n";
                userMenu(system, user);
            }
            else {
                cout << "Invalid user credentials.\n";
            }
        }
        else if (choice == 3) {
            string u, p;
            cout << "Enter new username: ";
            cin >> u;
            if (system.findUser(u)) {
                cout << "Username already exists.\n";
                continue;
            }
            cout << "Enter new password: ";
            cin >> p;
            system.addUser(User(u, p));
            cout << "User registered successfully.\n";
        }
        else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}

void addSongInteractive(MusicSystem& system) {
    string name, artistName, genre;
    int year;
    cout << "Enter song name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter artist name: ";
    getline(cin, artistName);
    cout << "Enter release year: ";
    cin >> year;
    cout << "Enter genre: ";
    cin.ignore();
    getline(cin, genre);
    Song song(name, artistName, year, genre);
    system.addSong(song);
    cout << "Song added successfully.\n";
}

void createPlaylistInteractive(MusicSystem& system) {
    string name;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, name);
    if (system.findPlaylist(name)) {
        cout << "Playlist already exists.\n";
        return;
    }
    system.createPlaylist(name);
    cout << "Playlist created successfully.\n";
}

void addSongToPlaylistInteractive(MusicSystem& system) {
    string playlistName;
    cout << "Enter playlist name to add song to: ";
    cin.ignore();
    getline(cin, playlistName);
    Playlist* playlist = system.findPlaylist(playlistName);
    if (!playlist) {
        cout << "Playlist not found.\n";
        return;
    }
    cout << "System Songs:\n";
    system.displaySongs(system.songs);
    int songIndex;
    cout << "Enter song number to add: ";
    cin >> songIndex;
    if (songIndex < 1 || songIndex >(int)system.songs.size()) {
        cout << "Invalid song selection.\n";
        return;
    }
    playlist->addSong(system.songs[songIndex - 1]);
    cout << "Song added to playlist.\n";
}

void removeSongFromPlaylistInteractive(MusicSystem& system) {
    string playlistName;
    cout << "Enter playlist name to remove song from: ";
    cin.ignore();
    getline(cin, playlistName);
    Playlist* playlist = system.findPlaylist(playlistName);
    if (!playlist) {
        cout << "Playlist not found.\n";
        return;
    }
    playlist->displaySongs();
    int songIndex;
    cout << "Enter song number to remove: ";
    cin >> songIndex;
    if (songIndex < 1 || songIndex > playlist->getNumberOfSongs()) {
        cout << "Invalid song selection.\n";
        return;
    }
    playlist->removeSong(playlist->songs[songIndex - 1]);
    cout << "Song removed from playlist.\n";
}

void createArtistPageInteractive(MusicSystem& system) {
    string artistName;
    int albums;
    cout << "Enter artist name: ";
    cin.ignore();
    getline(cin, artistName);
    cout << "Enter number of albums: ";
    cin >> albums;
    Artist* artist = system.findArtist(artistName);
    if (artist) {
        artist->editArtist(albums);
        cout << "Artist updated successfully.\n";
    }
    else {
        Artist newArtist(artistName, albums);
        system.artists[artistName] = newArtist;
        cout << "Artist created successfully.\n";
    }
}

void addSongToArtistInteractive(MusicSystem& system) {
    string artistName;
    cout << "Enter artist name to add song to: ";
    cin.ignore();
    getline(cin, artistName);
    Artist* artist = system.findArtist(artistName);
    if (!artist) {
        cout << "Artist not found.\n";
        return;
    }
    cout << "System Songs:\n";
    system.displaySongs(system.songs);
    int songIndex;
    cout << "Enter song number to add: ";
    cin >> songIndex;
    if (songIndex < 1 || songIndex >(int)system.songs.size()) {
        cout << "Invalid song selection.\n";
        return;
    }
    Song song = system.songs[songIndex - 1];
    if (song.artistName != artistName) {
        cout << "Song's artist does not match.\n";
        return;
    }
    artist->addSong(song);
    cout << "Song added to artist's page.\n";
}

void adminMenu(MusicSystem& system) {
    while (true) {
        cout << "\nAdmin Menu:\n"
            << "1. Add Song\n"
            << "2. Create Playlist\n"
            << "3. Add Song to Playlist\n"
            << "4. Remove Song from Playlist\n"
            << "5. Create/Edit Artist Page\n"
            << "6. Add Song to Artist Page\n"
            << "7. Display All Songs\n"
            << "8. Display All Playlists\n"
            << "9. Logout\n"
            << "Choose option: ";
        int opt; cin >> opt;
        switch (opt) {
        case 1: addSongInteractive(system); break;
        case 2: createPlaylistInteractive(system); break;
        case 3: addSongToPlaylistInteractive(system); break;
        case 4: removeSongFromPlaylistInteractive(system); break;
        case 5: createArtistPageInteractive(system); break;
        case 6: addSongToArtistInteractive(system); break;
        case 7: system.displaySongs(system.songs); break;
        case 8: system.displayPlaylists(system.playlists); break;
        case 9: return;
        default: cout << "Invalid option.\n";
        }
    }
}

void userAddSongToPlaylist(User* user, MusicSystem& system) {
    string playlistName;
    cout << "Enter your playlist name: ";
    cin.ignore();
    getline(cin, playlistName);
    Playlist* playlist = user->findPlaylist(playlistName);
    if (!playlist) {
        cout << "Playlist not found.\n";
        return;
    }
    cout << "System Songs:\n";
    system.displaySongs(system.songs);
    int songIndex;
    cout << "Enter song number to add: ";
    cin >> songIndex;
    if (songIndex < 1 || songIndex >(int)system.songs.size()) {
        cout << "Invalid song selection.\n";
        return;
    }
    playlist->addSong(system.songs[songIndex - 1]);
    cout << "Song added to playlist.\n";
}

void userRemoveSongFromPlaylist(User* user) {
    string playlistName;
    cout << "Enter your playlist name: ";
    cin.ignore();
    getline(cin, playlistName);
    Playlist* playlist = user->findPlaylist(playlistName);
    if (!playlist) {
        cout << "Playlist not found.\n";
        return;
    }
    playlist->displaySongs();
    int songIndex;
    cout << "Enter song number to remove: ";
    cin >> songIndex;
    if (songIndex < 1 || songIndex > playlist->getNumberOfSongs()) {
        cout << "Invalid song selection.\n";
        return;
    }
    playlist->removeSong(playlist->songs[songIndex - 1]);
    cout << "Song removed from playlist.\n";
}

void userCreatePlaylist(User* user) {
    string name;
    cout << "Enter new playlist name: ";
    cin.ignore();
    getline(cin, name);
    if (user->findPlaylist(name)) {
        cout << "Playlist already exists.\n";
        return;
    }
    user->addPlaylist(Playlist(name));
    cout << "Playlist created.\n";
}

void userDeletePlaylist(User* user) {
    string name;
    cout << "Enter playlist name to delete: ";
    cin.ignore();
    getline(cin, name);
    if (!user->findPlaylist(name)) {
        cout << "Playlist not found.\n";
        return;
    }
    user->deletePlaylist(name);
    cout << "Playlist deleted.\n";
}

void userPlaylistPlayback(User* user) {
    string playlistName;
    cout << "Enter playlist name to play: ";
    cin.ignore();
    getline(cin, playlistName);
    Playlist* playlist = user->findPlaylist(playlistName);
    if (!playlist) {
        cout << "Playlist not found.\n";
        return;
    }
    int mode;
    cout << "Select playback mode:\n1. Sequential\n2. Shuffle\n3. Repeat\nChoice: ";
    cin >> mode;
    if (mode == 1) playlist->setPlaybackMode(SEQUENTIAL);
    else if (mode == 2) playlist->setPlaybackMode(SHUFFLE);
    else if (mode == 3) playlist->setPlaybackMode(REPEAT);
    else {
        cout << "Invalid playback mode. Default sequential used.\n";
        playlist->setPlaybackMode(SEQUENTIAL);
    }
    char cmd;
    cout << "Playing playlist \"" << playlist->name << "\". Commands: n = next, p = previous, q = quit\n";
    cout << "Current song: " << playlist->currentSong().name << " by " << playlist->currentSong().artistName << '\n';
    while (true) {
        cout << "Command: ";
        cin >> cmd;
        if (cmd == 'n') {
            playlist->nextSong();
            cout << "Now playing: " << playlist->currentSong().name << " by " << playlist->currentSong().artistName << '\n';
        }
        else if (cmd == 'p') {
            playlist->previousSong();
            cout << "Now playing: " << playlist->currentSong().name << " by " << playlist->currentSong().artistName << '\n';
        }
        else if (cmd == 'q') {
            break;
        }
        else {
            cout << "Unknown command.\n";
        }
    }
}

void userMenu(MusicSystem& system, User* user) {
    while (true) {
        cout << "\nUser Menu:\n"
            << "1. View Saved Songs\n"
            << "2. View Favorite Songs\n"
            << "3. View Favorite Playlists\n"
            << "4. View Personal Playlists\n"
            << "5. Create Playlist\n"
            << "6. Delete Playlist\n"
            << "7. Add Song to Playlist\n"
            << "8. Remove Song from Playlist\n"
            << "9. Search Songs\n"
            << "10. Filter Songs by Artist\n"
            << "11. Filter Songs by Year\n"
            << "12. Filter Songs by Genre\n"
            << "13. Sort Songs Alphabetically\n"
            << "14. Add Song to Saved Songs\n"
            << "15. Remove Song from Saved Songs\n"
            << "16. Add Song to Favorite Songs\n"
            << "17. Remove Song from Favorite Songs\n"
            << "18. Playback Playlist\n"
            << "19. View Artist Page\n"
            << "20. Logout\n"
            << "Choose option: ";
        int opt; cin >> opt;
        switch (opt) {
        case 1: user->displaySavedSongs(); break;
        case 2: user->displayFavoriteSongs(); break;
        case 3: user->displayFavoritePlaylists(); break;
        case 4: user->displayPersonalPlaylists(); break;
        case 5: userCreatePlaylist(user); break;
        case 6: userDeletePlaylist(user); break;
        case 7: userAddSongToPlaylist(user, system); break;
        case 8: userRemoveSongFromPlaylist(user); break;
        case 9: {
            cout << "Enter keyword to search: ";
            string kw; cin.ignore(); getline(cin, kw);
            vector<Song> results = system.searchSongs(kw);
            cout << "Search Results:\n";
            system.displaySongs(results);
            break;
        }
        case 10: {
            cout << "Enter artist name: ";
            string artist; cin.ignore(); getline(cin, artist);
            system.filterSongsByArtist(artist);
            break;
        }
        case 11: {
            cout << "Enter release year: ";
            int year; cin >> year;
            system.filterSongsByYear(year);
            break;
        }
        case 12: {
            cout << "Enter genre: ";
            string genre; cin.ignore(); getline(cin, genre);
            system.filterSongsByGenre(genre);
            break;
        }
        case 13: system.sortSongsAlphabetically(); break;
        case 14: {
            cout << "System Songs:\n";
            system.displaySongs(system.songs);
            int idx; cout << "Enter song number to add to saved songs: "; cin >> idx;
            if (idx < 1 || idx >(int)system.songs.size()) cout << "Invalid song number.\n";
            else user->addToSavedSongs(system.songs[idx - 1]);
            break;
        }
        case 15: {
            user->displaySavedSongs();
            int idx; cout << "Enter song number to remove from saved songs: "; cin >> idx;
            if (idx < 1 || idx >(int)user->savedSongs.size()) cout << "Invalid song number.\n";
            else user->removeFromSavedSongs(user->savedSongs[idx - 1]);
            break;
        }
        case 16: {
            cout << "System Songs:\n";
            system.displaySongs(system.songs);
            int idx; cout << "Enter song number to add to favorite songs: "; cin >> idx;
            if (idx < 1 || idx >(int)system.songs.size()) cout << "Invalid song number.\n";
            else user->addToFavoriteSongs(system.songs[idx - 1]);
            break;
        }
        case 17: {
            user->displayFavoriteSongs();
            int idx; cout << "Enter song number to remove from favorite songs: "; cin >> idx;
            if (idx < 1 || idx >(int)user->favoriteSongs.size()) cout << "Invalid song number.\n";
            else user->removeFromFavoriteSongs(user->favoriteSongs[idx - 1]);
            break;
        }
        case 18: userPlaylistPlayback(user); break;
        case 19: {
            cout << "Enter artist name: ";
            string artist; cin.ignore(); getline(cin, artist);
            system.displayArtistPage(artist);
            break;
        }
        case 20: return;
        default: cout << "Invalid option.\n";
        }
    }
}