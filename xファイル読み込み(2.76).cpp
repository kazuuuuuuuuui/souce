#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<vector>
#include<string>
#include<Windows.h>
#include"glut.h"

//アングル
float angle = 0.0f;

//頂点数
unsigned int nVertices;

//インデックス数
unsigned int nIndeces;

//法線数
unsigned int nNormals;

//uv座標数
//unsigned int nTextures;

std::vector<float>vect_v;
std::vector<unsigned short>vect_i;
std::vector<float>vect_n;
//std::vector<float>vect_t;

//struct RGB{
//	unsigned char r, g, b;
//};

//void loadImage(char *_Filename){
//	//画像読み込み
//	FILE *pBinMapFile;
//	pBinMapFile = fopen(_Filename, "rb");
//
//	assert(pBinMapFile != NULL);
//
//	BITMAPFILEHEADER bmpHeader;
//	fread(
//		&bmpHeader,
//		sizeof(BITMAPFILEHEADER),
//		1,
//		pBinMapFile
//		);
//
//	BITMAPINFOHEADER bmpInfoHeader;
//	fread(
//		&bmpInfoHeader,
//		sizeof(BITMAPINFOHEADER),
//		1,
//		pBinMapFile
//		);
//
//	int size = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGB);
//	RGB *pixels = (RGB*)malloc(size);
//
//	fread(
//		pixels,
//		size,
//		1,
//		pBinMapFile
//		);
//	fclose(pBinMapFile);
//
//
//	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
//		unsigned char keep;
//		keep = pixels[i].r;
//		pixels[i].r = pixels[i].b;
//		pixels[i].b = keep;
//	}
//
//	glTexParameteri(
//		GL_TEXTURE_2D,          // GLenum target
//		GL_TEXTURE_MIN_FILTER,  // GLenum pname
//		GL_NEAREST);            // GLint param
//
//	glTexParameteri(
//		GL_TEXTURE_2D,          // GLenum target
//		GL_TEXTURE_MAG_FILTER,  // GLenum pname
//		GL_NEAREST);
//
//	glTexImage2D(
//		GL_TEXTURE_2D,   //GLenum target
//		0,               //GLint level
//		GL_RGB,          //GLint internalformat(生成するテクスチャのフォーマット)
//		bmpInfoHeader.biWidth,               //GLsizei width
//		bmpInfoHeader.biHeight,               //GLsizei height
//		0,               //GLint border
//		GL_RGB,          //GLenum format(ピクセルデータのフォーマット)
//		GL_UNSIGNED_BYTE,//GLenum type
//		pixels          //const GLvoid *pixels
//		);
//
//	free(pixels);
//}

void loadXFile(const char *_xFileName){
	FILE *pFile = fopen(_xFileName, "r");
	assert(pFile != NULL);

	char buf[256];

	while (EOF != fscanf(pFile, "%s", buf)){
		if (strcmp("Mesh", buf) == 0){
			//読み飛ばし
			fscanf(pFile, "%*s", buf);// "{"
			fscanf(pFile, "%*s", buf);// "//"
			fscanf(pFile, "%*s", buf);// "平面"
			fscanf(pFile, "%*s", buf);// "mesh"

			//頂点数読み込み
			fscanf(pFile, "%u", &nVertices);
			printf("頂点数:%u\n", nVertices);
			fscanf(pFile, "%*s", buf);// ";"

			//頂点の読み込み
			for (int i = 0; i < nVertices; i++){
				float v[3];
				fscanf(pFile, "%f", &v[0]);
				fscanf(pFile, "%*c", buf);// ";"

				fscanf(pFile, "%f", &v[1]);
				fscanf(pFile, "%*c", buf);// ";"

				fscanf(pFile, "%f", &v[2]);
				fscanf(pFile, "%*s", buf);// ";,"

				vect_v.push_back(v[0]);
				vect_v.push_back(v[1]);
				vect_v.push_back(v[2]);
			}

			//インデックス数読み込み
			fscanf(pFile, "%u", &nIndeces);
			printf("インデックス数:%u\n", nIndeces);
			fscanf(pFile, "%*s", buf);// ";"

			//インデックス読み込み
			for (int i = 0; i < nIndeces; i++){
				fscanf(pFile, "%*2s", buf);// "3;"
				unsigned short indeces[3];
				fscanf(pFile, "%hu", &indeces[0]);
				fscanf(pFile, "%*c", buf);//","

				fscanf(pFile, "%hu", &indeces[1]);
				fscanf(pFile, "%*c", buf);//","

				fscanf(pFile, "%hu", &indeces[2]);
				fscanf(pFile, "%*s", buf);//";,"

				vect_i.push_back(indeces[0]);
				vect_i.push_back(indeces[1]);
				vect_i.push_back(indeces[2]);
			}

			//読み飛ばし
			fscanf(pFile, "%*s", buf);// "MeshNormals"
			fscanf(pFile, "%*s", buf);// "}"
			fscanf(pFile, "%*s", buf);// "//"
			fscanf(pFile, "%*s", buf);// "平面"
			fscanf(pFile, "%*s", buf);// "normals"

			//法線数読み込み	
			fscanf(pFile, "%u", &nNormals);
			printf("法線数:%u\n", nNormals);
			fscanf(pFile, "%*s", buf);

			//法線読み込み
			for (int i = 0; i < nNormals; i++){
				float normals[3];
				fscanf(pFile, "%f", &normals[0]);
				fscanf(pFile, "%*c", buf);//";"

				fscanf(pFile, "%f", &normals[1]);
				fscanf(pFile, "%*c", buf);//";"

				fscanf(pFile, "%f", &normals[2]);
				fscanf(pFile, "%*s", buf);//";,"

				vect_n.push_back(normals[0]);
				vect_n.push_back(normals[1]);
				vect_n.push_back(normals[2]);
			}

		}

	}

	fclose(pFile);
}

void timer(int value){
	angle += 0.8f;

	glutPostRedisplay();
	glutTimerFunc(
		1000 / 60,
		timer,
		0);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		90,//GLdouble fovy,
		1,//GLdouble aspect,
		0.1,//GLdouble zNear,
		100);//GLdouble zFar
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0, 0, 10,
		0, 0, 0,
		0, 1, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	std::vector<float>::iterator itr_v = vect_v.begin();
	glVertexPointer(
		3,//GLint size
		GL_FLOAT,//GLenum type
		0,//GLsizei stride//頂点データの間隔
		&(*itr_v)//const GLvoid *pointer
		);

	std::vector<float>::iterator itr_n = vect_n.begin();
	glNormalPointer(
		GL_FLOAT,
		0,
		&(*itr_n));

	//std::vector<float>::iterator itr_t = vect_t.begin();
	//glTexCoordPointer(
	//	2,//GLint size
	//	GL_FLOAT,//GLenum type
	//	0,//GLsizei stride
	//	&(*itr_t));//const GLvoid *pointer

	glRotatef(angle, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//glEnable(GL_TEXTURE_2D);

	std::vector<unsigned short>::iterator itr_i = vect_i.begin();
	
	/*glDrawArrays(GL_TRIANGLES
		, 0, nVertices);*/

	glDrawElements(
		GL_TRIANGLES,//GLenum mode
		nIndeces * 3,//GLsizei count
		GL_UNSIGNED_SHORT,//GLenum type
		&(*itr_i)//const GLvoid *indices
		);

	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(900, 780);
	glutCreateWindow("xファイル読み込み(ver2.7)");

	loadXFile("animationPanda.x");
	//loadImage("cellwall.bmp");

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,
		timer,
		0);

	glutMainLoop();
}