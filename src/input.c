#include <stdio.h>

#include <GL/glut.h>

#include "input.h"
#include "core.h"
#include "jumping_logic.h"

static int oldX = 0;
static int oldY = 0;

static bool leftClickFlag = true;

void keyboard(unsigned char key, int x, int y)
{
	UNUSED_VAR x;
	UNUSED_VAR y;

	switch (key)
	{
		case ' ':
			jumpingSettings();
			break;
		case 'v':
		case 'V':
			switchDebug();
			break;
		case 't':
		case 'T':
			switchTextureFlag();
			glutPostRedisplay();
			break;
		case 'p':
		case 'P':
			switchWireFlag();
			glutPostRedisplay();
			break;
		case 'o':
		case 'O':
			switchAxesFlag();
			glutPostRedisplay();
			break;
		case 'n':
		case 'N':
			switchNormalFlag();
			glutPostRedisplay();
			break;
		case 'l':
		case 'L':
			switchLightFlag();
			glutPostRedisplay();
			break;
		case 'b':
		case 'B':
			switchPause();
			glutPostRedisplay();
			break;
		case 'd':
		case 'D':
			if (!getJumpingFlag())
			{
				frog.r0.theta = (frog.r0.theta > M_PI/2 - M_PI/16) ?
					M_PI/2-M_PI/32 : frog.r0.theta+M_PI/32;
				updateCartesian(&frog.r0);
				glutPostRedisplay();
			}
			break;
		case 'a':
		case 'A':
			if (!getJumpingFlag())
			{
				frog.r0.theta = (frog.r0.theta < M_PI/16) ?
					M_PI/32 : frog.r0.theta-M_PI/32;
				updateCartesian(&frog.r0);
				glutPostRedisplay();
			}
			break;
		case 'w':
		case 'W':
			if (!getJumpingFlag())
			{
				frog.r0.r = (frog.r0.r > 9.8) ? 10 : frog.r0.r+0.2;
				updateCartesian(&frog.r0);
				glutPostRedisplay();
			}
			break;
		case 's':
		case 'S':
			if (!getJumpingFlag())
			{
				frog.r0.r = (frog.r0.r < 1.2) ? 1 : frog.r0.r-0.2;
				updateCartesian(&frog.r0);
				glutPostRedisplay();
			}
			break;
		case 27:
		case 'q':
		case 'Q':
			if (getDebug())
				printf("\n>>>>>EXIT<<<<<\n");
			exit(EXIT_SUCCESS);
		default:
			break;
	}
}

void specialKeys(int key, int x, int y)
{
	UNUSED_VAR x;
	UNUSED_VAR y;

	switch (key)
	{
		case GLUT_KEY_UP:
			setSegments(getSegments()*2);
			break;
		case GLUT_KEY_DOWN:
			setSegments((getSegments() < 8) ? 4 : getSegments()/2);
			break;
		case GLUT_KEY_LEFT:
			frog.r0.phi += M_PI/16;
			updateCartesian(&frog.r0);
			break;
		case GLUT_KEY_RIGHT:
			frog.r0.phi -= M_PI/16;
			updateCartesian(&frog.r0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
	UNUSED_VAR state;

	oldX = x;
	oldY = y;
	if (button == GLUT_LEFT_BUTTON)
		leftClickFlag = true;
	else if (button == GLUT_RIGHT_BUTTON)
		leftClickFlag = false;
}

void mouseMove(int x, int y)
{
	int diffX = oldX - x, diffY = oldY - y;

	if (leftClickFlag)
	{
		setRotateCamY(getRotateCamY() + diffX);
		setRotateCamX(getRotateCamX() + diffY);
	}
	else if ((getCamZoom()-(diffY*0.1) > 0.5) &&
			(getCamZoom()-(diffY*0.1) < 6))
		setCamZoom(getCamZoom()-diffY*0.01);

	oldX = x;
	oldY = y;
	glutPostRedisplay();
}

