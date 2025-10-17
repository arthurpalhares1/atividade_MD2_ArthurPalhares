/*
 * Nome: Arthur Palhares Ferreira Silva
 * Matrícula: 232000688
 * Questão 01: Sistema RSA com fatoração p de Pollard
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <tuple>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;
using int64 = long long;

// --- FUNCOES MATEMATICAS FUNDAMENTAIS

// Função para fazer multiplicação modular (a * b) % mod
int64 mulmod(int64 a, int64 b, int64 mod) {
    int64 res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

// Função pra calcular o MDC mostrando os passos do Algoritmo de Euclides.
int64 mdc_com_passos(int64 a, int64 b) {
    a = llabs(a);
    b = llabs(b);
    int64 a_orig = a, b_orig = b;

    cout << "  [MDC] Calculando mdc(" << a_orig << ", " << b_orig << ") com Algoritmo de Euclides:\n";
    if (b == 0) {
        cout << "  [MDC] b=0, mdc=" << a << "\n";
        return a;
    }
    while (b != 0) {
        int64 r = a % b;
        cout << "  [MDC] " << a << " = " << (a / b) << " * " << b << " + " << r << "\n";
        a = b;
        b = r;
    }
    cout << "  [MDC] Resultado: " << a << "\n";
    return a;
}

// Essa aqui é pra achar o inverso modular. Usei Euclides Estendido.
// Também mostra uma tabelinha com os passos pra ficar mais fácil de entender.
int64 inverso_modular_com_passos(int64 a, int64 m) {
    if (m == 1) return 0;

    int64 m0 = m, a0 = a;
    int64 x0 = 1, x1 = 0;
    
    cout << "  [Inverso Modular] Calculando inverso de " << a << " mod " << m << " com Euclides Estendido:\n";
    cout << "  [Inv. Mod.] q\ta\tm\tr\tx0\tx1\n";
    cout << "  [Inv. Mod.] ----------------------------------------\n";
    
    while (a > 1) {
        int64 q = a / m;
        int64 r = a % m;
        
        cout << "  [Inv. Mod.] " << q << "\t" << a << "\t" << m << "\t" << r << "\t" << x0 << "\t" << x1 << "\n";

        // A troca de variáveis clássica do algoritmo
        int64 temp_m = m;
        m = r;
        a = temp_m;
        
        int64 temp_x = x1;
        x1 = x0 - q * x1;
        x0 = temp_x;
    }
    cout << "  [Inv. Mod.] " << "-" << "\t" << a << "\t" << m << "\t" << "-" << "\t" << x0 << "\t" << x1 << "\n";
    
    // Se 'a' não terminar em 1, significa que o mdc não é 1, então não tem inverso.
    if (a != 1) {
      cout << "  [Inv. Mod.] Inverso nao existe pois mdc(" << a0 << ", " << m0 << ") != 1.\n";
      return -1;
    }

    // Se o resultado for negativo, a gente ajusta somando o módulo original.
    int64 resultado = x0;
    if (resultado < 0) {
      resultado += m0;
      cout << "  [Inv. Mod.] Ajustando resultado negativo: " << x0 << " + " << m0 << " = " << resultado << "\n";
    }
    
    cout << "  [Inv. Mod.] Inverso modular encontrado: " << resultado << "\n";
    return resultado;
}


// Função pra fazer potencia modular (exponenciação por quadrados).
int64 powmod(int64 base, int64 exp, int64 mod) {
    base %= mod;
    if (base < 0) base += mod;
    int64 resultado = 1;
    while (exp > 0) {
        if (exp % 2 == 1) resultado = mulmod(resultado, base, mod); 
        base = mulmod(base, base, mod); 
        exp /= 2;
    }
    return resultado;
}

// Testando primos.
bool eh_primo(int64 n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int64 i = 3; i * i <= n; i += 2) if (n % i == 0) return false;
    return true;
}

// Método Pollard
// A função de iteração é: g(x) = x^2 + 1.
int64 pollard_rho(int64 n, vector<string>& log_passos) {
    if (n % 2 == 0) return 2;
    if (eh_primo(n)) return n;

    auto f = [&](int64 x){ return (mulmod(x, x, n) + 1) % n; };
    int64 x = 2, y = 2, d = 1;
    int iter = 0;
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        int64 diff = llabs(x - y);
        
        // Montando a string pra mostrar o log depois
        ostringstream oss;
        oss << "  Iteracao " << ++iter << ": x=" << x << ", y=" << y << ", |x-y|=" << diff;
        log_passos.push_back(oss.str());

        // A cada passo, calcula o mdc para achar o fator.
        d = mdc_com_passos(diff, n);
        log_passos.back() += ", mdc=" + to_string(d);
        
        // Se d=n, o método falhou com essa semente.
        if (d == n) break; 
    }
    if (d == n || d == 1) return -1; // Não achou um fator
    return d; // Achou um fator
}

// --- FUNCOES DE CODIFICACAO E DECODIFICACAO ---

// Transforma a mensagem em números. A=11, B=12. Espaço vira 00.
string pre_codificar(const string &msg) {
    string out;
    for (char ch : msg) {
        char c = toupper((unsigned char)ch);
        if (c == ' ') {
            out += "00";
        } else if (c >= 'A' && c <= 'Z') {
            out += to_string(11 + (c - 'A'));
        } else {
        
            out += "00";
        }
    }
    return out;
}

// Faz o caminho inverso: pega os números e transforma em letra de novo.
string decodificar_precodificado(const string &s) {
    string out;
    for (size_t i = 0; i + 1 < s.size(); i += 2) {
        int v = stoi(s.substr(i, 2));
        if (v == 0) {
            out.push_back(' ');
        } else if (v >= 11 && v <= 36) {
            out.push_back(char('A' + (v - 11)));
        } else {
            out.push_back('?'); 
        }
    }
    return out;
}

// Essa função é a cabeça do RSA. Ela decide qual teorema usar pra diminuir
// o expoente e depois faz a conta de potencia.
int64 aplicar_reducao_e_modexp(int64 M, int64 e, int64 n, int64 z, vector<string>& logs) {
    int64 exp_reduzido = e;
    
     if (eh_primo(n)) {
        logs.push_back("  [Decisao] n=" + to_string(n) + " eh PRIMO. Aplicando Pequeno Teorema de Fermat.");
        logs.push_back("  Por Fermat: a^(p-1) ≡ 1 (mod p), entao reduzimos o expoente mod (n-1)");
        exp_reduzido = e % (n - 1);
        if (exp_reduzido == 0 && e > 0) exp_reduzido = n - 1;
        logs.push_back("  Expoente reduzido: " + to_string(e) + " mod " + to_string(n-1) + " = " + to_string(exp_reduzido));
    }
    // Usando Euler

    if (mdc_com_passos(M, n) == 1) {
        logs.push_back("  (Decisao) mdc(M,n) = 1. Vou usar o Teorema de Euler.");
        exp_reduzido = e % z;
        logs.push_back("  Expoente reduzido: " + to_string(e) + " mod " + to_string(z) + " = " + to_string(exp_reduzido));
    } else {
        logs.push_back("  (Decisao) mdc(M,n) != 1. Nao posso usar Euler. Vou pela Divisao Euclidiana (calculo direto).");
    }
    
    logs.push_back("  Calculando " + to_string(M) + "^" + to_string(exp_reduzido) + " mod " + to_string(n) + "...");
    return powmod(M, exp_reduzido, n);
}

vector<int64> blocos_de_mensagem(const string &precod) {
    vector<int64> blocos;
    for (size_t i = 0; i + 1 < precod.size(); i += 2) {
        blocos.push_back(stoll(precod.substr(i, 2)));
    }
    return blocos;
}


// -------------------- PROGRAMA PRINCIPAL --------------------
int main() {
    // ETAPA 1: Começar fatorando os números.
    cout << "====== ETAPA 1: FATORACAO COM METODO p DE POLLARD ======\n";
    int64 N1, N2;
    cout << "Digite N1 (numero composto, 3 ou 4 digitos): ";
    cin >> N1;
    cout << "Digite N2 (numero composto, 3 ou 4 digitos): ";
    cin >> N2;

    if (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999) {
        cout << "Os numeros precisam estar entre 100 e 9999.\n";
        return 1;
    }

    // Agora a gente chama o Pollard pra N1
    cout << "\n--- Fatorando N1 = " << N1 << " (g(x)=x^2+1, semente x0=2) ---\n";
    vector<string> logN1;
    int64 p = pollard_rho(N1, logN1);
    for (const auto &s : logN1) cout << s << "\n";
    if (p == -1) { cout << "Nao consegui fatorar o N1, tente outro numero.\n"; return 1; }
    
    // depois para o N2.
    cout << "\n--- Fatorando N2 = " << N2 << " (g(x)=x^2+1, semente x0=2) ---\n";
    vector<string> logN2;
    int64 q = pollard_rho(N2, logN2);
    for (const auto &s : logN2) cout << s << "\n";
    if (q == -1) { cout << "Nao consegui fatorar o N2, tente outro numero.\n"; return 1; }

    cout << "\n[RESULTADO ETAPA 1] Primos definidos: p = " << p << " (de N1), q = " << q << " (de N2).\n";

    // ETAPA 2: Achamos os primos p e q. Agora é só montar as chaves.
    cout << "\n====== ETAPA 2: GERACAO DAS CHAVES RSA ======\n";
    int64 n = p * q;
    int64 z = (p - 1) * (q - 1); // z é o totiente
    cout << "Calculo do modulo: n = p * q = " << n << "\n";
    cout << "Calculo do Totiente de Euler: z(n) = (p-1)*(q-1) = " << z << "\n";

    // Agora achar o 'e'. Pega o primeiro que for coprimo com z.
    int64 e = 2;
    while (mdc_com_passos(e, z) != 1) {
        e++;
    }
    cout << "Expoente publico escolhido (menor E > 1 tal que mdc(E,z)=1): e = " << e << "\n";

    // 'd' é o inverso de 'e' mod z. Aqui que entra o Euclides Estendido.
    int64 d = inverso_modular_com_passos(e, z);
    if (d == -1) { cout << "Erro bizarro, nao achei o inverso modular.\n"; return 1; }
    cout << "Expoente privado calculado: d = " << d << "\n";

    cout << "\n[RESULTADO ETAPA 2]\n";
    cout << "Chave Publica: (n=" << n << ", e=" << e << ")\n";
    cout << "Chave Privada: (n=" << n << ", d=" << d << ")\n";

    // ETAPA 3: Cifrar e decifrar a mensagem.
    cout << "\n====== ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA ======\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Digite a mensagem a ser cifrada:\n> ";
    string mensagem;
    getline(cin, mensagem);

    // Transformar as letras em números.
    string precod = pre_codificar(mensagem);
    cout << "\n1) Pre-codificacao:\n";
    cout << "   Mensagem original: \"" << mensagem << "\"\n";
    cout << "   Representacao numerica: " << precod << "\n";

    vector<int64> blocos = blocos_de_mensagem(precod);
    
    // Criptografando bloco por bloco
    cout << "\n2) Processo de Criptografia (C = M^e mod n):\n";
    vector<int64> cifrados;
    for (int64 M : blocos) {
        cout << "\n-- Cifrando bloco M = " << M << " --\n";
        vector<string> logs;
        cifrados.push_back(aplicar_reducao_e_modexp(M, e, n, z, logs));
        for (const auto &l : logs) cout << l << "\n";
        cout << "   Resultado: C = " << cifrados.back() << "\n";
    }
    
    cout << "\n   Mensagem cifrada (blocos): ";
    for (auto c : cifrados) cout << c << " ";
    cout << "\n";
    
    // Decifrar tudo.
    cout << "\n3) Processo de Descriptografia (M = C^d mod n):\n";
    vector<int64> decifrados;
    for (int64 C : cifrados) {
        cout << "\n-- Decifrando bloco C = " << C << " --\n";
        vector<string> logs;
        decifrados.push_back(aplicar_reducao_e_modexp(C, d, n, z, logs));
        for (const auto &l : logs) cout << l << "\n";
        cout << "   Resultado: M = " << decifrados.back() << "\n";
    }

    // Junta os pedaços e transforma de volta pra texto.

    ostringstream rec_precod_stream;
    for (auto mval : decifrados) {
        rec_precod_stream << setfill('0') << setw(2) << mval;
    }
    string mensagem_recuperada = decodificar_precodificado(rec_precod_stream.str());
    cout << "\n4) Reconversao para texto:\n";
    cout << "   Mensagem recuperada: \"" << mensagem_recuperada << "\"\n";

    // Conferindo se deu tudo certo no final.
    cout << "\n====== CONFIRMACAO FINAL ======\n";
    string original_upper;
    transform(mensagem.begin(), mensagem.end(), back_inserter(original_upper), ::toupper);
    if (mensagem_recuperada.rfind(original_upper, 0) == 0) {
      cout << "SUCESSO: A mensagem decifrada e identica a original.\n";
    } else {
      cout << "FALHA: A mensagem decifrada NAO corresponde a original.\n";
    }

    return 0;
}