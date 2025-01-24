# Pista de Skate Interativa com OpenGL

## Descrição
Este projeto é uma pista de skate interativa desenvolvida em **C++** com **OpenGL** utilizando a biblioteca GLUT.

## Tecnologias
- **C++**
- **OpenGL**
- **GLUT**

## Como Usar
- **Seta para cima**: O skate acelera para a extremidade direita.
- **Seta para baixo**: O skate acelera para a extremidade esquerda.
- **Seta para esquerda**: Inclina e acelera para a esquerda.
- **Seta para direita**: Inclina e acelera para a direita.

## Pré-requisitos
Certifique-se de ter as bibliotecas necessárias instaladas no seu sistema. No Linux, você pode instalá-las com os comandos abaixo:

```bash
sudo apt update
sudo apt install -y freeglut3 freeglut3-dev libglew-dev libglm-dev build-essential
```
## Compilação e Execução
Para compilar o projeto, utilize o seguinte comando:

```bash
g++ -o skate main.cpp -lGL -lGLU -lglut
```

Para executar o projeto, utilize o comando:
```bash
./skate
```