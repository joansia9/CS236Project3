#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H

#include "Header.h"

#include <vector>
#include <string>
#include <sstream>

class Tuple{
private:
    vector<string> tuples;

public:
    Tuple() = default;
    Tuple (vector<string> values) : tuples(values) { }

    bool operator< (const Tuple t) const {
        return tuples < t.tuples;
    }

    //gets the size
    int size() {
        return tuples.size();
    }

    //gets the tuple value
    string Get_TupleValue(int position) {
        int size = tuples.size();

        if (position > size) {
            throw "Ouf of bounds";
        }
        return tuples.at(position);
    }

    //adds the tuple values
    void Add_TupleValue(string value) {
        tuples.push_back(value);
    }

    //print funcftion
    string toString(Header header) {
        if (size() != header.size()) {
            throw "Tuple size has to equal Header size!";
        }
        stringstream o;
        string space = "";
        for (int i = 0; i < size(); i++) {
            o << space << " " << header.Find_Header(i) << "=" << Get_TupleValue(i);
            space = ",";
        }
        return o.str();

        //this will output ='bob', ='jane' in A='bob', X='jane'
    }

};

#endif //PROJECT_1_TUPLE_H
