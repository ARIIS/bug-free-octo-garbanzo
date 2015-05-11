#ifndef CHANGE_H
#define	CHANGE_H

#include "Estado.h"
#include <unordered_set>

struct identificators{
    int state1;
    int state2;
    literalNegativo lit;
    bool cut;
} changeid;

class Change{
    private:
        //int type;
        int state1;
        int state2;
        literalNegativo lit;
        bool cut;
        unordered_set<int> graphs;
        
    public:
        void include(int subid);
        bool isMember(int subid);
        changeid getChangeId();
};

#endif