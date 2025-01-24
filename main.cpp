#include <GL/glut.h>
#include <cmath>

float skatista_x = 0.0f;
float skatista_y = 0.0f;
float velocidade = 0.0f;
float inclinacao = 0.0f;
const float gravidade = 0.002f;
const float atrito = 0.99f;
const float rampa_altura = 0.5f;
const float rampa_largura = 1.0f;
const float skatista_tamanho = 0.1f;
const float MAX_VELOCIDADE = 0.05f;
const float ACELERACAO = 0.003f;

float alturaRampa(float x) {
    return -rampa_altura + (x * x);
}

void desenhaCirculo(float cx, float cy, float raio) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angulo = i * M_PI / 180.0f;
        glVertex2f(cx + cos(angulo) * raio, cy + sin(angulo) * raio);
    }
    glEnd();
}

void desenhaSkate(float x, float y, float largura, float altura, float angulo) {
    glPushMatrix();
    glTranslatef(x, y + altura / 2, 0.0f);
    glRotatef(angulo, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-largura / 2, -altura / 2);
    glVertex2f(largura / 2, -altura / 2);
    glVertex2f(largura / 2, altura / 2);
    glVertex2f(-largura / 2, altura / 2);
    glEnd();

    desenhaCirculo(-largura / 3, -altura / 1.5, altura / 2.5);
    desenhaCirculo(largura / 3, -altura / 1.5, altura / 2.5);

    glPopMatrix();
}

void desenhaRampa() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (float x = -rampa_largura; x <= rampa_largura; x += 0.01f) {
        float y = alturaRampa(x);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaRampa();

    desenhaSkate(skatista_x, skatista_y, skatista_tamanho * 2.5, skatista_tamanho / 2.5, inclinacao);

    glutSwapBuffers();
}

void atualiza(int valor) {
    skatista_x += velocidade;

    skatista_y = alturaRampa(skatista_x) + skatista_tamanho * 0.4f;

    inclinacao = atan(2 * skatista_x) * 180.0f / M_PI;

    if (skatista_x != 0) {
        velocidade -= gravidade * skatista_x / fabs(skatista_x);
    }

    velocidade *= atrito;

    if (velocidade > MAX_VELOCIDADE) {
        velocidade = MAX_VELOCIDADE;
    } else if (velocidade < -MAX_VELOCIDADE) {
        velocidade = -MAX_VELOCIDADE;
    }

    if (skatista_x <= -rampa_largura || skatista_x >= rampa_largura) {
        skatista_x = (skatista_x < 0 ? -rampa_largura : rampa_largura);
        velocidade = -velocidade * 0.5f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, atualiza, 0);
}

void tecladoEspecial(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_LEFT:
            if (skatista_x > -rampa_largura) {
                velocidade -= ACELERACAO;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (skatista_x < rampa_largura) {
                velocidade += ACELERACAO;
            }
            break;
        case GLUT_KEY_UP:
            skatista_x = rampa_largura;
            velocidade = 0.0f;
            break;
        case GLUT_KEY_DOWN:
            skatista_x = -rampa_largura;
            velocidade = 0.0f;
            break;
    }
}

void inicializa() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Skate By Luiz Gusttavo");

    inicializa();
    glutDisplayFunc(display);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(16, atualiza, 0);

    glutMainLoop();
    return 0;
}