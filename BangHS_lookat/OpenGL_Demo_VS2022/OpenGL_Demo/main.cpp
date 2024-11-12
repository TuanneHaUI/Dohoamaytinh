#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <freeglut.h>

#include <vector_matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	 -0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4  model_mat_cpp;
int model_mat_location;

mat4 view_mat_cpp;			//Ma trận view	
float T[3] = { 0.0f, 0.0f, 0.0f };
float Alpha_1 = 0.0f;
float Alpha_2 = 0.0f;
// Biến truyền dữ liệu cho uniform
int	view_mat_location;

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------
// Hàm vẽ mặt bang
void matbang()
{
	mat4 instance = identity_mat4();
	
	instance = model_mat_cpp * scale(vec3(1.2, 0.7, 0.06));

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);	
	
}
// ------------------------------------------

//Hàm vẽ vien bang
void viendoc()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.05, 0.7, 0.05));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);		
}
void vienngang()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(1.2, 0.05, 0.05));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


// ---------------------------------------------------------------------------	
void DisplayFunc(void)
{
	vec3	eye(0.1f, 0.1f, 0.2f),
			at(0.0f, 0.0f, 0.0f),
			up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);


	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");

	model_mat_cpp = identity_mat4();
	model_mat_cpp = rotate_y(Alpha_2) * rotate_x(Alpha_1) * translate(vec3(T[0], T[1], T[2]));
	//Mặt bàn	
	matbang();
	
	//Chân trước trái		
	model_mat_cpp = rotate_y(Alpha_2) * rotate_x(Alpha_1) * translate(vec3(T[0], T[1], T[2])) *translate(vec3(-0.58, -0.0, -0.05));
	viendoc();
	model_mat_cpp = rotate_y(Alpha_2) * rotate_x(Alpha_1) * translate(vec3(T[0], T[1], T[2]))*translate(vec3(0.58, -0.0, -0.05));
	viendoc();
	model_mat_cpp = rotate_y(Alpha_2) * rotate_x(Alpha_1) * translate(vec3(T[0], T[1], T[2])) *translate(vec3(0.0, -0.33, -0.05));
	vienngang();
	model_mat_cpp = rotate_y(Alpha_2) * rotate_x(Alpha_1) * translate(vec3(T[0], T[1], T[2]))*translate(vec3(0.0, 0.33, -0.05));
	vienngang();

	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;
		// tịnh tiến theo trục x
	case 'x':
		T[0] -= 0.05f;
		break;
	case 'X':
		T[0] += 0.05f;
		break;
		// tịnh tiến theo trục y
	case 'y':
		T[1] -= 0.05f;
		break;
	case 'Y':
		T[1] += 0.05f;
		break;
		// tịnh tiến theo trục z
	case 'z':
		T[2] -= 0.05f;
		break;
	case 'Z':
		T[2] += 0.05f;
		break;
		// nhấn phím x hoặc X để quay
	case 'w'  :
			Alpha_1 -= 10.0f; break;
	case 's' :
			Alpha_1 += 10.0f; break;
	case 'a':
		Alpha_2 -= 10.0f; break;
	case 'd':
		Alpha_2 += 10.0f; break;
	}

}
// ------------------------------------------

// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Bang den");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}