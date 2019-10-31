#include "index_worker.h"
#include <iostream>

index_worker::index_worker() {
    
    (this->num_fields)["CI"] = 4;
    (this->num_fields)["RI"] = 3;
    (this->num_fields)["GI"] = 3;

}

index_worker::~index_worker() {

}

int index_worker::run(vector<string> args) {

    if (args.size() == this->num_fields[args[0]]) {
        
        if (!args[0].compare("CI")) {
            return this->CI(args);
        }
        else if (!args[0].compare("RI")) {
            return this->RI(args);
        }
        else if (!args[0].compare("GI")) {
            return this->GI(args);
        } else { 
            return 2;
        }   
    } else {
        cout << "Número incorreto de argumentos" << endl;
        return 1;
    }
}
int index_worker::get_num_fields(string func) {
    map<string,int>::iterator it = (this->num_fields).find(func);
    if(it != (this->num_fields).end()) {
        return (this->num_fields[func]);
    } else {
        return 0;
    }
}

int index_worker::CI(vector<string> arg) {
    cout << "Criando um índice para a tabela " << arg[2] << " usando ";
    string tipo;
    if (!arg[1].compare("A")) {
        cout << "Arvore " << endl;
    } else if (!arg[1].compare("H")) {
        cout << "Hashing " << endl;
    }
    return 0;
}

int index_worker::RI(vector<string> arg) {
    cout << "Removendo o indice da tabela " << arg[1] << " cuja chave e " << arg[2] << endl;
    return 0;
}

int index_worker::GI(vector<string> arg) {
    cout << "Gerando novamente o indice da tabela " << arg[1] << " cuja chave e " << arg[2] << endl;
    return 0;
}
