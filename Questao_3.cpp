/*
 * Nome: Arthur Palhares Ferreira Silva
 * Matrícula: 232000688
 * Questão 03: A Razão de Eficiência de um Número
 */


#include <iostream>  
#include <vector>    
#include <utility>   
#include <iomanip>   
#include <cmath>     

using namespace std;
using int64 = long long;

// Função para calcular potência de inteiros.
// A função pow() padrão retorna double, o que pode dar problema de precisão.
// Essa aqui é mais segura para o nosso caso.
int64 potencia_inteira(int64 base, int exp) {
    int64 resultado = 1;
    for (int i = 0; i < exp; ++i) {
        resultado *= base;
    }
    return resultado;
}

int main() {
    cout << "Questao 03: Razao de Eficiencia de um Numero\n\n";

    // Pegando os dados do usuário e validando se estão certos.
    int64 N;
    cout << "Digite um numero inteiro N (entre 1 e 100000): ";
    cin >> N;

    // Validando a entrada N, conforme o enunciado.
    if (N < 1 || N > 100000) {
        cout << "\nErro: O numero N deve estar entre 1 e 100000.\n";
        return 1;
    }
    
    cout << "\n"; 

    // O caso N=1 é especial e precisa ser tratado separadamente.
    if (N == 1) {
        cout << "Para N=1:\n";
        cout << "  tau(1) = 1\n";
        cout << "  sigma(1) = 1\n";
        cout << "  Razao de Eficiencia = 1.00\n";
        return 0; 
    }

    // Passo 1: Fatoração Prima
    cout << "1. Fatoracao Prima de " << N << " \n" ;
    int64 temp = N;
    vector<pair<int64, int>> fatores;

    // Loop de fatoração. Testa divisores até a raiz quadrada de N.
    for (int64 p = 2; p * p <= temp; ++p) {
        if (temp % p == 0) {
            int contagem = 0;
            while (temp % p == 0) {
                temp /= p;
                contagem++;
            }
            fatores.push_back({p, contagem});
        }
    }
    // Se 'temp' ainda for maior que 1, o que sobrou também é um fator primo.
    if (temp > 1) {
        fatores.push_back({temp, 1});
    }

    cout << "   Fatores primos e seus expoentes: ";
    for (size_t i = 0; i < fatores.size(); ++i) {
        cout << fatores[i].first << "^" << fatores[i].second << (i == fatores.size() - 1 ? "" : " * ");
    }
    cout << "\n";

    // Passo 2: Cálculo de tau(N) (número de divisores)
    cout << "\n2. Calculo de tau(N) (numero de divisores)\n";
    int64 tau = 1;
    for (const auto& par : fatores) {
        int expoente = par.second;
        tau *= (expoente + 1);
        cout << "   Para o fator " << par.first << ", o expoente e " << expoente << ". Somando 1, temos " << (expoente + 1) << ".\n";
    }
    cout << "   -> Resultado de tau(" << N << "): " << tau << "\n";

    // Passo 3: Cálculo de sigma(N) (soma dos divisores)
    cout << "\n3. Calculo de sigma(N) (soma dos divisores)\n";
    int64 sigma = 1;
    for (const auto& par : fatores) {
        int64 p = par.first;
        int e = par.second;
        
        // Usamos a fórmula: (p^(e+1) - 1) / (p - 1)
        int64 potencia = potencia_inteira(p, e + 1);
        int64 termo_sigma = (potencia - 1) / (p - 1);
        sigma *= termo_sigma;
        cout << "   Para o fator " << p << ", o termo da soma e " << termo_sigma << ".\n";
    }
    cout << "   -> Resultado de sigma(" << N << "): " << sigma << "\n";

    // Junta tudo e mostra o resultado final.
    cout << "\n4. Calculo da Razao de Eficiencia\n";
    
    // A razão é sigma / tau.
    double razao = 0.0;
    if (tau != 0) {
        razao = static_cast<double>(sigma) / tau;
    }
    
    cout << "   A razao e definida como sigma(N) / tau(N).\n";
    cout << "   Calculo: " << sigma << " / " << tau << "\n";
    cout << "   => Resultado final: " << fixed << setprecision(2) << razao << "\n";
    
    return 0;
}