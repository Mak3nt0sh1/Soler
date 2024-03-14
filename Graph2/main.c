#include <windows.h>
#include <gl/gl.h>
#include "stb-master/stb_easy_font.h"
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int width, height;

unsigned int texture;

void Game_Init()
{
    int w, h, cnt;
    unsigned char *data = stbi_load("First1.png", &w, &h, &cnt, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}



float vertex[] = {-0.3,-0.5,0, 0.3,-0.5,0, 0.3,0.1,0, -0.3,0.1,0};
float textCoord[] = {0,1, 1,1, 1,0, 0,0};


void Game_Show()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor3f(1,1,1);
    glPushMatrix();
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, textCoord);
        glDrawArrays(GL_TRIANGLE_FAN, 0 , 4);

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

}

typedef struct {
    char name[20];
    float vert[8];
    BOOL hover;
}TButton;

TButton btn[] = {
    {"start", {10,10, 110,10, 110,40, 10,40}, FALSE},
    {"stop", {10,50, 110,50, 110,80, 10,80}, FALSE},
    {"quit", {10,90, 110,90, 110,120, 10,120}, FALSE}

};
int btnCnt = sizeof(btn) / sizeof(btn[0]);

void TButton_Show(TButton btn)
{
    glEnableClientState(GL_VERTEX_ARRAY);
        if (btn.hover) glColor3f(1, 1, 1);
        else glColor3f(0.8,0.8,0.8);
        glVertexPointer(2, GL_FLOAT, 0, btn.vert);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

BOOL PointInButton(int x, int y, TButton btn)
{
    return (x>btn.vert[0]) && (x<btn.vert[4]) &&
    (y>btn.vert[1]) && (y<btn.vert[5]);
}

void Quad(float x, float y, float dx, float dy)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x,       y);
        glVertex2f(x+dx,    y);
        glVertex2f(x+dx, y+dy);
        glVertex2f(x,    y+dy);
    glEnd();
}


void ShowMenu()
{
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1,1);
        for(int i = 0; i < btnCnt; i++)
            TButton_Show(btn[i]);
    glPopMatrix();
}

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

    Game_Init();

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
            glClear(GL_COLOR_BUFFER_BIT);

            glColor3f(0.07, 0.25, 0.43);
            Quad(-2, 0.15, 4, 1);
            glColor3f(0.2, 0.2, 0.2);
            Quad(-2, 0.15, 4, -2);


            glPushMatrix();
                glTranslatef(0.5, 0.7, 0);
                glColor3f(0.73, 0.81, 0.89);
                Quad(0, 0, 0.2, 0.2);
            glPopMatrix();



            ShowMenu();

            Game_Show();



            SwapBuffers(hDC);

            theta += 1.0f;
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

        case WM_LBUTTONDOWN:
            for(int i = 0; i < btnCnt; i++)
                if (PointInButton(LOWORD(lParam), HIWORD(lParam), btn[i]))
                {
                    printf("%s\n", btn[i].name);
                    if(strcmp(btn[i].name, "quit") == 0)
                        PostQuitMessage(0);

                }

        break;

        case WM_MOUSEMOVE:
            for(int i = 0; i < btnCnt; i++)
                btn[i].hover = (PointInButton(LOWORD(lParam), HIWORD(lParam), btn[i]));

        break;


        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            glViewport(0, 0, width, height);
            glLoadIdentity();
            float k = width/(float)height;
            glOrtho(-k, k, -1,1, -1,1);
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

