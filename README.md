# Questão de Código - Prova 2 (MD2)

**Feito por:** Arthur Palhares Ferreira Silva
**Matrícula:** 232000688



# Questão de Código - Prova 2 (MD2)

**Feito por:** Arthur Palhares Ferreira Silva
**Matrícula:** 232000688

---

### Objetivo

Implementação de códigos em C++ para a disciplina de Matemática Discreta II, com o propósito de aplicar na prática os conceitos teóricos estudados em aula. O projeto aborda a resolução de quatro questões distintas, focando nos seguintes algoritmos e teorias:

* [cite_start]A construção de um sistema de criptografia **RSA** completo, que envolve a fatoração de números com o **método p de Pollard**, a geração de chaves com os **algoritmos de Euclides** (padrão e estendido) e a aplicação dos **teoremas de Fermat e Euler** para otimizar a exponenciação modular[cite: 20, 21].

* [cite_start]O cálculo do **Mínimo Múltiplo Comum (MMC)** como solução para o problema de sincronização de eventos periódicos ("Chaves Periódicas")[cite: 85, 97].

* [cite_start]A análise de propriedades de um número N através do cálculo das funções **τ(N)** (número de divisores) e **σ(N)** (soma dos divisores), a partir de sua fatoração prima[cite: 104, 105, 112].

* [cite_start]A finalização e análise de um código que realiza operações de **divisão e exponenciação modular**, demonstrando o entendimento prático desses algoritmos[cite: 130].

[cite_start]Um requisito central em todas as implementações é a exibição de um passo a passo detalhado dos cálculos, garantindo a clareza do processo de resolução[cite: 295, 296].### Objetivo

Implementação de

---

### 📝 Conteúdo da Atividade

* **Questão 1:** Implementar RSA, fatorando com método p de Pollard, sem uso de long long.
* **Questão 2:** Calcular o MMC de todos os ciclos e verificar se o resultado está dentro do limite de 50 anos.
* **Questão 3:** Calcular a Razão de Eficiência de N e imprimir o resultado com duas casas decimais de precisão.
* **Questão 4 (Bônus):** Implementar cálculo modular com inverso e exponenciação.

---

### ✔️ Respostas da Questão 4 (Verdadeiro ou Falso)

* **(V)** O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
* **(F)** Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
* **(V)** A operação (H * inverso) % Zn representa a divisão modular de H por G.
* **(V)** Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod nl.
* **(F)** A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.
* **(V)** Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
* **(V)** O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando nl não é primo.

