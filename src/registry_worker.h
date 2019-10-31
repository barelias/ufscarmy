#include "worker.h"
#include "table.h"
#include <string>
#include <vector>
#include <map> 

#ifndef REGISTRY_H
#define	REGISTRY_H
using namespace std;
// typedef int (*pfunc)(vector<string> arg, table tabl);

class registry_worker : public worker{
public:

    registry_worker();
    ~registry_worker();
    virtual int run(vector<string> arg);
    int get_num_fields(string func);

private:

    map<string, string> results;
    table *tbl;
    int IR(vector<string> arg, table tbl);
    int BR(vector<string> arg, table tbl);
    int AR(vector<string> arg, table tbl);
    int RR(vector<string> arg, table tbl);
    map<string, int> initial_addresses;
    map<string, int> final_addresses;

};

#endif