//	This is a sample program that illustrates OpenGL and GLUT in 3D. It
//	renders a picture of a tokamak. The camera can be moved by dragging
//	the mouse. The camera moves forward by hitting the up-arrow key and
//	back by moving the down-arrow key. Hit ESC, 'q' or 'Q' to exit.
//
//	Warning #1: This program uses the function glutSpecialUpFunc, which
//	may not be available in all GLUT implementations. If your system
//	does not have it, you can comment this line out, but the up arrow
//	processing will not be correct.
//----------------------------------------------------------------------

#include <stdlib.h> 
#include <math.h> 
#include <stdio.h> 
#include <vector>
#include <iostream>

// The following works for both linux and MacOS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
// escape key (for exit)
#define N 70
#define ESC 27

// g++ Fusion.cpp -o Fusion.exe -lglut -lGL -lGLU 

//----------------------------------------------------------------------
// Global variables
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera position. The values (lx, ly)
// point in the direction the camera is looking. The variables angle and
// deltaAngle control the camera's angle. The variable deltaMove
// indicates the amount of incremental motion for the camera with each
// redraw cycle. The variables isDragging and xDragStart are used to
// monitor the mouse when it drags (with the left button down).
//----------------------------------------------------------------------


// CIRCLE


class circle{
public : float x,y,z,rot;

public:
circle(float x,float y,float z){x = x;y=y;z=z;}
void createcircle (int k, int r, int h); 
void createcircle1 (int r); 
};
void circle::createcircle (int k, int r, int h) {
  glBegin(GL_LINES);
    for (int i = 0; i < 180; i++)
    {
    x = r * cos(i) - h;
    y = r * sin(i) + k;
    glVertex3f(x + k,y - h,z);
    
    x = r * cos(i + 0.1) - h;
    y = r * sin(i + 0.1) + k;
    glVertex3f(x + k,y - h,z);
    }
    glEnd();
}

void circle::createcircle1 (int r) {
  glBegin(GL_LINES);
    for (int i = 0; i < 180; i++)
    {
    glVertex3f(x + r*cos(i)+1,y +r*sin(i)-1,z);
    glVertex3f(x + r*cos(i+0.1)+1,y +r*sin(i+0.1)-1,z);
    }
    glEnd();
}



// Camera position
float x = -50.0 , y = -50.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move
float deltaMove_z = 0.0;

float z = 0.0;

// Camera direction
float lx = 1.0, ly = 1.0; // camera points initially along y-axis
float lz = 1.0;
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

struct Position{
	float x;
	float y;
	float z;
};
std::vector<Position> Positions;

struct Point {
	GLint x;
	GLint y;
};

struct couple{
    float x, y, z;
};

struct carre{
    couple c1;
    couple c2;
    couple c3;
    couple c4;
};

std::vector<float> temps;
std::vector <carre> carres;
std::vector <std::vector <carre>> helice;
carre c;
couple m;

int n=2*N;
float t=0;
float angle_t=0;
float rayon= 25.0;
float b=2.0;
int const m1=2;
int const m2=2;
float diametre = 12;
float phi=0;

//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h) 
{
	float ratio =  ((float) w) / ((float) h); // window aspect ratio
	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


float t2 = 0;
float t1 = 0;
void drawSphere(){

	// Draw body (a 20x20 spherical mesh of radius 0.75 at height 0.75)
	glColor3f(t1/(2*M_PI), t1/(2*M_PI), t2/(2*M_PI)); // set drawing color to white
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.75);
		glutSolidSphere(0.75, 20, 20);
	glPopMatrix();

}

void draw_circle(Point pC, GLfloat radius) {
	GLfloat step = 1/radius;
	GLfloat x, y;

	for(GLfloat theta = 0; theta <= 360; theta += step) {
		x = pC.x + (radius * cos(theta));
		y = pC.y + (radius * sin(theta));
		glVertex2i(x, y);
	}
}

void Beignet(std::vector <std::vector <carre>> helice){
	/*
	glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
        for(int p=0;p<n;p++){
            for(int k=0;k<n;k++){
                for(int i=0;i<n;i++){

                    glVertex3f(helice[k][i].c1.x+diametre/2*cos(phi), helice[k][i].c1.y, helice[k][i].c1.z+diametre/2*sin(phi));
                    
                }
            }
            phi+=2*M_PI/n;
        }
    glEnd();
    */
    float r1 = 35;
    float r2 = 7;
    float x = 0;
    float y = 0;
    float z = 0;
    float theta1 = 0;
    float theta2 = 0;
    int H = 500;
    /*
    for(int i = 0;i<=H;i++){
        y = r1*cos(theta1);
        x = r1*sin(theta1);
        z = 0;
        theta2 = 0;
        for(int j=0;j<=H;j++){
            if(theta2>M_PI/2 && theta2<3*M_PI/2){
                glColor3f(1.0,0.0,1.0);
            }
            else{
                glColor3f(0.0,1.0,1.0);
            }
            glBegin(GL_LINES);
            glVertex3f(x+r2*cos(theta2) ,y ,z+r2*sin(theta2) );
            glVertex3f(x+r2*cos(theta2+2*M_PI/H) ,y ,z+r2*sin(theta2+2*M_PI/H) );
            glEnd();
            theta2+=2*M_PI/H;
        }
        theta1+=2*M_PI/H;
    }
    std::cout << "theta 1 = " << theta1 << std::endl;
    */
   
    for(int i = 0;i<=H;i++){
        y = r1*cos(theta1);
        x = r1*sin(theta1);
        z = 0;
        theta2 = 0;
        for(int j=0;j<=H;j++){
            if(theta2>M_PI/2 && theta2<3*M_PI/2){
                glColor3f(1.0,0.0,1.0);
            }
            else{
                glColor3f(1.0,1.0,1.0);
            }
            glBegin(GL_LINES);
            glVertex3f(x+r2*cos(theta2)*sin(theta1),y+r2*cos(theta2)*cos(theta1) ,z+r2*sin(theta2) );
            glVertex3f(x+r2*cos(theta2+2*M_PI/H)*sin(theta1) ,y+r2*cos(theta2+2*M_PI)*cos(theta1),z+r2*sin(theta2+2*M_PI/H) );
            glEnd();
            theta2+=2*M_PI/H;
        }
        theta1+=2*M_PI/H;
    }
    


    /*
    for(int p=0;p<n;p++){
                // glVertex3f(helice[k][i].c1.x+diametre/2*cos(phi), helice[k][i].c1.y, helice[k][i].c1.z+diametre/2*sin(phi));
                //circle a(21000,0,-100);
                //a.createcircle(diametre/2*cos(phi),2,+diametre/2*sin(phi));

                circle b(diametre/2*cos(phi),diametre/2*sin(phi),20);
                b.createcircle1(2);

        phi+=2*M_PI/n;
    }
    */
    /*
	circle a(20,20,10);
    a.createcircle(0,2,1);

    circle b(40,20,2);
    b.createcircle(5,2,7);

    circle c(40,20,1);
    c.createcircle(0,2,0);
    */
/*
	 for(int p=0;p<n;p++){
            for(int k=0;k<n;k++){
                for(int i=0;i<n;i++){

					Point pt = { helice[k][i].c1.x+diametre/2*cos(phi),helice[k][i].c1.y+diametre/2*sin(phi) };
					GLfloat radius = 20;
					glBegin(GL_POINTS);
						draw_circle(pt, 50);
					glEnd();
                
                }
            }
            phi+=2*M_PI/n;
        }
*/
}

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update(void) 
{
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * ly * 0.1;
		// z += deltaMove_z * lz *0.1;
	}
	glutPostRedisplay(); // redisplay everything
}

void change(std::vector<Position> &Positions){

	Position e = Positions[0];

	for(int i=0;i<Positions.size()-1;i++){

		Positions[i] = Positions[i+1];

	}
	Positions[Positions.size()-1] = e;

}

void change(std::vector<float> &temps){

	float e = temps[0];

	for(int i=0;i<temps.size()-1;i++){

		temps[i] = temps[i+1];

	}
	temps[temps.size()-1] = e;

}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We first update the camera location based on its distance from the
// origin and its direction.
//----------------------------------------------------------------------

float x1 = rayon/2;
float y_1 = 0;
float z1 = b;

void renderScene(void) 
{
	int i, j;

	// Clear color and depth buffers
	glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	glTranslatef(0,z,0);
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(
			x,      y,      1.0,
			x + lx, y + ly, 1.0,
			0.0,    0.0,    1.0);

	// Draw ground - 200x200 square colored green
	glColor3f(0.0, 0.7, 0.0);
	/*
	glBegin(GL_QUADS);
		glVertex3f(-100.0, -100.0, 0.0);
		glVertex3f(-100.0,  100.0, 0.0);
		glVertex3f( 100.0,  100.0, 0.0);
		glVertex3f( 100.0, -100.0, 0.0);
	glEnd();
	*/

	// Draw 36 snow men
	/*
	for(i = -3; i < 3; i++)
		for(j = -3; j < 3; j++) {
			glPushMatrix();
				glTranslatef(i*7.5, j*7.5, 0);
				drawFusion();
			glPopMatrix();
		}
	*/
	// Drawn snow man turning in the tokamak
    /*
	 if(t1 > 2*M_PI){
        t1 = 0;
    }
    else{
        t1+=4*M_PI/N;
    }
    x1 = diametre/2*cos(t1);
    z1 = diametre/2*sin(t1);
	glPushMatrix();
		glTranslatef(x1, y_1, z1);
		drawSphere();
	glPopMatrix();
	t2 = t1;
	for(int i=0;i<temps.size();i++){
		glPushMatrix();
		//glTranslatef(Positions[i].x, Positions[i].y, Positions[i].z);
		// glTranslatef(diametre/2*cos(temps[i]), y_1, diametre/2*sin(temps[i]));
		glTranslatef(diametre/2*cos(t2), y_1, diametre/2*sin(t2));

		if(t2 > 2*M_PI){
			t2 = 0;
		}
		else{
			t2+=2*M_PI/temps.size();
		}
		drawSphere();
		glPopMatrix();
	}
	change(Positions);
	change(temps);
    */
	Beignet(helice);

	glutSwapBuffers(); // Make it all visible
} 

//----------------------------------------------------------------------
// User-input callbacks

//
// processNormalKeys: ESC, q, and Q cause program to exit
// pressSpecialKey: Up arrow = forward motion, down arrow = backwards
// releaseSpecialKey: Set incremental motion to zero
//----------------------------------------------------------------------
void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
} 

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 20.0; break;
		case GLUT_KEY_DOWN : deltaMove = -20.0; break;
		case GLUT_KEY_LEFT : z += -1.0; break;
		case GLUT_KEY_RIGHT : z += 1.0; break;
	}
} 

void releaseSpecialKey(int key, int x, int y) 
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
		// case GLUT_KEY_LEFT : z = 0.0; break;
		// case GLUT_KEY_RIGHT : z = 0.0; break;
	}
} 

//----------------------------------------------------------------------
// Process mouse drag events
// 
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void mouseMove(int x, int y) 
{ 	
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
int main(int argc, char **argv) 
{
	printf("\n\
-----------------------------------------------------------------------\n\
  OpenGL Sample Program:\n\
  - Drag mouse left-right to rotate camera\n\
  - Hold up-arrow/down-arrow to move camera forward/backward\n\
  - q or ESC to quit\n\
-----------------------------------------------------------------------\n");

	for(int p=0;p<m1;p++){

        for(int l=0;l<m2;l++){
        
            for(int k=0;k<n;k++){
                
                for(int i=0;i<n;i++){

                    m.x=rayon*cos(angle_t);
                    m.y=rayon*sin(angle_t);
                    m.z=b;
                    carres.push_back(c);

                        carres[i].c1=m;

                        carres[i].c2.x=m.x+0.1;
                        carres[i].c2.y=m.y;
                        carres[i].c2.z=m.z;

                        carres[i].c3.x=m.x+0.1;
                        carres[i].c3.y=m.y+0.1;
                        carres[i].c3.z=m.z;

                        carres[i].c4.x=m.x;
                        carres[i].c4.y=m.y+0.1;
                        carres[i].c4.z=m.z;
                    
                    t+=2*M_PI/n;
                    angle_t+=2*M_PI/n;
                }
                helice.push_back(carres);
                carres.clear();
                angle_t=0;
            }
        }
    }
	
	for(int i = 0;i<N;i++){
		Position e;
		e.x = rayon*cos(i*M_2_PI/(2*N));
		e.y = rayon*sin(i*M_2_PI/(2*N));
		e.z = b;
		Positions.push_back(e);
	}
	int BOULES = 80;
	for(int i = 0;i<BOULES;i++){
		temps.push_back(i*2*M_PI/BOULES);
	}
	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("OPENGL TOKAMAK ");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(renderScene); // (re)display callback
	glutIdleFunc(update); // incremental update 
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}
