# MVC19
**M**ódulo **V**oltímetro **C**an 2019

Embarcação Guarapuvu II

Equipe Zênite Solar


###  Sobre

Este módulo é responsável por exibir os principais parâmetros do sistema para o piloto em um display OLED de 0,96" (SSD1306).

![3DDOWN](hardware/IMG/3DDOWN.png?raw=true)

![3DDOWN](hardware/IMG/3DUP.png?raw=true)


#### Requisitos e Abordagens
1. Adquirir os parâmetros relevantes da rede CAN

2. Filtragem dos dados
	- Utilizar o ID de cada módulo desejado
	- Conferir se o módulo está enviando informações corretamente, sinalizando em caso de falhas.

3. Formatação para exibição no display
	- Separar os dados conforme display conectado
	
	- Utilização de fonte visível para o piloto
	
	- Criação de layout que facilite leitura rápida dos dados
	
	  


## Informações exibidas nos displays

------


#### Display 1

​	Informações de Tensão em cada uma das 3 baterias principais.

​	

#### Display 2

​	Corrente de entrada e saída do sistema.

​	RPM do motor.
