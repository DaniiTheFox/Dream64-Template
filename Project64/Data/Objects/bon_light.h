// *******************************
// * THIS IS THE LIGHTING ENGINE *
// *******************************
// --------------------------------------------------------
class Bon_Lights {
	public:
		Bon_Lights(int);      // << THIS SETUPS THE LIGHTING ENGINE AND ENVIRONMENT
		void Bon_Management();// << THIS STARTS THE AMBIENT LIGHTING
};
// ---------------------------------------------------------
Bon_Lights::Bon_Lights(int _null){} // THE CONSTRUCTOR DOES NOTHING
// ---------------------------------------------------------
void Bon_Lights::Bon_Management() {
  //-------------------------------
  	GLfloat light_ambient[] =	//
  	{0.95, 0.95, 0.95, 0.5};		// IN THIS SEGMENT OF CODE
  	GLfloat light_diffuse[] =	// WE DEFINE THE BASE LIGHTING
  	{1.0, 1.0, 1.0, 1.0};		// FOR OUR RENDERING ENGINE
  	GLfloat light_specular[] =	// WE DEFINE THE BASE SPECULAR
  	{1.0, 1.0, 1.0, 1.0};		// POSITION, DIFFUSE AND AMBIENT
  	GLfloat light_position[] =	// MOSTLY THE BASICS FOR MATERIALS
  	{1.0, 1.0, 1.0, 0.0};		//
  // ------------------------------
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  // ------------------------------
  // ---- WHITE FOG ----
  GLfloat fogColor[4] = {0.0f, 0.0f, 0.0f, 0.55f}; // menos densa
  glEnable(GL_FOG);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogi(GL_FOG_MODE, GL_LINEAR);      
  glFogf(GL_FOG_START, 1000.0f);  // empieza más cerca pero suave
  glFogf(GL_FOG_END,   2000.0f);  // se vuelve completa más lejos
  glHint(GL_FOG_HINT, GL_NICEST); 
}

// ---------------------------------------
Bon_Lights *Bon_Latern = new Bon_Lights(0);// We create the base object