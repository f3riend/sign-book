#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

struct Saved {
    string name;
    string purpose;
    string link;
};

struct Options {
    string option;
    bool selected;
};

string fileName = "sign-book.csv";

void addData() {
    Saved data;

    cout << "Name: ";
    getline(cin, data.name);
    cout << "Purpose: ";
    getline(cin, data.purpose);
    cout << "Link: ";
    getline(cin, data.link);

    if (data.name.empty() || data.purpose.empty() || data.link.empty()) {
        cout << "Error: All fields must be filled out." << endl;
        return;
    }

    try {
        ofstream file(fileName, ios::app);
        if (file.is_open()) {
            file << data.name << "," << data.purpose << "," << data.link << "\n";
            file.close();
            cout << "Data Added" << endl;
        } else {
            cerr << "Error opening file" << endl;
        }
    } catch (const std::exception& e) {
        cerr << "File operation error: " << e.what() << endl;
    }
}

void loadData(vector<Saved>& dataList) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Saved data;
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            data.name = line.substr(0, pos1);
            data.purpose = line.substr(pos1 + 1, pos2 - pos1 - 1);
            data.link = line.substr(pos2 + 1);
            dataList.push_back(data);
        }
        file.close();
    } else {
        cerr << "Error opening file" << endl;
    }
}

void saveData(const vector<Saved>& dataList) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& data : dataList) {
            file << data.name << "," << data.purpose << "," << data.link << "\n";
        }
        file.close();
    } else {
        cerr << "Error opening file" << endl;
    }
}

void listAndDelete() {
    vector<Saved> dataList;
    loadData(dataList);

    int selected = 0;
    bool finished = false;

    while (!finished) {
        system("cls");

        for (size_t i = 0; i < dataList.size(); ++i) {
            if (i == selected)
                cout << "-> ";
            else
                cout << "   ";
            cout << dataList[i].name << " | " << dataList[i].purpose << " | " << dataList[i].link << endl;
        }

        cout << "\nUse arrow keys to navigate, 'd' to delete, and Enter to return to the menu." << endl;
        char key = _getch();

        switch (key) {
        case 72:
            if (selected > 0)
                selected--;
            break;

        case 80:
            if (selected < dataList.size() - 1)
                selected++;
            break;

        case 13:
            finished = true;
            break;

        case 'd':
            if (!dataList.empty() && selected < dataList.size()) {
                dataList.erase(dataList.begin() + selected);
                if (selected >= dataList.size() && selected > 0)
                    selected--;
            }
            break;
        }
    }

    saveData(dataList);
}

void optionMenu() {
    int selected = 0;
    bool finished = false;

    vector<Options> options = {
        {"Add Data", true},
        {"List and Delete Data", false},
        {"Exit", false}
    };

    while (!finished) {
        system("cls");

        for (size_t i = 0; i < options.size(); ++i) {
            if (i == selected)
                cout << "-> ";
            else
                cout << "   ";

            if (options[i].selected)
                cout << "[x] ";
            else
                cout << "[ ] ";

            cout << options[i].option << endl;
        }

        char key = _getch();

        switch (key) {
        case 72:
            if (selected > 0)
                selected--;
            break;

        case 80:
            if (selected < options.size() - 1)
                selected++;
            break;

        case 13:
            switch (selected) {
            case 0:
                system("cls");
                addData();
                break;
            case 1:
                listAndDelete();
                break;
            case 2:
                finished = true;
                break;
            }
            break;
        }

        for (size_t i = 0; i < options.size(); ++i) {
            options[i].selected = (i == selected);
        }
    }
}

int main() {
    optionMenu();
    system("cls");
    return 0;
}
