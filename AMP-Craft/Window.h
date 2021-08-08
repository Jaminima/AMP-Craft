#ifndef __Window
#define __Window

#include "GL/glut.h"
#include "GL/freeglut.h"

#include "Renderer.h"
#include "Color.h"
#include "Inputs.h"
#include "FPSTracker.h"

unsigned int getWindowHeight() {
	return input_main_camera.view_height;
}

unsigned int getWindowWidth() {
	return input_main_camera.view_width;
}

void drawFrame()
{
	glDrawPixels(getWindowWidth(), getWindowHeight(), GL_RGBA, GL_UNSIGNED_BYTE, Renderer::View);

	glutSwapBuffers();
}

void triggerReDraw()
{
	completion_future future = Renderer::RenderRays(input_main_camera);

	FPSTracker::AddFPS();

	future.wait();

	glutPostRedisplay();
}

void initWindow(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(getWindowWidth(), getWindowHeight());
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("AMP-Craft");

	glutDisplayFunc(drawFrame);
	glutIdleFunc(triggerReDraw);

	glutWarpPointer(getWindowWidth() / 2, getWindowHeight() / 2);

	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(KeyboardDepressed);

	glutMainLoop();
}

#endif