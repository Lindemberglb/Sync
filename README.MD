# Sincronização do Metrô

Implementação de um sistema de sincronização de passageiros e carros utilizando threads (`pthreads`) em C.

## Arquivos do projeto

- **`sync_car.c`**: contém a implementação das funções de sincronização, responsáveis por controlar a chegada do carro, a espera dos passageiros e a confirmação do embarque.
- **`sync_car-runner.c`**: arquivo de testes fornecido na atividade, responsável por executar os testes e verificar o funcionamento da implementação.
- **`sync_car.h`**: define a struct `station` e declara as funções utilizadas no projeto.
- **`Makefile`**: contém as instruções necessárias para compilar o programa.
- **`.gitignore`**: especifica os arquivos que não devem ser enviados ao Git.

## Sistema operacional

O projeto foi implementado em **Linux, utilizando o WSL2 no Windows 11**.

## Como compilar

No terminal, acesse a pasta do projeto e execute:

```bash
make
```

O comando compila os arquivos necessários e gera o executável `sync_car`.

## Como executar e testar

Após a compilação, execute:

```bash
./sync_car
```

O programa executará os testes fornecidos pelo professor e apresentará os resultados no terminal.

Se a implementação estiver funcionando corretamente, será exibida a mensagem:

```text
Looks good!
```

## Limpar os arquivos gerados

Para remover o executável após os testes, execute:

```bash
make clean
```