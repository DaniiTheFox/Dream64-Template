// ***********************************************************
// * THIS IS THE AUXILIAR FUNCTION THAT WILL LOAD THE MODELS *
// ***********************************************************
int aux_vnum = 0;
// ----------------------------------------------------------------------------------------
int ll_Obj_Load_Model(char *filename, double mdl[9][20000], double _uv[6][20000], double nrm[9][20000], int _n){// funcion de lectura de modelo desde string
 // ---------------------------------------------------------------------------------------
 std::string _m = "";                     // 
 std::ifstream file(filename);            // THIS FUNCTION WILL 
 std::string file_content;                // LOAD THE ACTUAL FILE
 while(std::getline(file, file_content)){ // FROM THE DISK
  _m = _m + file_content + "\n";          // AND WILL STORE IT INSIDE A STRING
 }                                        // 
 //std::cout<<"model loading..... file: "<<filename<<"\n model:"<<_m<<std::endl;
 //LL_Sterm->LL_Termios_Log("loading the model: \n"+_m+"\n into game...");
 // ----------------------------------------------------------------------------------------
 double vertices[3][20000];                                                    // array temporal de vertices
 double uvMappin[3][20000];                                                    // array temporal de mapa de textura
 double VertxNrm[3][20000];
 char vert1[20], vert2[20], vert3[20];                                        // variables temporales para conversion
 float tmpv1 = 0, tmpv2 = 0, tmpv3 = 0;
 int vcounter = 0, tcounter = 0, ncounter = 0, bcounter = 0;                  // variables de construccion vertex,texture,build counter
 char v1[15],v2[15],v3[15];int trash;
 int cv1,cv2,cv3,cv4,cv5,cv6,vn1,vn2,vn3;
 //-------------------------------------------------------------------------------------------
 std::istringstream m_tmp(_m);                                                // hacer la conversion para leer linea por linea el string
 std::string tmp_line = "";                                                   // donde se almacena la linea actual
 while(std::getline(m_tmp, tmp_line)){                                        // mientras no termine de leer el archivo
  // ---------------------------------------------------------------------------
  char lh[128];
  char temporal[128];                                                         // usados para el scanf general
  strcpy(temporal, tmp_line.c_str());                                         // pasar la linea a un array char temporal
  sscanf(temporal, "%s", &lh);                                                // la primera lectura para saber que esta leyendo
  // ---------------------------------------------------------------------------
  if(strcmp(lh, "v") == 0){
   sscanf(temporal,"%s %s %s %s\n",&trash , &vert1, &vert2, &vert3 );         // leer los datos a convertir
   tmpv1 = atof(vert1);
   tmpv2 = atof(vert2);                                                       // conversion de los datos a flotante para almacenar en array
   tmpv3 = atof(vert3);
   vertices[0][vcounter] = tmpv1; vertices[1][vcounter] = tmpv2; vertices[2][vcounter] = tmpv3;
   vcounter++;                                                                // nueva linea en el array de vertices
  }
  // ---------------------------------------------------------------------------
  if(strcmp(lh, "vt") == 0){
   sscanf(temporal,"%s %s %s\n",&trash , &vert1, &vert2 );                    // escanear los datos del mapeo de la textura por vertice
   tmpv1 = atof(vert1);
   tmpv2 = atof(vert2);                                                       // hacer la conversion a flotantes
   tmpv3 = 0;
   uvMappin[0][tcounter] = tmpv1; uvMappin[1][tcounter] = tmpv2;              // almacenar el dato
   tcounter++;                                                                // cambio de linea del array de uv map
  }
  // ---------------------------------------------------------------------------
  if(strcmp(lh, "vn") == 0){
   sscanf(temporal,"%s %s %s %s\n",&trash , &vert1, &vert2, &vert3 );         // leer los datos a convertir
   tmpv1 = atof(vert1);
   tmpv2 = atof(vert2);                                                       // conversion de los datos a flotante para almacenar >
   tmpv3 = atof(vert3);
   VertxNrm[0][ncounter] = tmpv1; VertxNrm[1][ncounter] = tmpv2; VertxNrm[2][ncounter] = tmpv3;
   ncounter++;                                                                // nueva linea en el array de vertices
  }
  // ---------------------------------------------------------------------------
  std::string tmp = "",num1 = "",num2 = "";
  bool isL = true;
  std::string tmp2 = "",num3 = "",num4 = "";                                  // temporales para conversiones y generar el orden de el modelo
  bool isL2 = true;
  std::string tmp3 = "",num5 = "",num6 = "";
  bool isL3 = true;
  bool ns1 = true,ns2 = true,ns3 = true;
  // ----------------------------------------------------------------------------
  if(strcmp(lh, "f") == 0){
   sscanf(temporal, "%s %s %s %s ",&trash, &v1, &v2, &v3);
   tmp = v1;tmp2 = v2; tmp3 = v3;
   tmp = tmp+".";tmp2 = tmp2+"."; tmp3 = tmp3+".";                            // añadir un punto al final para facilitar la lectura
   ns1 = true;ns2 = true;ns3 = true;
   isL = true; isL2 = true; isL3 = true;                                      //cuando la conversion finaliza se procede a crear numeros enteros
   // ----------------------------------------------------------------------------
   sscanf(tmp.c_str() , "%i/%i/%i", &cv1, &cv2, &vn1);
   sscanf(tmp2.c_str(), "%i/%i/%i", &cv3, &cv4, &vn2);
   sscanf(tmp3.c_str(), "%i/%i/%i", &cv5, &cv6, &vn3);
   // ----------------------------------------------------------------------------
   cv1--; cv2--; cv3--;
   cv4--; cv5--; cv6--;
   vn1--; vn2--; vn3--;
   // -----------------------------------------------------------------------------
   _uv[0][bcounter] = uvMappin[0][cv2]; _uv[1][bcounter] = uvMappin[1][cv2];
   mdl[0][bcounter] = vertices[0][cv1]; mdl[1][bcounter] = vertices[1][cv1]; mdl[2][bcounter] = vertices[2][cv1];
   nrm[0][bcounter] = VertxNrm[0][vn1]; nrm[1][bcounter] = VertxNrm[1][vn1]; nrm[2][bcounter] = VertxNrm[2][vn1];

   _uv[2][bcounter] = uvMappin[0][cv4]; _uv[3][bcounter] = uvMappin[1][cv4];
   mdl[3][bcounter] = vertices[0][cv3]; mdl[4][bcounter] = vertices[1][cv3]; mdl[5][bcounter] = vertices[2][cv3];
   nrm[3][bcounter] = VertxNrm[0][vn2]; nrm[4][bcounter] = VertxNrm[1][vn2]; nrm[5][bcounter] = VertxNrm[2][vn2];

   _uv[4][bcounter] = uvMappin[0][cv6]; _uv[5][bcounter] = uvMappin[1][cv6];
   mdl[6][bcounter] = vertices[0][cv5]; mdl[7][bcounter] = vertices[1][cv5]; mdl[8][bcounter] = vertices[2][cv5];
   nrm[6][bcounter] = VertxNrm[0][vn3]; nrm[7][bcounter] = VertxNrm[1][vn3]; nrm[8][bcounter] = VertxNrm[2][vn3];
   // ------------------------------------------------------------------------------
   bcounter++;                                                            // eso se guarda en un array para simplemente dibujar al final
  }
 }
  //std::cout<<"<PRISM> Loaded model..."<<std::endl;
  LL_Sterm->LL_Termios_Log("OBJ model has been loaded into game...");
  return bcounter;                                                        // guardar numero de triangulos por dibujar (evitar la basura)
}
// ----------------------------------------------------------------------------------