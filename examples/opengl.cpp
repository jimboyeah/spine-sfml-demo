#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#define freeglut_static
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

using namespace std;

// https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
// The following line is to favor the high performance NVIDIA GPU if there are multiple GPUs
// Has to be .exe module to be correctly detected.
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

// And the AMD equivalent
// Also has to be .exe module to be correctly detected.
extern "C" __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;

/*
 * OpenGL 2+ shader mode needs some function and macro definitions,
 * avoiding a dependency on additional libraries like GLEW or the
 * GL/glext.h header
 * Reference: 
 * https://github.com/KhronosGroup/OpenGL-Registry/tree/main/api/GL/glext.h
 * https://github.com/KhronosGroup/EGL-Registry/tree/main/api/KHR/khrplatform.h
 */
#ifndef GLAPIENTRY
#define GLAPIENTRY APIENTRY
#endif

PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallback;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLVALIDATEPROGRAMPROC glValidateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;

void initExtensionEntries(void)
{
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) glutGetProcAddress ("glDeleteProgram");
    glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKARBPROC) glutGetProcAddress ("glDebugMessageCallback");
    glBindBuffer = (PFNGLBINDBUFFERPROC) glutGetProcAddress ("glBindBuffer");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) glutGetProcAddress ("glEnableVertexAttribArray");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glutGetProcAddress ("glVertexAttribPointer");
    glBufferData = (PFNGLBUFFERDATAPROC) glutGetProcAddress ("glBufferData");
    glGenBuffers = (PFNGLGENBUFFERSPROC) glutGetProcAddress ("glGenBuffers");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) glutGetProcAddress ("glBindVertexArray");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glutGetProcAddress ("glGenVertexArrays");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) glutGetProcAddress ("glValidateProgram");
    glCreateShader = (PFNGLCREATESHADERPROC) glutGetProcAddress ("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC) glutGetProcAddress ("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC) glutGetProcAddress ("glCompileShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) glutGetProcAddress ("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC) glutGetProcAddress ("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) glutGetProcAddress ("glLinkProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC) glutGetProcAddress ("glUseProgram");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) glutGetProcAddress ("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glutGetProcAddress ("glGetShaderInfoLog");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) glutGetProcAddress ("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glutGetProcAddress ("glGetProgramInfoLog");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) glutGetProcAddress ("glGetAttribLocation");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glutGetProcAddress ("glGetUniformLocation");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glutGetProcAddress ("glUniformMatrix4fv");
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) glutGetProcAddress ("glUniformMatrix3fv");
    if (!glCreateShader || !glShaderSource || !glCompileShader || !glCreateProgram || !glAttachShader 
        || !glLinkProgram || !glUseProgram || !glGetShaderiv || !glGetShaderInfoLog || !glGetProgramiv)
    {
        fprintf (stderr, "One more OpenGL API not found.\n");
        exit(1);
    }
}

template <typename T>
class Vector2
{
public:
    Vector2(){};
    Vector2(T X, T Y);
    T x; ///< X coordinate of the vector
    T y; ///< Y coordinate of the vector
};

template <typename T>
Vector2<T>::Vector2(T X, T Y): x(X), y(Y) {};

typedef Vector2<float>  vec2;


bool ReadFile(string fileName, string &out)
{
    string line;
    stringstream ss;
    ifstream file (fileName, ios::ate); // position at end for size
    int size = file.tellg();
    file.seekg (0, ios::beg); // position at beginning of content
    if (!file.is_open()) return false;
    while (getline (file, line))
    {
        ss << line << endl;
    }
    file.close();
    out = ss.str();
    return true;
}

class InitShaderError: public runtime_error 
{
public:
    InitShaderError(char *str): runtime_error(str) {}
    InitShaderError(string str): runtime_error(str) {}
    InitShaderError(const InitShaderError &other): runtime_error(other) {}
};

void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        throw InitShaderError(string("Error creating shader type ") + to_string(ShaderType));
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        throw InitShaderError(string("Error compiling shader type ") + to_string(ShaderType) + ": "+ InfoLog);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

GLuint InitShader(const char *vsFileName, const char *fsFileName)
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        throw InitShaderError(string("Error creating shader program."));
    }
    
    string vs, fs;

    if (!ReadFile(vsFileName, vs)) {
        throw InitShaderError(string("Faile to read file content: ")+vsFileName);
    };

    if (!ReadFile(fsFileName, fs)) {
        throw InitShaderError(string("Faile to read file content: ")+fsFileName);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        // throw InitShaderError(string("Invalid shader program: ")+ErrorLog);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        // throw InitShaderError(string("Invalid shader program: ")+ErrorLog);
    }

    return ShaderProgram;
}

void init( void )
{
    vec2 points[6] =
    {
        vec2( -0.75, -0.75 ), vec2(  0.5, -0.5 ),
        vec2(  0.5,  0.5 ), vec2(  0.5,  0.5 ),
        vec2( -0.5,  0.5 ), vec2( -0.5, -0.5 )
    };
    GLuint vao, buffer;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER , buffer);
    glBufferData(GL_ARRAY_BUFFER , sizeof(points), points, GL_STATIC_DRAW);
    string vert = "../examples/opengl_insights_ch1.vert";
    string frag = "../examples/opengl_insights_ch1.frag";
    GLuint program = InitShader(vert.c_str(), frag.c_str());
    glUseProgram(program);
    // glDeleteProgram(program);
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES , 0, 6);
    glutSwapBuffers();
}

void GLAPIENTRY
MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, 
                 GLsizei length, const GLchar* message, const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "`GL ERROR`" : "" ), type, severity, message );
}

void keypress( unsigned char code, int x, int y )
{
    switch (code)
    {
        case 27: exit(0); break;
    }
}

void timer(int value)
{
    glutTimerFunc(300, timer, 8);
}

int main(int argc, char **argv) try
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello World");

    cout << "GL_SHADING_LANGUAGE_VERSION:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "GL_SHADING_LANGUAGE_VERSION_ARB:" << glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) << endl;
    // cout << "GL_EXTENSIONS:" << glGetString(GL_EXTENSIONS) << endl;
    cout << "GL_RENDERER:" << glGetString(GL_RENDERER) << endl;
    cout << "GL_VENDOR:" << glGetString(GL_VENDOR) << endl;
    cout << "GL_VERSION:" << glGetString(GL_VERSION) << endl;

    initExtensionEntries();

    // During init, enable debug output
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );
    init();
    cout << "GL_GetError: 0x" << hex << glGetError() << endl;
    glutDisplayFunc(display);
    glutKeyboardFunc(keypress);
    glutTimerFunc(300, timer, 9);
    glutMainLoop();
}
catch (runtime_error ex)
{
    cout << ex.what() << endl;
}