class Object3D {
    public:
        double o_mdl[9][20000];
        double o__uv[9][20000];
        double o_nrm[9][20000];
        int    o_n = 0;

        GLuint Texture;
        Vec3 position;
        int yawRotation;

        Object3D (int,int,int);
        void setPos (int,int,int);
        void setMdl (char *filename, char * _tex,int,int);
        void render();

};

Object3D::Object3D (int _x, int _y, int _z) {
    position.x = _x;
    position.y = _y;
    position.z = _z;
}

void Object3D::setPos (int _x, int _y, int _z) {
    position.x = _x;
    position.y = _y;
    position.z = _z;
}

void Object3D::setMdl (char *_filename, char *_tex, int _h, int _w) {
    Texture = LL_Bmp_Load_Image (_tex, _h, _w);
    o_n = ll_Obj_Load_Model(_filename, o_mdl, o__uv, o_nrm, o_n);
}

void Object3D::render () {
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(yawRotation, 0, 1, 0);
        ll_Obj_Draw_Model(o_mdl, o__uv, o_nrm, o_n, Texture);
    glPopMatrix();
}