// Esse projeto foi adaptado de TeaPot3D.cpp - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualização de objetos 3D.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415926535

#include <math.h>

GLint DOIS_PI = 360;
GLfloat contaVolta = 1;

GLfloat velTransMercurio;
GLfloat velTransVenus;
GLfloat velTransTerra;
GLfloat velTransMarte;
GLfloat velTransJupter;
GLfloat velTransSaturno;
GLfloat velTransUrano;
GLfloat velTransNetuno;


GLfloat velRotMercurio;
GLfloat velRotVenus;
GLfloat velRotTerra;
GLfloat velRotMarte;
GLfloat velRotJupter;
GLfloat velRotSaturno;
GLfloat velRotUrano;
GLfloat velRotNetuno;

// Vari�veis que guardam os valores dos diâmetros dos planetas
GLfloat diametroSol = 5, diametroMercurio = 0.5, diametroVenus = 0.6, diametroTerra = 0.8, diametroMarte = 0.5, diametroJupiter = 1.5, diametroSaturno = 1.4, diametroUrano = 1.3, diametroNeturno = 1.3;

// Variavel que gerencia o estado de exibir na tela ou não
GLboolean exibirSol= true, exibirSaturno = true, exibirVenus = true, exibirMercurio = true, exibirTerra = true, exibirMarte = true, exibirJupter = true, exibirUrano = true, exibirNeturno = true;

// Variavel que gerencia o estado de exibir na tela ou não as orbitas
GLboolean exibirOrb1= true, exibirOrb2 = true, exibirOrb3 = true, exibirOrb4 = true, exibirOrb5 = true, exibirOrb6 = true, exibirOrb7 = true, exibirOrb8 = true;

// Variavel que gerencia o estado de exibir a animação
GLboolean executarAnima = true;

// Variavel que gerencia o estado de exibir informações da terra
GLboolean exibirInfoTerra = true;


GLfloat angle, fAspect, rotX, rotY, a, o, z,deslocamentoZ,deslocamentoX,deslocamentoY;
GLdouble obsX, obsY, obsZ;

void desenhaOrbita(double raio)
{

    float angulo, incremento;

    glColor3f(1.0f, 1.0f, 1.0f);

    glPointSize(4.0f);

    incremento = (2 * M_PI) / 200;

    glBegin(GL_LINE_LOOP);
    for(angulo=0; angulo<2*M_PI; angulo+=incremento)
    {
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
    }
    glEnd();
}

void desenhaSatelite(double raio)
{

    float angulo, incremento;

    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(raio, 0.0f, 0.0f);
    glPointSize(4.0f);

    incremento = (2 * M_PI) / 200;

    glutSolidSphere(raio/2,10.0,10.0);

	//glutSwapBuffers();

}


void desenhaPlaneta(double raio, double color[], int qntOrbitas, int qntSatelites)
{


    float angulo, incremento;

    glColor3f(color[0], color[1], color[2]);



    glutSolidSphere(raio,50.0,50.0);

// Execução dos comandos de desenho

    //Desenha orbitas
    for(double i =1; i <= qntOrbitas; i++)
    {
        double raioOrbita = raio + (i/3);
        desenhaOrbita(raioOrbita);
    }

    //Desenha Satélites
    for(double i =1; i <= qntSatelites; i++)
    {
        glPushMatrix();
        desenhaSatelite((raio + (0.6f)) * pow(-1,i));
        glPopMatrix();
    }
    	//glutSwapBuffers();


}

void DefineIluminacao()
{
GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; // "brilho"
GLfloat posicaoLuz[4]={0.0, 0.0, 0.0, 0.0};
GLfloat posicaoLuz2[4]={a, o, z, 1.0};

// Capacidade de brilho do material
GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
GLint especMaterial = 60;
// Define a refletância do material
glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
// Define a concentração do brilho
glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
// Ativa o uso da luz ambiente
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
// Define os parâmetros da luz de número 0
glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular );
glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz2 );
}

void desenhaTerreno(){
    float L = 500.0;
    float incr = 10;
    float y = 0.5;
    for(float i = -L; i <= L; i+= incr){
        glBegin(GL_LINES);
        glVertex3f(y,i,-L);
        glVertex3f(y,i,L);

        glVertex3f(-L,i,y);
        glVertex3f(L,i,y);
        glEnd();
    }

}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela de visualização com a cor de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();

	// Troca cor corrente para azul
	glColor3f(1.0f, 1.0f, 1.0f);

	//desenhaTerreno();

    float rOrb1 = 8.0f, rOrb2 = 12.0f, rOrb3 = 16.0f, rOrb4 = 20.0f, rOrb5 = 24.0f, rOrb6 = 28.0f, rOrb7 = 32.0f, rOrb8 = 36.0f;

    if(exibirOrb1){
        desenhaOrbita(rOrb1);
    }
    if(exibirOrb2){
       desenhaOrbita(rOrb2);
    }
    if(exibirOrb3){
       desenhaOrbita(rOrb3);
    }
    if(exibirOrb4){
       desenhaOrbita(rOrb4);
    }
    if(exibirOrb5){
       desenhaOrbita(rOrb5);
    }
    if(exibirOrb6){
       desenhaOrbita(rOrb6);
    }
    if(exibirOrb7){
       desenhaOrbita(rOrb7);
    }
    if(exibirOrb8){
       desenhaOrbita(rOrb8);
    }

// Desenha Sol
    double corSol[] = {1.0f, 1.0f, 0.0f};
    int qntOrbitas = 0;
    int qntSatelites = 0;
    int posicao = 0;
    if(exibirSol){
        desenhaPlaneta(diametroSol, corSol, qntOrbitas, qntSatelites);
            //glutSwapBuffers();

    }

// Mercurio
    glPushMatrix();
    glRotated(velTransMercurio, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb1, 0.0f, 0.0f);
    glRotated(velRotMercurio, 0.0f, 0.0f, 1.0f);


    double corPlanMercurio[] = {0.929f, 0.49f, 0.192f};
   // if(exibirMercurio){
        desenhaPlaneta(diametroMercurio, corPlanMercurio, 0, 0);
            //glutSwapBuffers();

   // }

    glPopMatrix();

// Vênus
    glPushMatrix();
    glRotated(velTransVenus, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb2, 0.0f, 0.0f);
    glRotated(velRotVenus, 0.0f, 0.0f, 1.0f);


    double corPlanVenus[] = {133.0/255.0f, 60.0/255.0f, 12.0/255.0f};
    if(exibirVenus){
        desenhaPlaneta(diametroVenus, corPlanVenus, 0, 0);
            //glutSwapBuffers();

    }

    glPopMatrix();

// Terra
    glPushMatrix();
    glRotated(velTransTerra, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb3, 0.0f, 0.0f);
    glRotated(velRotTerra, 0.0f, 0.0f, 1.0f);


    double corPlanTerra[] = {0.0f, 112.0/255.0f, 192.0/255.0f};
    if(exibirTerra){
        desenhaPlaneta(diametroTerra, corPlanTerra, 0, 1);
        glPushMatrix();
        glPopMatrix();
    //glutSwapBuffers();

    }

    glPopMatrix();

// Marte
    glPushMatrix();
    glRotated(velTransMarte, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb4, 0.0f, 0.0f);
    glRotated(velRotMarte, 0.0f, 0.0f, 1.0f);


    double corPlanMarte[] = {1.0f, 0.0f, 0.0f};
    if(exibirMarte){
         desenhaPlaneta(0.5, corPlanMarte, 0, 2);
            // glutSwapBuffers();

    }

    glPopMatrix();

// Júpter
    glPushMatrix();
    glRotated(velTransJupter, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb5, 0.0f, 0.0f);
    glRotated(velRotJupter, 0.0f, 0.0f, 1.0f);


    double corPlanJupter[] = {1.0f, 192.0/255.0f, 0.0f};
    if(exibirJupter){
        desenhaPlaneta(diametroJupiter, corPlanJupter, 1, 1);
           // glutSwapBuffers();

    }

    glPopMatrix();

// Saturno
    glPushMatrix();
    glRotated(velTransSaturno, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb6, 0.0f, 0.0f);
    glRotated(velRotSaturno, 0.0f, 0.0f, 1.0f);


    double corPlanSaturno[] = {191.0/255.0f, 144.0/255.0f, 0.0f};
    if(exibirSaturno){
        desenhaPlaneta(diametroSaturno, corPlanSaturno, 4, 1);
            //glutSwapBuffers();

    }
    glPopMatrix();


// Urano
    glPushMatrix();
    glRotated(velTransUrano, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb7, 0.0f, 0.0f);
    glRotated(velRotUrano, 0.0f, 0.0f, 1.0f);


    double corPlanUrano[] = {84.0/255.0f, 130.0/255.0f, 53.0/255.0f};
    if(exibirUrano){
        desenhaPlaneta(diametroUrano, corPlanUrano, 2, 1);
            //glutSwapBuffers();

    }

    glPopMatrix();

// Netuno
    glPushMatrix();
    glRotated(velTransNetuno, 0.0f, 0.0f, 1.0f);
    glTranslated(rOrb8, 0.0f, 0.0f);
    glRotated(velRotNetuno, 0.0f, 0.0f, 1.0f);


    double corPlanNetuno[] = {180.0/255.0f, 199.0/255.0f, 231.0/255.0f};
    if(exibirNeturno){
        desenhaPlaneta(diametroNeturno, corPlanNetuno, 1, 2);
            //glutSwapBuffers();

    }

    glPopMatrix();

    glutSwapBuffers();
	// Execução dos comandos de desenho
}

void Anima(int value)
{
    if(executarAnima){
        //Tempo que a terra está orbitando o sol

        velTransMercurio += 0.45;
        velTransVenus += 0.35;
        velTransTerra += 0.3;
		if(velTransTerra > contaVolta * DOIS_PI){
			//tempTerraOrbSol++;
			contaVolta++;
		}
        velTransMarte += 0.2;
        velTransJupter += 0.12;
        velTransSaturno += 0.06;
        velTransUrano += 0.03;
        velTransNetuno += 0.01;

        velRotMercurio += 0.43;
        velRotVenus += 0.36;
        velRotTerra += 0.65;
        velRotMarte += 0.65;
        velRotJupter += 0.85;
        velRotSaturno += 0.85;
        velRotUrano += 0.75;
        velRotNetuno += 0.75;

        glutPostRedisplay();
        glutTimerFunc(11,Anima, 1);

    }
}


// Inicialização
void Inicializa(void)
{
// Define a cor de fundo da janela de visualização como branca
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
// Habilita a definição da cor do material a partir da cor corrente
glEnable(GL_COLOR_MATERIAL);
//Habilita o uso de iluminação
glEnable(GL_LIGHTING);
// Habilita a luz de número 0
//glEnable(GL_LIGHT0);

glEnable(GL_LIGHT1);
// Habilita o depth-buffering
glEnable(GL_DEPTH_TEST);
// Habilita o modelo de colorização de Gouraud
glShadeModel(GL_SMOOTH);
// Inicializa a variável que especifica o ângulo da projeção perspectiva
angle=50;
// Inicializa as variáveis usadas para alterar a posição do observador virtual
rotX = 30;
rotY = 0;
obsZ = 200;
obsY = 0;
}


// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Especifica posição do observador e do alvo
	glTranslatef(0,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}


// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador, do alvo e do vetor up
	gluLookAt(0+deslocamentoX,0+deslocamentoY,150+deslocamentoZ,
		0+deslocamentoX,0+deslocamentoY,0+deslocamentoZ,
		0,1,0);

}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Callback para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-out
			if (angle <= 130)
				angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


// Função callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{

		case GLUT_KEY_F11:	// desloca o volume de visualização para frente
								obsY--;
								break;
		case GLUT_KEY_F12:// desloca o volume de visualização para trás
								obsY++;
                            break;
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ++;
							break;
		case GLUT_KEY_END:	obsZ--;
							break;
        case GLUT_KEY_F1: o= o+15;
							break;
        case GLUT_KEY_F2: o= o-15;
							break;
        case GLUT_KEY_F3: a= a-15;
							break;
        case GLUT_KEY_F4: a= a+15;
							break;
        case GLUT_KEY_F5: z= z-15;
							break;
        case GLUT_KEY_F6: z= z+15;
							break;
	}
	PosicionaObservador();
	glutPostRedisplay();
}


// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500, 500);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de um teapot com iluminação");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);

	// Registra a funcao callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);
    glutTimerFunc(150, Anima, 1);

	// Registra a funcao callback para tratamento do redimensionamento da janela
    glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a funcao callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);

	Inicializa();
	glutMainLoop();
}

