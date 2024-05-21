#include <windows.h>
#include <gl/gl.h>
#include <math.h>

float xAlfa = 20;
float zAlfa = 0;
POINTFLOAT pos = {0, 0};
float vert[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};
int n = 20;


void MoveCamera()
{
    if (GetKeyState(VK_UP) < 0) xAlfa = ++xAlfa > 180 ? 180 : xAlfa;
    if (GetKeyState(VK_DOWN) < 0) xAlfa = --xAlfa < 0 ? 0 : xAlfa;
    if (GetKeyState(VK_LEFT) < 0) zAlfa++;
    if (GetKeyState(VK_RIGHT) < 0) zAlfa--;

    float ungol = -zAlfa / 180 * M_PI;
    float speed = 0;
    if (GetKeyState('W') < 0) speed = 0.1;
    if (GetKeyState('S') < 0) speed = -0.1;
    if (GetKeyState('A') < 0) { speed = 0.1; ungol -= M_PI*0.5; }
    if (GetKeyState('D') < 0) { speed = 0.1; ungol += M_PI*0.5; }
    if (speed != 0)
    {
        pos.x += sin(ungol) * speed;
        pos.y += cos(ungol) * speed;
    }

    glRotatef(-xAlfa, 1, 0, 0);
    glRotatef(-zAlfa, 0, 0, 1);
    glTranslatef(-pos.x, -pos.y, -3);
}

float vertex[] = {-1,-1,1, 1,-1,1, 1,1,1, -1,1,1};
float normal[] = {-1,-1,1, 1,-1,1, 1,1,1, -1,1,1};

void drawCoords() {//coordinate axes
    glBegin(GL_LINES);
    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void Draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glNormalPointer(GL_FLOAT, 0, normal);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawTile(float tileSize)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glNormalPointer(GL_FLOAT, 0, normal);
        glEnable(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(tileSize, 0.0f, 0.0f);
        glVertex3f(tileSize, tileSize, 0.0f);
        glVertex3f(0.0f, tileSize, 0.0f);
        glEnd();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void drawChessboard(int n, float posX, float posY, float PosZ){
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    for (int i = -n; i < n; i++) {
        for (int j = -n; j < n; j++) {
            if ((i + j) % 2 == 0) glColor3f(0.1f, 0.7f, 0.55f);
            else glColor3f(0.63f, 0.3f, 0.0f);

            glPushMatrix();
            glTranslatef(i*2, j*2, -1);
            Draw();
            glPopMatrix();
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawCube1()
{
    glPushMatrix();
        glScalef(1, 1, 1);
        glTranslatef(1, -1, 1);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 0,1,0);
        Draw();
        glRotatef(180, 0,1,0);
        Draw();
    glPopMatrix();
}

void DrawCube2()
{
    glPushMatrix();
        glScalef(1.5, 1.5, 1.5);
        glTranslatef(7, -7, 1);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 0,1,0);
        Draw();
        glRotatef(180, 0,1,0);
        Draw();
    glPopMatrix();
}

void DrawCube3()
{
    glPushMatrix();
        glScalef(0.7, 0.7, 0.7);
        glTranslatef(-5, 6, 1);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 0,1,0);
        Draw();
        glRotatef(180, 0,1,0);
        Draw();
    glPopMatrix();
}

void DrawCube4()
{
    glPushMatrix();
        glScalef(1, 1, 1);
        glTranslatef(6.5, 7, 1);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 0,1,0);
        Draw();
        glRotatef(180, 0,1,0);
        Draw();
    glPopMatrix();
}

void DrawCube5()
{
    glPushMatrix();
        glScalef(1, 1, 1);
        glTranslatef(-7, -8, 1);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 1,0,0);
        Draw();
        glRotatef(90, 0,1,0);
        Draw();
        glRotatef(180, 0,1,0);
        Draw();
    glPopMatrix();
}
void Init()
{
    glEnable(GL_BLEND);/*разрешение смешивания цветов*/
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);/*настройка смешивания цветов для каждой точки*/
    /*как будет братся цвет из источника, как будет братся цвет из приемника */

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
}

void DrawTruncatedPyramid(const int n) {
    const float pi = acos(-1);
    const float height = 1.0f;
    const float top_radius = 0.5f;
    const float bottom_radius = 1.0f;

    const int vn = 2 * n; // количество вершин (верхнее и нижнее основания)
    const int fn = 4 * n; // количество граней (каждая грань состоит из трех вершин)

    float vertices[3 * vn]; // вершины пирамиды
    float normals[3 * vn];  // нормали
    GLuint faces[3 * fn];   // грани пирамиды

    // Вершины нижнего основания
    for (int i = 0; i < n; i++) {
        float phi = 2 * pi * (float)i / (float)n;
        float x = bottom_radius * cos(phi);
        float y = bottom_radius * sin(phi);

        vertices[3 * i + 0] = x;
        vertices[3 * i + 1] = y;
        vertices[3 * i + 2] = -height / 2;

        normals[3 * i + 0] = 0;
        normals[3 * i + 1] = 0;
        normals[3 * i + 2] = -1;
    }

    // Вершины верхнего основания
    for (int i = 0; i < n; i++) {
        float phi = 2 * pi * (float)i / (float)n;
        float x = top_radius * cos(phi);
        float y = top_radius * sin(phi);

        vertices[3 * (n + i) + 0] = x;
        vertices[3 * (n + i) + 1] = y;
        vertices[3 * (n + i) + 2] = height / 2;

        normals[3 * (n + i) + 0] = 0;
        normals[3 * (n + i) + 1] = 0;
        normals[3 * (n + i) + 2] = 1;
    }

    // Боковые грани
    for (int i = 0; i < n; i++) {
        // First triangle
        faces[6 * i + 0] = i;
        faces[6 * i + 1] = (i + 1) % n;
        faces[6 * i + 2] = i + n;

        // Second triangle
        faces[6 * i + 3] = (i + 1) % n;
        faces[6 * i + 4] = (i + 1) % n + n;
        faces[6 * i + 5] = i + n;
    }

    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Drawing bottom base
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1);
    for (int i = 0; i < n; i++) {
        glVertex3fv(&vertices[3 * i]);
    }
    glEnd();

    // Drawing top base
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    for (int i = 0; i < n; i++) {
        glVertex3fv(&vertices[3 * (n + i)]);
    }
    glEnd();

    // Drawing side faces
    for (int i = 0; i < n; i++) {
        glBegin(GL_QUADS);
        // Compute normal for the quad
        float nx = (vertices[3 * i + 0] + vertices[3 * (n + i) + 0]) / 2;
        float ny = (vertices[3 * i + 1] + vertices[3 * (n + i) + 1]) / 2;
        float length = sqrt(nx * nx + ny * ny);
        nx /= length;
        ny /= length;

        glNormal3f(nx, ny, 0);
        glVertex3fv(&vertices[3 * i]);
        glVertex3fv(&vertices[3 * ((i + 1) % n)]);
        glVertex3fv(&vertices[3 * (((i + 1) % n) + n)]);
        glVertex3fv(&vertices[3 * (i + n)]);
        glEnd();
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glPopMatrix();
}

void DrawDoubleTruncatedPyramid(const int n) {
    glPushMatrix();

    // Рисуем нижнюю усечённую пирамиду
    DrawTruncatedPyramid(n);

    // Перемещаемся к верхнему основанию и рисуем перевёрнутую усечённую пирамиду
    glTranslatef(0, 0, 1.0f); // Перемещаемся на высоту нижней пирамиды
    glRotatef(180, 1, 0, 0); // Переворачиваем пирамиду
    DrawTruncatedPyramid(n);

    glPopMatrix();
}



LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          700,
                          700,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    glFrustum(-1,1, -1,1, 2,80);
    glEnable(GL_DEPTH_TEST); /*òåñò ãëóáèíû*/


    glMatrixMode(GL_PROJECTION);/*ìàòðèöà ïðîåêöèé*/
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.2, 1000);
    glMatrixMode(GL_MODELVIEW);/*ìàòðèöà ìîäåëåé*/
    glLoadIdentity();

    glEnable(GL_LIGHTING);/*допуск к освещению*/
    glEnable(GL_LIGHT0);/*режим*/
    glEnable(GL_COLOR_MATERIAL); /*материал*/
    glEnable(GL_NORMALIZE);/*доступ к нормали*/

    Init();

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPushMatrix();
                MoveCamera();
                drawCoords();
                drawChessboard(n, -n * 2 / 2.0f, -n * 2 / 2.0f, -1);

                glPushMatrix();
                    glRotatef(24,0,0,1);
                    glRotatef(theta,0,1,0);
                    float position[] = {0,0,1,0};
                    glLightfv(GL_LIGHT0, GL_POSITION, position);

                    glTranslatef(0,0,40);
                    glScalef(1,1,1);
                    glColor3f(1,1,1);
                    Draw();
                glPopMatrix();

                glColor3f(1,0,0);
                DrawCube1();
                glColor3f(0,1,1);
                DrawCube2();
                glColor3f(1,0.6,0.3);
                DrawCube3();
                glColor3f(0.3,0.7,1);
                DrawCube4();
                glColor3f(1,0.3,0.9);
                DrawCube5();

                glTranslatef(-13.0, 5.0, 0.5);
                float transparency = 0.1;
                for (int i = 0; i < 10; i++)
                {
                    glPushMatrix();
                        glRotatef(36*i, 0, 0, 1);
                        glTranslatef(5, 0, 0);
                        glColor4f(0.425,0.078,0.718,transparency);
                        DrawDoubleTruncatedPyramid(23);
                    glPopMatrix();
                    transparency += 0.1;
                }


            glPopMatrix();

            theta++;
            SwapBuffers(hDC);

            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
