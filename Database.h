//
// Created by Joan Siasoyco on 11/10/22.
//

#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H

#include <map>
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

class Database {

private:
    map<string, Relation> database; //makes a map of the relations!

public:
    map<string, Relation> Get_Database() {
        return database;
    }

    Relation Get_Relation(string key) {
        return database.at(key);
    }

    Relation Add_Relation(string name, Header header) {
        Relation new_Relation(name, header);

        database.insert({name, new_Relation});

        return new_Relation;
    }

    void Add_Tuple(string key, Tuple tuple) {
        database.at(key).Add_Tuple(tuple);
    }
};

#endif //PROJECT_1_DATABASE_H
