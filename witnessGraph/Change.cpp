#include "Change.h"

Change::Change(changeid in){
    this->state1 = in.state1;
    this->state2 = in.state2;
    this->lit = in.lit;
    this->cut = in.cut;
    graphs = *(new unordered_map<int>)
}

void Change::include(int subid){
    this->graphs.insert(subid);
}

bool Change::isContido(int subid){
    if (this->graphs.find(subid) == this->graphs.end()){
        return false;
    } else {
        return true;
    }
}

changeid Change::getChangeId(){
    changeid out;
    out.state1 = this->state1;
    out.state2 = this->state2;
    out.lit = this-lit;
    out.cut = this-cut;
    return out;
}
