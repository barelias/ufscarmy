#include <string>
#include <fstream>
#include <variant>
#include <tuple>

using namespace std;

#ifndef FILE_T
#define FILET

#define SEPARATOR_LINE "separatorline"
#define SEPARATOR_ITEM "separatoritem"

int bytes_to_int(string buff);

class metafile {
public:
    metafile(string file_path);
    ~metafile();
    bool insert_int(int a);
    bool insert_line(string line, vector<tuple<int,int>> available = vector<tuple<int, int>>()); //insere uma linha nova no arquivo
    bool remove_line(string line); //remove linha do arquivo
    bool invalidate_line(string line); //marca linha como inválida e disponível para inserção
    bool show_metadata(string name); //apresenta os metadados da tabela "query"
    void show(); //lista todas as tabelas criadas
    string find_first(string query); //encontra primeira ocorrência do elemento "query"
    string find_first_binary(int index, string value, vector<string> type, int & address, int & size, vector<int> deleted); //encontra primeira ocorrência do elemento "query"
    vector<string> find_many_binary(int index, string value, vector<string> type, vector<int> & address, vector<int> & size, vector<int> deleted);
    vector<string> find_all(string query); //encontra todas as ocorrências do elemento "query"
    static bool verify_file_existence(string file_path); //verifica a existência do arquivo
    vector <string> get_types(); //retorna os tipos da tabela
private:
    string file_name;
    ifstream *_file;
    bool verify_line_existence(string line);
    bool rewrite_ints_without(int deleted, vector<tuple<int,int>> available);
};

#endif