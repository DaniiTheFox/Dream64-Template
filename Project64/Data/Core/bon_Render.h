void bon_display_fnc () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glMatrixMode(GL_MODELVIEW);
    
    camera->applyCamera();
    bonii->Bon_Bonii_Render();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, Dbg_Floor);  
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);  
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000, -25, -1000);
            glTexCoord2f(5.0f, 0.0f); glVertex3f( 1000, -25, -1000);
            glTexCoord2f(5.0f, 5.0f); glVertex3f( 1000, -25,  1000);
            glTexCoord2f(0.0f, 5.0f); glVertex3f(-1000, -25,  1000);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        c_bonii->render();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(250,0,0);
        a_pilar->render();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-250,0,0);
        a_pilar->render();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}