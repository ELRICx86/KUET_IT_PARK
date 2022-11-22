#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>


extern bool bRotate,uRotate,car_bump,frotate,neon,rotate_fan;

extern float theta,alpha;
extern double dist_car,rotate_car,ftheta;




double extern Txval,Tyval,Tzval;
double extern windowHeight, windowWidth,eyeX, eyeY, eyeZ, lookX , lookY,lookZ, objX,objY,objZ,c1,c2;
float extern  alpha ,  theta , axis_x, axis_y ,theta_circle,theta_fan_rotate ;
extern bool  bRotate , uRotate ;
double extern obt;
double extern fru;
bool extern pl;

double extern dist_car , rotate_car ; bool extern car_bump ;

double extern ftheta ;
bool extern frotate;

extern void roll();
extern void pitch();
extern  void yaw();

extern void light0();
extern void light1();
extern void light2();


double extern aY, aP, aR ;

int extern bv;
extern void b_swap();


bool extern light_switch0, light_switch1, light_switch2;

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 't':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;


    case 'q':
        eyeY++;
        lookY++;
        glutPostRedisplay();
        break;
    case 'e':
        eyeY--;
        lookY--;
        glutPostRedisplay();
        break;

    case 'w':
        eyeZ--;
        lookZ--;
        glutPostRedisplay();
        break;
    case 's':
        eyeZ++;
        lookZ++;
        glutPostRedisplay();
        break;
    case 'a':
        eyeX--;
        lookX--;
        glutPostRedisplay();
        break;
    case 'd':
        eyeX++;
        lookX++;
        glutPostRedisplay();
        break;
    case 'p':
        eyeZ+=1.0;
        break;
    case 'o':
        eyeZ-=1.0;
        break;
    case 'i':
        lookX+=1.0;
        break;
    case 'u':
        lookX-=1.0;
        break;
    case 'l':
        lookY+=1.0;
        break;
    case 'k':
        lookY-=1.0;
        break;
    case 'j':
        objX+=0.1;
        objZ+=0.1;
        break;
    case 'h':
        objX-=0.1;
        objZ-=0.1;
        break;

    case 'm':
        c1+=5;
        break;

    case 'n':
        c1-=5;
        break;
    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'x':
        obt+=1;
        break;
    case 'z':
        obt-=1;
        break;

    case '3':
        rotate_fan = !rotate_fan;
        break;




    case '1':
        fru+=1;
        break;
    case '2':
        fru-=1;
        break;


    case '7':
        if(aP>=180)
           break;
        aP+=1;
        pitch();
        glutPostRedisplay();
        break;
    case '4':
        aP-=1;
        if(aP<=0)
            break;
        pitch();
        glutPostRedisplay();
        break;

    case '8':

          // aY -= 360.0*floor(aY/360.0);
        if(aY >= 180.0 )break;
        aY+=1;

        yaw();
        glutPostRedisplay();
        break;
    case '5':
        if( aY <=0)break;
        aY-=1;

           // aY += 360.0*floor(aY/360.0);
        yaw();
        glutPostRedisplay();
        break;


//
//     case '3':
//        frotate = !frotate;
//        break;


     case '9':

          // aY -= 360.0*floor(aY/360.0);
        if(aR >= 270.0 )
            break;
        aR+=1;

        roll();
        glutPostRedisplay();
        break;
    case '6':
        if( aR <= -90.0)
            break;
        aR-=1;

           // aY += 360.0*floor(aY/360.0);
        roll();
        glutPostRedisplay();
        break;

    case '=':
        if(!light_switch0 && !light_switch2)
        pl=!pl;
        break;
    case 'b':
        bv = !bv;
        b_swap();
        break;

         case '~': //bumper car
             car_bump = !car_bump; break;

    case 27:    // Escape key
        exit(1);


       case ';':
        light_switch0=!light_switch0;
        //light0();
        glutPostRedisplay();
        break;
    case '/':
        light_switch2=!light_switch2;
        //light0();
        glutPostRedisplay();
        break;

    case '.':
           // light_switch1=!light_switch1;
            neon=!neon;
            glutPostRedisplay();
            break;

    }

    glutPostRedisplay();
}
