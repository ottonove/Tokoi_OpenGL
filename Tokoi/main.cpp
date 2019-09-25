#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(){
    
    // GLFWを初期化する
    if(glfwInit() == GL_FALSE){
        //初期化に失敗
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }
    
    //プログラム終了時の処理を登録する
    atexit(glfwTerminate); // 関数名のみ。()で実行はしない。
    
    //OpenGL Version 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // ウインドウを作成する
    GLFWwindow *const window(glfwCreateWindow(640, 480, "hello!", NULL, NULL));
    if(window == NULL){
        //ウインドウが作成できなかった
        std::cerr << "Can't create GLFW window." << std::endl;
        return 1;
    }
    
    // 作成したウインドウをOpenGLの処理対象にする
    glfwMakeContextCurrent(window);
    
    // GLEWを初期化する
    glewExperimental = GL_TRUE; //どうやら必要みたい。
    if(glewInit() != GLEW_OK){
        // GLEWの初期化に失敗
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }
    
    // ＊よくわからない＊
    // 垂直同期のタイミングを待つ
    glfwSwapInterval(1);
    
    // 背景色を指定する
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    // ウインドウが開いている間繰り返す
    // glfwWindowShouldCloseは、windowを閉じる必要がある時に、Trueになる。
    while(glfwWindowShouldClose(window) == GL_FALSE){
        
        // カラーウインドウを消去（glClearColorで指定した色で塗りつぶす）。
        glClear(GL_COLOR_BUFFER_BIT);
        
        // ここで描画処理
        
        // カラーバッファを入れ替える
        glfwSwapBuffers(window);
        
        // イベントを取り出す
        glfwWaitEvents();
    }
}
