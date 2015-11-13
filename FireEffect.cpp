#define _CRT_SECURE_NO_WARNINGS

#define NUMBER (20)

#include<stdio.h>
#include<assert.h>
#include<vector>
#include<string>
#include<Windows.h>
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glut.h"

//ビュー行列
glm::mat4 viewMatrix;

//ビルボード行列
glm::mat4 BillboardMatrix;

class Fire{
public:
	glm::vec3 m_position;
	float m_scale;
	float m_alpha;
	void Draw();
	void Update();
	Fire(){};
};

void Fire::Draw(){
	glPushMatrix();
	BillboardMatrix = glm::inverse(viewMatrix);
	BillboardMatrix[3][0] = 0;
	BillboardMatrix[3][1] = 0;
	BillboardMatrix[3][2] = 0;

	//ビルボード行列適用
	glMultMatrixf((GLfloat*)&BillboardMatrix);
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale / 2, scale, scale / 2);

	glBegin(GL_QUADS);
	{
		glColor4f(1, 0.5, 0.25, alpha);
		glTexCoord2f(0.f, 0.f);
		glVertex2f(-1.f, -1.f);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(-1.f, 1.f);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(1.f, 1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(1.f, -1.f);
	}
	glEnd();
	glPopMatrix();
}

void Fire::Update(){
	alpha -= 1.f / NUMBER;
	scale += 3.f / NUMBER;
	position.y += 0.1f;

	if (alpha < 0.f){
		alpha = 1.f;
		scale = 0.f;
		position = { 0.f, 0.1f, 0.f };
	}
}

Fire fire[NUMBER];

GLuint textures;

//透過度無し
class RGB{
public:
	unsigned char r, g, b;
};

//透過度有り
class RGBA{
public:
	unsigned char r, g, b, a;
};

//画像読み込み
void loadImage(char *_Filename){
	FILE *pBinMapFile;
	pBinMapFile = fopen(_Filename, "rb");

	assert(pBinMapFile != NULL);

	BITMAPFILEHEADER bmpHeader;
	fread(
		&bmpHeader,
		sizeof(BITMAPFILEHEADER),
		1,
		pBinMapFile
		);

	BITMAPINFOHEADER bmpInfoHeader;
	fread(
		&bmpInfoHeader,
		sizeof(BITMAPINFOHEADER),
		1,
		pBinMapFile
		);

	int imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGB);
	RGB *pixels = (RGB*)malloc(imageSize);

	fread(
		pixels,
		imageSize,
		1,
		pBinMapFile
		);
	fclose(pBinMapFile);


	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	int texDataSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGBA);
	RGBA *pixelsData = (RGBA*)malloc(texDataSize);

	//RGBを白で初期化
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		pixelsData[i].r = 0xff;
		pixelsData[i].g = 0xff;
		pixelsData[i].b = 0xff;
	}

	//各ピクセルのRの値を、テクスチャ用ピクセルのアルファ値に書き込む。
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		pixelsData[i].a = pixels[i].r;
	}

	glGenTextures(
		1,        //GLsizei n
		&textures);//GLuint *textures

	////pixcel
	//glBindTexture(
	//	GL_TEXTURE_2D,//GLenum target
	//	textures[0]//GLuint texture
	//	);

	//glTexImage2D(
	//	GL_TEXTURE_2D,   //GLenum target
	//	0,               //GLint level
	//	GL_RGB,          //GLint internalformat(生成するテクスチャのフォーマット)
	//	bmpInfoHeader.biWidth,               //GLsizei width
	//	bmpInfoHeader.biHeight,               //GLsizei height
	//	0,               //GLint border
	//	GL_RGB,          //GLenum format(ピクセルデータのフォーマット)
	//	GL_UNSIGNED_BYTE,//GLenum type
	//	pixels          //const GLvoid *pixels
	//	);

	//glTexParameteri(
	//	GL_TEXTURE_2D,          // GLenum target
	//	GL_TEXTURE_MIN_FILTER,  // GLenum pname
	//	GL_NEAREST);            // GLint param

	//glTexParameteri(
	//	GL_TEXTURE_2D,          // GLenum target
	//	GL_TEXTURE_MAG_FILTER,  // GLenum pname
	//	GL_NEAREST);

	//pixceldata
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target
		textures//GLuint texture
		);

	glTexImage2D(
		GL_TEXTURE_2D,   //GLenum target
		0,               //GLint level
		GL_RGBA,          //GLint internalformat(生成するテクスチャのフォーマット)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGBA,          //GLenum format(ピクセルデータのフォーマット)
		GL_UNSIGNED_BYTE,//GLenum type
		pixelsData          //const GLvoid *pixels
		);

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MAG_FILTER,  // GLenum pname
		GL_NEAREST);

	free(pixels);
	free(pixelsData);
}

void timer(int value){
	for (int i = 0; i < NUMBER; ++i){
		fire[i].update();
	}

	glutPostRedisplay();
	glutTimerFunc(
		1000 / 60,
		timer,
		0);
}

void display(){
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		60,//GLdouble fovy,
		1,//GLdouble aspect,
		0.1,//GLdouble zNear,
		100);//GLdouble zFar
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	static float angle = 0.f;
	angle += 0.01;

	//ビュー行列
	viewMatrix = glm::lookAt(
		glm::vec3(7.f*cos(angle), 3, 7.f*sin(angle)),//eye
		glm::vec3(0, 0, 0), //center
		glm::vec3(0, 1, 0));//up

	//先生に聞く
	glMultMatrixf((GLfloat*)&viewMatrix);

	//フィールド描画
	glBegin(GL_LINES);
	for (float i = -10; i <= 10; i++)
	{
		glColor3f(1, 0, 0);
		glVertex3f(i, 0, -10);//(GLfloat x, GLfloat y, GLfloat z)
		glVertex3f(i, 0, 10);

		glColor3f(0, 1, 0);
		glVertex3f(-10, 0, i);//(GLfloat x, GLfloat y, GLfloat z)
		glVertex3f(10, 0, i);
	}
	glEnd();

	//ブレンド
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,   // GLenum sfactor
		GL_ONE);        // GLenum dfactor

	glEnable(GL_TEXTURE_2D);

	glBindTexture(
		GL_TEXTURE_2D,//GLenum target
		textures//GLuint texture
		);

	//描画
	for (int i = 0; i < NUMBER; i++){
		fire[i].draw();
	}

	glDisable(GL_TEXTURE_2D);

	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(900, 780);
	glutCreateWindow("炎エフェクト");

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,
		timer,
		0);

	//初期化
	for (int i = 0; i < NUMBER; ++i){
		fire[i].position = { 0, 0.2*i, 0 };
		fire[i].scale = 3.f / NUMBER*i;
		fire[i].alpha = 1.f - 1.f / NUMBER*i;
	}

	loadImage("smoke.bmp");

	glutMainLoop();
}
