struct iframe {
    double o_mdl[9][20000];
    double o__uv[9][20000];
    double o_nrm[9][20000];
    int    o_n;
};

class AnimObj3D {
public:
    iframe animesh[20];
    
    // Variables de animación
    int currentFrameIndex = 2;
    float currentFrameTime = 0.1;
    float animationSpeed;
    bool isPlaying;
    int totalFrames;
    
    // Rangos de animación
    int animStartFrame=2;
    int animEndFrame;
    bool loopAnimation;
    
    GLuint Texture;
    Vec3 position;
    int yawRotation;

    AnimObj3D(int, int, int);
    void setPos(int, int, int);
    void loadAnimationFrames(char *baseFilename, char *_tex, int _h, int _w, int frameCount);
    iframe interpolateFrames(const iframe& A, const iframe& B, double t);
    void updateAnimation(float deltaTime);
    void playAnimation();
    void stopAnimation();
    void setAnimationSpeed(float speed);
    void setAnimationRange(int startFrame, int endFrame, bool loop = true);
    void render();
};

AnimObj3D::AnimObj3D(int _x, int _y, int _z) {
    position.x = _x;
    position.y = _y;
    position.z = _z;
    
    // Inicializar animación
    currentFrameIndex = 0;
    currentFrameTime = 0.0f;
    animationSpeed = 1.0f;
    isPlaying = false;
    totalFrames = 0;
    
    // Inicializar rangos
    animStartFrame = 0;
    animEndFrame = 0;
    loopAnimation = true;
    
    // Inicializar frames
    for (int i = 0; i < 20; i++) {
        animesh[i].o_n = 0;
    }
}

void AnimObj3D::setAnimationRange(int startFrame, int endFrame, bool loop) {
    animStartFrame = startFrame;
    animEndFrame = endFrame;
    loopAnimation = loop;
    
    // Asegurar que esté dentro de los límites
    animStartFrame = std::max(0, std::min(animStartFrame, totalFrames - 1));
    animEndFrame = std::max(0, std::min(animEndFrame, totalFrames - 1));
    
    // Empezar desde el frame inicial
    //currentFrameIndex = animStartFrame;
    //currentFrameTime = 0.0f;
}

void AnimObj3D::updateAnimation(float deltaTime) {
    if (!isPlaying || totalFrames <= 1) return;
    
    // Avanzar el tiempo de animación
    currentFrameTime += deltaTime * animationSpeed;
    
    // Calcular cuánto tiempo debe durar cada frame
    float timePerFrame = 1.0f;
    
    // Si pasamos al siguiente frame
    if (currentFrameTime >= timePerFrame) {
        currentFrameIndex++;
        currentFrameTime = 0.0f;
        
        // Verificar si llegamos al final del rango
        if (currentFrameIndex >= animEndFrame) {
            if (loopAnimation) {
                currentFrameIndex = animStartFrame; // Volver al inicio
            } else {
                currentFrameIndex = animEndFrame; // Quedarse en el último frame
                isPlaying = false; // Detener animación
            }
        }
    }
}

void AnimObj3D::render() {
    if (totalFrames == 0) return;
    
    iframe blended;
    
    if (animStartFrame == animEndFrame) {
        blended = animesh[animStartFrame];
    } else {
        int frameA = currentFrameIndex;
        int frameB = currentFrameIndex + 1;
        
        if (frameB > animEndFrame) {
            if (loopAnimation) {
                frameB = animStartFrame; // Loop al inicio
            } else {
                frameB = animEndFrame; // Quedarse en el último frame
            }
        }
        
        float timePerFrame = 1.0f;
        float t = currentFrameTime / timePerFrame;
        
        blended = interpolateFrames(animesh[frameA], animesh[frameB], t);
    }

    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(yawRotation, 0, 1, 0);
        ll_Obj_Draw_Model(blended.o_mdl, blended.o__uv, blended.o_nrm, blended.o_n, Texture);
    glPopMatrix();
}

void AnimObj3D::setPos(int _x, int _y, int _z) {
    position.x = _x;
    position.y = _y;
    position.z = _z;
}

void AnimObj3D::loadAnimationFrames(char *baseFilename, char *_tex, int _h, int _w, int frameCount) {
    Texture = LL_Bmp_Load_Image(_tex, _h, _w);
    totalFrames = frameCount;
    
    for (int i = 1; i < frameCount; i++) {
        char filename[256];
        snprintf(filename, sizeof(filename), "%s.frame.%d.obj", baseFilename, i);
        
        animesh[i].o_n = ll_Obj_Load_Model(filename, animesh[i].o_mdl, animesh[i].o__uv, animesh[i].o_nrm, animesh[i].o_n);
        LL_Sterm->LL_Termios_Log("Loaded frame " + std::to_string(i) + ": " + std::to_string(animesh[i].o_n) + " vertices");
    }
    
    // Por defecto, usar todos los frames
    setAnimationRange(0, frameCount - 1, true);
}

iframe AnimObj3D::interpolateFrames(const iframe& A, const iframe& B, double t) {
    iframe result;
    result.o_n = std::min(A.o_n, B.o_n);

    for (int i = 0; i < result.o_n; i++) {
        for (int j = 0; j < 9; j++) {
            result.o_mdl[j][i] = A.o_mdl[j][i] * (1.0 - t) + B.o_mdl[j][i] * t;
            result.o_nrm[j][i] = A.o_nrm[j][i] * (1.0 - t) + B.o_nrm[j][i] * t;
        }
        for (int j = 0; j < 6; j++) {
            result.o__uv[j][i] = A.o__uv[j][i] * (1.0 - t) + B.o__uv[j][i] * t;
        }
    }
    return result;
}

void AnimObj3D::playAnimation() {
    isPlaying = true;
}

void AnimObj3D::stopAnimation() {
    isPlaying = false;
}

void AnimObj3D::setAnimationSpeed(float speed) {
    animationSpeed = speed;
}