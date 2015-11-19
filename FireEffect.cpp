#define _CRT_SECURE_NO_WARNINGS

#define ParticleNumber (20)

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
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(m_scale / 2, m_scale, m_scale / 2);

	glBegin(GL_QUADS);
	{
		glColor4f(1, 0.5, 0.25, m_alpha);
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
	m_alpha -= 1.f / ParticleNumber;
	m_scale += 3.f / ParticleNumber;
	m_position.y += 0.1f;

	if (m_alpha < 0.f){
		m_alpha = 1.f;
		m_scale = 0.f;
		m_position = { 0.f, 0.1f, 0.f };
	}
}

Fire *fire[ParticleNumber];

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

	//RとB反転
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

	glTexImage2D(
		GL_TEXTURE_2D,   
		0,               
		GL_RGBA,          
		bmpInfoHeader.biWidth,
		bmpInfoHeader.biHeight, 
		0,               
		GL_RGBA,          
		GL_UNSIGNED_BYTE,
		pixelsData   
		);

	glTexParameteri(
		GL_TEXTURE_2D,          
		GL_TEXTURE_MIN_FILTER,  
		GL_NEAREST);            

	glTexParameteri(
		GL_TEXTURE_2D,          
		GL_TEXTURE_MAG_FILTER, 
		GL_NEAREST);

	free(pixels);
	free(pixelsData);
}

void timer(int value){
	for (int i = 0; i < ParticleNumber; ++i){
		fire[i]->Update();
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

	glMultMatrixf((GLfloat*)&viewMatrix);

	//フィールド描画
	glBegin(GL_LINES);
	for (float i = -10; i <= 10; i++)
	{
		glColor3f(1, 0, 0);
		glVertex3f(i, 0, -10);
		glVertex3f(i, 0, 10);

		glColor3f(0, 1, 0);
		glVertex3f(-10, 0, i);
		glVertex3f(10, 0, i);
	}
	glEnd();

	//ブレンド
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,  
		GL_ONE);       

	glEnable(GL_TEXTURE_2D);

	//描画
	for (int i = 0; i < ParticleNumber; i++){
		fire[i]->Draw();
	}

	glDisable(GL_TEXTURE_2D);

	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(900, 780);
	glutCreateWindow("炎エフェクト");

	glutDisplayFunc(display);

	glutTimerFunc(
		0,
		timer,
		0);

	//初期化
	for (int i = 0; i < ParticleNumber; ++i){
		fire[i] = new Fire();
		fire[i]->m_position = { 0, 0.2*i, 0 };
		fire[i]->m_scale = 3.f / ParticleNumber*i;
		fire[i]->m_alpha = 1.f - 1.f / ParticleNumber*i;
	}

	loadImage("smoke.bmp");

	glutMainLoop();
}
