#include "table_worker.h"
#include "table.h"
#include "file.h"
#include <iostream>


int RT(vector<string> args) { //remove tabela. EX: RT CLIENTES

    cout << "Deletando tabela " << args[1] << endl;

    table _table(args[1], false);
    bool res = _table.del();

    cout << "meta/"+args[1]+".meta" << endl;

    if (res) {
        cout << "Deletado com sucesso" << endl;
    } else {
        cout << "Falha deletando a tabela " << endl;
        return 1;          
    }

    return 0;

}
int CT(vector<string> args) { //cria tabela. EX: CT TABELA CAMPO_DE_DADOS

    if (!metafile::verify_file_existence("meta/" + args[1] + ".meta")) {
        cout << "Erro: tabela já existente" << endl;
        return 1;
    }
    else{
        cout << "Criando tabela: " << args[1] << endl;
        cout << "Com os campos: " << args[2] << endl;

        table _table(args);
        // result_Fields(argv[2]);

        return 0;

    }
}

int AT(vector<string> args) { //lista metadados de uma tabela. EX: AT CLIENTES
    
    metafile m_table("meta/tables.meta");
    m_table.show_metadata(args[1]);   

    return 0;
}

int LT(vector<string> args) { //lista todas as tabelas existentes. EX: LT
    cout << "Lista das tabelas criadas: " << endl;
    metafile metadata_table("meta/tables.meta");
    metadata_table.show();
    
    return 0;
}

table_worker::table_worker() {
    
    this->functions = new map<string, tfunc>; 
    (*this->functions)["CT"] = (tfunc) CT;
    (*this->functions)["RT"] = (tfunc) RT;
    (*this->functions)["AT"] = (tfunc) AT;
    (*this->functions)["LT"] = (tfunc) LT;
    
    (this->num_fields)["CT"] = 3;
    (this->num_fields)["RT"] = 2;
    (this->num_fields)["AT"] = 2;
    (this->num_fields)["LT"] = 1;

}

table_worker::~table_worker() {
    
    delete this->functions; 
    
}

int table_worker::get_num_fields(string func) {
    map<string,int>::iterator it = (this->num_fields).find(func);
    if(it != (this->num_fields).end()) {
        return (this->num_fields[func]);
    } else {
        return 0;
    }
}

int table_worker::run(vector<string> args) {

    if ((*this->functions).find(args[0]) != (*this->functions).end()) {
        if (args.size() == this->num_fields[args[0]]) {
            return (*(*this->functions)[args[0]])(args);
        } else {
            cout << "Número incorreto de argumentos" << endl;
            return 1;
        }
    } else { 
        return 2;
    }   
    
}
