#include "registry_worker.h"
#include "table.h"
#include <iostream>

int registry_worker::IR(vector<string> args, table tbl)
{ //insere registro na tabela. EX: IR TABELA CAMPO_DE_DADOS

    cout << "Inserindo Registro na tabela: " << args[1] << endl;
    cout << "Com os Registros: " << args[2] << endl;

    tbl.insert_one(args[2], args[1]);

    return 0;
}

int registry_worker::BR(vector<string> args, table tbl)
{ //realiza busca na tabela

    string main_result = "";
    if (!args[1].compare("N")) { //busca por todas as ocorrências na tabela
        main_result = "Registros da tabela " + args[0] + " com o critério " + args[3] + "\n\n";
        vector<string> result;
        vector<int> inital_address, final_address;
        result = tbl.query_many(args[3], inital_address, final_address);
        if (result.empty()) {
            main_result += "Nenhum registro encontrado\n\n";
        }
        else {   
            main_result += " registros encontrados:\n\n";
            int idx = 0;
            for (vector<string>::iterator it = result.begin(); it != result.end(); it++) {
                main_result += *it + "\n\n";
                this->initial_addresses[args[2]] = inital_address[idx];
                this->final_addresses[args[2]] = final_address[idx];
            }
        }
    }
    else if(!args[1].compare("U")) { //busca pela primeira ocorrência na tabela
        main_result = "Busca em " + args[2] + " pelo critério " + args[3] + "\n\n";
        int inital_address, final_address;
        string result;
        result = tbl.query_one(args[3], inital_address, final_address);
        if (result.empty()) {
            main_result += "Nenhum registro encontrado\n\n";;
        } else {
            this->initial_addresses[args[2]] = inital_address;
            this->final_addresses[args[2]] = final_address;
            main_result += "Registro encontrado:\n\n" + result;
        }
    }
    else{
        main_result += "syntax error\n\n";
    }
 
    this->results[args[2]] = main_result;

    return 0;
}

int registry_worker::AR(vector<string> args, table tbl)
{

    cout << "Registros da última busca: " << endl;
    cout << this->results[args[1]] << endl;
    return 0;
}

int registry_worker::RR(vector<string> args, table tbl)
{

    tbl.invalidate_line(initial_addresses[args[1]], final_addresses[args[1]]);

    return 0;
}

int registry_worker::get_num_fields(string func)
{
    map<string, int>::iterator it = (this->num_fields).find(func);
    if (it != (this->num_fields).end())
    {
        return (this->num_fields[func]);
    }
    else
    {
        return 0;
    }
}

registry_worker::registry_worker()
{

    // this->functions = new map<string, pfunc>;
    (this->num_fields)["IR"] = 3;
    (this->num_fields)["BR"] = 4;
    (this->num_fields)["AR"] = 2;
    (this->num_fields)["RR"] = 2;
    this->results.clear(); //limpa os resultados quando abre uma nova execucao
}

registry_worker::~registry_worker()
{

    // free(this->functions);
}

int registry_worker::run(vector<string> args)
{

    if (this->get_num_fields(args[0]))
    {

        if (args.size() == this->num_fields[args[0]])
        {

            if (this->tbl && (*this->tbl).get_name().compare((!args[0].compare("BR") ? args[2] : args[1])))
            {
            }
            else
            {
                this->tbl = new table((!args[0].compare("BR") ? args[2] : args[1]));
            }

            if (!args[0].compare("IR"))
            {
                return this->IR(args, *(this->tbl));
            }
            else if (!args[0].compare("BR"))
            {
                return this->BR(args, *(this->tbl));
            }
            else if (!args[0].compare("AR"))
            {
                return this->AR(args, *(this->tbl));
            }
            else if (!args[0].compare("RR"))
            {
                return this->RR(args, *(this->tbl));
            }
            else
            {
                return 2;
            }
        }
        else
        {
            cout << "Número incorreto de argumentos" << endl;
            return 1;
        }
    }
    else
    {
        return 2;
    }
}