#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<vector>
#include<string>
#include<Windows.h>
#include"glut.h"

//�A���O��
float angle = 0.0f;

//���_��
unsigned int nVertices;

//�C���f�b�N�X��
unsigned int nIndeces;

//�@����
unsigned int nNormals;

//uv���W��
//unsigned int nTextures;

std::vector<float>vect_v;
std::vector<unsigned short>vect_i;
std::vector<float>vect_n;
//std::vector<float>vect_t;

//struct RGB{
//	unsigned char r, g, b;
//};

//void loadImage(char *_Filename){
//	//�摜�ǂݍ���
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
//		GL_RGB,          //GLint internalformat(��������e�N�X�`���̃t�H�[�}�b�g)
//		bmpInfoHeader.biWidth,               //GLsizei width
//		bmpInfoHeader.biHeight,               //GLsizei height
//		0,               //GLint border
//		GL_RGB,          //GLenum format(�s�N�Z���f�[�^�̃t�H�[�}�b�g)
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
			//�ǂݔ�΂�
			fscanf(pFile, "%*s", buf);// "{"
			fscanf(pFile, "%*s", buf);// "//"
			fscanf(pFile, "%*s", buf);// "����"
			fscanf(pFile, "%*s", buf);// "mesh"

			//���_���ǂݍ���
			fscanf(pFile, "%u", &nVertices);
			printf("���_��:%u\n", nVertices);
			fscanf(pFile, "%*s", buf);// ";"

			//���_�̓ǂݍ���
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

			//�C���f�b�N�X���ǂݍ���
			fscanf(pFile, "%u", &nIndeces);
			printf("�C���f�b�N�X��:%u\n", nIndeces);
			fscanf(pFile, "%*s", buf);// ";"

			//�C���f�b�N�X�ǂݍ���
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

			//�ǂݔ�΂�
			fscanf(pFile, "%*s", buf);// "MeshNormals"
			fscanf(pFile, "%*s", buf);// "}"
			fscanf(pFile, "%*s", buf);// "//"
			fscanf(pFile, "%*s", buf);// "����"
			fscanf(pFile, "%*s", buf);// "normals"

			//�@�����ǂݍ���	
			fscanf(pFile, "%u", &nNormals);
			printf("�@����:%u\n", nNormals);
			fscanf(pFile, "%*s", buf);

			//�@���ǂݍ���
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
		0,//GLsizei stride//���_�f�[�^�̊Ԋu
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
	glutCreateWindow("x�t�@�C���ǂݍ���(ver2.7)");

	loadXFile("animationPanda.x");
	//loadImage("cellwall.bmp");

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,
		timer,
		0);

	glutMainLoop();
}