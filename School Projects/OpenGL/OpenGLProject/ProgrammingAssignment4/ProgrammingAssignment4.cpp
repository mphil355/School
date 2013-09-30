#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h> 
#include <math.h>
#include <iostream>
using namespace std;

#ifdef __APPLE_
#include <GLUT/glut.h>
#else
#include <gl/gl.h>
#include <gl/glut.h>
#endif


#define NUM_PARTICLES    5000          /* Number of particles  */
#define NUM_DEBRIS       350            /* Number of debris     */
#define KEY_ESC	27
#define RandomFactor 2.0

typedef GLfloat light0_pos[4];
typedef GLfloat spot_direction[3];
struct SVertex
{
	GLfloat x,y,z;
};

//It's not the best style to put classes into the main file, 
//but here it is easier for you and me!
class CDrop
{
private:
	GLfloat time;  //How many steps the drop was "outside", when it falls into the water, time is set back to 0
	SVertex ConstantSpeed;  //See the doc for explanation of the physics
	GLfloat AccFactor;
public:
	void SetConstantSpeed (SVertex NewSpeed);
	void SetAccFactor(GLfloat NewAccFactor);
	void SetTime(GLfloat NewTime);
	void GetNewPosition(SVertex * PositionVertex);  //increments time, gets the new position
};
void CDrop::SetConstantSpeed(SVertex NewSpeed)
{
	ConstantSpeed = NewSpeed;
}
void CDrop::SetAccFactor (GLfloat NewAccFactor)
{
	AccFactor = NewAccFactor;
}
void CDrop::SetTime(GLfloat NewTime)
{
	time = NewTime;
}
void CDrop::GetNewPosition(SVertex * PositionVertex)
{
	SVertex Position;
	time += 1.0;
	Position.x = ConstantSpeed.x * time;
	Position.y = ConstantSpeed.y * time - AccFactor * time * time;
	Position.z = ConstantSpeed.z * time;
	PositionVertex->x = Position.x;
	PositionVertex->y = Position.y + 0.5;
	PositionVertex->z = Position.z;
	if (Position.y < 0.0) 
	{
		/*the drop has fallen into the water. The problem is now, that we cannot
		set time to 0.0, because if there are more "DropsPerRay" than "TimeNeeded" (See InitFountain())
		several drops would be seen as one. Check it out.
		*/
		time = time - int(time);
		if (time > 0.0) time -= 1.0;
	}
		
}
////////////////////////////////////////////////////////////////////////////////

CDrop * FountainDrops;
SVertex * FountainVertices;
GLint Steps = 4;   //a fountain has several steps, each with its own height
GLint RaysPerStep = 10;  
GLint DropsPerRay = 5;
GLfloat DropsComplete = Steps * RaysPerStep * DropsPerRay;
GLfloat AngleOfDeepestStep = 60;
GLfloat AccFactor = 0.011;

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

typedef struct {
    float x, y, z;
	float rotation;
} MPObject;


MPObject bunny = {-3.0, 0.0, -3.0, 135.0};
MPObject duck = {-1.0, 0.0, 0.0, -45.0};
MPObject dino = {1.0, 0.0, 1.0, 135.0};

typedef struct
{
    int X;
    int Y;
    int Z;
    double U;
    double V;
}VERTICES;

const double PI = 3.1415926535897;
const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES VERTEX[VertexCount];

/* A particle */

struct particleData
{
  float   position[3];
  float   speed[3];
  float   color[3];
};
typedef struct particleData    particleData;


/* A piece of debris */

struct debrisData
{
  float   position[3];
  float   speed[3];
  float   orientation[3];        /* Rotation angles around x, y, and z axes */
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
};
typedef struct debrisData    debrisData;


/* Globals */

particleData     particles[NUM_PARTICLES];
debrisData       debris[NUM_DEBRIS];   
int              fuel = 0;  
//prototypes
		void collision();
		void MPidle(); // idle callback for movement
		void MPmenu(int key); //menu callback
		void MPresetView();	
		void MPinit();
		void MPkeys(GLubyte key, int x, int y);//keyboard callback
		void MPprintMenu();// print to help menu to console
		void specialkeys(int key, int x, int y);//special keys callback
		void MPpond (float x_center, float y_center, float w, float h, int n);
		void MPfence();
		void MPgrid();
		void MPcube();
		void newSpeed (float dest[3]);
		void newExplosion(void);
		GLfloat GetRandomFloat(GLfloat range);
		void InitFountain(void);
		void DrawFountain(void);
		void displaySphere (double R, GLuint texture);
		void createSphere (double R, double H, double K, double Z);
		void MPbunny();
		void MPdino();
		void MPduck();
		void MPdrawGround();
		void MPreshape(int width, int height);
		void MPmouse(int btn, int state, int x, int y);// mouse callback
		void MPmotion(int x, int y); // motion callback
		void MPflyCamera(float dist, float azimuth, float incidence, float twist);
		void MPdrawScene(); // display callback
		void MPcreateMenu();
//variables
GLuint curBunnyTex, curDuckTex, curDinoTex, curGroundTex, curPondTex, curCubeTex, curSphereTex;//current textures
GLuint bunnyTex, duckTex, dinoTex, groundTex, pondTex, cubeTex, sphereTex;//normal
GLuint stripesTex, checkersTex, trollTex, dotsTex; // custom

int t = 0;
int i = 0;
int idleFlag = 0;
bool colors = false;
bool sphereHit, redCubeHit, blueCubeHit, fenceHit;
bool lightsOn = true;
int action, view;

int lightingMenu, viewingMenu, textureMenu, mainMenu; // main menu ids
int groundTexMenu, bunnyTexMenu, duckTexMenu, dinoTexMenu, texAllMenu; // texture ids
int colorSubMenu, angleSubMenu, positionSubMenu; // lighting ids

float xStart = 0.0, yStart = 0.0; // used for mouse detection
float nearClip, farClip, dist, twistAngle, incAngle, azimAngle; // camera manipulation
int width, height, flat;

static GLfloat theta[] = {0.0,0.0,0.0};

light0_pos defaultLightPos = {12.0, 12.0, 12.0, 0.0};
spot_direction defaultLightAngle = { -1.0, -1.0, -1.0 };

light0_pos lightPos[] ={{12.0, 12.0, 12.0, 0.0},// front top right
						{0.0, 12.0, 12.0, 0.0},// front top middle
						{-12.0, 12.0, 12.0, 0.0},// front top left
						{-12.0, 12.0, 12.0, 0.0},// left top front
						{-12.0, 12.0, 0.0, 0.0},// left top mieddle
						{-12.0, 12.0, -12.0, 0.0},// left top back
						{-12.0, 12.0, -12.0, 0.0},// back top left
						{0.0, 12.0, -12.0, 0.0},// back top middle
						{12.0, 12.0, -12.0, 0.0},// back top right
						{12.0, 12.0, -12.0, 0.0},// right top back
						{12.0, 12.0, 0.0, 0.0},// right top middle
						{12.0, 12.0, 12.0, 0.0}};// right top front

spot_direction spotDir[] ={{-12.0, -12.0, -12.0},// front top right
						{0.0, -12.0, -12.0},// front top middle
						{12.0, -12.0, -12.0},// front top left
						{12.0, -12.0, -12.0},// left top front
						{12.0, -12.0, 0.0},// left top mieddle
						{12.0, -12.0, 12.0},// left top back
						{12.0, -12.0, 12.0},// back top left
						{0.0, -12.0, 12.0},// back top middle
						{-12.0, -12.0, 12.0},// back top right
						{-12.0, -12.0, 12.0},// right top back
						{-12.0, -12.0, 0.0},// right top middle
						{-12.0, -12.0, -12.0}};// right top front

materialStruct whiteShinyMaterials = {
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	100.0
	};

materialStruct selectedMaterials = {
	{1.0, 1.0, 0.0, 1.0},
	{1.0, 1.0, 0.0, 1.0},
	{1.0, 1.0, 0.0, 1.0},
	500.0
	};

materialStruct fenceMaterials = {
	{0.0, 0.5, 1.0, 1.0},
	{0.0, 0.5, 1.0, 1.0},
	{0.0, 0.5, 1.0, 1.0},
	100.0
	};
materialStruct blackShinyMaterials = {
	{0.0, 0.0, 0.0, 1.0},
	{0.0, 0.0, 0.0, 1.0},
	{0.0, 0.0, 0.0, 1.0},
	0.0
	};

materialStruct groundMaterials = {
	{0.0, 0.3, 0.0, 1.0},
	{0.0, 0.3, 0.0, 1.0},
	{0.0, 0.3, 0.0, 1.0},
	0.0
	};

materialStruct bunnyMaterials = {
	{1.0, 0.5, 0.5, 1.0},
	{1.0, 0.5, 0.5, 1.0},
	{1.0, 0.5, 0.5, 1.0},
	50.0
	};

materialStruct duckMaterials = {
	{0.1, 1.0, 0.1, 1.0},
	{0.1, 1.0, 0.1, 1.0},
	{0.1, 1.0, 0.1, 1.0},
	0.0
	};

materialStruct dinoMaterials = {
	{0.0, 0.0, 0.9, 1.0},
	{0.0, 0.0, 0.9, 1.0},
	{0.0, 0.0, 0.9, 1.0},
	50.0
	};

materialStruct redCubeMaterials = {
	{1.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0},
	100.0
	};

materialStruct blueCubeMaterials = {
	{0.0, 0.0, 1.0, 1.0},
	{0.0, 0.0, 1.0, 1.0},
	{0.0, 0.0, 1.0, 1.0},
	100.0
	};

materialStruct sphereMaterials = {
	{0.25, 0.25, 1.0, 1.0},
	{0.25, 0.25, 1.0, 1.0},
	{0.25, 0.25, 1.0, 1.0},
	50.0
	};

materialStruct pondMaterials = {
	{0.0, 0.0, 0.5, 1.0},
	{0.0, 0.0, 0.5, 1.0},
	{0.0, 0.0, 0.5, 1.0},
	0.0
	};

lightingStruct whiteLighting = {
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0}
	};

lightingStruct redLighting = {
	{1.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0}
	};

lightingStruct greenLighting = {
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0}
	};

lightingStruct blueLighting = {
	{0.0, 0.0, 1.0, 1.0},
	{0.0, 0.0, 1.0, 1.0},
	{0.0, 0.0, 1.0, 1.0}
	};

lightingStruct coloredLighting = {
	{1.0, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0}
	};

materialStruct *currentMaterials;
lightingStruct *currentLighting;

GLuint LoadTexture( const char * filename, int width, int height )
{
	GLuint texture;
    unsigned char * data;
    FILE * file;
	const char * mode = "rb";

    file = fopen( filename, mode );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); //generate the texture 
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successfull
}
void MPidle()
{
	bool bunnyOn, movingUp;
	duck.x += .25;
	if(duck.rotation > 360) duck.rotation = -duck.rotation;
	duck.rotation -= .25;
	duck.x -= .25;		

	if (sphereHit && redCubeHit && blueCubeHit)
	{
		newExplosion();//when all 3 are hit, make a new explosion and reset everything
		sphereHit = redCubeHit = blueCubeHit = false;
		bunny.x = -3.0;
		bunny.y = 0.0;
		bunny.z = -3.0;
		bunny.rotation = 135.0;
		dino.x = 2.0;
		dino.y = 0.0;
		dino.z = 2.0;
		dino.rotation = 135.0;
		duck.x = -1.0;
		duck.y = 0.0;
		duck.z = 0.0;
		duck.rotation = -45.0;
	}

	if (colors)
		glClearColor((double)rand()/(double)RAND_MAX,(double)rand()/(double)RAND_MAX,(double)rand()/(double)RAND_MAX, 1.0 );

	currentMaterials = &redCubeMaterials;
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	int i;
	if (fuel > 0)
	{
		for ( i = 0; i < NUM_PARTICLES; i++)
	    {
			particles[i].position[0] += particles[i].speed[0] * 0.02;
			particles[i].position[1] += particles[i].speed[1] * 0.02;
			particles[i].position[2] += particles[i].speed[2] * 0.02;
	      
			particles[i].color[0] -= 1.0 / 500.0;
			if (particles[i].color[0] < 0.0)
			{
				particles[i].color[0] = 0.0;
			}
	      
			particles[i].color[1] -= 1.0 / 100.0;
			if (particles[i].color[1] < 0.0)
			{
				particles[i].color[1] = 0.0;
			}
	      
			particles[i].color[2] -= 1.0 / 50.0;
	        if (particles[i].color[2] < 0.0)
			{
				particles[i].color[2] = 0.0;
			}
	    }
	  
		for (i = 0; i < NUM_DEBRIS; i++)
	    {
			debris[i].position[0] += debris[i].speed[0] * 0.01;
			debris[i].position[1] += debris[i].speed[1] * 0.01;
			debris[i].position[2] += debris[i].speed[2] * 0.01;
	      
			debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
			debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
			debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
	    }
	  
	  --fuel;
	}

	glutPostRedisplay();
}
void MPresetView()
{
    dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
    twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
    incAngle = -45.0f;
    azimAngle = 45.0f;
}
void MPprintMenu()
{
	cout << "Programming Assignment 3 "<< endl << endl;
	cout << "***************************" << endl;
	cout << "*    General Options      *: "<< endl;	
	cout << "***************************" << endl;
	cout << "F1: - Print help/menu"<< endl;
	cout << "0:  - switch between smooth/flat shading"<< endl;
	cout << "' ' space: - turn on KrAzY KoLoRz"<< endl;
	cout << "ESC: - exit the program"<< endl;
	cout << "***************************" << endl;
	cout << "*    Camera Controls      *: "<< endl;	
	cout << "***************************" << endl;
	cout << "Left click - Rotate/Look around"<< endl;
	cout << "Right click - Grab&move/Pan around"<< endl;
	cout << "Middle click - Open menu"<< endl;
	cout << "Scroll wheel - Zoom in/out"<< endl;
	cout << "***************************" << endl;
	cout << "*    Viewing Options      *: "<< endl;	
	cout << "***************************" << endl;
	cout << "f: - Front view "<< endl;
	cout << "b: - Back view "<< endl;
	cout << "r: - Right view )"<< endl;
	cout << "l: - Left view "<< endl;
	cout << "t: - Top view "<< endl;
	cout << "u: - Upper view "<< endl;
	cout << "i: - Isometric view (default)"<< endl;
	cout << "***************************" << endl;
	cout << "*    Lighting Options     *" << endl;
	cout << "***************************" << endl;
	cout << "1: - switch to white light"<< endl;
	cout << "2: - switch to colored light"<< endl;
	cout << "3: - switch to red light"<< endl;
	cout << "4: - switch to green light"<< endl;
	cout << "5: - switch to blue light"<< endl;
	cout << "***************************" << endl;
	cout << "*Lighting Position Options*" << endl;
	cout << "***************************" << endl;
	cout << "<<--: (left arrow) - adjust light position left"<< endl;
	cout << "-->>: (right arrow) - adjust light position right"<< endl;
}
void MPinit()
{
    /* set clear color to black */
    glClearColor(0.0, 0.0, 0.0, 0.0);	
	glLineWidth(2.0);
    /* enable the depth buffer */
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// near and far clip for distance
    nearClip = 1.0f;
    farClip = nearClip + 50.0f;

	MPresetView();
			
	curDuckTex = duckTex;
	curBunnyTex = bunnyTex;
	curDinoTex = dinoTex;
	curGroundTex = groundTex;
	curPondTex = pondTex;
	curCubeTex = cubeTex;
	curSphereTex = sphereTex;
	sphereHit = blueCubeHit = redCubeHit = false;
	
    createSphere(80,0,0,0);
	glPointSize(3.0);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[0]);
	
	currentLighting = &whiteLighting;

	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
}
void MPreshape(int width, int height)
{
    double aspect;

    glViewport(0, 0, width, height);

    /* compute aspect ratio */
    aspect = (double)width / (double)height;
    if (height > width) aspect = 1.0f;
    glMatrixMode(GL_PROJECTION);

    /* Reset world coordinates first ... */
    glLoadIdentity();

    /* Reset the viewing volume based on the new aspect ratio */
    gluPerspective(60.0f, aspect, nearClip, farClip);

    glMatrixMode(GL_MODELVIEW);
}
void MPflyCamera(float dist, float azimuth, float incidence, float twist)
{
    glTranslatef(0.0f, 0.0f, -dist);
    glRotatef(-twist, 0.0f, 0.0f, 1.0f);
    glRotatef(-incidence, 1.0f, 0.0f, 0.0f);
    glRotatef(-azimuth, 0.0f, 1.0f, 0.0f);
}
void MPdrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (view)
	{	
	case 1://isometric 
		MPresetView();
		break;
	case 2://front
			dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = -15.0f;
			azimAngle = 0.0f;
			break;
	case 3://back
			dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = -15.0f;
			azimAngle = 180.0f;
			break;
	case 4://right
			dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = -15.0f;
			azimAngle = 90.0f;
			break;
	case 5://left
			dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = -15.0f;
			azimAngle = -90.0f;
			break;
	case 6://top
			dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = -90.0f;
			azimAngle = 0.0f;
			break;
	case 7://bottom
			dist = (float)nearClip + (float)((farClip - nearClip) / 2.0);
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = 90.0f;
			azimAngle = 0.0f;
			break;
	case 8://middle looking front
			dist = 0.5;
			glTranslatef(0.0f, -dist, 0.0f);
			twistAngle = 180.0f;	/* rotation of viewing volume (camera) */
			incAngle = 180.0f;
			azimAngle = 0.0f;
			break;
	case 9://middle looking back-right
			dist = 0.5;
			glTranslatef(0.0f, -dist, 0.0f);
			twistAngle = 180.0f;	/* rotation of viewing volume (camera) */
			incAngle = 180.0f;
			azimAngle = -145.0f;
			break;
	case 10://middle looking back-left
			dist = 0.5;
			glTranslatef(0.0f, -dist, 0.0f);
			twistAngle = 180.0f;	/* rotation of viewing volume (camera) */
			incAngle = 180.0f;
			azimAngle = 145.0f;
			break;
	case 11://front looking middle
			dist = 6.0;
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = 0.0f;
			azimAngle = 0.0f;
			break;
	case 12://front looking back-right
			dist = 6.0;
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = 0.0f;
			azimAngle = -20.0f;
			break;
	case 13://front looking back-left
			dist = 6.0;
			twistAngle = 0.0f;	/* rotation of viewing volume (camera) */
			incAngle = 0.0f;
			azimAngle = 20.0f;
			break;
	}

    glPushMatrix();
    /* set up viewing transformation */
    MPflyCamera(dist, azimAngle, incAngle, twistAngle);
	
	if (fuel == 0)
    {
		collision();
	/******************************
	 *         FOUNTAIN           *
	 ******************************/	
	currentMaterials = &whiteShinyMaterials;
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	
	glPushMatrix();
		glTranslatef(-0.5, 0.0, 0.75);
		DrawFountain();
	glPopMatrix();
	
	/******************************
	 *           GROUND            *
	 ******************************/
    MPdrawGround();//draws floor, grid, pond, sphere and 2 cubes

	//draw the animals
		
		/******************************
		 *           BUNNY            *
		 ******************************/
	
		glPushMatrix();//bunny
			glTranslatef(bunny.x, bunny.y, bunny.z);
			glRotatef(bunny.rotation, 0.0, 1.0, 0.0);	

			currentMaterials = &bunnyMaterials;
			glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
			glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);

			MPbunny();
		glPopMatrix();
		
		/******************************
		 *           DUCK             *
		 ******************************/
		glPushMatrix();//duck
			glScalef(0.75, 0.75, 0.75);
			glTranslatef(duck.x, duck.y, duck.z);
			glRotatef(duck.rotation, 0.0, 1.0, 0.0);				
			glTranslatef(-duck.x,-duck.y, -duck.z);	

			currentMaterials = &duckMaterials;
			glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
			glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);

			MPduck();
		glPopMatrix();
		
		/******************************
		 *           DINO             *
		 ******************************/
		glPushMatrix();//dino
			glScalef(0.75, 0.75, 0.75);
			glTranslatef(dino.x, dino.y, dino.z);
			glRotatef(dino.rotation, 0.0, 1.0, 0.0);

			currentMaterials = &dinoMaterials;
			glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
			glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);

			MPdino();
		glPopMatrix();
	}
	
	/******************************
	 *         EXPLOSION          *
	 ******************************/	
	
	currentMaterials = &redCubeMaterials;
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	if (fuel > 0)
	{
		//translate to correct position
		glPushMatrix ();

			glBegin (GL_POINTS);
			for (i = 0; i < NUM_PARTICLES; i++)
			{
				glColor3fv (particles[i].color);
				glVertex3fv (particles[i].position);
			}  
			glEnd ();

		glPopMatrix ();

		glNormal3f (0.0, 0.0, 1.0);
		for (i = 0; i < NUM_DEBRIS; i++)
		{
			glColor3fv (debris[i].color);
			glPushMatrix ();
      
				glTranslatef (debris[i].position[0],
					debris[i].position[1],
					debris[i].position[2]);

				glRotatef (debris[i].orientation[0], 1.0, 0.0, 0.0);
				glRotatef (debris[i].orientation[1], 0.0, 1.0, 0.0);
				glRotatef (debris[i].orientation[2], 0.0, 0.0, 1.0);

				glScalef (debris[i].scale[0],
					debris[i].scale[1],
					debris[i].scale[2]);

				glBegin (GL_TRIANGLES);
				glVertex3f (0.0, 0.5, 0.0);
				glVertex3f (-0.25, 0.0, 0.0);
				glVertex3f (0.25, 0.0, 0.0);
				glEnd ();	  
	  
			glPopMatrix ();
		}
	}
	
    glPopMatrix();
	/******************************
	 *           LIGHT            *
	 ******************************/
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);

	glFlush();
    glutSwapBuffers();
}
void collision()
{
	//collision with the objects
	if (dino.x >= 4.5 && dino.z >= 4.5)
	{
		dino.x += -1.0;
		dino.z += -1.0;
		blueCubeHit = true;
	}
	if (dino.x >= 4.5 && dino.z <= -4.5)
	{
		dino.x += -1.0;
		dino.z += 1.0;
		redCubeHit = true;
	}
	if (dino.x <= -4.5 && dino.z >= 4.5)
	{
		dino.x += 1.0;
		dino.z += -1.0;
		sphereHit = true;
	}	

	// collision with fence
	if (dino.x >= 7.0)
	{
		fenceHit = true;
		dino.x += -1.0;
		glutPostRedisplay();
	}
	if (dino.x <= -7.0)
	{
		fenceHit = true;
		dino.x += 1.0;
		glutPostRedisplay();
	}
	if (dino.z >= 7.0)
	{
		fenceHit = true;
		dino.z += -1.0;
		glutPostRedisplay();
	}
	if (dino.z <= -7.0)
	{
		fenceHit = true;
		dino.z += 1.0;
		glutPostRedisplay();
	}

	if (dino.x >= -5.75 && dino.x <= 5.75 && dino.z >= -5.75 && dino.z <= 5.75)
	{		
		fenceHit = false;
	}
	glutPostRedisplay();	
}
void MPcreateMenu()
{	
	//set up menus
		viewingMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("Isometric view (default)", 11);
			glutAddMenuEntry("Front view", 12);
			glutAddMenuEntry("Back view", 13);
			glutAddMenuEntry("Right view", 14);
			glutAddMenuEntry("Left view", 15);
			glutAddMenuEntry("Top view", 16);
			glutAddMenuEntry("Under view", 17);
			glutAddMenuEntry("Middle looking front", 18);
			glutAddMenuEntry("Middle looking back-right", 19);
			glutAddMenuEntry("Middle looking back-left", 10);
			glutAddMenuEntry("Front looking middle", 111);
			glutAddMenuEntry("Front looking back-right", 112);
			glutAddMenuEntry("Front looking back-left", 113);
			
		colorSubMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("White Light", 21);
			glutAddMenuEntry("Colored Light", 22);
			glutAddMenuEntry("Red Light", 23);
			glutAddMenuEntry("Green Light", 24);
			glutAddMenuEntry("Blue Light", 24);

		positionSubMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("*Reset Light Position*", 31);
			glutAddMenuEntry("Front Top Right", 32);
			glutAddMenuEntry("Front Top Middle", 33);
			glutAddMenuEntry("Front Top Left", 34);
			glutAddMenuEntry("Left Top Front", 35);
			glutAddMenuEntry("Left Top Middle", 36);
			glutAddMenuEntry("Left Top back", 37);
			glutAddMenuEntry("Back Top Left", 38);
			glutAddMenuEntry("Back Top Middle", 39);
			glutAddMenuEntry("Back Top Right", 30);
			glutAddMenuEntry("Right Top Back", 311);
			glutAddMenuEntry("Right Top Middle", 312);
			glutAddMenuEntry("Right Top Frront", 313);

		angleSubMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("180 - large(default)", 41);
			glutAddMenuEntry("90 - medium ", 42);
			glutAddMenuEntry("60 - small", 43);
			glutAddMenuEntry("45 - smaller", 44);
			glutAddMenuEntry("30 - smallest", 45);

		texAllMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("Default", 51);
			glutAddMenuEntry("Troll", 52);
			glutAddMenuEntry("Checker", 53);
			glutAddMenuEntry("Dots", 54);
			glutAddMenuEntry("Stripes", 55);
		dinoTexMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("Default", 61);
			glutAddMenuEntry("Troll", 62);
			glutAddMenuEntry("Checker", 63);
			glutAddMenuEntry("Dots", 64);
			glutAddMenuEntry("Stripes", 65);
		duckTexMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("Default", 71);
			glutAddMenuEntry("Troll", 72);
			glutAddMenuEntry("Checker", 73);
			glutAddMenuEntry("Dots", 74);
			glutAddMenuEntry("Stripes", 75);
		bunnyTexMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("Default", 81);
			glutAddMenuEntry("Troll", 82);
			glutAddMenuEntry("Checker", 83);
			glutAddMenuEntry("Dots", 84);
			glutAddMenuEntry("Stripes", 85);
		groundTexMenu = glutCreateMenu(MPmenu);
			glutAddMenuEntry("Default", 91);
			glutAddMenuEntry("Troll", 92);
			glutAddMenuEntry("Checker", 93);
			glutAddMenuEntry("Dots", 94);
			glutAddMenuEntry("Stripes", 95);

		mainMenu = glutCreateMenu(MPmenu);
			glutAddSubMenu("Viewing", viewingMenu);
			glutAddSubMenu("Color", colorSubMenu);
			glutAddSubMenu("Position", positionSubMenu);
			glutAddSubMenu("Angle", angleSubMenu);
			glutAddSubMenu("Texture All", texAllMenu);
			glutAddSubMenu("Dino", dinoTexMenu);
			glutAddSubMenu("Duck", duckTexMenu);
			glutAddSubMenu("Bunny", bunnyTexMenu);
			glutAddSubMenu("Ground", groundTexMenu);

		glutAddMenuEntry("KrAzY KoLoRz", 1);
		glutAddMenuEntry("Toggle Lighting", 2);
		glutAddMenuEntry("Exit", 9);
		glutAttachMenu(GLUT_MIDDLE_BUTTON);
}
void MPmenu(int key)
{	
	switch (key)
	{	
		/****************************
		 *     View Sub-Menu        *
		 ****************************/
		case 11://isometric & default
			view = 1;
			break;
		case 12://front	
			view = 2;
			break;
		case 13://back
			view = 3;
			break;
		case 14://right
			view = 4;
			break;
		case 15://left
			view = 5;
			break;
		case 16://top
			view = 6;
			break;
		case 17://under
			view = 7;
			break;
		case 18://middle looking front
			view = 8;
			break;
		case 19://middle looking back-right
			view = 9;
			break;
		case 10://middle looking back-left
			view = 10;
			break;
		case 111://front looking middle
			view = 11;
			break;
		case 112://front looking back-right
			view = 12;
			break;
		case 113://front looking back-left
			view = 13;
			break;

			/****************************
			 *     Color Sub-Menu       *
			 ****************************/
		case 21://white light
			currentLighting = &whiteLighting;
			break;
		case 22://colored light
			currentLighting = &coloredLighting;
			break;
		case 23://red light
			currentLighting = &redLighting;
			break;
		case 24://green light
			currentLighting = &greenLighting;
			break;
		case 25://blue light
			currentLighting = &blueLighting;
			break;
			/****************************
			 * Light Position Sub-Menu  *
			 ****************************/
		case 31://reset light position			
			glLightfv(GL_LIGHT0, GL_POSITION, defaultLightPos);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[0]);
			break;
		case 32://front top right		
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[0]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[0]);
			break;
		case 33://front top middle				
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[1]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[1]);
			break;
		case 34://front top left				
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[2]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[2]);
			break;
		case 35://left top front		
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[3]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[3]);
			break;
		case 36://left top middle			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[4]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[4]);
			break;
		case 37://left top back			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[5]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[5]);
			break;
		case 38://back top left			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[6]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[6]);
			break;
		case 39://back top middle			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[7]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[7]);
			break;
		case 30://back top right			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[8]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[8]);
			break;
		case 311://right top back			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[9]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[9]);
			break;
		case 312://right top middle			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[10]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[10]);
			break;
		case 313://right top front			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[11]);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir[11]);
			break;
			
		/****************************
		 *  Light angle Sub-Menu    *
		 ****************************/
			
		case 41://large (default)			
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
			break;
		case 42://medium
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
			break;
		case 43://small			
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
			break;
		case 44://smaller	
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
			break;
		case 45://smallest		
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
			break;

		/****************************
		 *  Texture Sub-Menu    *
		 ****************************/
			//texture all
		case 51: //default
			curDuckTex = duckTex;
			curDinoTex = dinoTex;
			curBunnyTex = bunnyTex;
			curGroundTex = groundTex;
			curCubeTex = cubeTex;
			curSphereTex = sphereTex;
			break;
		case 52://troll
			curDuckTex = trollTex;
			curDinoTex = trollTex;
			curBunnyTex = trollTex;
			curGroundTex = trollTex;
			curCubeTex = trollTex;
			curSphereTex = trollTex;
			break;
		case 53://checkers
			curDuckTex = checkersTex;
			curDinoTex = checkersTex;
			curBunnyTex = checkersTex;
			curGroundTex = checkersTex;
			curCubeTex = checkersTex;
			curSphereTex = checkersTex;
			break;
		case 54://dots
			curDuckTex = dotsTex;
			curDinoTex = dotsTex;
			curBunnyTex = dotsTex;
			curGroundTex = dotsTex;
			curCubeTex = dotsTex;
			curSphereTex = dotsTex;
			break;
		case 55://stripes
			curDuckTex = stripesTex;
			curDinoTex = stripesTex;
			curBunnyTex = stripesTex;
			curGroundTex = stripesTex;
			curCubeTex = stripesTex;
			curSphereTex = stripesTex;
			break;		

				//dino textures
				case 61: //default
					curDinoTex = dinoTex;
					break;
				case 62://troll
					curDinoTex = trollTex;
					break;
				case 63://checkers
					curDinoTex = checkersTex;
					break;
				case 64://dots
					curDinoTex = dotsTex;
					break;
				case 65://stripes
					curDinoTex = stripesTex;
					break;
			
				//duck textures
				case 71: //default
					curDuckTex = duckTex;
					break;
				case 72://troll
					curDuckTex = trollTex;
					break;
				case 73://checkers
					curDuckTex = checkersTex;
					break;
				case 74://dots
					curDuckTex = dotsTex;
					break;
				case 75://stripes
					curDuckTex = stripesTex;
					break;

				//bunny textures			
				case 81: //default
					curBunnyTex = bunnyTex;
					break;
				case 82://troll
					curBunnyTex = trollTex;
					break;
				case 83://checkers
					curBunnyTex = checkersTex;
					break;
				case 84://dots
					curBunnyTex = dotsTex;
					break;
				case 85://stripes
					curBunnyTex = stripesTex;
					break;
			
				//ground textures
				case 91: //default
					curGroundTex = groundTex;
					break;
				case 92://troll
					curGroundTex = trollTex;
					break;
				case 93://checkers
					curGroundTex = checkersTex;
					break;
				case 94://dots
					curGroundTex = dotsTex;
					break;
				case 95://stripes
					curGroundTex = stripesTex;
					break;
			
			/****************************
			 *        Main Menu         *
			 ****************************/
		case 1:	// KrAzY KoLoRz 
			if( colors == 1)
				colors = 0;
			else
				colors = 1;
			if (colors == 0)
			{
				glClearColor(0.0, 0.0, 0.0, 1.0);
				curDuckTex = duckTex;
				curDinoTex = dinoTex;
				curBunnyTex = bunnyTex;
				curGroundTex = groundTex;
				curCubeTex = cubeTex;
				curSphereTex = sphereTex;
			}
			else
			{
				curDuckTex = trollTex;
				curDinoTex = trollTex;
				curBunnyTex = trollTex;
				curGroundTex = trollTex;
				curCubeTex = trollTex;
				curSphereTex = trollTex;
			}
			break;		
		case 2:	// toggle lighting
			lightsOn = !lightsOn;
			if (lightsOn)
				glEnable(GL_LIGHTING);
			else
				glDisable(GL_LIGHTING);
			break;
		case 9:	/* Exit when the Escape key is pressed */
			exit(0);
			break;
	}

	/******************************
	 *           LIGHT            *
	 ******************************/
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
	glutPostRedisplay();
}
void MPkeys(GLubyte key, int x, int y)
{
	int speed = 2;

	switch (key)
	{	
		/****************************
		 *     Lighting Controls    *
		 ****************************/
		case (GLubyte) '1'://white light
			currentLighting = &whiteLighting;
			break;
		case (GLubyte) '2'://colored light
			currentLighting = &coloredLighting;
			break;
		case (GLubyte) '3'://red light
			currentLighting = &redLighting;
			break;
		case (GLubyte) '4'://green light
			currentLighting = &greenLighting;
			break;
		case (GLubyte) '5'://blue light
			currentLighting = &blueLighting;
			break;
			
		/****************************
		 *     Viewing Controls     *
		 ****************************/
		case (GLubyte)'i'://isometric & default
			view = 1;
			break;
		case (GLubyte)'f'://front
			view = 2;
			break;
		case (GLubyte)'b'://back
			view = 3;
			break;
		case (GLubyte)'r'://right
			view = 4;
			break;
		case (GLubyte)'l'://left
			view = 5;
			break;
		case (GLubyte)'t'://top
			view = 6;
			break;
		case (GLubyte)'u'://under
			view = 7;
			break;
			
		/****************************
		 *     Misc. Controls       *
		 ****************************/
			
		case (GLubyte)'x'://change selected object
			newExplosion();
			break;
		case (GLubyte)'n'://change selected object
			t++;
			if (t > 2)
				t = 0;
			break;
		case (GLubyte)'0':	
			/* toggle between smooth and flat shading */
			if (flat == 0)
				flat = 1;
			else
				flat = 0;
			if (flat == 1)
				glShadeModel(GL_FLAT);
			else
				glShadeModel(GL_SMOOTH);
			break;
		case (GLubyte)' ':	// KrAzY KoLoRz 
			if( colors == 1)
				colors = 0;
			else
				colors = 1;
			if (colors == 0)
			{
				glClearColor(0.0, 0.0, 0.0, 1.0);
				curDuckTex = duckTex;
				curDinoTex = dinoTex;
				curBunnyTex = bunnyTex;
				curGroundTex = groundTex;
				curCubeTex = cubeTex;
				curSphereTex = sphereTex;
			}
			else
			{
				curDuckTex = trollTex;
				curDinoTex = trollTex;
				curBunnyTex = trollTex;
				curGroundTex = trollTex;
				curCubeTex = trollTex;
				curSphereTex = trollTex;
			}
			break;	
		case (GLubyte)KEY_ESC:	/* Exit when the Escape key is pressed */
			exit(0);
			break;
			
		/****************************
		 *     Movement Keys        *
		 ****************************/
		case (GLubyte)'z'://reset all positions
			fuel = 0;
			sphereHit = redCubeHit = blueCubeHit = false;
			bunny.x = -3.0;
			bunny.y = 0.0;
			bunny.z = -3.0;
			bunny.rotation = 135.0;
			dino.x = 2.0;
			dino.y = 0.0;
			dino.z = 2.0;
			dino.rotation = 135.0;
			duck.x = -1.0;
			duck.y = 0.0;
			duck.z = 0.0;
			duck.rotation = -45.0;
			break;
		case (GLubyte)'w'://move forward
				dino.z -= 0.25*speed;
			break;
		case (GLubyte)'s'://move back
				dino.z += 0.25*speed;
			break;
		case (GLubyte)'e'://move right
				dino.x += 0.25*speed;
			break;
		case (GLubyte)'q'://move left
				dino.x -= 0.25*speed;
			break;
		case (GLubyte)'a'://turn left
				dino.rotation += 2.0*speed;
			break;
		case (GLubyte)'d'://turn right
				dino.rotation -= 2.0*speed;
			break;
	}
	/******************************
	 *           LIGHT            *
	 ******************************/
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);

	glutPostRedisplay();
}
void specialkeys(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_F1:	/* Function key #1 */
			/* print help information */
			MPprintMenu();
			break;
		case GLUT_KEY_LEFT:	/* Left arrow key */
			if (i > 11) i = 0;
			i++;
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[i]);
			break;
		case GLUT_KEY_RIGHT:	/* Right arrow key */
			if (i < 0) i = 11;
			i--;
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos[i]);
			break;
	}
	glutPostRedisplay();
}
void MPmouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		action = 1;
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        action = 2;
    if(btn == 3)
	{
		dist -= (float)(1.0 + (y - yStart) / width);
		glutPostRedisplay();
	}
    if(btn== 4 )
	{
		dist += (float)(1.0 + (y - yStart) / width);
		glutPostRedisplay();
	}

        /* Update the saved mouse position */
    xStart = (float)x;
    yStart = (float)y;
	view = 0;
}
void MPmotion(int x, int y)
{
    if (action == 1)
    {
        azimAngle -= (float)(x - xStart);
        incAngle -= (float)(y - yStart);
	}
	if (action == 2)
	{
        glTranslatef(-(x - xStart)/5, (y - yStart)/5, 0.0);
	}

    /* Update the stored mouse position for later use */
    xStart = (float)x;
    yStart = (float)y;

    glutPostRedisplay();
}
void MPpond (float x_center, float y_center, float w, float h, int n)
{
	float theta, angle_increment;
	float x, z;	
	if (n <= 0)
		n = 1;

	angle_increment = (float)(3.14159*2) / n;

	//  draw the oval using triangle fan
	
	glBindTexture( GL_TEXTURE_2D, curPondTex);
	glEnable(GL_TEXTURE_2D);
	glNormal3f(0.0, 1.0, 0.0);	
	glBegin (GL_POLYGON);

	//  specify the center
	glVertex3f (0.0, (GLfloat)0.001, 0.0);
	
	for (theta = 0.0f; (theta - (3.14159*2)) < 0.001; theta += angle_increment)
	{
		x = w/2 * cos (theta);
		z = h/2 * sin (theta);
					
		glTexCoord2d(w/2 * cos (theta), h/2 * sin (theta));		glVertex3f(x, 0.0, z);
	}

	glEnd ();
	glDisable(GL_TEXTURE_2D);
}
void MPfence()	
{		
	/******************************
	 *           FRONT             *
	 ******************************/
	glBegin(GL_LINES);
			
		/******************************
		 *           VERTICAL         *
		 ******************************/
		glVertex3f(6.0, 0.0, 6.0);
		glVertex3f(6.0, 12.0, 6.0);
		
		glVertex3f(6.0, 0.0, 5.0);
		glVertex3f(6.0, 12.0, 5.0);
		
		glVertex3f(6.0, 0.0, 4.0);
		glVertex3f(6.0, 12.0, 4.0);
		
		glVertex3f(6.0, 0.0, 3.0);
		glVertex3f(6.0, 12.0, 3.0);

		glVertex3f(6.0, 0.0, 2.0);
		glVertex3f(6.0, 12.0, 2.0);
		
		glVertex3f(6.0, 0.0, 1.0);
		glVertex3f(6.0, 12.0, 1.0);

		glVertex3f(6.0, 0.0, 0.0);
		glVertex3f(6.0, 12.0, 0.0);
		
		glVertex3f(6.0, 0.0, -1.0);
		glVertex3f(6.0, 12.0, -1.0);

		glVertex3f(6.0, 0.0, -2.0);
		glVertex3f(6.0, 12.0, -2.0);
		
		glVertex3f(6.0, 0.0, -3.0);
		glVertex3f(6.0, 12.0, -3.0);

		glVertex3f(6.0, 0.0, -4.0);
		glVertex3f(6.0, 12.0, -4.0);
	
		glVertex3f(6.0, 0.0, -5.0);
		glVertex3f(6.0, 12.0, -5.0);
		
		glVertex3f(6.0, 0.0, -6.0);
		glVertex3f(6.0, 12.0, -6.0);

			
		/******************************
		 *           HORIZONTAL       *
		 ******************************/
		glVertex3f(6.0, 1.0, 6.0);
		glVertex3f(6.0, 1.0, -6.0);
		
		glVertex3f(6.0, 2.0, 6.0);
		glVertex3f(6.0, 2.0, -6.0);
		
		glVertex3f(6.0, 3.0, 6.0);
		glVertex3f(6.0, 3.0, -6.0);
		
		glVertex3f(6.0, 4.0, 6.0);
		glVertex3f(6.0, 4.0, -6.0);

		glVertex3f(6.0, 5.0, 6.0);
		glVertex3f(6.0, 5.0, -6.0);
		
		glVertex3f(6.0, 6.0, 6.0);
		glVertex3f(6.0, 6.0, -6.0);

		glVertex3f(6.0, 7.0, 6.0);
		glVertex3f(6.0, 7.0, -6.0);
		
		glVertex3f(6.0, 8.0, 6.0);
		glVertex3f(6.0, 8.0, -6.0);

		glVertex3f(6.0, 9.0, 6.0);
		glVertex3f(6.0, 9.0, -6.0);
		
		glVertex3f(6.0, 10.0, 6.0);
		glVertex3f(6.0, 10.0, -6.0);

		glVertex3f(6.0, 11.0, 6.0);
		glVertex3f(6.0, 11.0, -6.0);
	
		glVertex3f(6.0, 12.0, 6.0);
		glVertex3f(6.0, 12.0, -6.0);
	glEnd();
		
	/******************************
	 *           BACK             *
	 ******************************/
	glBegin(GL_LINES);
			
		/******************************
		 *           VERTICAL         *
		 ******************************/
		glVertex3f(6.0, 0.0, 6.0);
		glVertex3f(6.0, 12.0, 6.0);
		
		glVertex3f(5.0, 0.0, 6.0);
		glVertex3f(5.0, 12.0, 6.0);

		glVertex3f(4.0, 0.0, 6.0);
		glVertex3f(4.0, 12.0, 6.0);

		glVertex3f(3.0, 0.0, 6.0);
		glVertex3f(3.0, 12.0, 6.0);

		glVertex3f(2.0, 0.0, 6.0);
		glVertex3f(2.0, 12.0, 6.0);

		glVertex3f(1.0, 0.0, 6.0);
		glVertex3f(1.0, 12.0, 6.0);

		glVertex3f(0.0, 0.0, 6.0);
		glVertex3f(0.0, 12.0, 6.0);

		glVertex3f(-1.0, 0.0, 6.0);
		glVertex3f(-1.0, 12.0, 6.0);

		glVertex3f(-2.0, 0.0, 6.0);
		glVertex3f(-2.0, 12.0, 6.0);

		glVertex3f(-3.0, 0.0, 6.0);
		glVertex3f(-3.0, 12.0, 6.0);

		glVertex3f(-4.0, 0.0, 6.0);
		glVertex3f(-4.0, 12.0, 6.0);

		glVertex3f(-5.0, 0.0, 6.0);
		glVertex3f(-5.0, 12.0, 6.0);

		glVertex3f(-6.0, 0.0, 6.0);
		glVertex3f(-6.0, 12.0, 6.0);
		
			
		/******************************
		 *           HORIZONTAL       *
		 ******************************/
		glVertex3f(6.0, 1.0, 6.0);
		glVertex3f(-6.0, 1.0, 6.0);
		
		glVertex3f(6.0, 2.0, 6.0);
		glVertex3f(-6.0, 2.0, 6.0);

		glVertex3f(6.0, 3.0, 6.0);
		glVertex3f(-6.0, 3.0, 6.0);

		glVertex3f(6.0, 4.0, 6.0);
		glVertex3f(-6.0, 4.0, 6.0);

		glVertex3f(6.0, 5.0, 6.0);
		glVertex3f(-6.0, 5.0, 6.0);

		glVertex3f(6.0, 6.0, 6.0);
		glVertex3f(-6.0, 6.0, 6.0);

		glVertex3f(6.0, 7.0, 6.0);
		glVertex3f(-6.0, 7.0, 6.0);

		glVertex3f(6.0, 8.0, 6.0);
		glVertex3f(-6.0, 8.0, 6.0);

		glVertex3f(6.0, 9.0, 6.0);
		glVertex3f(-6.0, 9.0, 6.0);

		glVertex3f(6.0, 10.0, 6.0);
		glVertex3f(-6.0, 10.0, 6.0);

		glVertex3f(6.0, 11.0, 6.0);
		glVertex3f(-6.0, 11.0, 6.0);

		glVertex3f(6.0, 12.0, 6.0);
		glVertex3f(-6.0, 12.0, 6.0);
	glEnd();
		
	/******************************
	 *           LEFT             *
	 ******************************/
	glBegin(GL_LINES);
			
		/******************************
		 *           VERTICAL         *
		 ******************************/
		glVertex3f(-6.0, 0.0, 6.0);
		glVertex3f(-6.0, 12.0, 6.0);

		glVertex3f(-6.0, 0.0, 5.0);
		glVertex3f(-6.0, 12.0, 5.0);

		glVertex3f(-6.0, 0.0, 4.0);
		glVertex3f(-6.0, 12.0, 4.0);

		glVertex3f(-6.0, 0.0, 3.0);
		glVertex3f(-6.0, 12.0, 3.0);

		glVertex3f(-6.0, 0.0, 2.0);
		glVertex3f(-6.0, 12.0, 2.0);
		
		glVertex3f(-6.0, 0.0, 1.0);
		glVertex3f(-6.0, 12.0, 1.0);

		glVertex3f(-6.0, 0.0, 0.0);
		glVertex3f(-6.0, 12.0, 0.0);
		
		glVertex3f(-6.0, 0.0, -1.0);
		glVertex3f(-6.0, 12.0, -1.0);
		
		glVertex3f(-6.0, 0.0, -2.0);
		glVertex3f(-6.0, 12.0, -2.0);

		glVertex3f(-6.0, 0.0, -3.0);
		glVertex3f(-6.0, 12.0, -3.0);
		
		glVertex3f(-6.0, 0.0, -4.0);
		glVertex3f(-6.0, 12.0, -4.0);

		glVertex3f(-6.0, 0.0, -5.0);
		glVertex3f(-6.0, 12.0, -5.0);

		glVertex3f(-6.0, 0.0, -6.0);
		glVertex3f(-6.0, 12.0, -6.0);

			
		/******************************
		 *           HORIZONTAL       *
		 ******************************/		
		glVertex3f(-6.0, 1.0, 6.0);
		glVertex3f(-6.0, 1.0, -6.0);

		glVertex3f(-6.0, 2.0, 6.0);
		glVertex3f(-6.0, 2.0, -6.0);

		glVertex3f(-6.0, 3.0, 6.0);
		glVertex3f(-6.0, 3.0, -6.0);

		glVertex3f(-6.0, 4.0, 6.0);
		glVertex3f(-6.0, 4.0, -6.0);

		glVertex3f(-6.0, 5.0, 6.0);
		glVertex3f(-6.0, 5.0, -6.0);
		
		glVertex3f(-6.0, 6.0, 6.0);
		glVertex3f(-6.0, 6.0, -6.0);

		glVertex3f(-6.0, 7.0, 6.0);
		glVertex3f(-6.0, 7.0, -6.0);
		
		glVertex3f(-6.0, 8.0, 6.0);
		glVertex3f(-6.0, 8.0, -6.0);
		
		glVertex3f(-6.0, 9.0, 6.0);
		glVertex3f(-6.0, 9.0, -6.0);

		glVertex3f(-6.0, 10.0, 6.0);
		glVertex3f(-6.0, 10.0, -6.0);
		
		glVertex3f(-6.0, 11.0, 6.0);
		glVertex3f(-6.0, 11.0, -6.0);

		glVertex3f(-6.0, 12.0, 6.0);
		glVertex3f(-6.0, 12.0, -6.0);

	glEnd();
		
	/******************************
	 *           RIGHT            *
	 ******************************/
	glBegin(GL_LINES);
			
		/******************************
		 *           VERTICAL         *
		 ******************************/
		glVertex3f(-6.0, 0.0, -6.0);
		glVertex3f(-6.0, 12.0, -6.0);

		glVertex3f(-5.0, 0.0, -6.0);
		glVertex3f(-5.0, 12.0, -6.0);

		glVertex3f(-4.0, 0.0, -6.0);
		glVertex3f(-4.0, 12.0, -6.0);

		glVertex3f(-3.0, 0.0, -6.0);
		glVertex3f(-3.0, 12.0, -6.0);

		glVertex3f(-2.0, 0.0, -6.0);
		glVertex3f(-2.0, 12.0, -6.0);
	
		glVertex3f(-1.0, 0.0, -6.0);
		glVertex3f(-1.0, 12.0, -6.0);

		glVertex3f(0.0, 0.0, -6.0);
		glVertex3f(0.0, 12.0, -6.0);
		
		glVertex3f(1.0, 0.0, -6.0);
		glVertex3f(1.0, 12.0, -6.0);
		
		glVertex3f(2.0, 0.0, -6.0);
		glVertex3f(2.0, 12.0, -6.0);

		glVertex3f(3.0, 0.0, -6.0);
		glVertex3f(3.0, 12.0, -6.0);
		
		glVertex3f(4.0, 0.0, -6.0);
		glVertex3f(4.0, 12.0, -6.0);

		glVertex3f(5.0, 0.0, -6.0);
		glVertex3f(5.0, 12.0, -6.0);

		glVertex3f(6.0, 0.0, -6.0);
		glVertex3f(6.0, 12.0, -6.0);

			
		/******************************
		 *           HORIZONTAL       *
		 ******************************/		
		glVertex3f(-6.0, 1.0, -6.0);
		glVertex3f(6.0, 1.0, -6.0);

		glVertex3f(-6.0, 2.0, -6.0);
		glVertex3f(6.0, 2.0, -6.0);

		glVertex3f(-6.0, 3.0, -6.0);
		glVertex3f(6.0, 3.0, -6.0);

		glVertex3f(-6.0, 4.0, -6.0);
		glVertex3f(6.0, 4.0, -6.0);

		glVertex3f(-6.0, 5.0, -6.0);
		glVertex3f(6.0, 5.0, -6.0);
		
		glVertex3f(-6.0, 6.0, -6.0);
		glVertex3f(6.0, 6.0, -6.0);

		glVertex3f(-6.0, 7.0, -6.0);
		glVertex3f(6.0, 7.0, -6.0);
		
		glVertex3f(-6.0, 8.0, -6.0);
		glVertex3f(6.0, 8.0, -6.0);
		
		glVertex3f(-6.0, 9.0, -6.0);
		glVertex3f(6.0, 9.0, -6.0);

		glVertex3f(-6.0, 10.0, -6.0);
		glVertex3f(6.0, 10.0, -6.0);
		
		glVertex3f(-6.0, 11.0, -6.0);
		glVertex3f(6.0, 11.0, -6.0);

		glVertex3f(-6.0, 12.0, -6.0);
		glVertex3f(6.0, 12.0, -6.0);
		
	glEnd();
}
void MPgrid()
{		
	/******************************
	 *           HORIZONTAL       *
	 ******************************/
	glBegin(GL_LINES);
		glVertex3f(-6.0, 0.0, 6.0);
		glVertex3f(6.0, 0.0, 6.0);

		glVertex3f(-6.0, 0.0, 5.0);
		glVertex3f(6.0, 0.0, 5.0);

		glVertex3f(-6.0, 0.0, 4.0);
		glVertex3f(6.0, 0.0, 4.0);

		glVertex3f(-6.0, 0.0, 3.0);
		glVertex3f(6.0, 0.0, 3.0);

		glVertex3f(-6.0, 0.0, 2.0);
		glVertex3f(6.0, 0.0, 2.0);

		glVertex3f(-6.0, 0.0, 1.0);
		glVertex3f(6.0, 0.0, 1.0);

		glVertex3f(-6.0, 0.0, 0.0);
		glVertex3f(6.0, 0.0, 0.0);

		glVertex3f(-6.0, 0.0, -1.0);
		glVertex3f(6.0, 0.0, -1.0);

		glVertex3f(-6.0, 0.0, -2.0);
		glVertex3f(6.0, 0.0, -2.0);

		glVertex3f(-6.0, 0.0, -3.0);
		glVertex3f(6.0, 0.0, -3.0);

		glVertex3f(-6.0, 0.0, -4.0);
		glVertex3f(6.0, 0.0, -4.0);

		glVertex3f(-6.0, 0.0, -5.0);
		glVertex3f(6.0, 0.0, -5.0);

		glVertex3f(-6.0, 0.0, -6.0);
		glVertex3f(6.0, 0.0, -6.0);
	glEnd();
		
	/******************************
	 *           VERTICAL         *
	 ******************************/
	glBegin(GL_LINES);
		glVertex3f(6.0, 0.0, -6.0);
		glVertex3f(6.0, 0.0, 6.0);

		glVertex3f(5.0, 0.0, -6.0);
		glVertex3f(5.0, 0.0, 6.0);

		glVertex3f(4.0, 0.0, -6.0);
		glVertex3f(4.0, 0.0, 6.0);

		glVertex3f(3.0, 0.0, -6.0);
		glVertex3f(3.0, 0.0, 6.0);

		glVertex3f(2.0, 0.0, -6.0);
		glVertex3f(2.0, 0.0, 6.0);

		glVertex3f(1.0, 0.0, -6.0);
		glVertex3f(1.0, 0.0, 6.0);

		glVertex3f(0.0, 0.0, -6.0);
		glVertex3f(0.0, 0.0, 6.0);

		glVertex3f(-1.0, 0.0, -6.0);
		glVertex3f(-1.0, 0.0, 6.0);

		glVertex3f(-2.0, 0.0, -6.0);
		glVertex3f(-2.0, 0.0, 6.0);

		glVertex3f(-3.0, 0.0, -6.0);
		glVertex3f(-3.0, 0.0, 6.0);

		glVertex3f(-4.0, 0.0, -6.0);
		glVertex3f(-4.0, 0.0, 6.0);

		glVertex3f(-5.0, 0.0, -6.0);
		glVertex3f(-5.0, 0.0, 6.0);

		glVertex3f(-6.0, 0.0, -6.0);
		glVertex3f(-6.0, 0.0, 6.0);
	glEnd();
}
void MPcube()
{		
	glBindTexture( GL_TEXTURE_2D, curCubeTex);
	glEnable(GL_TEXTURE_2D);
	/******************************
	 *           RIGHT            *
	 ******************************/
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(1.0, -1.0, 1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(1.0, -1.0, -1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(1.0, 1.0, -1.0);
	glEnd();
		
	/******************************
	 *           FRONT            *
	 ******************************/
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-1.0, 1.0, 1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(-1.0, -1.0, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(1.0, -1.0, 1.0);
	glEnd();
		
	/******************************
	 *           TOP              *
	 ******************************/
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-1.0, 1.0, 1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(-1.0, 1.0, -1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(1.0, 1.0, -1.0);
	glEnd();
		
	/******************************
	 *           BOTTOM           *
	 ******************************/
	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(-1.0, -1.0, -1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-1.0, -1.0, 1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(1.0, -1.0, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
		
	/******************************
	 *           BACK             *
	 ******************************/
	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(1.0, 1.0, -1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-1.0, 1.0, -1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(-1.0, -1.0, -1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
		
	/******************************
	 *           LEFT             *
	 ******************************/
	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(-1.0, -1.0, -1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-1.0, 1.0, -1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(-1.0, 1.0, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void newSpeed (float dest[3])
{
	float    x;
	float    y;
	float    z;
	float    len;

	x = ((2.2 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0);
	y = ((2.2 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0);
	z = ((2.2 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0);

	/*
	* Normalizing the speed vectors gives a "fireball" effect
	*
	*/

	len = sqrt (x * x + y * y + z * z);

	if (len)
	{
		x = x / len;
		y = y / len;
		z = z / len;
	}

	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}
void newExplosion (void)
{
  int    i;

  for (i = 0; i < NUM_PARTICLES; i++)
    {
      particles[i].position[0] = 0.0;
      particles[i].position[1] = 0.0;
      particles[i].position[2] = 0.0;

      particles[i].color[0] = 1.0;
      particles[i].color[1] = 1.0;
      particles[i].color[2] = 0.5;

      newSpeed (particles[i].speed);
    }

  for (i = 0; i < NUM_DEBRIS; i++)
    {
      debris[i].position[0] = 0.0;
      debris[i].position[1] = 0.0;
      debris[i].position[2] = 0.0;

      debris[i].orientation[0] = 0.0;
      debris[i].orientation[1] = 0.0;
      debris[i].orientation[2] = 0.0;

      debris[i].color[0] = 0.7;
      debris[i].color[1] = 0.7;
      debris[i].color[2] = 0.7;

      debris[i].scale[0] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      debris[i].scale[1] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      debris[i].scale[2] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

      newSpeed (debris[i].speed);
      newSpeed (debris[i].orientationSpeed);
    }
  
  fuel = 5000;
}
GLfloat GetRandomFloat(GLfloat range)
{
	return (GLfloat)rand() / (GLfloat)RAND_MAX * range * RandomFactor;
}
void InitFountain(void)
{
	//This function needn't be and isn't speed optimized
	FountainDrops = new CDrop [ DropsComplete ];
	FountainVertices = new SVertex [ DropsComplete ];
	SVertex NewSpeed;
	GLfloat DropAccFactor; //different from AccFactor because of the random change
	GLfloat TimeNeeded;
	GLfloat StepAngle; //Angle, which the ray gets out of the fountain with
	GLfloat RayAngle;	//Angle you see when you look down on the fountain
	GLint i,j,k;
	for (k = 0; k <Steps; k++)
	{
		for (j = 0; j < RaysPerStep; j++)
		{
			for (i = 0; i < DropsPerRay; i++)
			{
				DropAccFactor = AccFactor + GetRandomFloat(0.0005);
				StepAngle = AngleOfDeepestStep + (90.0-AngleOfDeepestStep) 
						* GLfloat(k) / (Steps-1) + GetRandomFloat(0.2+0.8*(Steps-k-1)/(Steps-1));
				//This is the speed caused by the step:
				NewSpeed.x = cos ( StepAngle * PI / 180.0) * (0.2+0.04*k);
				NewSpeed.y = sin ( StepAngle * PI / 180.0) * (0.2+0.04*k);
				//This is the speed caused by the ray:
	
				RayAngle = (GLfloat)j / (GLfloat)RaysPerStep * 360.0;
				//for the next computations "NewSpeed.x" is the radius. Care! Dont swap the two
				//lines, because the second one changes NewSpeed.x!
				NewSpeed.z = NewSpeed.x * sin ( RayAngle * PI /180.0);
				NewSpeed.x = NewSpeed.x * cos ( RayAngle * PI /180.0);
				
				//Calculate how many steps are required, that a drop comes out and falls down again
				TimeNeeded = NewSpeed.y/ DropAccFactor;
				FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetConstantSpeed ( NewSpeed );
				FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetAccFactor (DropAccFactor);
				FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetTime(TimeNeeded * i / DropsPerRay);
			}
		}
	}


	//Tell OGL that we'll use the vertex array function
	glEnableClientState(GL_VERTEX_ARRAY);
	//Pass the date position
	glVertexPointer(	3,			//x,y,z-components
						GL_FLOAT,	//data type of SVertex
						0,			//the vertices are tightly packed
						FountainVertices);				
}
void DrawFountain(void)
{
	glColor4f(0.8,0.8,0.8,0.8);
	for (int i = 0; i < DropsComplete; i++)
	{
		FountainDrops[i].GetNewPosition(&FountainVertices[i]);
	}
	glDrawArrays(	GL_POINTS,
					0,
					DropsComplete);
}
void displaySphere (double R, GLuint texture)
{
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int b;
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);
    //glRotatef (90, 1, 0, 0);
    glBindTexture (GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
    glBegin (GL_TRIANGLE_STRIP);
    for ( b = 0; b <VertexCount; b++)
    {
        glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
    }	
	for ( b = 0; b <VertexCount; b++)
	{
		glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);
		glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
	}
    glEnd();
	glDisable(GL_TEXTURE_2D);
}
void createSphere (double R, double H, double K, double Z) 
{
    int n;
    double a;
    double b;
    n = 0;
	for( b = 0; b <= 90 - space; b+=space)
	{
		for( a = 0; a <= 360 - space; a+=space)
		{
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a) / 360;

			n++;
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * (b + space)) / 360;
			VERTEX[n].U = (a) / 360;
			n++;
			VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;
			VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) /180 * PI) - H;
			VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) /180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * (b + space)) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;
		}
}
}
void MPbunny()
{		
	glBindTexture( GL_TEXTURE_2D, curBunnyTex);
	glEnable(GL_TEXTURE_2D);
	/******************************
	 *           RIGHT            *
	 ******************************/
	

	glColor3f(1.0, (GLfloat)0.85, (GLfloat)0.85);//pink
	glNormal3f(1.5, -0.75, -0.25);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(-0.5, 0.0, 0.0);		
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.75, 0.75);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.0, 1.25, -0.75);
		glTexCoord2d(0.0,1.0);	glVertex3f(-0.5, 0.0, -1.5);
	glEnd();
		
	/******************************
	 *           LEFT             *
	 ******************************/
	glNormal3f(-1.875, -0.75, 0.0);
	glBegin(GL_POLYGON); 		
		glTexCoord2d(0.0,0.0);	glVertex3f(0.5, 0.0, 0.0);		
		glTexCoord2d(1.0,0.0);	glVertex3f(0.5, 0.0, -1.5);		
		glTexCoord2d(1.0,1.0);	glVertex3f(0.0, 1.25, -0.75);		
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 0.75, 0.75);
	glEnd();
		
	/******************************
	 *           HEAD             *
	 ******************************/
	glColor3f(1.0, 0.5, 0.5);
	glNormal3f(-1.3125, -0.5, -0.375);
	glBegin(GL_TRIANGLES);		
		glTexCoord2d(0.0,0.0);	glVertex3f(0.5, 0.0, 0.0);		
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.75, 0.75);		
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.5, -0.25);
	glEnd();
	glNormal3f(1.3125, -0.5, -0.375);
	glBegin(GL_TRIANGLES);		
		glTexCoord2d(0.0,0.0);	glVertex3f(-0.5, 0.0, 0.0);		
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.75, 0.75);		
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.5, -0.25);
	glEnd();
		
	/******************************
	 *           TAIL             *
	 ******************************/
	glColor3f(1.0, 0.75, 0.75);
	glNormal3f((GLfloat)0.45, (GLfloat)0.1125, (GLfloat)0.225);
	glBegin(GL_TRIANGLES);		
		glTexCoord2d(0.0,0.0);	glVertex3f((GLfloat)0.15, (GLfloat)0.75, (GLfloat)-0.85);		
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 1.5, -1.0);		
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 0.75, -0.25);
	glEnd();
	glNormal3f((GLfloat)0.45, (GLfloat)-0.1125, (GLfloat)-0.225);
	glBegin(GL_TRIANGLES);		
		glTexCoord2d(0.0,0.0);	glVertex3f((GLfloat)-0.15, (GLfloat)0.75, (GLfloat)-0.85);		
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 1.5, -1.0);		
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 0.75, -0.25);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}
void MPdino()
{   	
	glBindTexture( GL_TEXTURE_2D, curDinoTex);
	glEnable(GL_TEXTURE_2D);
	/******************************
	 *           BODY             *
	 ******************************/
	

	glColor3f(0.5, 0.5, 1.0);//blue
	glNormal3f(1.5, -0.5625, 0.0625);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.25, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.25, 1.0, 1.75);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.5, 1.5, 0.25);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.25, -3.0);
	glEnd();	
	glNormal3f(-1.5, -0.5625, 0.0625);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.25, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(-0.25, 1.0, 1.75);
		glTexCoord2d(1.0,1.0);	glVertex3f(-0.5, 1.5, 0.25);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.25, -3.0);
	glEnd();

	/******************************
	 *           NECK             *
	 ******************************/
	glColor3f(0.25, 0.25, 1.0);
	glNormal3f(-1.125, 0.03125, 0.34375);
	glBegin(GL_POLYGON); 
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.25, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.25, 1.0, 1.75);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.125, 2.0, 1.25);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 1.75, 1.0);
	glEnd();
	glNormal3f(-1.125, -0.03125, -0.34375);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.25, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(-0.25, 1.0, 1.75);
		glTexCoord2d(1.0,1.0);	glVertex3f(-0.125, 2.0, 1.25);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 1.75, 1.0);
	glEnd();
		
	/******************************
	 *           HEAD             *
	 ******************************/
	glColor3f(0.75, 0.75, 1.0);
	glNormal3f(-0.53125, 0.09375, 0.0);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 1.75, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.75, 1.75);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.125, 2.0, 1.25);
	glEnd();
	glNormal3f(-0.53125, -0.09375, 0.0);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 1.75, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.75, 1.75);
		glTexCoord2d(1.0,0.0);	glVertex3f(-0.125, 2.0, 1.25);
	glEnd();
		
	/******************************
	 *           WINGS            *
	 ******************************/
	glColor3f(0.75, 0.75, 1.0);
	glNormal3f(-2.625, -2.6875, 1.4375);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.25, -3.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.5, 1.5, 0.25);
		glTexCoord2d(1.0,0.0);	glVertex3f(1.25, 0.5, -0.25);
	glEnd();
	glNormal3f(2.625, -2.6875, 1.4375);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.25, -3.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(-1.25, 0.5, -0.25);
		glTexCoord2d(1.0,0.0);	glVertex3f(-0.5, 1.5, 0.25);
	glEnd();
		
	/******************************
	 *           FEET             *
	 ******************************/
	glColor3f(0.25, 0.25, 1.0);
	glNormal3f(0.125, 0.0, 0.0);
	glBegin(GL_POLYGON); 
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 0.25, 0.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.0, 0.25, 0.5);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.0, 0.5);
	glEnd();
	glNormal3f(-0.125, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, -1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 0.25, -1.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.0, 0.25, -1.5);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.0, 0.0, -1.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void MPduck()
{
		
	glBindTexture( GL_TEXTURE_2D, curDuckTex);
	glEnable(GL_TEXTURE_2D);

	/******************************
	 *           RIGHT             *
	 ******************************/
	glColor3f(0.5, 1.0, 0.5);   // green
	glNormal3f(-0.75, -0.375, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-0.25, 0.5, 1.25);
		glTexCoord2d(1.0,1.0);	glVertex3f(-0.5, 1.0, 0.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(-0.25, 0.5, -1.25);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, -1.0);
	glEnd();
		
	/******************************
	 *           LEFT             *
	 ******************************/
	glNormal3f(-0.75, 0.375, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.25, 0.5, 1.25);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.5, 1.0, 0.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.25, 0.5, -1.25);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, -1.0);
	glEnd();
		
	/******************************
	 *           TAIL             *
	 ******************************/
	glColor3f(0.25, 1.0, 0.25);
	glNormal3f(0.3125, 0.0, -0.3125);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, -1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-0.25, 0.5, -1.25);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.25, -1.0);
	glEnd();
	glNormal3f(0.3125, 0.0, 0.3125);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, -1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.25, 0.5, -1.25);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.25, -1.0);
	glEnd();
		
	/******************************
	 *           NECK             *
	 ******************************/
	glColor3f(0.75, 1.0, 0.75);
	glNormal3f(-0.375, 0.03125, 0.3125);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.25, 0.5, 1.25);
		glTexCoord2d(1.0,1.0);	glVertex3f(0.125, 1.5, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.25, 0.75);
	glEnd();
	glNormal3f(-0.375, -0.03125, -0.3125);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(-0.25, 0.5, 1.25);
		glTexCoord2d(1.0,1.0);	glVertex3f(-0.125, 1.5, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.25, 0.75);
	glEnd();
		
	/******************************
	 *           BEAK             *
	 ******************************/
	glColor3f(0.25, 1.0, 0.25);
	glNormal3f(0.1875, -0.09375, 0.0);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 1.25, 0.75);
		glTexCoord2d(1.0,0.0);	glVertex3f(0.125, 1.5, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.25, 1.5);
	glEnd();
	glNormal3f(0.1875, 0.09375, 0.0);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0,0.0);	glVertex3f(0.0, 1.25, 0.75);
		glTexCoord2d(1.0,0.0);	glVertex3f(-0.125, 1.5, 1.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(0.0, 1.25, 1.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void MPdrawGround()
{	
	/******************************
	 *           GRID             *
	 ******************************/

	glColor3f(0.0, 0.0, 0.0);//black
		currentMaterials = &blackShinyMaterials;
		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	MPgrid();
	
	/******************************
	 *           FENCE            *
	 ******************************/
	glColor3f(1.0, 1.0, 1.0);//white

		if (fenceHit)
			currentMaterials = &fenceMaterials;
		else
			currentMaterials = &whiteShinyMaterials;
		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	MPfence();
	
	/******************************
	 *           POND             *
	 ******************************/
	glColor3f(0.75, 0.75, 1.0);//blue
		currentMaterials = &pondMaterials;
		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	glPushMatrix();
		glRotatef(-45.0, 0.0, 1.0, 0.0);
		glTranslatef(-0.5, (GLfloat)0.01, 0.75);
		MPpond(0.0, 0.0, 3.0, 4.0, 50);
	glPopMatrix();

	/******************************
	 *           TOP              *
	 ******************************/
	glColor3f(0.0, 0.5, 0.0);//green		
		currentMaterials = &groundMaterials;
		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);	
		
	glBindTexture( GL_TEXTURE_2D, curGroundTex);
	glEnable(GL_TEXTURE_2D);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glTexCoord2d(0.0,0.0);	glVertex3f(6.0, 0.0, 6.0);
		glTexCoord2d(1.0,0.0);	glVertex3f(6.0, 0.0, -6.0);
		glTexCoord2d(1.0,1.0);	glVertex3f(-6.0, 0.0, -6.0);
		glTexCoord2d(0.0,1.0);	glVertex3f(-6.0, 0.0, 6.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	/******************************
	 *           BOTTOM           *
	 ******************************/
	glColor3f(0.0, 0.0, 0.0);//black
		currentMaterials = &blackShinyMaterials;
		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess); 
	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(6.0, (GLfloat)-0.001, 6.0);
		glVertex3f(-6.0, (GLfloat)-0.001, 6.0);
		glVertex3f(-6.0, (GLfloat)-0.001, -6.0);
		glVertex3f(6.0, (GLfloat)-0.001, -6.0);
	glEnd();
	
	/******************************
	 *           SPHERE           *
	 ******************************/
	glColor3f(0.0, 0.0, 1.0);//blue

		if (sphereHit)
			currentMaterials = &selectedMaterials;
		else
			currentMaterials = &sphereMaterials;

		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	glPushMatrix();
		glTranslatef(-5.0, 1.0, 5.0);
		displaySphere(1.0, curSphereTex);
	glPopMatrix();
	
	/******************************
	 *           BLUE CUBE        *
	 ******************************/
	glBindTexture( GL_TEXTURE_2D, curCubeTex);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 1.0);//blue

		if (blueCubeHit)
			currentMaterials = &selectedMaterials;
		else
			currentMaterials = &blueCubeMaterials;

		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	glPushMatrix();
		glTranslatef(5.0, 1.0, 5.0);
		MPcube();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	/******************************
	 *           RED CUBE         *
	 ******************************/
	glBindTexture( GL_TEXTURE_2D, curCubeTex);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 0.0, 0.0);//red

		if (redCubeHit)
			currentMaterials = &selectedMaterials;
		else
			currentMaterials = &redCubeMaterials;

		glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
	glPushMatrix();
		glTranslatef(5.0, 1.0, -5.0);
		MPcube();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void main(int argc, char **argv)
{
	srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	width = glutGet(GLUT_SCREEN_WIDTH);
    height = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition(width / 4, height / 4);
    glutInitWindowSize(width / 2, height / 2);
    glutCreateWindow("Phillips - JURASSIC PARK - v.4");
	InitFountain();
    glutReshapeFunc(MPreshape);
    glutDisplayFunc(MPdrawScene);
	glutIdleFunc(MPidle);
    glutMouseFunc(MPmouse);
	glutMotionFunc(MPmotion);
	glutKeyboardFunc(MPkeys);
	glutSpecialFunc(specialkeys);
	MPprintMenu();
	MPcreateMenu();

    pondTex = LoadTexture( "water.bmp" , 256, 256 );
    bunnyTex = LoadTexture( "bunny.bmp" , 256, 256 );
    dinoTex = LoadTexture( "dino.bmp" , 256, 256 );
    duckTex = LoadTexture( "duck.bmp" , 256, 256 );
    groundTex = LoadTexture( "grass.bmp" , 256, 256 );
    cubeTex = LoadTexture( "brick.bmp" , 256, 256 );
    sphereTex = LoadTexture( "beachball.bmp" , 256, 256 );
	
    stripesTex = LoadTexture( "stripes.bmp" , 256, 256 );
    dotsTex = LoadTexture( "dots.bmp" , 256, 256 );
    trollTex = LoadTexture( "troll.bmp" , 256, 256 );
    checkersTex = LoadTexture( "checker.bmp" , 256, 256 );

	MPinit();		
	
    glutMainLoop();
}
