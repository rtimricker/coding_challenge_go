
 /* 
  Your solution must be able to answer the following types of questions about the example log:
    1. How many users accessed the server?
    2. How many uploads were larger than `50kB`?
    3. How many times did `jeff22` upload to the server on April 15th, 2020?

 # Details
 The log is represented by a CSV formatted file where column data is ordered: `timestamp`, `username`, `operation`, `size`.
 
 - The `timestamp` is recorded in the UNIX date format.
 - The `username` is a unique identifier for the user.
 - The `operation` indicates if an `upload` or `download` occurred, no other values will appear in this column.
 - The `size` is an integer reflecting file size in `kB`.
 */

#include <iostream>     // std::cin, std::cout
#include <fstream>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <stdlib.h>

using namespace std;

class _log 
{
private:
    struct items {
        string timestamp;
        string username;
        string operation;
        string size;
     };

    vector<struct items> v_items;
    list<string> usernamelist;
    string line;
    ifstream file;
    items i; 
    int count = 0;
    string namefile;

public:
    ~_log(void)
    {
        //cout << "destructor" << endl;
        file.close();
    }
    _log(void)
    {
        namefile = "server_log.csv";
        file.open(namefile);

        if( !file.is_open()) {
            cout << "File "<< namefile <<" not found." << endl;
            //exit(-1);
            return;
        }    

        // bypass first entry in file
        getline(file, line, '\n');
        // start with second line
        while (file) {
            i.timestamp.clear();
            i.username.clear();
            i.operation.clear();
            i.size.clear();

            getline(file, i.timestamp, ',');
            if (i.timestamp == "") break;
            getline(file, i.username, ',');
            getline(file, i.operation, ',');
            getline(file, i.size, '\n');

            v_items.emplace_back(i);
            //v_items.push_back(i);

            bool found = false;
            for (list<string>::iterator iter = begin(usernamelist); iter != end(usernamelist); ++iter) {
                if (i.username.compare(*iter) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                usernamelist.emplace_back(i.username);
                usernamelist.sort();
                usernamelist.unique();
            }
        }
    }

    int getTotalEntries() 
    {
        //for (auto iter : v_items) {
        //    cout << "timestamp: " << iter.timestamp 
        //        << ", username: " << iter.username 
        //        << ", operation: " << iter.operation
        //        << ", size: " << iter.size << endl;
        //}
        cout << "Total entries: " << v_items.size() << endl;
        return v_items.size();
    }

    int getUniqueEntriesCount()
    {
        cout << "Unique entries: " << usernamelist.size() << endl;
        return usernamelist.size();
    }

    int getUploadGreaterThanCount (int size)
    {
        // users upload greater than 50kB
        //cout << "========== ==========\n";
        for (vector<struct items>::iterator iter = begin(v_items); iter != end(v_items); ++iter) {
            if ((*iter).operation.compare("upload") == 0) {
                int val = atoi((*iter).size.c_str());
                if (val > size) {
                    //cout << "timestamp: " << (*iter).timestamp 
                    //<< ", username: " << (*iter).username 
                    //<< ", operation: " << (*iter).operation
                    //<< ", size: " << (*iter).size << endl;

                    count++;
                }
            }
        }
        return count;
    }

    int getUploadCount (string username, string timestamp)
    {
        count = 0;
        string mofy[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

        string _day, _month, _year;
        vector<string> result;
        stringstream s_stream(timestamp);

        getline(s_stream, _day, '/');
        getline(s_stream, _month, '/');
        getline(s_stream, _year, '/');
        int mnth = atoi(_month.c_str()) - 1;
        _month = mofy[mnth];

        cout << endl << "day: " << _day << ", month: " << _month << ", year: " << _year << endl;

        // How many times did `jeff22` upload to the server on April 15th, 2020?
        for (vector<struct items>::iterator iter = begin(v_items); iter != end(v_items); ++iter) {
                string day, month, date, clock, code, year;
                stringstream s_stream((*iter).timestamp);
                getline(s_stream, day, ' ');
                getline(s_stream, month, ' ');
                getline(s_stream, date, ' ');
                getline(s_stream, clock, ' ');
                getline(s_stream, code, ' ');
                getline(s_stream, year, ' ');
                //cout << "day: " << day << ", month: " << month << ", date: " << date << ", year: " << year << endl; 

            //if ((*iter).timestamp.compare(timestamp) == 0 && (*iter).operation.compare("upload") == 0) {
            if (date.compare(_day) == 0 &&
                month.compare(_month) == 0 && 
                year.compare(_year) == 0 &&
                (*iter).username.compare(username) == 0 &&
                (*iter).operation.compare("upload") == 0) {

                cout << "timestamp: " << (*iter).timestamp 
                    << ", username: " << (*iter).username 
                    << ", operation: " << (*iter).operation
                    << ", size: " << (*iter).size << endl;

                count++;
                if (count > 5) break;

            }
        }
        return count;
    }
};

int main(void)
{
    _log log;

    // 1. How many users accessed the server?
    cout << "1. How many users accessed the server? " << endl << log.getUniqueEntriesCount() << endl;

    // 2. How many uploads were larger than `50kB`?
    cout << "2. How many uploads were larger than `50kB`? " << endl << log.getUploadGreaterThanCount(50) << endl;

    // 3. How many times did `jeff22` upload to the server on April 15th, 2020?

//111 Wed Apr 15 03:06:46 UTC 2020,jeff22,upload,45

    // DD/MM/YYYY
    cout << "3. How many times did `jeff22` upload to the server on April 15th, 2020? " << log.getUploadCount("jeff22", "15/04/2020") << endl;
    return 0;
}


