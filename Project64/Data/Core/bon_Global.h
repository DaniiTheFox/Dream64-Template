typedef struct {float x,y,z;} Vec3; // Direction Vector

#define BON_CAMERA_MODE_LK01 1 // World Camera
#define BON_CAMERA_MODE_CN01 2 // Cinematic Camera

int isMoving = 0;

long long lastTime = 0;
float deltaTime = 0.0f;

int keyJ=0, keyL=0;

GLuint Dbg_Floor;
