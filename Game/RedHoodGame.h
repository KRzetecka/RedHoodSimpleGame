#include <time.h>
#include <vector>

void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void drawbackground(GLuint tex);
void WorldBushes(GLuint bush);
void WorldTree(GLuint tree);
void WorldCave(GLuint cave, GLuint cave2);
GLuint loadtex(const char * filename, int type);
void WolfRender();
void WolfGenerator(int x);
void WolfMove();
float WolfPosX(int id);
float WolfPosZ(int id);
bool WolfDead();
void WolfDamage(int id);
void displayText(char *string);
void score(int killed);

char score_string[11] = {'S', 'c', 'o', 'r', 'e', ':', ' '};
int test = 0;
bool runx = 0;
bool isup = 0;
int idle = 0, run = 0;
int op = 0, op2 = 0;
int ww = 0, www = 0, idleW, idleWW;
bool rot = 0;
int killed = 0;
int killed2 = 0;
int WOLFS = 7;
int isAttack = 0;
bool isWolfIdle = 1;

GLuint stone = 0;
GLuint hidle[5];
GLuint hrun[4], hrun2[4];
GLuint widle[2];
GLuint wwalk[3];
GLuint hattack[4];
GLuint bush;
GLuint sign;
GLuint tree;
GLuint cave;
GLuint cave2;



struct vec3 {
	float x, y, z;
};

vec3 LightPos;

struct Player {
	vec3 pos; 
	vec3 dir; 
	vec3 pos2;
	float speed; 

	Player();
	void attack(Player q);

	int health;
	float xfield;
	float zfield;
	bool left, right, up, down;
};
Player::Player() {
	this->health = 1000;
	this->xfield = this->pos.x + 0.1f;
	this->zfield = this->pos.z + 0.1f;
	this->down = 1;
}



struct Wolf {
	vec3 pos;
	vec3 dir;
	bool side;
	int id;
	struct Wolf *next;

	int move;
	float speed;
	float beta;
	Wolf(int id);
	float direc;

	int health;
};
Wolf::Wolf(int id) {
	this->id = id;
	this->direc = (rand() % 10000) * 0.01;
	float beta = atan2(this->dir.z, this->dir.x);
	this->dir.x = cos(direc + beta);
	this->dir.z = sin(direc + beta);
	this->dir.y = -0.9f;
	this->pos.x = rand() % ((6 - (-6) ) + 1) - 6;
	this->pos.z = rand() % ((4 - (-4) ) + 1) - 4;
	this->pos.y = .8f;
	this->speed = .0f;
	this->move = 0;
	this->side = 0;
	this->next = NULL;

	this->health = 50;
}

struct Wolf *first = NULL;

struct WolfList {
	WolfList();
	void moveWolf();
	void addWolf(int id);
	void killWolf(int id);
	void renderWolf(GLuint *wolftex, int i, bool rot);
	float getPosx(int id);
	float getPosz(int id);
	void damage(int id);
	bool WolfDead();
};
WolfList::WolfList() {
	//first = NULL;
	//last = NULL;
}


Player cam;
void HoodIdle(GLuint hidle[5], int i, Player cam, bool rot);
void HoodRun(GLuint frun[4], int i, Player cam, bool rot);
void HoodAttack(GLuint hattac[4], int i, Player cam);