#ifndef __Inputs
#define __Inputs
#include "Camera.h"
#include "Vec3.h"
#include "GL/glut.h"
#include "GL/freeglut.h"

const float camMoveStep = 1.0f;
const float camSensitvity = 0.001f;

Camera* input_main_camera;

unsigned int *input_view_width, *input_view_height;

void KeyboardDepressed(unsigned char key, int x, int y) {
	Vec3 camMove(0, 0, 0);

	if (key == 'w') camMove.z += camMoveStep;
	if (key == 's') camMove.z -= camMoveStep;

	if (key == 'a') camMove.x -= camMoveStep;
	if (key == 'd') camMove.x += camMoveStep;

	if (key == 'q') exit(0);

	input_main_camera->MoveCamera(camMove);
}

void MouseMove(int x, int y) {
	int movex = *input_view_width - x, movey = *input_view_height - y;

	input_main_camera->RotateCamera(Vec3(movey * camSensitvity, -movex * camSensitvity, 0));

	glutWarpPointer(*input_view_width, *input_view_height);
}
#endif