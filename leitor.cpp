#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctime>
using namespace std;

string removerCaracteres(string valor){
    string nome = valor;

    nome.erase(remove_if(nome.begin(), nome.end(), [](unsigned char c){
        return isspace(c) || ispunct(c);
    }) , nome.end());

    return nome;
}

string encapsulador (string name){
    string nome = name;
    transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

    for (int i = 0;  i < nome.length() ; i++){
        if (nome[i] == ' ' ){
            nome[i] = '_';
        }
    }
    return nome;
}

string desencapsulador (string name){
    string nome = name;
    transform(nome.begin(), nome.end(), nome.begin(), ::tolower);

    for (int i = 0;  i < nome.length() ; i++){
        if (nome[i] == '_'){
            nome[i] = ' ';
        }
    }
    return nome;
}

int quantidadeDeContatos (bool isVisible = false){
    fstream lista;
    lista.open("../lista.txt", ios:: in);
    string name, number, log , dia, mes ,hora , minuto;
    int cont = 0;


    while(lista >> name >> number >> log >> dia >> mes >> hora >> minuto){
        cont++;
    }

    if(isVisible == false) {
        cout << "Existem " << cont << " contatos em sua lista telefonica" << endl;
        return 1;
    } else {
        return cont;
    }

}

void listarUsuarios (){
    fstream lista;
    lista.open("../lista.txt", ios:: in);
    string nome, numero, log, dia, mes ,hora , minuto;

    while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){
        cout << desencapsulador(nome) << " : " << numero << " - " << log << " em  Data: " << dia << "/" << mes <<  "  hora: " << hora << ":"<< minuto <<  endl;
    }

    cout << endl;
    quantidadeDeContatos();

    lista.close();
}

void procurarUsuario(string nameUser , string numberUser = " "){

    fstream lista;
    lista.open("../lista.txt", ios:: in); 
    string nome, numero, log, dia, mes ,hora , minuto;
    bool encontrado; 
    int index = 0;

    while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){

        if ( nome == encapsulador(nameUser) || numero == removerCaracteres(numberUser) ){
            cout << desencapsulador(nome) << " : " << numero << endl;
            encontrado = true;
        }

        index++;
    }

    if (encontrado == false ){
        cout << "Contato não encontrado" << endl;
    }

    lista.close();

}

void procurarUsuarioFiltro(){

    int x;
    bool isSerach = false;
    string valor;
    system("cls");

    cout << "- Tipo de filtro " << endl;
    cout << "1 - Dia" << endl;
    cout << "2 - Mes" << endl;
    cout << "3 - Hora" << endl;
    cout << "4 - Editados" << endl;
    cout << "5 - Inseridos" << endl;
    cin >> x ;
    cout << endl;

    cout << "O valor: " ;
    cin >> valor;

    while (x > 5 || x < 1){
       cout << "Escreva um valor valido" << endl;
       cin >> x ;
    }
    
    fstream lista;
    lista.open("../lista.txt", ios:: in); 
    string nome, numero, log, dia, mes ,hora , minuto;

    switch (x){
        case 1:

            if (valor.length() == 1){
                valor = "0"+valor;
            }

            while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){

                if (valor == dia){
                    cout << desencapsulador(nome) << " : " << numero << " - " << log << " em  Data: " << dia << "/" << mes <<  "  hora: " << hora << ":"<< minuto <<  endl;
                    isSerach = true;
                } 
            }
            break;
        case 2:
            
            if (valor.length() == 1){
                valor = "0"+valor;
            }

            while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){

                if (valor == mes){
                    cout << desencapsulador(nome) << " : " << numero << " - " << log << " em  Data: " << dia << "/" << mes <<  "  hora: " << hora << ":"<< minuto <<  endl;
                    isSerach = true;
                }
            }
            break;
        case 3:
            
            if (valor.length() == 1){
                valor = "0"+valor;
            }

            while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){

                if (valor == hora){
                    cout << desencapsulador(nome) << " : " << numero << " - " << log << " em  Data: " << dia << "/" << mes <<  "  hora: " << hora << ":"<< minuto <<  endl;
                    isSerach = true;
                } 
            }
            break;
        case 4:
            while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){
                if ( "EDITADO" == log){
                    cout << desencapsulador(nome) << " : " << numero << " - " << log << " em  Data: " << dia << "/" << mes <<  "  hora: " << hora << ":"<< minuto <<  endl;
                    isSerach = true;
                }
            }
            break;
        case 5 : 
            while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){
                if ("INSERIDO" == log){
                    cout << desencapsulador(nome) << " : " << numero << " - " << log << " em  Data: " << dia << "/" << mes <<  "  hora: " << hora << ":"<< minuto <<  endl;
                    isSerach = true;
                }
            }
            break;

        default:
            break;
    }

    if (isSerach ==  false){
        cout << "Contato não encontrado" << endl;
    }
    
    cout << endl << endl;

    lista.close();


}

int retornarUsuarioProcurado (string nameUser , string numberUser = " "){

    fstream lista;
    lista.open("../lista.txt", ios:: in); 
    string nome, numero, log, dia, mes ,hora , minuto;
    bool encontrado; 
    int index = 0;

    while(lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){



        if ( nome == encapsulador(nameUser) || numero == removerCaracteres(numberUser) ){
            encontrado = true;
        }

        index++;
    }

    if (encontrado == false ){
        return 1;
    }

    lista.close();

    return index;

}


void cadastrarUsuario (string nameUser, string numbUser, bool estado = false){
    fstream lista;
    lista.open("../lista.txt", ios::out | ios::app);
    string nome = encapsulador(nameUser);
    string numero = removerCaracteres(numbUser);
    string log, Day, Month;

    if (estado == false){
        log = "INSERIDO";
    } else {
        log = "EDITADO";
    }

    time_t timer ;
    struct tm *horaAtual;
    time(&timer); 
    horaAtual = localtime(&timer);
    
    int dia = horaAtual->tm_mday;
    int mes = horaAtual->tm_mon + 1;

    int hora = horaAtual->tm_hour;
    int minuto = horaAtual->tm_min;

    Day = to_string(dia);
    Month = to_string(mes);

    if (Day.length() == 1){
        Day = "0"+Day;
    }
    if (Month.length() == 1){
        Month = "0"+Month;
    }

    lista << endl << nome << " " << numero << " " << log << " " << Day << " " << Month << " " << hora << " " << minuto;
    lista.close();
}

void excluirContato (string name ,string contato){
    int index = retornarUsuarioProcurado(name, contato);
    
    if (index != 1) {

        fstream lista;
        lista.open("../lista.txt", ios::in);
        string nome, numero, log, dia, mes ,hora , minuto;

        int contador = 0;

        int tamanho = quantidadeDeContatos(true) ;
        string listaDeUsuarios [tamanho][7];


        while (lista >> nome >> numero >> log >> dia >> mes >> hora >> minuto){
            if (desencapsulador(nome) == name && numero == removerCaracteres(contato) ){
                tamanho--;
            } else {
                listaDeUsuarios[contador][0] = nome;
                listaDeUsuarios[contador][1] = numero;
                listaDeUsuarios[contador][2] = log;
                listaDeUsuarios[contador][3] = dia;
                listaDeUsuarios[contador][4] = mes;
                listaDeUsuarios[contador][5] = hora;
                listaDeUsuarios[contador][6] = minuto;


                contador++;
            }
        }

        lista.close();

        lista.open("../lista.txt", ios::out);

        for (int i = 0 ; i < tamanho; i++){
            lista << listaDeUsuarios[i][0] << " " << listaDeUsuarios[i][1] << " " << listaDeUsuarios[i][2] << " " << listaDeUsuarios[i][3]; 
            lista << " " << listaDeUsuarios[i][4] << " " << listaDeUsuarios[i][5] << " " << listaDeUsuarios[i][6];

            if (i + 1 == tamanho){   
            } else {
                lista << endl; 
            }
        }

        lista.close();

    } else {
        cout << "Contato nao encontrado" << endl;
    }

}

void atualizarUsuario (string name, string number){
    string nome = name;
    string contato = number;
    excluirContato(nome,contato);

    string novoNome; 
    string novoContato ;


    cout << "Novo nome :" << endl; 
    getline(cin,novoNome);

    cout << "Novo numero :" << endl; 

    getline(cin,novoContato);

    cadastrarUsuario(novoNome,novoContato , true);
}

void sistemaDaLista (){
    int sair = 0;
    int controlador;
    string nome , numero;

    while (sair == 0){

        cout << "O que voce gostaria de fazer : " << endl ;
        cout << "1 - adicionar um numero" << endl ;
        cout << "2 - procurar um numero" << endl ;
        cout << "3 - listar todos os numero" << endl ;
        cout << "4 - Remover um numero" << endl ;
        cout << "5 - Atualizar um contato" << endl ;
        cout << "6 - Pesquisar por filtro" << endl;
        cout << "7 - sair" << endl;

        cin >> controlador;
        cout << endl;

        cin.ignore();

        switch (controlador){
            case 1:
                cout << "escreva o nome \n";
                getline(cin,nome);
                cout << endl; 

                cout << "escreva o numero \n";
                getline(cin,numero);
                cout << endl;

                nome = encapsulador(nome);

                cadastrarUsuario(nome,numero);

                cout << "usuario cadastrado" << endl;
                break;
            case 2:
                cout << "escreva o nome que deseja procurar\n";
                getline(cin,nome);
                cout << endl;
                cout << "escreva o numero \n";
                getline(cin,numero);
                cout << endl;


                nome = encapsulador(nome);

                procurarUsuario(nome,numero);
                break;
            case 3:
                cout << "Lista de usuarios" << endl ;
                listarUsuarios();

                cout << endl;
                break;
            case 4:
                cout << "Contato que deseja excluir" << endl ;
                getline(cin,nome);

                cout << "Numero que deseja excluir" << endl ;
                getline(cin,numero);

                excluirContato(nome,numero);

                cout << endl;
                break;
            case 5 :
                cout << "Contato que deseja altera" << endl ;
                getline(cin,nome);

                cout << "Numero do contato " << endl ;
                getline(cin,numero);

                atualizarUsuario(nome , numero);
                break;
            case 6 :
                procurarUsuarioFiltro();
                break;
            case 7 :
                sair = 2;
                cout << "Saindo...." << endl;
                break;
            default : 
                cout << "Digite um numero valido" << endl;
                break;
        }
    }
}


int main(){

    sistemaDaLista();

}