#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H

#include <vector>
#include <string>
#include <sstream>

#include "Predicate.h"
using namespace std;

class Rule{
private:
    //given in instructions/diagram
    vector<Predicate> predicates;
    Predicate head;

public:
    void set_PredicateHead(Predicate p) {
        head = p;
    }

    //rule: adding parameter to head
    void push_Predicate(Predicate p){
        predicates.push_back(p);
    }

    //printing
    string toString() {
        string pad = "";
        stringstream o;

        o << head.toString() << " :- "; //convert head to string because it is an object

        for (Predicate currPred : predicates) {
            o << pad << currPred.toString();
            pad = ",";
        }

        return o.str();
    }
};
#endif //PROJECT_1_RULE_H
