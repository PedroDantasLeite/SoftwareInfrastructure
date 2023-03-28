# SW-Atividade-6
Programa que utiliza várias threads para o calculo e o descarte de valores.

## Installation
```
$ git clone https://github.com/PedroDantasLeite/SW-Atividade-6.git
```

## Usage
```bash
$ make #Compilar o código
$ make run #Executa o programa
$ make clean #Limpar
```

O programa recebe 4 valores, sendo eles "P C N B". Eles significam: o número de produtores (P), o número de
consumidores (C), um limite N (os valores não passarão desse limite, vão voltar ao valor 0), e B que representa o tamanho do buffer,

Exemplo:
```bash
3 2 1 4
```
Seu output seguira este padrão:

Produtor Y produzindo Z na posição H

Consumidor I consumindo J da posição H

Exemplo:
```bash
Produtor 0 produzindo 1 na posição 0
Produtor 2 produzindo 1 na posição 1
Consumidor 1 consumindo 1 da posição 0
Produtor 0 produzindo 3 na posição 2
Consumidor 0 consumindo 1 da posição 1
Produtor 1 produzindo 1 na posição 3
Consumidor 0 consumindo 3 da posição 2
Consumidor 0 consumindo 1 da posição 3
```


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT]
(https://choosealicense.com/licenses/mit/)
