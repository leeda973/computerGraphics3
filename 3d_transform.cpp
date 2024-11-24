#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

float ball_y = 0.8f;       // ���� Y ��ġ
float velocity = 0.0f;     // ���� �ӵ�
float gravity = -0.001f;   // �߷� ���ӵ�
float elasticity = 0.7f;   // ź�� ���
float scale_x = 1.0f;      // ���� X ���� ������
float scale_y = 1.0f;      // ���� Y ���� ������
bool is_wireframe = false; // ���̾������� ��� ����
bool is_reset = false;     // ���� �ٽ� �����ϴ��� ����

void TimerFunction(int value) {
    if (!is_reset) {
        velocity += gravity;
        ball_y += velocity;

        if (ball_y < -0.8f) {
            ball_y = -0.8f;
            velocity = -velocity * elasticity;

            scale_x = 1.2f;
            scale_y = 0.8f;
        }
        else {
            scale_x = fmax(1.0f, scale_x - 0.01f);
            scale_y = fmin(1.0f, scale_y + 0.01f);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, TimerFunction, 0);
}

void KeyboardHandler(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        is_wireframe = true;
        break;
    case 's':
        is_wireframe = false;
        break;
    case 'j': // �߷� ����
        gravity -= 0.0005f;
        break;
    case 'k':  // �߷� ����
        gravity += 0.0005f;
        break;
    case 'f': // ���� �ʱ�ȭ
        ball_y = 0.8f;
        velocity = 0.0f;
        scale_x = 1.0f;
        scale_y = 1.0f;
        is_reset = false;
        break;
    }
    glutPostRedisplay();
}

void DrawScene() {
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(2.0f, 0.1f, 1.0f);
    if (is_wireframe) {
        glutWireCube(1.0);
    }
    else {
        glutSolidCube(1.0);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, ball_y, 0.0f);
    glScalef(scale_x, scale_y, 1.0f);
    if (is_wireframe) {
        glutWireSphere(0.2, 20, 20);
    }
    else {
        glutSolidSphere(0.2, 20, 20);
    }
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawScene();
    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Elastic Ball Animation");
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.4, 0.4, 0.4, 1.0);

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(KeyboardHandler);
    glutTimerFunc(16, TimerFunction, 0);

    glutMainLoop();
    return 0;
}
