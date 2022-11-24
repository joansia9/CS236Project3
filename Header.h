#include <string>
#include <vector>
#include <iostream>

using namespace std;

#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H

class Header{
private:
    vector<string> headers;
public:
    //constructors
    Header() = default;
    Header(vector<string> attributes) : headers(attributes) {}

    void Add_Header(string attribute) {
        headers.push_back(attribute);
    }


    //returns the name of the header at a specific position
    string Find_Header(int position) {
        int size = headers.size();

        if (position > size) {
            throw "Index is greater than size, so it is out of bounds";
        }

        return headers.at(position);
    }

    int size() {
        return headers.size();
    }
};
#endif //PROJECT_1_HEADER_H
