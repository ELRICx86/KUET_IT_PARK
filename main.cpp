// @author : 
//           Sajidul Islam
//           1707010
//           Khulna University of Engineering and Technology.


#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "BmpLoader.h"
#include"includes/animation.cpp"
#include "includes/keyboard.cpp"

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=700,eyeX=24, eyeY=5, eyeZ=120, lookX = 22 , lookY=0,lookZ=20, objX=0,objY=1,objZ=0,c1=0,c2=0;
float alpha = 0.0,  theta = 0.0, axis_x=0.0, axis_y=0.0 ,theta_circle=0.0,theta_fan_rotate = 0.0;
bool bRotate = false, uRotate = false;
double obt=0;
double fru=5;
bool pl=false;

bool neon=false;




double dist_car = 150, rotate_car = 0; bool car_bump = false;

double ftheta = 0;
bool frotate=0;
#define PI 3.1415927
//light color
const GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
const GLfloat gray[] = {0.8, 0.8, 0.8, 1.0};
const GLfloat silver[] = {0.75, 0.75, 0.75, 1.0};
const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
const GLfloat lime[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat green[] = {0.0, 0.8, 0.0, 1.0};
const GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
const GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
const GLfloat maroon[] = {0.8, 0.0, 0.0, 1.0};
const GLfloat woodColor[] = {0.56, 0.3, 0.2, 1.0};


void light0();
 void light1();
void light2();

unsigned int numOfTexs = 6;
unsigned int * textures;



//void animate();

double aY = 90, aP = 90, aR = 90;

void pitch() // x axis , y er about ,  o p
{
    //refX = 100.0*(cos(aP*3.1416/180.0));
    lookX = 100.0*(cos(aP*3.1416/180.0));
}

void yaw() // y axis, x axis about y u
{
    lookY = 100.0*(cos(aY*3.1416/180.0));
    printf("%lf\n" , aY);
}


void roll() // z axis h j
{
    objX = 10*(cos(aR*3.1416/180.0));
    objY = 10*(sin(aR*3.1416/180.0));
    //printf("%lf %faR\n" , aR,cos(aR*3.1416/180.0));
}

static GLfloat cube_vertices[8][3] =
{
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},

    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};

static GLfloat cube_vertices1[8][3] =
{
    {4, 4, 0},
    {-2, -2, 0},
    {4, -2, 0},
    {0, 4, 0},
    {4 ,4 ,2},

    {0, 4, 2},
    {-2, -2, 2},
    {4, -2, 2}
};


static GLfloat cube_vertices2[8][3] =
{
    {4, 4, 0},
    {0, -4, 0},
    {4, -2, 0},
    {0, 4, 0},
    {4 ,4 ,2},

    {0, 4, 2},
    {0, -4, 2},
    {4, -2, 2}
};

static GLubyte cube_plane_indics[6][4] =
{
    //consider y axis upper
    {0, 2, 6, 4}, //back
    {1, 5, 7, 3}, //front
    {0, 4, 5, 1}, //bottom
    {2, 3, 7, 6}, //top
    {0, 1, 3, 2}, //left
    {4, 6, 7, 5}  //right
};





static GLubyte cube_plane_indics1[6][4] =
{
    //consider y axis upper

    {0, 3, 5, 4}, //front
    {1, 6, 7, 2}, //back
    {3, 1, 2, 0}, //bottom
    {4, 5, 6, 7}, //top
    {2, 0, 4, 7}, //left
    {5, 3, 1, 6}  //right
};

//float aspect_ratio = float(width) / float(height);

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void draw_cube(GLfloat c1,GLfloat c2,GLfloat c3 )
{

    if(pl==true){
        c1=0;
        c2=0;c3=0;
    }

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.8, c2*0.8, c3*0.8, 1.0 };
    GLfloat mat_diffuse[] = { c1*0.7, c2*0.7, c3*0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(cube_vertices[cube_plane_indics[i][0]][0],
                    cube_vertices[cube_plane_indics[i][0]][1],
                    cube_vertices[cube_plane_indics[i][0]][2],
                    cube_vertices[cube_plane_indics[i][1]][0],
                    cube_vertices[cube_plane_indics[i][1]][1],
                    cube_vertices[cube_plane_indics[i][1]][2],
                    cube_vertices[cube_plane_indics[i][2]][0],
                    cube_vertices[cube_plane_indics[i][2]][1],
                    cube_vertices[cube_plane_indics[i][2]][2]);

        glVertex3fv(&cube_vertices[cube_plane_indics[i][0]][0]);
        glTexCoord2f(1,1);//0 1
        glVertex3fv(&cube_vertices[cube_plane_indics[i][1]][0]);
        glTexCoord2f(1, 0);//1 1
        glVertex3fv(&cube_vertices[cube_plane_indics[i][2]][0]);
        glTexCoord2f(0, 0);//1 0
        glVertex3fv(&cube_vertices[cube_plane_indics[i][3]][0]);
        glTexCoord2f(0, 1);//0 0

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&cube_vertices[cube_plane_indics[i][j]][0]);
        }
    }
    glEnd();
}







void draw_rect(GLfloat c1,GLfloat c2,GLfloat c3 )
{

    if(pl==true){
        c1=0;
        c2=0;c3=0;
    }

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.8, c2*0.8, c3*0.8, 1.0 };
    GLfloat mat_diffuse[] = { c1*0.7, c2*0.7, c3*0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(cube_vertices1[cube_plane_indics1[i][0]][0],
                    cube_vertices1[cube_plane_indics1[i][0]][1],
                    cube_vertices1[cube_plane_indics1[i][0]][2],
                    cube_vertices1[cube_plane_indics1[i][1]][0],
                    cube_vertices1[cube_plane_indics1[i][1]][1],
                    cube_vertices1[cube_plane_indics1[i][1]][2],
                    cube_vertices1[cube_plane_indics1[i][2]][0],
                    cube_vertices1[cube_plane_indics1[i][2]][1],
                    cube_vertices1[cube_plane_indics1[i][2]][2]);

        glVertex3fv(&cube_vertices1[cube_plane_indics1[i][0]][0]);
        glTexCoord2f(1,1);//0 1
        glVertex3fv(&cube_vertices1[cube_plane_indics1[i][1]][0]);
        glTexCoord2f(1, 0);//1 1
        glVertex3fv(&cube_vertices1[cube_plane_indics1[i][2]][0]);
        glTexCoord2f(0, 0);//1 0
        glVertex3fv(&cube_vertices1[cube_plane_indics1[i][3]][0]);
        glTexCoord2f(0, 1);//0 0

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&cube_vertices1[cube_plane_indics1[i][j]][0]);
        }
    }
    glEnd();
}


void draw_rect1(GLfloat c1,GLfloat c2,GLfloat c3 )
{

    if(pl==true){
        c1=0;
        c2=0;c3=0;
    }

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.8, c2*0.8, c3*0.8, 1.0 };
    GLfloat mat_diffuse[] = { c1*0.7, c2*0.7, c3*0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(cube_vertices2[cube_plane_indics1[i][0]][0],
                    cube_vertices2[cube_plane_indics1[i][0]][1],
                    cube_vertices2[cube_plane_indics1[i][0]][2],
                    cube_vertices2[cube_plane_indics1[i][1]][0],
                    cube_vertices2[cube_plane_indics1[i][1]][1],
                    cube_vertices2[cube_plane_indics1[i][1]][2],
                    cube_vertices2[cube_plane_indics1[i][2]][0],
                    cube_vertices2[cube_plane_indics1[i][2]][1],
                    cube_vertices2[cube_plane_indics1[i][2]][2]);

        glVertex3fv(&cube_vertices2[cube_plane_indics1[i][0]][0]);
        glTexCoord2f(1,1);//0 1
        glVertex3fv(&cube_vertices2[cube_plane_indics1[i][1]][0]);
        glTexCoord2f(1, 0);//1 1
        glVertex3fv(&cube_vertices2[cube_plane_indics1[i][2]][0]);
        glTexCoord2f(0, 0);//1 0
        glVertex3fv(&cube_vertices2[cube_plane_indics1[i][3]][0]);
        glTexCoord2f(0, 1);//0 0

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&cube_vertices2[cube_plane_indics1[i][j]][0]);
        }
    }
    glEnd();
}

//void drawBox()
//{
//  //  glColor3f(1,1,1);
//    //GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = {60};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
//
//    glBegin(GL_QUADS);
//    for (GLint i = 0; i <6; i++)
//    {
//        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
//        getNormal3p(v_box[quadIndices[i][0]][0], v_box[quadIndices[i][0]][1], v_box[quadIndices[i][0]][2],
//                    v_box[quadIndices[i][1]][0], v_box[quadIndices[i][1]][1], v_box[quadIndices[i][1]][2],
//                    v_box[quadIndices[i][2]][0], v_box[quadIndices[i][2]][1], v_box[quadIndices[i][2]][2]);
//
//        glVertex3fv(&v_box[quadIndices[i][0]][0]);glTexCoord2f(1,1);
//        glVertex3fv(&v_box[quadIndices[i][1]][0]);glTexCoord2f(1,0);
//        glVertex3fv(&v_box[quadIndices[i][2]][0]);glTexCoord2f(0,0);
//        glVertex3fv(&v_box[quadIndices[i][3]][0]);glTexCoord2f(0,1);
//    }
//    glEnd();
//    //glutSolidSphere (3.0, 20, 16);
//
//}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere (1.0, 16, 16);
}



void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTorus(innerRadius, outerRadius, nsides, rings);

    //glutSolidTorus(0.5, 10.0, 16, 12);
}
unsigned int ID[100],ID1;

int id= 1;
void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID[id++]);
    glBindTexture(GL_TEXTURE_2D, ID[id-1]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[id-1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}



void materialProperty_car(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}





void car(double pri_x, double pri_y, double pri_z, double sec_x, double sec_y, double sec_z)
{
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glEnd();


    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
//    glColor3f(1, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( sec_x, sec_y, sec_z, sec_x, sec_y, sec_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0f,-15.0f,15.0f);
    glVertex3f(-30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,15.0f);
    glEnd();


    glBegin(GL_3D);
//    glColor3f(1, 0, 0);
    glTranslated(-20.0f,-15.0f,15.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);


//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,-30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(45.0f,0.0f,0.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
    glEnd();




    glPushMatrix();
    glColor3f(3.0,4.0,5.0);
    //glRotatef(45,0,0,1);
    glScalef(10,0.3,3);

//    glutWireCube(-20);


    glPopMatrix();


    glPopMatrix();
}

void bumper_car()
{
    glPushMatrix();
    glScalef(125, 0.1, 120);
    glTranslatef (0,0,0);
    drawSphere(.5, .5, .5, .5, .5, .5);
    glPopMatrix();


    glPushMatrix();
    glScalef(1, 5, 1);
    glTranslatef (0,0,0);
    glRotatef(90,1,0,0);
    drawTorus(.5, .5, .5, .5, .5, .5, 1, 120, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5, .50, 0.3);
    glTranslatef (0,30,((-1)*dist_car));
    glRotatef(90,0,1,0);
    glRotatef(rotate_car,0,0,1);
    car(1, 0, 0, 0, 0, 1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5, .50, 0.3);
    glTranslatef (0,30,dist_car);
    glRotatef(270,0,1,0);
    glRotatef(rotate_car,0,0,1);
    car(0, 1, 0, 1, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5, .50, 0.3);
    glTranslatef (dist_car,30,0);
    glRotatef(rotate_car,0,0,1);
//    glRotatef(0,0,1,0);
    car(0, 0, 1, 0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5, .50, 0.3);
    glTranslatef (((-1)*dist_car),30,0);
    glRotatef(180,0,1,0);
    glRotatef(rotate_car,0,0,1);
    car(0, .7, .7, 0.5, .5, 0);
    glPopMatrix();
}


void draw_sphere(GLfloat c1, GLfloat c2, GLfloat c3)
{

        if(pl==true){
        c1=0;
        c2=0;c3=0;
    }
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.3, c2*0.3, c3*0.3, 1.0 };
    GLfloat mat_diffuse[] = { c1, c2, c3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(4.2,1.7,-2.9);
    glScalef(0.04,0.04,0.04);
    //glutSolidSphere(5, 50, 50);
    glutSolidTeapot(7);

}



void drawCylinder(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.5, 1.5, 19, 32, 32);

}

void draw_teapot(GLfloat c1, GLfloat c2, GLfloat c3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.3, c2*0.3, c3*0.3, 1.0 };
    GLfloat mat_diffuse[] = { c1, c2, c3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    //glutSolidSphere(5, 50, 50);
    glutSolidTeapot(1);

}







void wall()
{
    //beind_wall
   //glColor3f(0.0f, 0.5f, 0.5f);
    //glColor3f( 0.137255,  0.556863, 0.419608);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glScalef(9.5, 5, .5);
    glTranslatef(-.08,-.15,-8);

    //glRotatef( 30,0.0, 0.0, 1.0 );
    draw_cube(0.0f, .6f, 0.7f);
   // drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // left side_wall
    //glColor3f(0.0f, .6f, 0.7f);
      //glColor3f( 0.137255,  0.556863, 0.419608);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glScalef(.5, 5, 6.5);
    glTranslatef(-1.5,-.15,-.615);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    draw_cube(0.0f, .6f, 0.7f);
    //draw_cube();
    glPopMatrix();

    //right side_wall
    //glColor3f(0.0f, 0.6f, 0.7f);

    glPushMatrix();
    glScalef(.5, 5, 6.5);
    glTranslatef(16.5,-.15,-.61);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    draw_cube(0.0f, .6f, 0.7f);
    glPopMatrix();



    //floor
    //glColor3f(.3f, .3f, .3f);


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glScalef(9.5, .1, 6.5);
    glTranslatef(-.08,-8.5,-.615);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    draw_cube(1, 1, 1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void shelf()
{
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 5);
//glColor3f(0.36f, 0.25f, 0.20f);
glTranslatef(-.20,-.7,-4);
glScalef(8.9,2,2.0);
draw_cube(.7, 0.25f, 0.20f);
glPopMatrix();
glDisable(GL_TEXTURE_2D);

}
//
//
void racks()

{
    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D, textures[4]);
    //glColor3f(.71,.65,.26);
    glTranslatef(-.18,-.5,-2);
    glScalef(1,1.6,.1);
    draw_cube(.71,.65,.26);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.71,.65,.26);
    glTranslatef(1.1,-.5,-2);
    glScalef(1,1.6,.1);
    draw_cube(.71,.65,.26);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.71,.65,.26);
    glTranslatef(2.4,-.5,-2);
    glScalef(1,1.6,.1);
    draw_cube(.71,.65,.26);
    glPopMatrix();

    glPushMatrix();
   // glColor3f(.71,.65,.26);
    glTranslatef(3.8,-.5,-2);
    glScalef(1,1.6,.1);
    draw_cube(.71,.65,.26);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.71,.65,.26);
    glTranslatef(5.1,-.5,-2);
    glScalef(1,1.6,.1);
    draw_cube(.71,.65,.26);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(.71,.65,.26);
    glTranslatef(6.55,-.5,-2);
    glScalef(1,1.6,.1);
    draw_cube(.71,.65,.26);
    glPopMatrix();


    //dots

    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(.585,.2,-1.8);
    glScalef(.1,.3,.1);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(1.85,.2,-1.8);
    glScalef(.1,.3,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(3.25,.2,-1.8);
    glScalef(.1,.3,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(4.55,.2,-1.8);
    glScalef(.1,.3,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(5.85,.2,-1.8);
    glScalef(.1,.3,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(7.3,.2,-1.8);
    glScalef(.1,.3,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();

}
//
//
void sink(){




//top
glPushMatrix();
 glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 3);

//glColor3f(.90,.91,.98);
glTranslatef(7.5,0,0);
glScalef(1,.5,0);
draw_cube(.90,.91,.98);
glPopMatrix();


//right
glPushMatrix();
//glColor3f(.90,.91,.98);
glTranslatef(8.2,0,0);
glScalef(0,.5,1);
draw_cube(.90,.91,.98);
glPopMatrix();

//left
glPushMatrix();
//glColor3f(.90,.91,.98);
glTranslatef(7.5,0,0);
glScalef(0,.5,1);
draw_cube(.90,.91,.98);
glPopMatrix();


//bottom
glPushMatrix();
//glColor3f(.90,.91,.98);
glTranslatef(7.5,0,1);
glScalef(1,.5,0);
draw_cube(.90,.91,.98);
glPopMatrix();


//under

glPushMatrix();
glTranslatef(7.5,0,0);
glScalef(1,0,1);
draw_cube(.90,.91,.98);
glPopMatrix();

glDisable(GL_TEXTURE_2D);


//pipe
glPushMatrix();
//glColor3f(0,0,0);
glTranslatef(7.6,-.8,.7);
glScalef(.1,1,.1);
draw_cube(0,0,0);
glPopMatrix();

//tap


glPushMatrix();
//glColor3f(0,0,0);
glTranslatef(7.81,.6,.7);
glScalef(.1,.3,.1);
draw_cube(0,0,0);
glPopMatrix();


glPushMatrix();
//glColor3f(0,0,0);
glTranslatef(7.9,.8,.7);
glScalef(.5,.1,.1);
draw_cube(0,0,0);
glPopMatrix();





}
//
//
//
void smoker(){

glPushMatrix();
//glColor3f(.65,.49,.24);

glTranslatef(3.7,2.5,-3.5);
glScalef(1.2,.25,1.3);
draw_cube(.65,.49,.24);
glPopMatrix();


glPushMatrix();
//glColor3f(.55,.47,.14);
glTranslatef(4.1,2.5,-3.5);
glScalef(.4,1.8,.6);
draw_cube(.55,.47,.14);
glPopMatrix();


}
//
//
//
void cooker(){
    glPushMatrix();
    glTranslatef(3.8,1.3,-3.5);
    glScalef(1,.1,1.3);
    draw_cube(0,0,0);
    glPopMatrix();

    //top

    glPushMatrix();
    //glColor3f(1,1,1);
    glTranslatef(4.0,1.35,-3.2);
    glScalef(.5,.1,.1);
    draw_cube(1,1,1);
    glPopMatrix();

    //left
    glPushMatrix();
    //glColor3f(1,1,1);
    glTranslatef(4.0,1.35,-3.2);
    glScalef(.1,.1,.5);
    draw_cube(1,1,1);
    glPopMatrix();


    //right
     glPushMatrix();
    //glColor3f(1,1,1);
    glTranslatef(4.4,1.35,-3.2);
    glScalef(.1,.1,.5);
    draw_cube(1,1,1);
    glPopMatrix();


    //bottom
     glPushMatrix();
   // glColor3f(1,1,1);
    glTranslatef(4.0,1.35,-2.8);
    glScalef(.5,.1,.1);
    draw_cube(1,1,1);
    glPopMatrix();

}
//
//
void fridge(){


glPushMatrix();

 glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 4);
//glColor3f(0.5f, 1.0f, 1.0f);
glTranslatef(-.20,-.7,0);
glScalef(.7,1.5,1.5);
draw_cube(0.5f, 1.0f, 1.0f);
glPopMatrix();

glPushMatrix();
//glColor3f(0.5f, 1.0f, 1.0f);
glTranslatef(-.20,.9,0);
glScalef(.7,1.8,1.5);
draw_cube(0.5f, 1.0f, 1.0f);
glPopMatrix();



glPushMatrix();
//glColor3f(0.0f, 0.0f, 0.0f);
glTranslatef(-.20,.7,0);
glScalef(.69,.3,1.4);
draw_cube(0.0f, 0.0f, 0.0f);
glPopMatrix();


//handles

    glPushMatrix();
   // glColor3f(.0,.0,.0);
    glTranslatef(.42,1.1,.15);
    glScalef(.1,.7,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(.0,.0,.0);
    glTranslatef(.42,-.1,.15);
    glScalef(.1,.7,.1);
    draw_cube(.0,.0,.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




}


void ground(){

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(0,0,-50);
    glScalef(200,1,250);
    draw_cube(1,1,1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}


void surface(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glTranslatef(30,0,0);
    glScalef(60,2,128);
    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void structure(){



    for(int i=0,j=0;i<5;i++,j+=22){
    //--bottom right
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(80,3.2+j,50);
    glScalef(8,1.5,20);
    glRotatef(90,1,0,0);
    draw_rect(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //-----bottom left
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(40,0.2+j,50);
    glScalef(8,1.5,20);
    glRotatef(90,1,0,0);
    glRotatef(180,0,1,0);
    draw_rect(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    }




    //----pillars-----

    for(int l=0,tt=0;l<5;l++,tt+=17){


    for(int i=0,j=0,k=0;i<6;i++,j+=17,k+=2){


    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(75+k,20+tt,40+j);
    glRotatef(90,1,0,0);
    drawCylinder(1,1,1, 1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(105,20+tt,40+j);
    glRotatef(90,1,0,0);
    drawCylinder(1,1,1, 1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(45-k,20+tt,40+j);
    glRotatef(90,1,0,0);
    drawCylinder(1,1,1, 1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    }

    }



    //--sky staircase

    for(int i=0,j=0;i<3;i++,j+=22){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(45,22.75+j,50);
    glScalef(30,1,10);
    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(35,22.75+j,100);
    glScalef(50,1,10);
    //glDepthMask(1);
    //glColorMask(0,0,0,0);

    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    }




}




float a=0,b=0,c=0;

void design(){

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
   // glRotatef(180,0,0,1);
   glScalef(1,3,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4,-27,0);
    glScalef(1,3,1);
    glRotatef(180,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-46,0);
   // glRotatef(180,0,0,1);
   glScalef(1,3,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4,-72,0);
    glScalef(1,3,1);
    glRotatef(180,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();






    //---------------------

    glPushMatrix();
   glTranslatef(5,-12,0);
   glScalef(1,6,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(9,-60,0);
   glScalef(1,6,1);
    glRotatef(180,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();



    //-----------------------middle 4



    glPushMatrix();
    glTranslatef(14,0,2);
    glRotatef(180,0,1,0);
   glScalef(1,3,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();


     glPushMatrix();

    glTranslatef(10,-27,2);
    glScalef(1,3,1);
    glRotatef(180,0,0,1);
    glRotatef(180,0,1,0);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();


      glPushMatrix();
    glTranslatef(14,-46,2);
    glRotatef(180,0,1,0);
   glScalef(1,3,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,-72,2);
    glScalef(1,3,1);
    glRotatef(180,0,0,1);
    glRotatef(180,0,1,0);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();




//----------------------------
     glPushMatrix();
    glTranslatef(19,-12,2);
    glRotatef(180,0,1,0);
   glScalef(1,6,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,-60,2);
   glScalef(1,6,1);
    glRotatef(180,0,0,1);
    glRotatef(180,0,1,0);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();
    glPushMatrix();

//-------------------------- last 4

    glPushMatrix();
    glTranslatef(20,0,0);
   // glRotatef(180,0,0,1);
    glScalef(1,3,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(24,-27,0);
    glScalef(1,3,1);
    glRotatef(180,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();

          glPushMatrix();
    glTranslatef(20,-46,0);
   // glRotatef(180,0,0,1);
   glScalef(1,3,1);
   // glRotatef(-90,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(24,-72,0);
    glScalef(1,3,1);
    glRotatef(180,0,0,1);
   // glBindTexture();
    draw_rect1(2,2,2);
    glPopMatrix();


    //-----------draw square

    glPushMatrix();
    glTranslatef(-3,-84,0);
    glScalef(2,96,2);
    draw_cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(24.5,-84,0);
    glScalef(2,96,2);
    draw_cube(1,1,1);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //-------draw lights



    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(4,-6,0);
    glScalef(1,18,1);

    //glutSolidCube(1);
    draw_cube(a*.4,b,c);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(13.8,-6,0);
    glScalef(1,18,1);

    //glutSolidCube(1);
    draw_cube(a*.4,b,c);
    glPopMatrix();



    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(24,-6,0);
    glScalef(1,18,1);

    //glutSolidCube(1);
    draw_cube(a,b*.3,c);
    glPopMatrix();





    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(4,-85,0);
    glScalef(1,24,1);

    //glutSolidCube(1);
    draw_cube(c,b*.20,a);
    glPopMatrix();




    //----------


    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(24,-52,0);
    glScalef(.5,38,1);

    //glutSolidCube(1);
    draw_cube(b*.5,a,c*.6);
    glPopMatrix();



    //-------

    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(-1,-60,0);
    glScalef(1,38,1);

    //glutSolidCube(1);
    draw_cube(b*.9,a,c*.6);
    glPopMatrix();

    //-----

    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(14,-59,0);
    glScalef(.5,38,1);

    //glutSolidCube(1);
    draw_cube(b*.5,a,c);
    glPopMatrix();




    //-------

    glPushMatrix();
    //glColor3f(255,0,255);
    glTranslatef(19.2,-84,0);
    glScalef(.5,36,1);

    //glutSolidCube(1);
    draw_cube(b,c*.5,a);
    glPopMatrix();


}

GLUquadric *quad;

void tree()
{
    quad = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);

    glPushMatrix();
    draw_cube(1,1,1);
    glScalef(1, 2, 1);

    gluQuadricTexture(quad,1);
    glRotatef(90, 1, 0, 0);
    gluSphere(quad,4,100,100);

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glTranslatef(0, -7, 0);
    glRotatef(90, 1, 0, 0);
    gluQuadricTexture(quad,1);
    gluCylinder(quad, 1, 1, 10, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}






void table_set(){


    //--------table
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glTranslatef(30.5,7.5,32);
    glScalef(10,1,5);
    draw_cube(1,0,0);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(35,5,35);
    //glRotatef(90,1,0,0);
    glScalef(1,3,1);
    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //-----------chair
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(30.5,4.5,38);
    glScalef(10,2,4);
    draw_cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30.5,9.5,41);
    glRotatef(90,1,0,0);
    glScalef(10,1,4);
    draw_cube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(30.5,4.5,28);
    glScalef(10,2,4);
    draw_cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30.5,9.5,28);
    glRotatef(90,1,0,0);
    glScalef(10,1,4);
    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




}



void chair()
{
    //seat part
    glPushMatrix();
    glScalef(0.5, 0.05, 0.5);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left back
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right back
    glPushMatrix();
    glTranslatef(1.35, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(0.5, 0.05, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1.5 , 0);
    glScalef(0.5, 0.05, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.5, 0.05, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left front leg
    glPushMatrix();
    glTranslatef(0, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right front leg
    glPushMatrix();
    glTranslatef(1.35, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    draw_cube(1,0,0);
    //drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

}


void table()
{
    //table
    glPushMatrix();
    glScalef(4, 0.3, 4);
    drawSphere(0.8,0.4,0.00,  0.4,0.2,0);
    glPopMatrix();

    //stand
    glPushMatrix();
    glScalef(0.1, -1, -0.1);
    draw_cube(1,0,0);
    //drawCube1(0,0,0, 0,0,0.5);
    glPopMatrix();

    //stand bottom
    glPushMatrix();
    glTranslatef(0, -2.8, 0);
    glScalef(1, 0.2, 1);
    drawSphere(1,0.549,0.00,  0.5,0.2745,0);
    glPopMatrix();
}

void diningSet()
{
    glPushMatrix();
    glTranslatef(0, -16, 0);
    table();
    glPopMatrix();

    for(int i = 0; i <= 360; i+=72)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        glTranslatef(0, -17, -4);
        chair();
        glPopMatrix();
    }
}





GLfloat centerX = -0.5;
GLfloat centerY = -0.5;
GLfloat centerZ = -0.5;


float rotating = 0;
int rotating_angle_fan = 0;
bool rotate_fan = false;

void fanWheel(float cx, float cy, float cz, float r, int num_segments)
{

    GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_ambient[] = {0.7, 0.7, 0.5, 1.0f};
    GLfloat mat_diffuse[] = {0.7, 0.7, 0.5, 1.0f};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0f};
    GLfloat high_shininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle
        float x = r * cosf(theta);                                         //calculate the x component
        float y = r * sinf(theta);                                         //calculate the y component
        glVertex3f(x + cx, y + cy, cz);                                    //output vertex
    }
    glEnd();
}

void fan(float x = 0, float y = 0, float z = 0)
{
    glPushMatrix();
    glTranslated(x, y, z);

    //handle of fan
    glPushMatrix();
    glTranslated(0, 1.45, 0);
    glScaled(0.25, 2, 0.25);
    glTranslated(centerX, centerY, centerZ);
    draw_cube(0.40, 0.30, 0.0);
    glPopMatrix();

    //fan wing 1
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    draw_cube(0.8, 0.8, 0.8);
    glPopMatrix();

    //fan wing 2
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glRotated(120, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    draw_cube(0.8, 0.8, 0.8);
    glPopMatrix();

    //fan wing 3
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glRotated(240, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    draw_cube(0.8, 0.8, 0.8);
    glPopMatrix();

    //circle of fan
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glTranslated(0.5, -0.1, -1.5);
    glRotated(90, 1, 0, 0);
    glTranslated(centerX, centerX, centerZ);
    fanWheel(0.0, 2.0, 0.0, 1.25, 10000);
    glPopMatrix();

    glPopMatrix();
}



void stair(){

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    for(int i=0,j=0,k=0;i<5;i++,j+=2,k+=6){
    glPushMatrix();
    glTranslatef(42,0+j,192-k);
    glScalef(30,3,6);
    draw_cube(1,1,1);
    glPopMatrix();
    }

    glTranslatef(42,10,145);
    glScalef(30,3,25);
    draw_cube(1,1,1);
    glPopMatrix();



    for(int i=0,j=0,k=0;i<4;i++,j+=2,k+=6){
    glPushMatrix();
    glTranslatef(42,12+j,140-k);
    glScalef(30,3,6);
    draw_cube(1,1,1);
    glPopMatrix();
    }


    glTranslatef(40,21,100);
    glScalef(40,4,25);
    draw_cube(1,1,1);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(43,30,135);
    glRotatef(20,1,0,0);
    glScalef(.1,.1,3.5);
    drawCylinder(1,1,1, 1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(43,7.2,197.5);
    glRotatef(90,1,0,0);
    glScalef(.1,.1,.3);
    drawCylinder(1,1,1, 1,1,1);
    glPopMatrix();

      glPushMatrix();
    glTranslatef(70,7.2,197.5);
    glRotatef(90,1,0,0);
    glScalef(.1,.1,.3);
    drawCylinder(1,1,1, 1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70,30,135);
    glRotatef(90,1,0,0);
    glScalef(.1,.1,.7);
    drawCylinder(1,1,1, 1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(43,30,135);
    glRotatef(90,1,0,0);
    glScalef(.1,.1,.7);
    drawCylinder(1,1,1, 1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(70,30,135);
    glRotatef(20,1,0,0);
    glScalef(.1,.1,3.5);
    drawCylinder(1,1,1, 1,1,1);
    //drawCylinder(1,0,0, 0.5,0,0.5);
    glPopMatrix();

}


void right_side(){



    for(int i=0,j=0;i<3;i++,j+=22){

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(87,25+j,29);
    glScalef(23,20,100);
    draw_cube(0.0f, .6f, 0.7f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    }

}


void left_side(){


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(10,2,29);
    glScalef(23,20,100);
    draw_cube(1, 1, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    for(int i=0,j=0;i<3;i++,j+=22){

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(10,25+j,29);
    glScalef(23,20,100);
    draw_cube(0.0f, .6f, 0.7f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    }

}




void highway(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(125,2,-25);
    glScalef(30,1,220);
    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


double sky_z;


void sky(){
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(0,0,-175+sky_z);
    glScalef(200,250,1);
    draw_cube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,50+sky_z);
    glRotatef(90,0,1,0);
    glScalef(250,250,1);
    draw_cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,0,50+sky_z);
    glRotatef(90,0,1,0);
    glScalef(250,250,1);
    draw_cube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


void cafe(){


    wall();

//    fan();

    shelf();
//
    fridge();
//
  racks();
//
    sink();
//
    cooker();

    light0();
    light1();
    light2();


    glPushMatrix();
    //glScalef(15,15,15);
    glTranslatef(5,4,-2);
    glScalef(.5,.5,.5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
     fan(0, 7.5, -5);
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);


     glPushMatrix();
     glScalef(10,10,10);
     diningSet();
     glPopMatrix();



}



void object(){

    glTranslatef(0,0,obt);


    glPushMatrix();
    ground();
    glPushMatrix();


    //glPushMatrix();
    structure();
    //glPushMatrix();



    glPushMatrix();
    glTranslatef(82,90,135);
    glScalef(1,.8,.8);
    design();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(12,90,135);
    glScalef(1,.8,.8);
    design();
    glPopMatrix();





    glPushMatrix();
    glTranslatef(115,90,30);
    glScalef(1,.8,.8);
    glRotatef(90,0,1,0);
    design();
    glPopMatrix();


    glPushMatrix();
   stair();
   glPopMatrix();


   glPushMatrix();
   highway();
   glPopMatrix();


   glPushMatrix();
    for(int i=0,j=0;i<3;i++,j+=10){
            glPushMatrix();
            glTranslatef(54,0,20+j);
            glScalef(.8,.8,.8);
            table_set();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(70,0,20+j);
            glScalef(.8,.8,.8);
            table_set();
            glPopMatrix();

    }
   glPopMatrix();

    for(int i=0,j=0;i<6;i++,j+=40){
        glPushMatrix();
        glTranslatef(170,35,-30+j);
        glScalef(2,2,2);
        tree();
        glPopMatrix();
    }

        for(int i=0,j=0;i<5;i++,j+=40){
        glPushMatrix();
        glTranslatef(170-j,35,-30);
        glScalef(2,2,2);
        tree();
        glPopMatrix();
    }


    glPushMatrix();
    glTranslatef(15,22,155);
    glScalef(1.2,1.2,1.2);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30,22,155);
    glScalef(1.2,1.2,1.2);
    tree();
    glPopMatrix();


   glPushMatrix();
   right_side();
   glPopMatrix();

    glPushMatrix();
   left_side();
   glPopMatrix();


   glPushMatrix();
   surface();
   glPopMatrix();


   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
   glTranslatef(7,0,0);
   glScalef(105,100,10);
   draw_cube(1,1,1);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();


   glPushMatrix();
   sky();
   glPopMatrix();



    glPushMatrix();
    glTranslatef(70,6,30);
    glScalef(4,3,4);

    //glRotatef(90,0,1,0);
    cafe();
    glPopMatrix();


//    glPushMatrix();
//   bumper_car();
//   glPopMatrix();
    glPushMatrix();
    glTranslatef(130,0,140);
    glScalef(.6,.6,.6);
    glPushMatrix();
    glScalef(.5, .50, 0.3);
    glTranslatef (0,30,dist_car);
    glRotatef(270,0,1,0);
    //glRotatef(rotate_car,0,0,1);
    car(0, 1, 0, 1, 1, 0);
    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(145,0,30);
    glScalef(.6,.6,.6);

    glPushMatrix();
    glScalef(.5, .50, 0.3);
    glTranslatef (0,30,((-1)*dist_car));
    glRotatef(90,0,1,0);
    //glRotatef(rotate_car,0,0,1);
     car(1, 0, 0, 1, 0, 1);
    glPopMatrix();

    glPopMatrix();

//
//   glPushMatrix();
//   stair();
//   glPopMatrix();


//    GLfloat m[16] = {
//    1.0f, 0, 0.0f, 0.0f,
//    0, 1.0f, 0.0f, 0.0f,
//    0.0f, 0.0, 1.0f, 0.0f,
//    0.0f, 0.0f, 0.0f, 1.0f
//};
//    glMultMatrixf(m);


}


int bv = 0;


void b_swap()
{
    if(bv==1)
    {
        int tmp = eyeY;
        eyeY = eyeZ;
        eyeZ = tmp;

        tmp = objY;
        objY = objZ;
        objZ = tmp;

    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glColor3d(.5,.5,.5);
    glClearColor(.5,.5,.5,0);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFrustum(-5, 5, -5, 5, fru, 200);
   // gluPerspective(60,1,1,300);
    //gluPerspective(60,1,1,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  lookX,lookY,lookZ,  objX,objY,objZ);

    glViewport(c1, c2, windowHeight, windowWidth);
    //glTranslatef(2,2,2);

    // glRotatef(45, 0, 0, 1 );
    // triangle();

    //draw_cube();

    //draw_cube();
    //glRotatef( 70,1.0,0.0, 0.0 );

    //bed();

    object();

    //printf("%f", eyeZ);

   // table();
  //  chair();
  //  almirah();
   // laptop();
//glPushMatrix();
//    glTranslatef(2,2,2);
//
//    // glRotatef( alpha,axis_x, axis_y, 0.0 );
//    // glRotatef( theta, axis_x, axis_y, 0.0 );
//    draw_cube();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-2,-2,-2);
//
//    // glRotatef( alpha,axis_x, axis_y, 0.0 );
//    // glRotatef( theta, axis_x, axis_y, 0.0 );
//    draw_cube();
//    glPopMatrix();
//
//
//      glPushMatrix();
//         glTranslatef(0,0,Tzval);
//         glScalef(3,3,3);
//         glutSolidCube(1);
//     glPopMatrix();


    glFlush();
    glutSwapBuffers();
}






bool light_switch0 = 1, light_switch1 = 1, light_switch2 = 1;

void light0()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0, 0, 0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   // GLfloat light_position[] = { 10, 0.0, 50.0, 1.0 };
    GLfloat light_position[] = { -50, 10, 20, 0.0 }; // global . directional
    //GLfloat light_position[] = { 8, 30, 40.0, 1.0 };


    if(light_switch0)
    glEnable( GL_LIGHT0);
    else
    glDisable(GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}



void light1()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {.5, .5, .5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   // GLfloat light_position[] = { 10, 0.0, 50.0, 1.0 };
    GLfloat light_position[] = { 50, 10, 20, 0.0 }; // global . directional
    //GLfloat light_position[] = { 8, 30, 40.0, 1.0 };


    if(light_switch0)
    glEnable( GL_LIGHT0);
    else
    glDisable(GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}


void light2()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_spot[] = {-2,0,0.0}; // direction
    GLfloat light_position[] = { 8,2,0, 1.0 };
//    GLfloat light_position[] = { 8, -4, -55.0, 1.0 };


    if(light_switch2)
    glEnable( GL_LIGHT2);
    else
    glDisable(GL_LIGHT2);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 35.0);
    glLightf( GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
    glLightfv( GL_LIGHT2, GL_SPOT_DIRECTION, light_spot);
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);

}







int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(120,120);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

   // textures = (unsigned int *)malloc(numOfTexs * sizeof(unsigned int));
    //glGenTextures(numOfTexs, textures);
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\tiles.bmp"); /// 1
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\wall.bmp"); /// 2
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\sink1.bmp"); /// 3

    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\fridge.bmp"); /// 4
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\wood.bmp");//5
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\ground.bmp");//6
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\blue.bmp");//7
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\wall2.bmp");//8
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\wall3.bmp");//9
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\road.bmp");//10
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\leaf.bmp");//11
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\log.bmp");//12
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\sofa.bmp");//13
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\fidge2.bmp");//14
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\sky.bmp");//15
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\sky2.bmp");//15
    LoadTexture("G:\\4.2\\graphics lab\\glut lab\\TESTT\\imgs\\peebles.bmp");//15



    glEnable(GL_LIGHTING);
    glShadeModel ( GL_SMOOTH );
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
