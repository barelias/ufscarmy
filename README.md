# projeto-ori

# Proposta do projeto:
  Desenvolvimento e implementação de um sistema de gerenciador de banco de dados simplificado.
  
  * Liguagem de comandos simplificada
  * Base de dados única
  * Indexação dos arquivos por árvores e hash
  
 # Tópicos abordados:
 
  * Armazenamento em memória secundária
  * Conceitos de arquivos
  * Indexação
  * Hashing
  
# Lista de Comandos:


Comandos para manipulação de tabelas(dados e metadados)

| Comando              | Descrição                                                    |
| -------------------- | ------------------------------------------------------------ |
| CT tabela campos | Cria um arquivo vazio associado ao **nome tabela** e o regista como ativo na base, sendo campos uma lista de especificações dos campos que formarão o arquivo. |
| RT tabela          | Apaga o arquivo relativo a tabela e remove seus metadados da base, bem como estruturas associadas. |
| AT tabela          | Apresenta um resumo dos metadados da tabela indicada: arquivos, campos e índices existentens. |
| LT                   | Lista o nome de todas as tabelas existentes na base          |


A especificação de **campos** é uma lista separada por pontos-e-virgulas, sem espaços intermediários, com cada compo especificado pelo par tipo: *nome*

Tipos que devem ser considerados:

| Tipo | Descrição               |
| ---- | ----------------------- |
| INT  | Valor interio com sinal |
| FLT  | Valor real              |
| STR  | Cadeia de caracteres    |
| BIN  | Uma sequencia de bytes  |


Manipulaçao de registros nas tabelas permitem inserção, remoção:

| Comando              | Descrição                                                    |
| -------------------- | ------------------------------------------------------------ |
| IR *tabela registro* | Insere o registro no arquivo da tabela, usando a política de inserção adequada. |
| BR N *tabela busca*  | Busca em tabela todos os registros que satisfaçam o critério de busca. |
| BR U *tabela busca*  | Busca em tabela pelo primeiro registro que satisfaça o critéro busca |
| AR *tabela*          | Apresenta na tela os valores dos registros retornados pela última busca |
| RR *tabela*          | Remove, segundo a política de remoção da tabela, todos os registros da última busca realizada. |



Exemplo de Utilização dos comandos:

CT CLIENTES INT:CODIGO;STR:NOME;BIN:CERTIF</br>
AT CLIENTES</br>
LT</br>
IR CLIENTES 10;JOSE DA SILVA;jose_cert.crt</br>
IR CLIENTES 20;JOSE DE SOUZA;souza.crt</br>
IR CLIENTES 30;JOAO PASCOAL;jp.crt</br>
IR CLIENTES 40;LUIS BERTOLO;lb_novo.crt</br>
IR CLIENTES 50;JOAO PASCOAL;jp2.crt</br>
BR U CLIENTES CODIGO:10</br>
AR CLIENTES</br>
RR CLIENTES</br>
BR N CLIENTES NOME:JOSE DA SILVA</br>
AR CLIENTES</br>
IR CLIENTES 30;JOAO PASCOAL;jp.crt</br>
IR CLIENTES 10;JOSE DA SILVA;jose_cert.crt</br>
BR N CLIENTES NOME:JOAO PASCOAL</br>
AR CLIENTES</br>
EB</br>
