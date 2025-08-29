AnimObj3D *a_bonii = new AnimObj3D(0,0,0);
AnimObj3D *c_bonii = new AnimObj3D(100,25,0);
Object3D *a_pilar = new Object3D(0,25,0);

void Bon_Obj_Loaders () {
 c_bonii->loadAnimationFrames("Data/Models/bon/boni", "Data/Textures/bonii/char.bmp", 128, 128, 11);
 c_bonii->setAnimationSpeed(1.0f); // Más lento
 c_bonii->setAnimationRange(2, 6, true);
 c_bonii->currentFrameIndex = a_bonii->animStartFrame;
 c_bonii->currentFrameTime = 0.0f;
 c_bonii->playAnimation();

 a_bonii->loadAnimationFrames("Data/Models/bon/boni", "Data/Textures/bonii/char.bmp", 128, 128, 11);
 a_bonii->setAnimationSpeed(1.0f); // Más lento
 a_bonii->setAnimationRange(2, 6, true);
 a_bonii->currentFrameIndex = a_bonii->animStartFrame;
 a_bonii->currentFrameTime = 0.0f;
 a_bonii->playAnimation();

 a_pilar->setMdl("Data/Models/pilar.obj", "Data/Textures/RUIN01.bmp",256,256);
}

void Bon_Tex_Loaders () {
    Dbg_Floor = LL_Bmp_Load_Image ("Data/Textures/debug.bmp", 128, 128);
}