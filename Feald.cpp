#define _CRT_SECURE_NO_WARNINGS

#define FEALDSIZE (128)

#include<stdio.h>
#include<assert.h>
#include<vector>
#include<string>
#include<Windows.h>
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glut.h"

std::vector<float> v;
std::vector<unsigned short> indeces;
glm::vec3 position;

class RGB{
public:
	unsigned char r, g, b;
};
RGB *pixels;


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
	pixels = (RGB*)malloc(imageSize);

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

	glTexImage2D(
		GL_TEXTURE_2D,   //GLenum target
		0,               //GLint level
		GL_RGB,          //GLint internalformat(生成するテクスチャのフォーマット)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGB,          //GLenum format(ピクセルデータのフォーマット)
		GL_UNSIGNED_BYTE,//GLenum type
		pixels          //const GLvoid *pixels
		);

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MAG_FILTER,  // GLenum pname
		GL_NEAREST);

	//free(pixels);
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(
		1000 / 60,
		timer,
		0);
}

void display(){
	glPolygonMode(
		GL_FRONT_AND_BACK,  // GLenum face
		GL_FILL);

	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		60,//GLdouble fovy,
		1,//GLdouble aspect,
		0.1,//GLdouble zNear,
		300);//GLdouble zFar
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		0, 100, 150,
		0, 0, 0,
		0, 1, 0);

	glEnableClientState(GL_VERTEX_ARRAY);

	std::vector<float>::iterator itr_v = v.begin();
	glVertexPointer(
		3,
		GL_FLOAT,
		0,
		&(*itr_v));

	std::vector<unsigned short>::iterator itr_indeces = indeces.begin();

	glPushMatrix();
	{
		glTranslatef(-(FEALDSIZE / 2), 0, -(FEALDSIZE / 2));
		glDrawElements(GL_TRIANGLES, indeces.size(), GL_UNSIGNED_SHORT, &(*itr_indeces));
	}
	glPopMatrix();

	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitWindowSize(900, 780);
	glutCreateWindow("フィールド");

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,
		timer,
		0);

	for (int i = 0; i <= FEALDSIZE; ++i){
		for (int t = 0; t <= FEALDSIZE; ++t){
			position.x = t;
			position.y = pixels[i*t].r;
			position.z = i;

			v.push_back(position.x);
			v.push_back(position.y);
			v.push_back(position.z);
		}
	}





	for (int a = 0; a < FEALDSIZE; ++a){
		for (int b = 0; b < FEALDSIZE; ++b){
			unsigned short left[] = { b + (FEALDSIZE + 1)*a, b + 1 + (FEALDSIZE + 1)*a };
			unsigned short center[] = { b + 1 + (FEALDSIZE + 1)*a, FEALDSIZE + 2 + b + (FEALDSIZE + 1)*a };
			unsigned short right[] = { FEALDSIZE + 1 + b + (FEALDSIZE + 1)*a, FEALDSIZE + 1 + b + (FEALDSIZE + 1)*a };

			indeces.push_back(left[0]);
			indeces.push_back(center[0]);
			indeces.push_back(right[0]);

			indeces.push_back(left[1]);
			indeces.push_back(center[1]);
			indeces.push_back(right[1]);
		}
	}

	loadImage("Terrain1.bmp");

	glutMainLoop();
}
