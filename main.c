#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// --- Funcoes de simulacao de estagios ---
long long buscaInstrucao(int instrucao) {
    volatile long long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum++;
    }
    return sum;
}

long long decodificaInstrucao(int instrucao) {
    volatile long long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum++;
    }
    return sum;
}

long long executaInstrucao(int instrucao) {
    volatile long long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum++;
    }
    return sum;
}

long long escreveResultado(int instrucao) {
    volatile long long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum++;
    }
    return sum;
}


// --- Algoritmo Sem Pipeline ---
void processaSemPipeline(int numInstrucoes) {
    long long total = 0;
    for (int i = 1; i <= numInstrucoes; i++) {
        total += buscaInstrucao(i);
        total += decodificaInstrucao(i);
        total += executaInstrucao(i);
        total += escreveResultado(i);
    }
}


// --- Algoritmo com Simulacao de Pipeline ---
void processaComPipeline(int numInstrucoes) {
    long long total = 0;
    int instrucoesConcluidas = 0;
    int instrucaoAtual = 1;
    long long estagio1 = 0, estagio2 = 0, estagio3 = 0, estagio4 = 0;

    while (instrucoesConcluidas < numInstrucoes) {
        if (estagio4 > 0) {
            total += estagio4;
            instrucoesConcluidas++;
        }
        
        if (estagio3 > 0) {
            total += estagio3;
        }
        estagio4 = estagio3;

        if (estagio2 > 0) {
            total += estagio2;
        }
        estagio3 = estagio2;

        if (estagio1 > 0) {
            total += estagio1;
        }
        estagio2 = estagio1;

        if (instrucaoAtual <= numInstrucoes) {
            estagio1 = buscaInstrucao(instrucaoAtual);
            instrucaoAtual++;
        } else {
            estagio1 = 0;
        }
    }
}


// --- Funcao Principal (main) com medicao de tempo em milissegundos ---
int main() {
    int numInstrucoes = 20; 
    struct timeval inicio, fim;
    long long tempo_sem_pipeline_micros, tempo_com_pipeline_micros;
    double tempo_sem_pipeline_millis, tempo_com_pipeline_millis, diferenca_millis;

    // --- Processamento Sem Pipeline e medicao de tempo ---
    gettimeofday(&inicio, NULL);
    processaSemPipeline(numInstrucoes);
    gettimeofday(&fim, NULL);
    tempo_sem_pipeline_micros = (long long)(fim.tv_sec - inicio.tv_sec) * 1000000LL + (fim.tv_usec - inicio.tv_usec);
    tempo_sem_pipeline_millis = tempo_sem_pipeline_micros / 1000.0;

    // --- Processamento Com Pipeline e medicao de tempo ---
    gettimeofday(&inicio, NULL);
    processaComPipeline(numInstrucoes);
    gettimeofday(&fim, NULL);
    tempo_com_pipeline_micros = (long long)(fim.tv_sec - inicio.tv_sec) * 1000000LL + (fim.tv_usec - inicio.tv_usec);
    tempo_com_pipeline_millis = tempo_com_pipeline_micros / 1000.0;

    // --- Impressao dos resultados em milissegundos ---
    printf("==================================\n");
    printf("Resumo da Execucao (em milissegundos)\n");
    printf("==================================\n");
    printf("Tempo total (sem pipeline): %.2f ms\n", tempo_sem_pipeline_millis);
    printf("Tempo total (com pipeline): %.2f ms\n", tempo_com_pipeline_millis);
    diferenca_millis = tempo_sem_pipeline_millis - tempo_com_pipeline_millis;
    printf("Diferenca: %.2f ms\n", diferenca_millis);
    printf("==================================\n");
    
    return 0;
}