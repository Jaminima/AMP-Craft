#ifndef __Window
#define __Window

#include "GL/glut.h"
#include "GL/freeglut.h"

#include "Renderer.h"
#include "Color.h"

Renderer renderer;

unsigned int defaultWidth = 800, defaultHeight = 600;

unsigned int getWindowHeight() {
	return defaultHeight;
}

unsigned int getWindowWidth() {
	return defaultWidth;
}

void drawFrame()
{
	Color* view = renderer.RenderRays();

	glDrawPixels(getWindowWidth(), getWindowHeight(), GL_RGBA, GL_UNSIGNED_INT, view);

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