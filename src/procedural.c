#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glut.h>

#include "procedural.h"
#include "core.h"
#include "geometry.h"

#define RAND(min, max) ((rand()%(int)((max+1)-min)) + min)
#define V_CARS 0.1
#define V_LOGS 0.03

vertex randVertex(vertex *array, vertex lenght, int zMin, int zMax, int index);

vertex cars[20];

void initCars(void)
{
	vertex length = {CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH};
	for (int i = 0; i < 20; i++)
	{
		cars[i] = randVertex(cars, length, 30, 45, i);
		if (getDebug())
			printf("randCar=(%.0f, %.0f, %.0f)\n",
					cars[i].x, cars[i].y, cars[i].z);
	}
}

void initLogs(void)
{
	vertex length = {CYLINDER_HEIGHT, CYLINDER_RADIUS*2, CYLINDER_RADIUS*2};
	for (int i = 0; i < 20; i++)
	{
		logs[i] = randVertex(logs, length, 2, 20, i); 
		if (getDebug())
			printf("randLog=(%.0f, %.0f, %.0f)\n",
					logs[i].x, logs[i].y, logs[i].z);
	}
}

void drawCars(void)
{
	for (int i = 0; i < 20; i++)
	{
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(cars[i].x, cars[i].y, cars[i].z);
		drawCube();
		glPopMatrix();
	}
}

void drawLogs(void)
{
	for (int i = 0; i < 20; i++)
	{
		glColor3f(1, 0, 0);
		glTranslatef(logs[i].x, logs[i].y, logs[i].z);
		drawCylinder();
		glTranslatef(-logs[i].x, -logs[i].y, -logs[i].z);
	}
}

void updateCars(void)
{
	for (int i = 0; i < 20; i++)
		cars[i].x = (cars[i].x+V_CARS < GRID_WIDTH/2 - CUBE_LENGTH) ?
			cars[i].x+V_CARS : -GRID_WIDTH/2 + CUBE_LENGTH/2;
}

void updateLogs(void)
{
	for (int i = 0; i < 20; i++)
		logs[i].x = (logs[i].x+V_LOGS < GRID_WIDTH/2 - CYLINDER_HEIGHT/2) ?
			logs[i].x+V_LOGS : -GRID_WIDTH/2 + CYLINDER_HEIGHT/2;

	if (frog.onLog)
	{
		if (frog.r.x + V_LOGS < GRID_WIDTH/2 - CYLINDER_HEIGHT/2)
			frog.r.x = frog.r0.x = frog.r.x + V_LOGS;
		else
			resetGame();
	}
}

vertex randVertex(vertex *array, vertex length, int zMin, int zMax, int index)
{
	int i;
	vertex v = {0, 0, 0};

	while (1)
	{
		v.x = RAND(-GRID_WIDTH/2 + length.x/2, GRID_WIDTH/2 - length.x/2);
		v.z = RAND(zMin + length.z/2, zMax - length.z/2);
		for (i = 0; i < index; i++)
			if (array[i].x >= v.x-length.x/2 && array[i].x <= v.x+length.x/2 &&
				array[i].z >= v.z-length.z/2 && array[i].z <= v.z+length.z/2)
				break;
		if (i == index)
			break;
	}

	return v;
}

