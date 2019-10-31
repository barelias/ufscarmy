#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string/join.hpp>

#include "registry_worker.h"
#include "table_worker.h"
#include "index_worker.h"
#include "interpreter.h"
using namespace std;

interpreter::interpreter(string in) {

    this->_file = new ifstream;
    this->workers = new list<worker*>;
    this->_input = in;
    this->eof = false;

    (*workers).push_back(new table_worker);
    (*workers).push_back(new registry_worker);
    (*workers).push_back(new index_worker);

    if (in.compare("cin")) {
        (*this->_file).open(in);
    }
    
}

interpreter::~interpreter() {
    (*this->_file).close();
    delete workers;
}

vector<string> interpreter::read() { //lê comando do terminal
    string input;
    vector<string> splitted_input;
    cout << "[SHELL>$] ";
    do {
        if (!this->_input.compare("cin")){
            getline(cin, input);
        } else {
            getline((*this->_file), input);
            if ((*this->_file).eof()) {
                this->eof = true;
            }
        }
    } while (!input.compare(""));

    if (input.compare("") != 0) {

        int found_separator = 0;
        int index = 0;
        int state = 0;
        int already_found = 0;
        int num_params = 0;
        splitted_input.push_back("");
        for (auto s: input) {
            if (state == 0) {
                if (s != ' ') {
                    splitted_input.back().push_back(s);
                } else {
                    for (auto a: (*workers)) {
                        table_worker *tw = dynamic_cast<table_worker*>(a);
                        registry_worker *rw = dynamic_cast<registry_worker*>(a);
                        index_worker *iw = dynamic_cast<index_worker*>(a);
                        if (tw) num_params += tw->get_num_fields(splitted_input.back());
                        else if (rw) num_params += rw->get_num_fields(splitted_input.back());
                        else if (iw) num_params += iw->get_num_fields(splitted_input.back()); 
                    }
                    if (num_params == 0) return splitted_input;
                    index ++;
                    splitted_input.push_back("");
                    state = 1;
                }
            } else if (state == 1) {
                if (index < (num_params-1)) {
                    if (s != ' ') {
                        splitted_input.back().push_back(s);
                        already_found = 1;
                    } else if (already_found) {
                        index ++;
                        already_found = 0;
                        splitted_input.push_back("");
                        if (index >= (num_params-1)) {
                            state = 2;
                        } else {
                            already_found = 0;
                        }
                    } else {
                        splitted_input.back().push_back(s);
                    }
                } else {
                    if (s != ' ') splitted_input.back().push_back(s);
                    state = 2;
                }
            } else if (state == 2) {
                splitted_input.back().push_back(s);
            }
        }

        transform(splitted_input[0].begin(), splitted_input[0].end(), splitted_input[0].begin(),::toupper);

        if ((!splitted_input[0].compare("CI")) || (!splitted_input[0].compare("BR"))) {

            transform(splitted_input[1].begin(), splitted_input[1].end(), splitted_input[1].begin(),::toupper);
            transform(splitted_input[2].begin(), splitted_input[2].end(), splitted_input[2].begin(),::toupper);
        }
    }
    
    return splitted_input;

}

void interpreter::exec() { //chama os métodos correspondentes
 
    vector<string> input;
    do {
        input = read();
        cout << input[0] << endl;
    } while (run_all(input) && !this->eof);

}

bool interpreter::run_all(vector<string> args) {

    if (args[0].compare("EB")) {
        for (list<worker*>::iterator it=(workers->begin()); it != (workers->end()); it++) {
            
            int ret = 2;

            worker *wk = *it; 
            table_worker *tw = dynamic_cast<table_worker*>(wk);
            registry_worker *rw = dynamic_cast<registry_worker*>(wk);
            index_worker *iw = dynamic_cast<index_worker*>(wk);

            if (tw) ret = tw->run(args);
            else if (rw) ret = rw->run(args);
            else if (iw) ret = iw->run(args);
            if (ret == 0) return true;
            else if (ret == 1) return false;
        }
        return false;
    } else {
        return false;
    }
}