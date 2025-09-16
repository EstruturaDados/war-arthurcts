// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

// int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

//    return 0;
// }

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Constantes Globais
#define NUM_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20
#define NUM_MISSOES 2

// Estrutura de Dados
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Protótipos das Funções
Territorio* alocarMapa();
void inicializarTerritorios(Territorio* mapa);
void liberarMemoria(Territorio* mapa);
void exibirMenuPrincipal();
void exibirMapa(const Territorio* mapa);
void exibirMissao(int missaoId);
void faseDeAtaque(Territorio* mapa);
void simularAtaque(Territorio* atacante, Territorio* defensor);
int sortearMissao();
int verificarVitoria(const Territorio* mapa, int missaoId, const char* minhaCor);
void limparBufferEntrada();

// Função Principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    
    Territorio* mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa!\n");
        return 1;
    }
    
    inicializarTerritorios(mapa);
    char minhaCor[] = "Azul";
    int missaoId = sortearMissao();
    int opcao;
    int vitoria = 0;
    
    do {
        system("cls || clear");
        printf("=== GUERRA ESTRATÉGICA ===\n");
        printf("Seu exército: %s\n", minhaCor);
        exibirMapa(mapa);
        exibirMissao(missaoId);
        exibirMenuPrincipal();
        
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        
        switch(opcao) {
            case 1:
                faseDeAtaque(mapa);
                break;
            case 2:
                vitoria = verificarVitoria(mapa, missaoId, minhaCor);
                if (vitoria) {
                    printf("\n🎉 PARABÉNS! Você cumpriu sua missão e venceu a guerra!\n");
                } else {
                    printf("\n⚠️  Você ainda não cumpriu sua missão. Continue lutando!\n");
                }
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while (opcao != 0 && !vitoria);
    
    liberarMemoria(mapa);
    return 0;
}

// Implementação das Funções
Territorio* alocarMapa() {
    return (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* mapa) {
    printf("=== CADASTRO DE TERRITÓRIOS ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        
        printf("Nome: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o \n
        
        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // Remove o \n
        
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

void exibirMenuPrincipal() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
}

void exibirMapa(const Territorio* mapa) {
    printf("\n=== MAPA ATUAL ===\n");
    printf("%-20s | %-15s | %s\n", "Território", "Cor", "Tropas");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%-20s | %-15s | %d\n", 
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int missaoId) {
    printf("\n=== SUA MISSÃO ===\n");
    switch(missaoId) {
        case 0:
            printf("Destruir completamente o exército Verde!\n");
            break;
        case 1:
            printf("Conquistar pelo menos 3 territórios!\n");
            break;
        default:
            printf("Missão desconhecida!\n");
            break;
    }
}

void faseDeAtaque(Territorio* mapa) {
    int atacanteIdx, defensorIdx;
    
    printf("\n=== FASE DE ATAQUE ===\n");
    printf("Escolha o território ATACANTE (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacanteIdx);
    atacanteIdx--; // Ajusta para índice 0-based
    
    printf("Escolha o território DEFENSOR (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensorIdx);
    defensorIdx--; // Ajusta para índice 0-based
    
    if (atacanteIdx < 0 || atacanteIdx >= NUM_TERRITORIOS || 
        defensorIdx < 0 || defensorIdx >= NUM_TERRITORIOS) {
        printf("Índices inválidos!\n");
        return;
    }
    
    if (atacanteIdx == defensorIdx) {
        printf("Não é possível atacar o próprio território!\n");
        return;
    }
    
    simularAtaque(&mapa[atacanteIdx], &mapa[defensorIdx]);
}

void simularAtaque(Territorio* atacante, Territorio* defensor) {
    printf("\n=== SIMULAÇÃO DE ATAQUE ===\n");
    printf("%s (%s) ataca %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    // Simula dados de ataque (1-6) e defesa (1-6)
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;
    
    printf("Dado de ataque: %d\n", dadoAtaque);
    printf("Dado de defesa: %d\n", dadoDefesa);
    
    if (dadoAtaque >= dadoDefesa) {
        printf("✅ Ataque bem-sucedido! O defensor perde 1 tropa.\n");
        defensor->tropas--;
        
        if (defensor->tropas <= 0) {
            printf("🎯 %s foi conquistado!\n", defensor->nome);
            // Move uma tropa do atacante para o defensor
            atacante->tropas--;
            defensor->tropas = 1;
            // O conquistador assume o controle
            strcpy(defensor->cor, atacante->cor);
        }
    } else {
        printf("❌ Ataque fracassado! O atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

int sortearMissao() {
    return rand() % NUM_MISSOES;
}

int verificarVitoria(const Territorio* mapa, int missaoId, const char* minhaCor) {
    switch(missaoId) {
        case 0: // Destruir exército Verde
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                    return 0; // Ainda há tropas verdes
                }
            }
            return 1; // Todas as tropas verdes foram eliminadas
            
        case 1: // Conquistar 3 territórios
            int conquistados = 0;
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, minhaCor) == 0) {
                    conquistados++;
                }
            }
            return conquistados >= 3; // Vitória se conquistou 3 ou mais
            
        default:
            return 0;
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
