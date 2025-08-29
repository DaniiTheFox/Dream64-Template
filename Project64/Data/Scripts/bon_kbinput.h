void VectorInput (Camera*_c, Bonii*_b) {
    _c->camRad = _c->camRelativeYaw * M_PI / 180.0f;
    _b->forwardX = sinf(_c->camRad);
    _b->forwardZ = cosf(_c->camRad);
    _b->rightX = sinf(_c->camRad + M_PI/2.0f);
    _b->rightZ = cosf(_c->camRad + M_PI/2.0f); 
}

// ------------------ Input ------------------
void keyboardDown(unsigned char key, int x, int y){
    if (key=='w') bonii->KeyW=1; 
    if (key=='s') bonii->KeyS=1; 
    if (key=='a') bonii->KeyA=1;
    if (key=='d') bonii->KeyD=1;

    if (key=='j') {
        keyJ = 1;
        camera->manualCamTimer = 0.0f;
        
        if (camera->c_mode == BON_CAMERA_MODE_LK01) {
            if (camera->manualCamRotation > -camera->MAX_MANUAL_ROTATION) {
                camera->manualCamRotation -= 25.0f; // 25 grados por pulsación
                camera->camYawOffset -= 25.0f;
            }
        } else {
            camera->camYawOffset -= 25.0f;
        }
    }
    
    if (key=='l') {
        keyL = 1;
        camera->manualCamTimer = 0.0f;
        
        if (camera->c_mode == BON_CAMERA_MODE_LK01) {
            
            if (camera->manualCamRotation < camera->MAX_MANUAL_ROTATION) {
                camera->manualCamRotation += 25.0f; 
                camera->camYawOffset += 25.0f;
            }
        } else {
            camera->camYawOffset += 25.0f;
        }
    }
    
    if (key=='i') camera->goalPitch += 5.0f;
    if (key=='k') camera->goalPitch -= 5.0f;
    if (key=='o') camera->goalDist -= 20.0f;
    if (key=='p') camera->goalDist += 20.0f;
}

void keyboardUp(unsigned char key, int x, int y){
    if (key=='w') bonii->KeyW=0;
    if (key=='s') bonii->KeyS=0;
    if (key=='a') bonii->KeyA=0;
    if (key=='d') bonii->KeyD=0;
    if (key=='j') keyJ=0;
    if (key=='l') keyL=0;
}