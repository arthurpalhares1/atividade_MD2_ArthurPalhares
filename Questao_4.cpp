/*
 * Nome: Arthur Palhares Ferreira Silva
 * Matrícula: 232000688
 * Questão 04: Completar Código
 */

#include <stdio.h>

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos.
// Implementa o Algoritmo de Euclides.
int mdcComPassos(int a, int b) {
    int resto;
    // O laço continua enquanto o divisor 'b' não for zero.
    while (b != 0) { // [1] A condição correta é b != 0
        resto = a % b;
        printf("Algoritmo de Euclides: %d = (%d * %d) + %d\n", a, a / b, b, resto);
        
        // A lógica do algoritmo: o antigo divisor vira o novo dividendo,
        // e o resto vira o novo divisor.
        a = b;     // [10] Atribuição lógica do algoritmo
        b = resto; // [14] [2] Atribuição lógica do algoritmo
    }
    printf("MDC encontrado: %d\n", a);
    return a;
}

// Função para calcular o inverso modular usando o Algoritmo Estendido de Euclides.
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A_original = a; // Guarda o 'a' original para a mensagem final

    // O inverso só existe se mdc(a, m) == 1.
    // Este código não verifica antes, mas o algoritmo estendido lida com isso.
    // [3] Esta linha no PDF parece ser um erro de digitação/formatação e não é necessária.

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    // Se o resultado for negativo, ajustamos para o menor representante positivo.
    if (x1 < 0) {
        x1 += m0; // [4] Adiciona o módulo original se o resultado for negativo
    }
    
    printf("\nO inverso de %d mod %d e: %d\n", A_original, m0, x1);
    return x1;
}

// Função para exponenciação modular otimizada.
long long powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base;
    b %= mod;
    while (exp > 0) {
        // Se o expoente é ímpar, multiplica o resultado pela base atual.
        if (exp % 2 == 1) { // [5] Condição para expoente ímpar
            res = (res * b) % mod;
        }
        // Eleva a base ao quadrado e divide o expoente por 2.
        b = (b * b) % mod;
        exp >>= 1; // Equivale a exp = exp / 2;
    }
    return res;
}

int main() {
    int H, G, Zn, x, n1;
    
    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    // Para fazer a divisão modular (H/G) mod Zn, calculamos H * (inverso de G) mod Zn
    int inverso = inversoModular(G, Zn); // [6] Chamada da função para achar o inverso
    
    int a = ((long long)H * inverso) % Zn;

    printf("Fazendo a multiplicacao modular: (%d * %d) mod %d = %d\n", H, inverso, Zn, a);
    
    // Aplicação do Pequeno Teorema de Fermat: como n1=13 é primo, podemos reduzir o expoente x
    // fazendo x mod (n1-1), ou seja, 10 mod 12. Neste caso, não há redução.
    // O código já calcula eficientemente sem a redução explícita.
    printf("\nCalculando a^x mod n1 (a=%d, x=%d, n1=%d)...\n", a, x, n1);
    
    long long resultado = powMod(a, x, n1); // [7] Chamada da função de exponenciação
    
    printf("\nSendo %d o inverso de %d mod %d\n", inverso, G, Zn);
    printf("Valor final da congruencia: %lld\n", resultado);

    return 0;

}

/* Entradas e saídas do código:
Insira H: 7
Insira G: 3
Insira Zn: 11
Insira x: 10
Insira n1: 13 


O inverso de 3 mod 11 e: 4
Fazendo a multiplicacao modular: (7 * 4) mod 11 = 6

Calculando a^x mod n1 (a=6, x=10, n1=13)...        

Sendo 4 o inverso de 3 mod 11
Valor final da congruencia: 4

Resposta V ou F:
( V ) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
( F ) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
( V ) A operação (H * inverso) % Zn representa a divisão modular de H por G.
( F ) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.
( F ) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.
( V ) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

*/
