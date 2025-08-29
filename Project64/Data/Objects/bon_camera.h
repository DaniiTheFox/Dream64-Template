class Camera {
    public:
        // ------------------ Cámara Lakitu ------------------
        float camYaw   = 0.0f;   // grados, alrededor de Mario
        float camPitch = 200.0f;  // grados, arriba/abajo
        float camDist  = 400.0f; // distancia ojo->Mario

        int c_mode = BON_CAMERA_MODE_LK01;

        float goalYaw   = 0.0f;  
        float goalPitch = 200.0f;
        float goalDist  = 400.0f;

        float camRad = 0.0f;

        float camYawOffset = 180.0f; 

        float camRelativeYaw = 0.0f;
    
        float manualCamRotation = 0.0f; 
        float manualCamTimer = 0.0f;   
        const float CAM_RESET_TIME = 0.2f;
        const float MAX_MANUAL_ROTATION = 180.0f;
        

        Bonii *target = NULL;

        Camera (Bonii*);
        void applyCamera ();
        void cameraUpdate ();
        Vec3 sphericalOffset(float, float, float);
};

Camera::Camera (Bonii *_t) {
    target = _t;
}

Vec3 Camera::sphericalOffset(float yawDeg, float pitchDeg, float dist){
    float yaw   = yawDeg   * M_PI / 180.0f;
    float pitch = pitchDeg * M_PI / 180.0f;
    float cy = cosf(yaw),  sy = sinf(yaw);
    float cp = cosf(pitch), sp = sinf(pitch);

    float fx =  sy * cp;
    float fy =  sp;
    float fz =  cy * cp;

    return (Vec3){ target->boni.x - fx*dist,
                   target->boni.y - fy*dist,
                   target->boni.z - fz*dist };
}

// ------------------ Camara LookAt ------------------
void Camera::applyCamera(){
    // suavizado más lento tipo Lakitu
    camYaw   = approachAngle(camYaw, goalYaw, 1.0f);
    camPitch = approachf   (camPitch, goalPitch, 0.5f);
    camDist  = approachf   (camDist,  goalDist,  5.0f);

    Vec3 eye = sphericalOffset(camYaw, camPitch, camDist);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 16.0/9.0, 10.0, 5000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z,
              target->boni.x, target->boni.y + 80, target->boni.z,
              0,1,0);
}

void Camera::cameraUpdate () {
    camRelativeYaw = camYaw - 180.0f;

    float camRad = camRelativeYaw * M_PI / 180.0f;

    if (c_mode == BON_CAMERA_MODE_LK01) {
        if (!keyJ && !keyL) {
            manualCamTimer += deltaTime;
        } else {
            manualCamTimer = 0.0f; // Reiniciar si se presiona J/L
        }
        
        if (manualCamTimer >= CAM_RESET_TIME && fabs(manualCamRotation) > 0.1f) {
            float resetSpeed = 45.0f * deltaTime;
            
            if (manualCamRotation > 0) {
                manualCamRotation -= resetSpeed;
                camYawOffset -= resetSpeed;
                if (manualCamRotation < 0) {
                    manualCamRotation = 0;
                    camYawOffset = 180.0f;
                }
            } else {
                manualCamRotation += resetSpeed;
                camYawOffset += resetSpeed;
                if (manualCamRotation > 0) {
                    manualCamRotation = 0;
                    camYawOffset = 180.0f;
                }
            }
        }
    }

    goalYaw = target->charYaw + camYawOffset;

    float speedMag = target->moveLength * target->moveSpeed;
    float baseDist = 330.0f;
    float runDist  = 430.0f;
    goalDist = baseDist + (runDist - baseDist) * (speedMag / target->moveSpeed);
}

Camera *camera = new Camera(bonii); 