#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>

#include "Header.h"
#include "Tuple.h"

using namespace std;

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
class Relation{
private:
    string name;
    Header header;
    set<Tuple> tuples;
public:
    //constructors
    Relation() = default;
    Relation(string name, Header header) : name(name), header(header) {}

    //getters
    string Get_Name() {
        return name;
    }
    int Get_Size() {
        return tuples.size();
    }

    //setters
    void Set_Tuples(set<Tuple> tuples) {
        this->tuples = tuples;
    }

    //adders
    void Add_Tuple(Tuple t) {
        tuples.insert(t);
    }

    //print function
    string toString() {
        stringstream o;
        for (Tuple t : tuples) {
            if (t.size() > 0) {
                o << " " << t.toString(header) << endl;
            }
            //this wil output A and X in A='bob', X='jane'
        }

        return o.str();
    }

    Relation select(int position, string value) {
        //purpose: finds all the tuples that have a constant value in a certain column
        //parameter: takes 2 parameters -> a position and value
        //result: different number of rows
            // the given position would need to have a value equal to the given value for that tuple

        Relation output(name, header); //create an output with name and header copied over from input
        Tuple tuple;

        //unsigned int tuple_size = tuples.size();
        for (Tuple tuple : tuples) { //go through each row...
            //gets the tuple value of the position desired
            string selected_tuple_value = tuple.Get_TupleValue(position);
            if (selected_tuple_value == value) { //if the tuple value = the value we want...
                output.Add_Tuple(tuple); //add the tuple to the output...

            }
        }
        return output; //returns a relation with different amount of rows!
    }

    Relation select(int position1, int position2) {
        //purpose: finds all the tuples that have the same value in 2 different columns
        //as long as both columns have the same value
        //parameter: takes 2 parameters: both positions
        //result: different number of rows
        // the 2 positions in a tuple would need to have equal values

        //cout << "in select function" << endl;

        Relation output(name, header); //create an output with name and header copied over from input

        //check: if the columns are in bounds
        if (position1 >= header.size() || position2 >= header.size()){ //if the position is greater or equal to size
            throw "out of bound"; //it is out of bound
        }

        for (Tuple tuple : tuples) { //go through each row (the set of tuples)
            if (tuple.Get_TupleValue(position1) == tuple.Get_TupleValue(position2)) { //if the tuple values are the same in both positions
                output.Add_Tuple(tuple); //add the tuple to the relation
            }
        }

        return output; //returns a new relation (ex) X='a' Y = 'a'
    }

    Relation project(vector<int> columnsToProject) { //column positions
        //purpose: changes the number and order of columns in a relation
        //result: either the same number or fewer columns
        //function: changes the header and all tuples in the relation
        //parameter: list of positions of the columns that should be included in the result (columns to be kept)

        Header new_Header; //create a new Header vector

        // Update columnNames with the selcted columns (passed in the function)
        int column_to_parse_through = columnsToProject.size();
        for (unsigned int i = 0; i < column_to_parse_through; i++) {
            string currHeader = header.Find_Header(i); //currHeader = the header we want to find
            new_Header.Add_Header(currHeader);
        }

        Relation output(name, new_Header);

        // Update rows at the selected columns (passed in the function)

        for (auto tuple : tuples) { //go through selected rows
            Tuple new_Tuple; //create a new tuple

            for (auto i : columnsToProject) {
                string currTuple = tuple.Get_TupleValue(i);
                new_Tuple.Add_TupleValue(currTuple); //add tuple
            }

            output.Add_Tuple(new_Tuple); //add tuple to relation
        }

        return output;
    }

    Relation rename(vector<string> header) {
        //purpose: changes the header of the relation
        //result: same tuples as the original (and columns and rows should not be changed)
        //parameter: position, and new name
        //function: replacing the entire list of attributes is easier and avoids issues with name conflicts

        Header new_header(header); //assigns input as a new header

        Relation output(name, new_header);
        output.Set_Tuples(tuples);

        return output;
    }

    bool isJoinable(){
        //purpose: receives 2 tuples and information about where they should match
        return true;
    }
/*
    Tuple Combine_Tuple() {
        //purpose: receives 2 tuples and information about where they should match
    }

    Header Join_Columns(Relation &column1, Relation &column2, map<int, int> &repeatedColumns, set<int> &uniqueColumns) {
        //in the video i think it is the Combine_Headers
        //purpose:
    }

    void Join_Rows(Relation &row1, Relation &row2, Relation &combinedTable, map<int, int> &repeatedColumns, set<int> &uniqueColumns) {
        //purpose:
    }

    Relation Unite(){
        //purpose: after a join, we have to put the relation back into the datbase

        //TIPS: be consistent about which relation is which
            //the one you are inside is the database relation
            //the one you pass in as an argument is the result from the rule evaluation
        //TIPS: when adding a tuple from the rule evaluation to the database, check if it is already existed
            //if(mySet.insert(myTuple).second)
                //set.insert returns a pair: the second part is a bool saying if the inserted element was new to the set
                //if it already existed, do nothing more
                //if it is a new tuple, print it out
    }

    Relation Join(Relation relation){
        //type: a function of the relation class
        //input: another relation to join with
        //returns: the joined relation

        //join is always possible:
            //there will always be a relation to return
            //2 headers can always be combined
            //there might not be any tuples that can be combined

        //join aspects
            //1. combine the 2 Headers
            //2. Go through every pair of tuples
                //a. See if you can combine the tuples
                    //Does every column that is supposed to match actually match?
                //b. If the tuples can be combined, then combine them


        //join psuedocode
        //make the header h for the result relation
        Relation output;
        //	    (combine r1's header with r2's header)
        //
        //	make a new empty relation r using header h
        //
        //	for each tuple t1 in r1
        //	    for each tuple t2 in r2
        //
        //		if t1 and t2 can join
        //		    join t1 and t2 to make tuple t
        //		    add tuple t to relation r
        //		end if
        //
        //	    end for
        //	end for

        //joining 3 or more relations
        //A(w,x,y,z) :- B(w), C(w), D(y), E(z)
            //1. take the first relation and start that as your "result"
            //2. join the result with the second relation and store the result
            //3. Join the result with the third relation and store the result
            //4. join the result with the fourth relation and store the result

        Relation joined_relation(name, header);

        return joined_relation;
    }
    */

};
#endif //PROJECT_1_RELATION_H
