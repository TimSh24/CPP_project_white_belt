#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;


class Database {

public:
    void add (const string& key, const string& event) {

        if (count(db[key].begin(), db[key].end(), event)==0){

            db[key].push_back(event);}
    };
    void del_single(const string& key, const string& event){

        try
        {
            if (count(db.at(key).begin(), db.at(key).end(), event) == 0){

                cout << "Event not found" << endl;
            }

            else {

                db[key].erase(std::remove(db[key].begin(), db[key].end(), event), db[key].end());

                cout << "Deleted succesfully" << endl;
            }
        }

        catch (exception& ex) {

            cout << "Event not found" << endl;}
    };

    void del_multiple(const string& key){

        int Size = db[key].size();

        db.erase(key);

        cout << "Deleted " << Size << " events" << endl;
    };

    const void print() {

        for (auto item : db) {

            cout << item.first << " ";

            for (auto i : item.second) {

                cout << i << " ";
            }

            cout << endl;
        }
    };

    void const find (const string& key) {

        vector<string> vect_for_visualization;

        try {

            vect_for_visualization = db.at(key);

        } catch (exception& ex) {

            cout << "Exception happens" << endl;
        }

        sort(vect_for_visualization.begin(), vect_for_visualization.end());

        for (auto item : vect_for_visualization) {

            cout << item << " ";
        }

        cout << endl;
    };

private:
    map <string, vector<string>> db;
};

string get_date(){

    string year, month, day, date, i;

    int m = 0;

    stringstream ss, tt;

    cin >> date;

    ss << date;

    tt << date;


    while (getline (tt,i,'-')) {

        if (i.size()>0) {

            m++;
        }
    }

    if (i == "" || m > 3) {

        stringstream err;
        err << "Неверный формат даты"; throw runtime_error(err.str());}


    if (ss.peek() == '-') {

        ss.ignore(1);

        if (ss.peek() == '-') {

            stringstream err;

            err << "Неверный формат года"; throw runtime_error(err.str());}

        else {

            getline(ss,year,'-');

            for (int i=0; i < int(year.size()); i++) {

                if (!isdigit(year[i])) {

                    stringstream err;

                    err << "Неверный формат года"; throw runtime_error(err.str());}
            }

            year.insert(0,"-");
        }
    }

    else {
        getline(ss,year,'-');

        for (int i = 0; i < int(year.size());i++) {

            if (!isdigit(year[i])) {

                stringstream err;

                err << "Неверный формат года"; throw runtime_error(err.str());}
        }
    }

    //ss.ignore(1);

    if (ss.peek() == '-') {

        stringstream err;

        err << "Неверный формат месяца"; throw runtime_error(err.str());}

    else {

        getline(ss,month,'-');}

    for (int i=0; i < int(month.size());i++) {

        if (!isdigit(month[i])) {

            stringstream err;

            err << "Неверный формат месяца"; throw runtime_error(err.str());}

        else if (stoi(month)>12) {

            stringstream err;

            err << "Номер месяца больше 12"; throw runtime_error(err.str());}

    }

    //ss.ignore(1);

    if (ss.peek() == '-') {

        stringstream err;

        err << "Неверный формат дня"; throw runtime_error(err.str());}

    getline(ss,day, ' ');

    for (int i=0; i < int(day.size());i++) {

        if (!isdigit(day[i])) {

            stringstream err;

            err << "Неверный формат дня"; throw runtime_error(err.str());}

        else if (stoi(day) > 31) {

            stringstream err;

            err << "Номер дня больше 31"; throw runtime_error(err.str());}

    }

    stringstream out_stream;

    out_stream << setw(4) << setfill('0') << right << year << setw(1) << '-';

    out_stream << setw(2) << setfill('0') << right << month << setw(1) << '-';

    out_stream << setw(2) << setfill('0') << right << day;

    out_stream >> date;

    return date;
};

int main(){

    Database Base;

    string command;

    string event;

    stringstream line;

    for(;;) {

        std::string line;
        std::string command;
        getline(cin, line);
        stringstream a;
        a << line;
        a >> command;
        if (command != "Print" || command!= "Add" || command != "Del" || command != "Find") {

            cout << "Unknown command: " << command << endl; continue;}

        if (command == "Print") {

            Base.print();}

        else {


            string date;

            try {

                date = get_date();}

            catch (exception& ex) {

                cout << ex.what() << endl;
            }

            if (command == "Add") {

                cin >> event;

                Base.add(date, event);
            }

            if (command == "Del") {

                char c;

                cin.get(c);

                if (c == ' ')

                {

                    cin >> event;

                    Base.del_single(date, event);}

                else {

                    Base.del_multiple(date);}

            }

            if (command == "Find") {

                Base.find(date);
            }

        }

    }

    return 0;

}

