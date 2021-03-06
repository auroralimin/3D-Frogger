#ifndef CORE_H
#define CORE_H

#include <math.h>
#include <stdbool.h>

#define REDUCTION 25
#define GRID_WIDTH 25
#define GRID_HEIGHT 25
#define CYLINDER_RADIUS 1.5
#define CYLINDER_HEIGHT 8
#define S_RADIUS 0.5
#define CUBE_LENGTH 2
#define LINE_WIDTH 4
#define LINE_OBSTACLES 6
#define OBSTACLE_SIZE 5
#define INTERVAL_SIZE 1
#define GRASS_SIZE 7
#ifndef M_PI
#define M_PI 3.14159265359
#endif
#define UNUSED_VAR (void)

typedef struct{
	float x, y, z;
	float r, theta, phi;
	float dx, dy, dz;
} projection;

typedef struct {
	projection r0, r;
	bool onLog;
	int logDirection;
} frogState;

typedef struct vertex2
{
	float x, y;
} vertex2;

typedef struct {
	float x, y, z;
} vertex;

void resetGame(void);
void resetPerformance(void);
void setProjectionMatrix(void);
void setupCamera(void);
void drawText(char *text, float x, float y, float z, void *font);
void calculatePerformance(void);
void incFrameCount(void);
void setSegments(int newSegments);
void setScore(int newScore);
void setLifes(int newLifes);
void setWidth(int newWidth);
void setHeight(int newHeight);
void setRotateCamTheta(float newRotateCamTheta);
void setRotateCamPhi(float newRotateCamPhi);
void setCamZoom(float newCamZoom);
void updateCartesian(projection *p);
void updateSpherical(projection *p);
void switchDebug(void);
void switchGameMode(void);
void switchPause(void);
void switchCartesianFlag(void);
void switchNormalFlag(void);
void switchWireFlag(void);
void switchAxesFlag(void);
void switchLightFlag(void);
void switchTextureFlag(void);
void switchVerletFlag(void);
void setGameOver(bool flag);
void setJumpingFlag(bool flag);
int getSegments(void);
int getScore(void);
int getLifes(void);
int getWidth(void);
int getHeight(void);
int getFps(void);
int getFrameDuration(void);
float getRotateCamTheta(void);
float getRotateCamPhi(void);
float getCamZoom(void);
bool getDebug(void);
bool getPause(void);
bool getGameMode(void);
bool getCartesianFlag(void);
bool getNormalFlag(void);
bool getWireFlag(void);
bool getAxesFlag(void);
bool getLightFlag(void);
bool getTextureFlag(void);
bool getVerletFlag(void);
bool getGameOver(void);
bool getJumpingFlag(void);

extern frogState frog;
extern vertex cars[OBSTACLE_SIZE][LINE_OBSTACLES];
extern vertex logs[OBSTACLE_SIZE][LINE_OBSTACLES];

#endif

