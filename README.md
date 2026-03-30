# TP1-SO
Atividade TP1

Descrição

Este programa em C cria múltiplas threads utilizando a biblioteca pthreads. Cada thread conta de 0 até 99 e imprime seus valores na tela. As threads competem entre si, e a vencedora é aquela que realiza a 100ª impressão total.

Objetivo

Demonstrar o uso de threads, sincronização e controle de concorrência em C.


Conceitos Utilizados

Threads (pthread)
Mutex (pthread_mutex_t)
Barreira (pthread_barrier_t)
Sincronização de processos


Funcionamento

O usuário informa a quantidade de threads.
Todas as threads aguardam em uma barreira para iniciar juntas.
Cada thread executa um loop de 0 a 99.
Um contador global controla o número total de impressões.
Quando o total chega a 100, o programa identifica a thread vencedora.
As demais threads são encerradas.


Compilar

gcc tp1.c -o programa -lpthread
