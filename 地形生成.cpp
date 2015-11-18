#define _CRT_SECURE_NO_WARNINGS

#define FEALDSIZE (127.f)

#include<stdio.h>
#include<assert.h>
#include<vector>
#include<string>
#include<Windows.h>
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glut.h"

std::vector<float> v;
std::vector<unsigned short> n;
std::vector<float> uv;

glm::vec3 position = { 0, 0, 0 };

//透過度無し
class RGB{
public:
	unsigned char r, g, b;
};

RGB *pixels;
BITMAPFILEHEADER bmpHeader;
BITMAPINFOHEADER bmpInfoHeader;
//画像読み込み
void loadImage(char *_Filename){
	FILE *pBinMapFile;
	pBinMapFile = fopen(_Filename, "rb");

	assert(pBinMapFile != NULL);


	fread(
		&bmpHeader,
		sizeof(BITMAPFILEHEADER),
		1,
		pBinMapFile
		);

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



	float u, v;

	for (int i = 0; i <= FEALDSIZE; i++){
		for (int t = 0; t <= FEALDSIZE; t++){
			u = (1.f / FEALDSIZE)*t;
			v = (1.f / FEALDSIZE)*i;
			uv.push_back(u);
			uv.push_back(v);
		}
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
	glClearColor(0, 0, 1, 1);
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

	//viewMatrix = glm::lookAt();
	gluLookAt(
		0, 2, 2,
		0, 0, 0,
		0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE_MODE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	std::vector<float>::iterator itr_v = v.begin();
	glVertexPointer(
		3,
		GL_FLOAT,
		0,
		&(*itr_v));

	std::vector<float>::iterator itr_uv = uv.begin();
	glTexCoordPointer(
		2,
		GL_FLOAT,
		0,
		&(*itr_uv));

	glPolygonMode(
		GL_FRONT_AND_BACK,  // GLenum face
		GL_FILL);

	glEnable(GL_TEXTURE_2D);

	auto ind = n.begin();

	static float angle = 0.f;
	angle += 1.f;

	glRotatef(angle, 0, 1, 0);
	glTranslatef(-0.5f, 0, -0.5f);

	glDrawElements(GL_TRIANGLES, n.size(), GL_UNSIGNED_SHORT, &(*ind));

	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitWindowSize(900, 780);
	glutCreateWindow("title");

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	loadImage("test.bmp");

	glutTimerFunc(
		0,
		timer,
		0);

	for (int i = 0; i <= FEALDSIZE; ++i){
		for (int t = 0; t <= FEALDSIZE; ++t){
			//position = { 0, 0, 0 };
			position.x = (1.f / FEALDSIZE)*t;

			//unsigned int indian = pixels[bmpInfoHeader.biWidth*i + t].r + pixels[bmpInfoHeader.biWidth*i + t].g + pixels[bmpInfoHeader.biWidth*i + t].b;
			unsigned int a = (int)(((i / FEALDSIZE)*(bmpInfoHeader.biHeight-1))*bmpInfoHeader.biWidth + ((t / FEALDSIZE)*(bmpInfoHeader.biWidth-1)));

			unsigned int h = bmpInfoHeader.biHeight;
			unsigned int w = bmpInfoHeader.biWidth;
			unsigned int n1 = (int)((i / FEALDSIZE) * (h-1) * w) + ( (t / FEALDSIZE ) * (w-1) );
			a = n1;

			printf("%d\n",a);

			unsigned int indian = pixels[a].r +
				pixels[a].g +
				pixels[a].b;
			position.y = (indian / 3.f) / 255.f / 3;

			if (i == FEALDSIZE && t == FEALDSIZE){
				int aa = 0; 
				a++;
			}
			
			//position.y = 0;
			position.z = (1.f / FEALDSIZE)*i;

			v.push_back(position.x);
			v.push_back(position.y);
			v.push_back(position.z);
		}
	}

	printf("rgb = r:%d g:%d b:%d \n", pixels[8191].r, pixels[8191].g, pixels[8191].b);

	for (int t = 0; t < FEALDSIZE; t++){
		for (int i = 0; i < FEALDSIZE; i++){
			unsigned short left[] = { i + (FEALDSIZE + 1)*t, i + 1 + (FEALDSIZE + 1)*t };

			unsigned short center[] = { i + 1 + (FEALDSIZE + 1)*t, FEALDSIZE + 2 + i + (FEALDSIZE + 1)*t };

			unsigned short right[] = { FEALDSIZE + 1 + i + (FEALDSIZE + 1)*t, FEALDSIZE + 1 + i + (FEALDSIZE + 1)*t };

			//printf("%hu %hu %hu\n", left[0], center[0], right[0]);
			//printf("%hu %hu %hu\n", left[1], center[1], right[1]);
			//printf("\n");

			n.push_back(left[0]);
			n.push_back(center[0]);
			n.push_back(right[0]);

			n.push_back(left[1]);
			n.push_back(center[1]);
			n.push_back(right[1]);
		}
	}



	glutMainLoop();
}
