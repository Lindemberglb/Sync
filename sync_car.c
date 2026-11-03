#include "sync_car.h"

void station_init(struct station *station) {
    pthread_mutex_init(&station->mutex, NULL);

    pthread_cond_init(&station->passageiros, NULL);
    pthread_cond_init(&station->embarque, NULL);

    station->passageiros_esperando = 0;
    station->assentos_disponiveis = 0;
    station->passageiros_embarcando = 0;
    station->carro_na_estacao = 0;
}

void station_load_car(struct station *station, int count) {
    pthread_mutex_lock(&station->mutex);

    if (count <= 0) {
        pthread_mutex_unlock(&station->mutex);
        return;
    }

    station->carro_na_estacao = 1;
    station->assentos_disponiveis = count;

    pthread_cond_broadcast(&station->passageiros);

    while (station->passageiros_embarcando > 0 ||
           (station->assentos_disponiveis > 0 &&
            station->passageiros_esperando > 0)) {

        pthread_cond_wait(&station->embarque, &station->mutex);
    }

    station->carro_na_estacao = 0;
    station->assentos_disponiveis = 0;

    pthread_mutex_unlock(&station->mutex);
}

void station_wait_for_car(struct station *station) {
    pthread_mutex_lock(&station->mutex);

    station->passageiros_esperando++;

    while (station->carro_na_estacao == 0 ||
           station->assentos_disponiveis <= 0) {

        pthread_cond_wait(&station->passageiros, &station->mutex);
    }

    station->passageiros_esperando--;
    station->assentos_disponiveis--;
    station->passageiros_embarcando++;

    pthread_mutex_unlock(&station->mutex);
}

void station_on_board(struct station *station) {
    pthread_mutex_lock(&station->mutex);

    station->passageiros_embarcando--;

    if (station->passageiros_embarcando == 0 &&
        (station->passageiros_esperando == 0 ||
         station->assentos_disponiveis == 0)) {

        pthread_cond_signal(&station->embarque);
    }

    pthread_mutex_unlock(&station->mutex);
}