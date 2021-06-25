#include "stdafx.h"
#include "RedHoodGame.h"
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));

	glutInit(&argc, argv);


	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Red Hood");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);


	cam.pos.x = 0.0f;
	cam.pos.y = 2.5f;
	cam.pos.z = 6.9f;
	cam.dir.x = 0.0f;
	cam.dir.y = -0.9f;
	cam.dir.z = -1.0f;

	cam.pos2.x = 0.0f;
	cam.pos2.y = -0.85f;
	cam.pos2.z = 3.9f;

	cam.speed = .1f;
	//sndPlaySound("music.mp3", SND_LOOP | SND_ASYNC); //play music in game

	WolfGenerator(WOLFS);
	stone = loadtex("stone.png", GL_RGB);
	hidle[0] = loadtex("HoodIdle1.png", GL_RGBA);
	hidle[1] = loadtex("HoodIdle2.png", GL_RGBA);
	hidle[2] = loadtex("HoodIdle3.png", GL_RGBA);
	hidle[3] = loadtex("HoodIdle4.png", GL_RGBA);
	hidle[4] = loadtex("HoodIdle5.png", GL_RGBA);
	hrun[0] = loadtex("RedHoodRun1.png", GL_RGBA);
	hrun[1] = loadtex("RedHoodRun2.png", GL_RGBA);
	hrun[2] = loadtex("RedHoodRun3.png", GL_RGBA);
	hrun[3] = loadtex("RedHoodRun4.png", GL_RGBA);
	hrun2[0] = loadtex("RedHoodRunUp1.png", GL_RGBA);
	hrun2[1] = loadtex("RedHoodRunUp2.png", GL_RGBA);
	hrun2[2] = loadtex("RedHoodRunUp3.png", GL_RGBA);
	hrun2[3] = loadtex("RedHoodRunUp4.png", GL_RGBA);
	hattack[0] = loadtex("RedHoodAttack1.png", GL_RGBA);
	hattack[1] = loadtex("RedHoodAttack2.png", GL_RGBA);
	hattack[2] = loadtex("RedHoodAttack3.png", GL_RGBA);
	hattack[3] = loadtex("RedHoodAttack4.png", GL_RGBA);
	widle[0] = loadtex("WolfIdle1.png", GL_RGBA);
	widle[1] = loadtex("WolfIdle2.png", GL_RGBA);
	wwalk[0] = loadtex("WolfWalk0.png", GL_RGBA);
	wwalk[1] = loadtex("WolfWalk1.png", GL_RGBA);
	wwalk[2] = loadtex("WolfWalk2.png", GL_RGBA);
	bush = loadtex("bush1.png", GL_RGBA);
	sign = loadtex("sign.png", GL_RGBA);
	tree = loadtex("tree.png", GL_RGBA);
	cave = loadtex("cave_entry.png", GL_RGBA);
	cave2 = loadtex("cave.png", GL_RGBA);


	glutMainLoop();

	return 0;
}

bool keystate[256];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
	runx = 0;
	isup = 0;
	isAttack = 0;
}

void OnTimer(int id) {

	glutTimerFunc(17, OnTimer, 0);

	op++;
	if (op == 0) idle = 0;
	if (op == 5) idle = 1;
	if (op == 10) idle = 2;
	if (op == 15) idle = 3;
	if (op == 20) {
		idle = 4;
		op = -1;
	}
	op2++;
	if (op2 == 0) run = 0;
	if (op2 == 5) run = 1;
	if (op2 == 10) run = 2;
	if (op2 == 15) {
		run = 3;
		op2 = -1;
	}

	ww++;
	if (ww == 0) idleW = 0;
	if (ww == 20) {
		idleW = 1;
		ww = -1;
	}
	www++;
	if (www == 0) idleWW = 0;
	if (www == 20) idleWW = 1;
	if (www == 40) {
		idleWW = 2;
		www = -20;
	} 
	WolfMove();

	if (keystate['w']) {
		cam.pos.x += cam.dir.x * cam.speed;
		cam.pos.z += cam.dir.z * cam.speed;
		cam.pos2.x += cam.dir.x * cam.speed;
		cam.pos2.z += cam.dir.z * cam.speed;
		cam.up = 1;
		cam.down = 0;
		cam.left = 0;
		cam.right = 0;
		isup = 1;
	}

	if (keystate['s']) {
		cam.pos.x -= cam.dir.x * cam.speed;
		cam.pos.z -= cam.dir.z * cam.speed;
		cam.pos2.x -= cam.dir.x * cam.speed;
		cam.pos2.z -= cam.dir.z * cam.speed;
		cam.up = 0;
		cam.down = 1;
		cam.left = 0;
		cam.right = 0;
		runx = 1;
		isup = 0;
	}

	if (keystate['d']) {
		cam.pos.x += (-cam.dir.z) * cam.speed;
		cam.pos.z += cam.dir.x * cam.speed;
		cam.pos2.x += (-cam.dir.z) * cam.speed;
		cam.pos2.z += cam.dir.x * cam.speed;
		cam.up = 0;
		cam.down = 0;
		cam.left = 0;
		cam.right = 1;
		rot = 1;
		runx = 1;
		isup = 0;
	}

	if (keystate['a']) {
		cam.pos.x -= (-cam.dir.z) * cam.speed;
		cam.pos.z -= cam.dir.x * cam.speed;
		cam.pos2.x -= (-cam.dir.z) * cam.speed;
		cam.pos2.z -= cam.dir.x * cam.speed;
		cam.up = 0;
		cam.down = 0;
		cam.left = 1;
		cam.right = 0;
		rot = 0;
		runx = 1;
		isup = 0;
	}
	if (keystate['b']) {
		isAttack = 1;
		cam.attack(cam);
		//cooldown(150);
	}
	if (keystate['p']) {
		return;
		//cooldown(150);
	}

	//world border
	if (cam.pos2.x > 6.0f) {
		cam.pos2.x = 6.0f;
		cam.pos.x = 6.0f;
	}
	if (cam.pos2.x < -6.0f) {
		cam.pos2.x = -6.0f;
		cam.pos.x = -6.0f;
	}
	if (cam.pos2.z > 4.0f) {
		cam.pos2.z = 4.0f;
		cam.pos.z = 7.0f;
	}
	if (cam.pos2.z < -4.0f) {
		cam.pos2.z = -4.0f;
		cam.pos.z = -1.0f;
	}



	if (WolfDead() == 1) {
		WolfGenerator(7);
	}
	//printf("x=  %f    z=  %f", cam.pos2.x, cam.pos2.z);
	//system("cls");
}

void OnRender() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.pos.x + cam.dir.x, cam.pos.y + cam.dir.y, cam.pos.z + cam.dir.z, 
		0.0f, 1.0f, 0.0f 
	);

	//Rendering all elements of game

	//draw floor
	drawbackground(stone);
	//some world elements
	WorldTree(tree);
	WorldBushes(bush);
	WorldCave(cave, cave2);
	//enemy
	WolfRender();
	//hood
	if (isAttack == 1) {
		HoodAttack(hattack, run, cam);
	}
	else if (runx == 1) {
		HoodRun(hrun, run, cam, rot);
	}
	else if (isup == 1) {
		HoodRun(hrun2, run, cam, rot);
	}
	else {
		HoodIdle(hidle, idle, cam, rot);
	}

	score(killed);
	//displayText(string);


	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
}

GLuint loadtex(const char * filename, int type)
{
	int width, height;
	unsigned char * img = NULL;
	if (type == GL_RGB) img = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	if (type == GL_RGBA) img = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, img);

	SOIL_free_image_data(img);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}


void drawbackground(GLuint tex) {

	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	for (int i = -12; i < 24; i = i + 2)
	{
		for (int j = -12; j < 24; j = j + 2)
		{
			glPushMatrix();
			glTranslatef(i, -1.8f, j);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.0);
			glEnd();
			glPopMatrix();
		}
	}

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void WorldBushes(GLuint bush) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, bush);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
		glTranslatef(-4.0f, 0.3f, -4.3f);
		glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, -2.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, -2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4.0f, 0.3f, -4.3f);
		glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, -2.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, -2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 0.3f, -4.3f);
		glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, -2.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, -2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -1.0f, -4.0f);
		glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, -0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);

}
void WorldTree(GLuint tree) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tree);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
		glTranslatef(-4.0f, 1.0f, -5.5f);
		glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0, 3.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0, 3.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0, -3.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0, -3.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.3f, 1.0f, -6.5f);
		glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.5, 3.5, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5, 3.5, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5, -3.5, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.5, -3.5, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);
}
void WorldCave(GLuint cave, GLuint cave2) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, cave2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(-10.5f, -0.0f, 1.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0, 4.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4.0, 4.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4.0, -4.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0, -4.0, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, cave);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(-9.0f, 3.0f, 0.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, 5.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, 5.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, -5.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, -5.0, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);

	



	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, cave2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(10.5f, -0.0f, 1.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0, 4.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4.0, 4.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4.0, -4.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0, -4.0, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);




	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, cave);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(9.0f, 3.0f, 0.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, 5.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, 5.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, -5.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, -5.0, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Player::attack(Player q) {

	float playerx = cam.pos2.x - cam.dir.x;
	float playerz = -(cam.pos2.z + cam.dir.z);

	for (int i = 0; i < WOLFS; i++) {

		float x = WolfPosX(i);
		float z = WolfPosZ(i);

		if (z >(playerz - 2.5f) && z < (playerz + 1.5f) && x >(playerx - 2.0f) && x < (playerx + 2.0f)) {
			WolfDamage(i);
		}
		/*
		if (up == 1) {
		if (z >= (playerz - 2.0f) && z <= (playerz)) {
		if (x >(playerx - 1.3f) && x < (playerx + 1.3f)) {
		WolfDamage(i);
		}
		}
		}
		if (down == 1) {
		if (z <= (playerz + 2.0f) && z >= (playerz)) {
		if (x >(playerx - 1.3f) && x < (playerx + 1.3f)) {
		WolfDamage(i);
		}
		}
		}

		if (right == 1) {
		if (x <= (playerx + 2.0f) && x >= (playerx)) {
		if (z >(playerz - 1.3f) && z < (playerz + 1.3f)) {
		WolfDamage(i);
		}
		}
		}
		if (left == 1) {
		if (x >= (playerx - 2.0f) && x <= (playerx)) {
		if (z >(playerz - 1.3f) && z < (playerz + 1.3f)) {
		WolfDamage(i);
		}
		}
		}*/
	}
	return;
}
void WolfList::killWolf(int id) {
	Wolf *x = first;

	if (x == NULL) {
		return;
	}

	Wolf *prev = x;

	while (x != NULL && (x->id != id))
	{
		prev = x;
		x = x->next;
		if (x == NULL)break;
	}
	if (x == NULL) return;
	Wolf *next = x->next;
	if (x == first)
	{
		if (x == NULL) return;
		first = next;
	}
	else
	{
		if (x == NULL) return;
		prev->next = next;
	}

	delete x;
}
void WolfList::damage(int id) {
	Wolf *x = first;

	if (x == NULL) {
		return;
	}

	while (x != NULL && (x->id != id))
	{
		x = x->next;
		if (x == NULL)return;
	}
	x->health--;
	if (x->health <= 0) {
		killed++;
		printf("killed = %d\n", killed);
		killWolf(id);
	}
	return;
}
float WolfList::getPosx(int id) {
	Wolf *x = first;
	if (x == NULL) {
		return 0.0f;
	}

	if (id == 0) {
		return x->pos.x;
	}

	while (x->id != id) {
		x = x->next;
		if (x == NULL) return 0.0f;
	}
	if (x == NULL) {
		return 0.0f;
	}
	if (x->id == id) {
		return x->pos.x;
	}

}
float WolfList::getPosz(int id) {
	Wolf *x = first;
	if (x == NULL) {
		return 0.0f;
	}
	if (id == 0) {
		return x->pos.z;
	}

	while (x->id != id) {
		x = x->next;
		if (x == NULL) return 0.0f;
	}
	if (x == NULL) {
		return 0.0f;
	}
	if (x->id == id) {
		return x->pos.z;
	}
}
void WolfList::addWolf(int id) {
	Wolf *newie = new Wolf(id);

	if (first == NULL) {
		first = newie;
	}
	else {
		Wolf *x = first;

		while (x->next) x = x->next;
		x->next = newie;
	}
}
void WolfList::moveWolf() {

	Wolf *x = first;
	if (x != NULL) {
		while (x) {
			//wilk idzie
			if (x->move < 30) {
				x->pos.x += x->dir.x * x->speed;
				x->pos.z += x->dir.z * x->speed;
				if (x->move < 30) {
					isWolfIdle = 0;
					x->speed = 0.1f;
				}
				x->move++;
			}
			//wilk stoi
			if (x->move >= 30 && x->move < 100) {
				isWolfIdle = 1;
				x->speed = 0.0f;
				x->move++;
			}
			//reset
			if (x->move >= 100) {
				x->move = 0;
				x->beta = atan2(x->dir.z, x->dir.x);
				x->direc = (rand() % 10000) * 0.01;
				x->dir.x = cos(x->direc + x->beta);
				x->dir.z = sin(x->direc + x->beta);
				x->speed = 0.0f;
			}
			//granice
			if (x->pos.x > 6.0f) {
				x->pos.x = 6.0f;
				x->direc = -(x->pos.x);
			}
			if (x->pos.x < -6.0f) {
				x->pos.x = -6.0f;
				x->direc = -(x->pos.x);
			}
			if (x->pos.z > 4.0f) {
				x->pos.z = 4.0f;
				x->direc = -(x->pos.z);
			}
			if (x->pos.z < -3.0f) {
				x->pos.z = -4.0f;
				x->direc = -(x->pos.z);
			}

			x = x->next;
		}
	}
}


WolfList WList;
void WolfGenerator(int x) {
	for (int i = 0; i < x; i++) {
		WList.addWolf(i);
	}
}
void WolfRender() {
		WList.renderWolf(widle, 1, rot);
}
void WolfMove() {
	WList.moveWolf();
}
float WolfPosX(int id) {
	return WList.getPosx(id);
}
float WolfPosZ(int id) {
	return WList.getPosz(id);
}
void WolfDamage(int id) {
	WList.damage(id);
}
bool WolfDead() {
	Wolf *x = first;
	if (x == NULL) return 1;
	if (x != NULL) return 0;
	return 0;
}


void cooldown(int i) {
	for (int x = 0; x < i; x++);
}
void HoodIdle(GLuint hidle[5], int i, Player cam, bool rot) {
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, hidle[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(cam.pos2.x, (cam.pos2.y), (cam.pos2.z));
	glRotatef(150.0f, 1.0f, 0.0f, 0.0f);

	if (rot == 1) {
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void HoodAttack(GLuint hattack[4], int i, Player cam) {
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, hattack[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(cam.pos2.x, (cam.pos2.y), (cam.pos2.z));
	glRotatef(150.0f, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void HoodRun(GLuint frun[4], int i, Player cam, bool rot) {
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, frun[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glTranslatef(cam.pos2.x, (cam.pos2.y), (cam.pos2.z));
	glRotatef(150.0f, 1.0f, 0.0f, 0.0f);
	if (rot == 1) {
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void WolfList::renderWolf(GLuint *wolftex, int i, bool rot) {
	Wolf *x = first;

	while (x) {
		glColor3f(1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, wolftex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glPushMatrix();
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

		glTranslatef(x->pos.x, x->pos.y, x->pos.z);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, -0.5);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, -0.5);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.5);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.5);

		glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, 0);

		x = x->next;
	}

}
void displayText(char *string) {
	int j = strlen(string);

	glColor3f(1, 1, 1);
	glRasterPos2f(0.0f, 0.0f);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void score(int killed) {

	if (killed == 999) {
		killed = 0;
	}

	char number_buffer[4];
	snprintf(number_buffer, 4, "%d", killed);

	score_string[7] = number_buffer[0];
	score_string[8] = number_buffer[1];
	score_string[9] = number_buffer[2];
	score_string[10] = number_buffer[3];


	displayText(score_string);
}