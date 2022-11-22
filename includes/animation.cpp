#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

extern bool bRotate,uRotate,car_bump,frotate,neon;

extern int rotating_angle_fan;
extern float theta,alpha;
extern float a,b,c;
extern double dist_car,rotate_car,ftheta;
extern bool rotate_fan;
extern double sky_z,eyeZ;


void animate()
{
    if(eyeZ<=125){
        sky_z=125;
    }
    else sky_z=eyeZ;
    if (rotate_fan)
    {
        rotating_angle_fan = rotating_angle_fan + 4;
    }
    //clock_rotate = clock_rotate + 0.01;
    glutPostRedisplay();


    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

        if (frotate == true)
    {
        ftheta -= 10;
       // if(ftheta > 360.0)
         //   ftheta -= 360.0*floor(ftheta/360.0);
    }

    if (car_bump == true)
    {
        dist_car -= 1;

        if(dist_car<=-700){
            dist_car=150;
        }
    }

    if(neon==true){
        a=a+0.005;
        b=b+.005;
        c=c+.005;
        if(a>=1)a=0;
        if(b>=1)b=0;
        if(c>=1)c=0;


       // glutPostRedisplay();
    }

    glutPostRedisplay();


    glutPostRedisplay();

}
