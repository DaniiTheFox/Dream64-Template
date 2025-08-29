#define BONI_RUNNING_STATE 0x01
#define BONI_STANDING_STATE 0x02

class Bonii {
    public:
        // ----- VECTOR FOR MATH AND PHYS ----
        Vec3 boni = {0,0,0};
        float charYaw = 0.0f;
        float yawRad = 0.0f;
        float yawGl = 0.0f;
        // ----- Movement Flags --------------
        int KeyW = 0;
        int KeyA = 0;
        int KeyS = 0;
        int KeyD = 0;
        // -----------------------------------
        float moveSpeed = 5.0f;
        // -----------------------------------
        float forwardX = 0.0f;
        float forwardZ = 0.0f;
        float rightX = 0.0f;
        float rightZ = 0.0f;
        // ------- ANIMATION STATES --------
        int anim_st = BONI_STANDING_STATE;
        // ----------------------------------
        Vec3 moveDir = {0, 0, 0};
        float moveLength = 0.0f;
        // -----------------------------------
        Bonii (int,int,int);
        void Bon_Bonii_Update();
        void Bon_Bonii_Animate();
        void Bon_Bonii_Render();
};

Bonii::Bonii (int _x, int _y, int _z) {
    boni.x = _x;
    boni.y = _y;
    boni.z = _z;
}

void Bonii::Bon_Bonii_Animate () {
    switch (anim_st) {
        case BONI_STANDING_STATE:
            a_bonii->setAnimationSpeed(1.0f); // Más lento
            a_bonii->setAnimationRange(2, 6, true); 
        break;
        case BONI_RUNNING_STATE:
            a_bonii->setAnimationSpeed(10.0f); // Más lento
            a_bonii->setAnimationRange(6, 11, true); 
        break;
        default:
            a_bonii->setAnimationSpeed(1.0f); // Más lento
            a_bonii->setAnimationRange(2, 6, true);
        break;
    }
}

void Bonii::Bon_Bonii_Update () {
    moveSpeed = 5.0f * deltaTime * 60.0f;
    float rotationSpeed = 5.0f * deltaTime * 60.0f;


    moveDir = {0, 0, 0};

    Bon_Bonii_Animate();
    
    if (KeyW) {
        anim_st = BONI_RUNNING_STATE;
        moveDir.x += forwardX;
        moveDir.z += forwardZ;
        isMoving = 1;
    }
    if (KeyS) {
        anim_st = BONI_RUNNING_STATE;
        moveDir.x -= forwardX;
        moveDir.z -= forwardZ;
        isMoving = 1;
    }
    if (KeyA) {
        anim_st = BONI_RUNNING_STATE;
        moveDir.x += rightX;
        moveDir.z += rightZ;
        isMoving = 1;
    }
    if (KeyD) {
        anim_st = BONI_RUNNING_STATE;
        moveDir.x -= rightX;
        moveDir.z -= rightZ;
        isMoving = 1;
    }

    if (moveDir.x == 0 || moveDir.z == 0) {
        anim_st = BONI_STANDING_STATE;
    }

    moveLength = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
    if (moveLength > 0) {
        moveDir.x /= moveLength;
        moveDir.z /= moveLength;
        
        
        boni.x += moveDir.x * moveSpeed;
        boni.z += moveDir.z * moveSpeed;
        
        if (isMoving) {
            yawGl = atan2f(moveDir.x, moveDir.z) * 180.0f / M_PI;
        }
    }

    charYaw = smoothAngle(charYaw, yawGl, rotationSpeed);
    
}

void Bonii::Bon_Bonii_Render () {
    glPushMatrix();
        glTranslatef(boni.x, boni.y+25, boni.z);
        glRotatef(charYaw, 0, 1, 0);
        a_bonii->render();
    glPopMatrix();
}

Bonii *bonii = new Bonii(0,0,0);