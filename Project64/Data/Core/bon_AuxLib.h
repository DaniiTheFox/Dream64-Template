void bon_reshape_fnc(int xs, int ys){ 
    const float ar = (float) xs / (float) ys;
    
    glViewport(0, 0, xs, ys); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(60, xs / (float) ys, 0.1, 3000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void bon_idle_fnc () {
    
    long long currentTime = currentTimeMillis();
    if (lastTime == 0) {
        lastTime = currentTime;
    }
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    
    if (deltaTime > 0.1f) {
        deltaTime = 0.1f;
    }
    
    isMoving = 0; // Resetear bandera de movimiento

    bonii->Bon_Bonii_Update();
    camera->cameraUpdate();
    a_bonii->updateAnimation(deltaTime);
    c_bonii->updateAnimation(deltaTime);
    VectorInput(camera, bonii);
    
    glutPostRedisplay();
    usleep(33);
}

