#include "FreeRTOS.h"         // Biblioteca principal do FreeRTOS
#include "task.h"             // Manipulação de tarefas do FreeRTOS
#include <stdio.h>            
#include "pico/stdlib.h"     

// Definição dos pinos conectados aos canais do LED RGB
#define LED_VERDE    11
#define LED_VERMELHO 13

// Função da tarefa que simula o funcionamento de um semáforo
void semaforo_task(void *params) {
    // Inicializa os pinos dos LEDs
    gpio_init(LED_VERDE);
    gpio_init(LED_VERMELHO);

    // Define os pinos como saída
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    // Loop infinito do semáforo
    while (true) {
        // 🔴 Ativa o LED vermelho por 5 segundos
        gpio_put(LED_VERDE, 0);     // Garante que o verde esteja desligado
        gpio_put(LED_VERMELHO, 1);  // Vermelho ligado

        for (int i = 5; i > 0; i--) {
            printf("VERMELHO - %d segundos\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));  // Espera 1 segundo
        }

        // 🟢 Ativa o LED verde por 5 segundos
        gpio_put(LED_VERDE, 1);     // Verde ligado
        gpio_put(LED_VERMELHO, 0);  // Vermelho desligado

        for (int i = 5; i > 0; i--) {
            printf("VERDE - %d segundos\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));  // Espera 1 segundo
        }

        // 🟡 Simula o LED amarelo por 3 segundos 
        gpio_put(LED_VERDE, 1);     // Verde ligado
        gpio_put(LED_VERMELHO, 1);  // Vermelho ligado (forma o amarelo)

        for (int i = 3; i > 0; i--) {
            printf("AMARELO - %d segundos\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));  // Espera 1 segundo
        }
    }
}

int main() {
    stdio_init_all();           // Inicializa UART/USB para printf funcionar
    sleep_ms(3000);             // Aguarda 3 segundos 
    printf("Inicializando semáforo...\n");

    // Cria a tarefa do semáforo com prioridade 1
    xTaskCreate(semaforo_task, "SemaforoTask", 256, NULL, 1, NULL);

    // Inicia o agendador do FreeRTOS (executa as tarefas)
    vTaskStartScheduler();

    // Loop de segurança (não será executado se o scheduler estiver rodando)
    while (true) {}
}
