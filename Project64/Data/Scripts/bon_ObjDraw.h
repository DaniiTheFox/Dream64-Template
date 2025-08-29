// ****************************************************************
// * THIS PART WILL BE THE FUNCTION WHICH WILL RENDER OUR OBJECTS *
// ****************************************************************
//------------------------------------------------------------------
void ll_Obj_Draw_Model( double vert_map[9][20000], double uv_map[6][20000], double nm_map[9][20000],int vert_num, GLuint Texture){
    glPushMatrix();                                                 //  
     glBindTexture(GL_TEXTURE_2D, Texture);                         //  THIS FUNCTION WILL DRAW THE OBJECTS
     glColor3f(1.0,1.0,1.0);                                        //  
     glBegin(GL_TRIANGLES);                                         //  --------------------------------------------
      for(int i = 0; i < vert_num; i++){                            //  IT MAKES A LOOP ALONG ALL THE VERTEX
       glTexCoord2f(uv_map[0][i], uv_map[1][i]);                    //  
       glNormal3f(  nm_map[0][i],   nm_map[1][i],   nm_map[2][i]);  //
       glVertex3f(vert_map[0][i], vert_map[1][i], vert_map[2][i]);  //  AND WILL START TO DRAW
       //glNormal3f(  nm_map[0][i],   nm_map[1][i],   nm_map[2][i]);  //
                                                                    //  
       glTexCoord2f(uv_map[2][i], uv_map[3][i]);                    //  FOR EACH ONE OF THE VERTEX
       glNormal3f(  nm_map[3][i],   nm_map[4][i],   nm_map[5][i]);  //
       glVertex3f(vert_map[3][i], vert_map[4][i], vert_map[5][i]);  //  IT WILL CREATE A TRIANGLE
       //glNormal3f(  nm_map[3][i],   nm_map[4][i],   nm_map[5][i]);  //
                                                                    //  WITH IT'S RESPECTIVE UV MAPPING
       glTexCoord2f(uv_map[4][i], uv_map[5][i]);                    //  AND THAT WILL CREATE
       glNormal3f(  nm_map[6][i],   nm_map[7][i],   nm_map[8][i]);  //
       glVertex3f(vert_map[6][i], vert_map[7][i], vert_map[8][i]);  //  THE OBJECT DRAWN
       //glNormal3f(  nm_map[6][i],   nm_map[7][i],   nm_map[8][i]);  //
      }                                                             //  ON THE OPENGL WINDOW
     glEnd();                                                       //  -----------------------------------------------
    glPopMatrix();                                                  //  
  }
  //----------------------------------------------------------------