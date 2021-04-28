/**
 * @file soma_binaria.cpp
 * @author Carlos Henrique Barreto Mareco
 * @date 20 Abr 2021
 */
#include <iostream>
#include <fstream> // Necessario para ler o arquivo
#include <string>

using namespace std;

void coutBin(bool vetor[]);
int  convBinToDec(bool vetor[]);
void convDecToBin(int valor, bool *vetor);
void c1(bool* vetor);
void c2(bool* vetor);
void somaBin(bool a[], bool b[], bool* resultado);
void exibirOperacoes(int* num);
bool verificaDec(int* num, int linha);
string strBin(bool vetor[]);

int main(){
    int num[2]; // Vetor que guarda os dois valores inteiros.
    ifstream arquivo;

    arquivo.open("decimais.txt"); // Abre o arquivo decimais.txt
    if(arquivo.is_open()){
        int linha = 1; // Contador de linhas do arquivo txt
        while (!arquivo.eof()){
            arquivo >> num[0] >> num[1];
            cout << "Linha (" << linha <<"):"<< endl;
            if(verificaDec(num, linha))
                exibirOperacoes(num);
            cout << "Pressione qualquer tecla para continuar para próxima linha.";
            linha++;
            getchar();
        }
        cout << "Todas as linhas foram lidas!";
        getchar();
        arquivo.close(); // Fecha o arquivo decimais.txt
    } else{
        cout << "ERRO: Não foi possível abrir o arquivo \"decimais.txt\"" << endl;
        getchar();
    }
    return 0;
}
// Imprime binário de 8 bits.
void coutBin(bool vetor[]){
    for (int i = 7; i >= 0; i--){
        cout << vetor[i];
    }
    cout << endl;
}
// Retorna binário de 8 bits em formato de string.
string strBin(bool vetor[]){
    string binario = "";
    for (int i = 7; i >= 0; i--){
        binario = binario + to_string(vetor[i]);
    }
    return binario;
}
// Converte binário de 8 bits para decimal.
int convBinToDec(bool vetor[]){
    int valor = 0;
    int negative = 1;
    int aux[7] = {1, 2, 4, 8, 16, 32, 64};
    if (vetor[7]){
        c1(vetor);
        c2(vetor);
        negative = -1;
    }
    for (int i = 0; i < 7; i++){
        valor += vetor[i] * aux[i];
    }
    return negative*valor;
}
// Converte decimal para binário de 8 bits.
void convDecToBin(int valor, bool* vetor){
    int negative = valor;
    for (int i = 0; i < 8; i++){
        vetor[i] = valor % 2;
        valor = valor / 2;
    }
    if (negative < 0){ //Converte inteiros negativos em binario utilizando c1 e c2.
        c1(vetor);
        c2(vetor);
    }
}
// Realiza o complemento a 1.
void c1(bool* vetor){
    for (int i = 0; i < 8; i++){
        vetor[i] = !(vetor[i]); // Equivalente a porta NOT.
    }
}
// Realiza o complemento a 2.
void c2(bool* vetor){
    bool bit_1[8] = {1,0,0,0,0,0,0,0}; // 1¹⁰ = 00000001²
    bool aux[8];
    somaBin(vetor, bit_1, aux); // Soma 'vetor' com 1 (em binário)
    for (int i = 0; i < 8; i++){
        vetor[i] = aux[i];
    } 
}
// Operação de soma entre dois binários de 8 bits.
void somaBin(bool a[], bool b[], bool* resultado){
    bool up = 0;  // Valor que vai para o próximo.
    for (int i = 0; i < 8; i++){
        resultado[i] = (a[i]^b[i])^up; // S = (A^B)^UP  (XOR = ^)
        up = (a[i]&b[i]) | (a[i]&up) | (b[i]&up); // S = (A.B)+(A.UP)+(B.UP)
    }
}
// Verifica se os valores inteiros são válidos.
bool verificaDec(int* num, int linha){
    bool ok = true;
    for(int i = 0; i < 2; i++){
        if((num[i] > 127) || (num[i] < -127)){
            cout << "ERRO (linha " << linha <<"): O inteiro " << num[i] << " excede o limite de 8 bits." << endl;
            ok = false;
        }
    }
    if((num[0]+num[1] > 127) || (num[0]+num[1] < -127)){
        cout << "ERRO (linha " << linha << "): Resultado da operação excede o limite de 8 bits." << endl;
        ok = false;
    }
    return ok;
}
// Imprime no console as operações realizadas.
void exibirOperacoes(int* num){
    bool bin1[8];
    bool bin2[8];
    bool res[8];
    convDecToBin(num[0], bin1);
    convDecToBin(num[1], bin2);
    somaBin(bin1, bin2, res);
    cout << "Soma: a + b = (" << num[0] << ") + (" << num[1] << ")\n  ";
    cout << strBin(bin1)<<"\n+ "<< strBin(bin2)<<"\n  "<<strBin(res)<<" = "<<convBinToDec(res)<< "\n\n";
    c1(bin2);
    cout << "Subtração: a + (-b) = (" <<num[0] << ") + (" << -1*num[1] << ")\nC1(b) = " << strBin(bin2) << endl;
    c2(bin2);
    cout << "C2(b) = " << strBin(bin2) << " = -b\n  ";
    somaBin(bin1, bin2, res);
    cout << strBin(bin1)<<"\n+ "<< strBin(bin2)<<"\n  "<<strBin(res)<<" = "<<convBinToDec(res)<< endl;
}