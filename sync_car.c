#include "sync_car.h"

void station_init(struct station *station){
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->passageiros, NULL);
    pthread_cond_init(&station->embarque, NULL);
    station->passageiros_esperando = 0;
    station->assentos_disponiveis = 0;
    station->passageiros_autorizados = 0;
    station->passageiros_embarcados = 0;
    station->carro_na_estacao = 0;
    station->passageiros_esperados_embarque = 0;
    station->proximo_ticket = 0;
    station->limite_ticket = 0;
}

void station_load_car(struct station *station, int count){
    pthread_mutex_lock(&station->mutex);

    if (count <= 0 || station->passageiros_esperando == 0) {
        pthread_mutex_unlock(&station->mutex);
        return;
    }

    int passageiros_esperados;

    if (station->passageiros_esperando < count) {
        passageiros_esperados = station->passageiros_esperando;
    } else {
        passageiros_esperados = count;
    }

    station->carro_na_estacao = 1;
    station->assentos_disponiveis = count;
    station->passageiros_autorizados = passageiros_esperados;
    station->passageiros_esperados_embarque = passageiros_esperados;
    station->passageiros_embarcados = 0;

    station->limite_ticket = station->proximo_ticket;

    pthread_cond_broadcast(&station->passageiros);

    while (station->passageiros_embarcados <
           station->passageiros_esperados_embarque) {
        pthread_cond_wait(&station->embarque, &station->mutex);
    }

    station->carro_na_estacao = 0;
    station->assentos_disponiveis = 0;
    station->passageiros_autorizados = 0;
    station->passageiros_esperados_embarque = 0;

    pthread_mutex_unlock(&station->mutex);
}

void station_wait_for_car(struct station *station){
    pthread_mutex_lock(&station->mutex);

    int meu_ticket = station->proximo_ticket;

    station->proximo_ticket++;
    station->passageiros_esperando++;

    while (station->carro_na_estacao == 0 ||
           meu_ticket >= station->limite_ticket ||
           station->passageiros_autorizados <= 0 ||
           station->assentos_disponiveis <= 0) {

        pthread_cond_wait(&station->passageiros, &station->mutex);
    }

    station->passageiros_esperando--;
    station->passageiros_autorizados--;
    station->assentos_disponiveis--;

    pthread_mutex_unlock(&station->mutex);
}

void station_on_board(struct station *station){
    pthread_mutex_lock(&station->mutex);

    station->passageiros_embarcados++;

    if (station->passageiros_embarcados >=
        station->passageiros_esperados_embarque) {

        pthread_cond_signal(&station->embarque);
    }

    pthread_mutex_unlock(&station->mutex);
    
}