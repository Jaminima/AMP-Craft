#ifndef __Window
#define __Window

#include "GL/glut.h"
#include "GL/freeglut.h"

#include "Renderer.h"

Renderer renderer;

unsigned int defaultWidth = 800, defaultHeight = 600;

unsigned int getWindowHeight() {
	return GLUT_WINDOW_HEIGHT;
}

unsigned int getWindowWidth() {
	return GLUT_WINDOW_WIDTH;
}

void drawFrame()
{
	bool* view = renderer.RenderRays();
	glutSwapBuffers();
}

void triggerReDraw()
{
}

void initWindow(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(defaultWidth, defaultHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("AMP-Craft");

	glutDisplayFunc(drawFrame);
	//glutIdleFunc(triggerReDraw);

	/*glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(KeyboardDepressed);*/

	glutMainLoop();
}

#endif