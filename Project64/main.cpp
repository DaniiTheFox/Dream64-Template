#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string.h> 
#include <sstream>
#include <cstdio>
#include <math.h>
#include <sys/time.h>
#include <future>
#include <chrono>

#define  STB_IMAGE_IMPLEMENTATION"
#include "Data/libs/stb_image.h"

#include "Data/Core/bon_Global.h"
#include "Data/libs/bon_termios.h"
#include "Data/Scripts/bon_math.h"
#include "Data/Scripts/bon_TexMgr.h"
#include "Data/Scripts/bon_ObjLoad.h"
#include "Data/Scripts/bon_ObjDraw.h"
#include "Data/Objects/bon_object.h"
#include "Data/Objects/bon_animobj.h"
#include "Data/Scripts/bon_Loaders.h"
#include "Data/Objects/bon_bonii.h"
#include "Data/Objects/bon_camera.h"
#include "Data/Objects/bon_light.h"
#include "Data/Scripts/bon_kbinput.h"
#include "Data/Core/bon_AuxLib.h"
#include "Data/Core/bon_Render.h"

void glInitialize ();

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow ("ねむりうた 64");
    glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
    glInitialize ();
    LL_Sterm->LL_Termios_Log("Engine Started");

    glutIdleFunc(bon_idle_fnc);
    glutDisplayFunc(bon_display_fnc);
    glutReshapeFunc(bon_reshape_fnc);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);

    lastTime = currentTimeMillis();
    glutMainLoop();
    return 0;
}

void glInitialize () {
    Bon_Latern->Bon_Management();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glAlphaFunc(GL_GREATER, 0.5f);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLoadIdentity();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    gluPerspective(60, 1, 0.1, 3000);

    Bon_Obj_Loaders();
    Bon_Tex_Loaders();
}
