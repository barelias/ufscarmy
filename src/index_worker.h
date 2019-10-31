#include "worker.h"
#include "table.h"
#include <string>
#include <vector>
#include <map> 

#ifndef INDEX_H
#define	INDEX_H
using namespace std;
// typedef int (*pfunc)(vector<string> arg, table tabl);

class index_worker : public worker{
public:

    index_worker();
    ~index_worker();
    virtual int run(vector<string> arg);
    int get_num_fields(string func);

private:

    map<string, string> results;
    int CI(vector<string> arg);
    int RI(vector<string> arg);
    int GI(vector<string> arg);

};

#endif