#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "Header.h"
#include "Database.h"
#include "datalogProgram.h"
class Interpreter{
private:
    DatalogProgram program;
    Database database;
public:
    //constructor
    Interpreter(DatalogProgram program) : program(program) {}

    void run(){
        //1. Process the schemes (same as the last project) DONE
        //2. Process the facts (same as the last project) DONE
        //3. Evaluate the rules (new code)
        //4. Evaluate the queries (same as the last project) DONE

        //cout << "will run Interpret_Schemes(); " << endl;
        Interpret_Schemes();

        //cout << "will run Interpret_Facts(); " << endl;
        Interpret_Facts();

        //cout << "will run Interpret_Rules(); " << endl;
        //Interpret_Rules();

        //cout << "will run Interpret_Queries(); " << endl;
        Interpret_Queries();

    }

    void Interpret_Schemes(){
        //takes care of headers
        //goes through each scheme one at a time
        vector<Predicate> scheme_to_go_through = program.Get_Schemes();

        //gets loves then hates
        for (Predicate currScheme : scheme_to_go_through) { //go through
            Header header; //creates new header vector

            //gets E,F then C,D
            //gets the vector of parameters in the scheme and its size
            vector <Parameter> scheme_parameters = currScheme.Get_Parameters();
            unsigned int scheme_parameter_size = scheme_parameters.size();

            //go through each scheme
            for (unsigned int i = 0; i < scheme_parameter_size; i++ ) {

                //find the current header
                Parameter currParameter = scheme_parameters.at(i);
                string currHeader = currParameter.Get_ID();

                //add current header to the header vector
                header.Add_Header(currHeader);
            }

            //find the current relation
            string currRelation = currScheme.Get_ID();

            //add the relation to the database
            database.Add_Relation(currRelation, header); //adding the header to the current scheme in the database!
        }
    }

    void Interpret_Facts() {
        //takes care of rows
        //goes through rows
        //for input 9, size should be 10
        vector <Predicate> rows_to_go_through = program.Get_Facts();

        for (Predicate currFact : rows_to_go_through) {
            Tuple tuple; //creates new tuple vector

            //goes through the things in the rows!
            //EX: loves('bob','jane'); should go through bob and jane (should always be size = 2)
            vector <Parameter> tuple_parameters_to_go_through = currFact.Get_Parameters();
            unsigned int tuple_parameter_size = tuple_parameters_to_go_through.size();

            //go through the tuples
            for (unsigned int i = 0; i < tuple_parameter_size; i++) {

                //get the tuple name
                Parameter currParameter = tuple_parameters_to_go_through.at(i);
                string currTuple = currParameter.Get_ID();

                //add current tuple to the tuple vector
                tuple.Add_TupleValue(currTuple);
            }

            //get the current Fact name
            string currRow = currFact.Get_ID();

            //add the fact
            database.Add_Tuple(currRow, tuple);//adding the tuple to the current row of the database
        }
    }

    void Interpret_Queries() {
        //cout << "Query Evaluation" << endl;

        vector <Predicate> queries_to_go_through = program.Get_Queries();
        int size_of_queries = queries_to_go_through.size();
        for (unsigned int i = 0; i < size_of_queries; i++) { //goes through the queries in the program
            //each query gets a copy of the relation in teh databse with the same name as the query
            //interpreting the query means understanding what the query's parameters want from this relation and....
            //morphing the relation copy into a smallr resulting relation using select, project, and rename functions we implemented in the Relations class

            Predicate currQuery = queries_to_go_through.at(i);
            cout << currQuery.toString() << "?";

            //helper function
            Relation output = Interpret_Predicate(currQuery);

            int output_size = output.Get_Size();

            if (output_size == 0) { //if theres nothing in the schemes, facts, rules or queries
                cout << " " << "No" << endl;
            } else { //if theres something
                cout << " " << "Yes(" << output_size << ")" << endl;
            }

            cout << output.toString();
        }
    }

    Relation Interpret_Predicate (Predicate predicate) {
        //output to return
        string pred_ID = predicate.Get_ID(); //gets the predicate name
        Relation output = database.Get_Relation(pred_ID); //result should have the inputted predicate ID (value)

        //remember me: ways to avoid pointers, make empty vectors lol

        //empty vectors
        //empty vectors to keep in track of whats seen
        map<string, unsigned int> seen;
        string seen_Values = "";

        //empty vectors to keep in track of whats not seen
        vector<int> unseen_Columns; //columns we have not seen
        vector<string> unseen_Headers; //headers we have not seen

        unsigned int col_position = 0; //to keep in track of columns we've seen

        vector<Parameter> tuple_in_predicate = predicate.Get_Parameters();
        unsigned int predicate_size = tuple_in_predicate.size(); //for the for loops

        //SELECT
        for (unsigned int i = 0; i < predicate_size; i++) { //goes through each tuple from the predicate
            Parameter currParameter = tuple_in_predicate.at(i);
            string new_parameter = currParameter.Get_ID(); //gets each parameters ID

            if (currParameter.isConstant()) { //if it is a '
                //uptdate the output by selecting the column
                output = output.select(col_position, new_parameter);    // select type 1 (position, value)

            } else { ////If the parameters/ll is a variable. have we seen the same variable before in this same auerv?
                //using the map of seen
                //map functions
                    //.find(key) accesses
                    //.end
                if (seen.find(new_parameter) != seen.end()) {
                    //update the output by selecting the columns
                    output = output.select(col_position, seen.at(new_parameter));   // select type 2 (position, position)
                    // mark it as seen
                } else {
                    seen.insert({new_parameter, col_position});
                    unseen_Columns.push_back(col_position);
                    unseen_Headers.push_back(new_parameter);
                }
            }
            col_position++;
        }

        // PROJECT
        //using a vector of the indexes at which variables were first seen, project out one column for each variable trom the relation
        output = output.project(unseen_Columns); //remember we are projecting positions

        // RENAME
        //using a vector of all variables found (with no duplicates), rename the relation's header column names to the query variables
        output = output.rename(unseen_Headers); //remember that renaming changes the header

        return output;
    }


};
#endif //PROJECT_1_INTERPRETER_H
