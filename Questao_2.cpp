/*
 * Nome: Arthur Palhares Ferreira Silva
 * Matrícula: 232000688
 * Questão 02: Chaves Periódicas
 */

#include <iostream> 
#include <vector>   
#include <cmath>    


using namespace std;
using int64 = long long;

// Função pra calcular o MDC. Usando Euclides.
int64 mdc(int64 a, int64 b){
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Função pra calcular o MMC.
// O primeiro ano em que tudo sincroniza é o MMC dos ciclos.
int64 mmc(int64 a, int64 b){
    if (a == 0 || b == 0) return 0;
    // Fórmula mmc(a,b) = (|a*b|) / mdc(a,b) Evitando Overflow.
    // Primeiro eu divido, depois multiplico.
    return (a / mdc(a, b)) * b;
}

int main(){
    cout << "====== QUESTAO 02: CHAVES PERIODICAS ======\n\n";

    // --- ENTRADA DE DADOS ---
    // Validando dados do Usuario
    cout << " --ENTRADA DE DADOS-- \n";
    int N;
    cout << "Digite o numero de chaves (entre 1 e 10): ";
    cin >> N;

    // Validando a entrada N.
    if (N < 1 || N > 10){
        cout << "\nErro: O numero de chaves deve estar entre 1 e 10.\n";
        return 1; // Termina o programa com um código de erro.
    }

    vector<int> ciclos(N);
    cout << "Digite os " << N << " ciclos (entre 2 e 20), separados por espaco: ";
    for (int i = 0; i < N; i++){
        cin >> ciclos[i];
        // Validando cada ciclo para ver se está dentro do limite.
        if (ciclos[i] < 2 || ciclos[i] > 20){
            cout << "\nErro: O ciclo " << i + 1 << " (" << ciclos[i] << ") esta fora do intervalo permitido (2 a 20).\n";
            return 1;
        }
    }

    // --- PROCESSAMENTO E PASSO A PASSO ---
    // Calculando MMC
    cout << "\n--- PROCESSAMENTO (Calculo do MMC) ---\n";
    cout << "O primeiro ano em que todas as chaves ativam juntas e o MMC de seus ciclos.\n";

    int64 resultado_mmc = ciclos[0];
    cout << "Passo 1: MMC inicial = " << resultado_mmc << " (ciclo da primeira chave)\n";

    for (int i = 1; i < N; i++){
        int64 mmc_anterior = resultado_mmc;
        resultado_mmc = mmc(resultado_mmc, ciclos[i]);
        cout << "Passo " << i + 1 << ": mmc(" << mmc_anterior << ", " << ciclos[i] << ") = " << resultado_mmc << "\n";

        // Se o MMC passou de 50, parar.
        if (resultado_mmc > 50) {
            cout << "AVISO: O MMC parcial (" << resultado_mmc << ") ja ultrapassou o limite de 50 anos.\n";
            break;
        }
    }

    // --- RESULTADO FINAL ---
    // Agora é só mostrar a conclusão de forma clara.
    cout << "\n--- RESULTADO FINAL ---\n";
    cout << "O MMC final de todos os ciclos e: " << resultado_mmc << ".\n";

    if (resultado_mmc <= 50) {
        cout << "Conclusao: O primeiro ano em que todas as chaves podem ser usadas simultaneamente e " << resultado_mmc << ".\n";
    } else {
        cout << "Conclusao: Nao existe um ano entre 1 e 50 em que todas as chaves possam ser usadas simultaneamente.\n";
    }

    return 0;
}