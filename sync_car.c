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
}

void station_load_car(struct station *station, int count){
    (void) station;
    (void) count;
}

void station_wait_for_car(struct station *station){
    (void) station;
}

void station_on_board(struct station *station){
    (void) station;
}