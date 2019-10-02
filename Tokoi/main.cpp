#include <cstdlib>
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shape.h"

// プログラムオブジェクトを作成
// vsrc：バーテックスシェーダのソースプログラムの文字列
// fsrc：フラグメントシェーダのソースプログラムの文字列
GLuint createProgram(const char *vsrc, const char *fsrc){

    // 空のプログラムオブジェクトを作成する
    const GLuint program(glCreateProgram());
    
    // バーテックスシェーダのソースがあれば処理を実行
    if(vsrc != NULL){
        // バーテックスシェーダのシェーダオブジェクトを作成
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        // シェーダオブジェクトにソースを読み込む
        glShaderSource(vobj, 1, &vsrc, NULL);
        // 読み込んだソースをコンパイル
        glCompileShader(vobj);
        // コンパイルしたシェーダオブジェクトをプログラムオブジェクトに組み込む
        glAttachShader(program, vobj);
        // シェーダオブジェクトを削除
        glDeleteShader(vobj);
    }
    
    // フラグメントシェーダのソースがあれば処理を実行
    if(fsrc != NULL){
        // フラグメントシェーダのシェーダオブジェクトを作成
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        // シェーダオブジェクトにソースを読み込む
        glShaderSource(fobj, 1, &fsrc, NULL);
        // 読み込んだソースをコンパイル
        glCompileShader(fobj);
        // コンパイルしたシェーダオブジェクトをプログラムオブジェクトに組み込む
        glAttachShader(program, fobj);
        // シェーダオブジェクトを削除
        glDeleteShader(fobj);
    }
    
    // プログラムオブジェクトをリンクする
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);
    
    return program;
}

// 矩形の頂点の位置
constexpr Object::Vertex rectangleVertex[] = {
    { -0.5f, -0.5f },
    {  0.5f, -0.5f },
    {  0.5f,  0.5f },
    { -0.5f,  0.5f }
};

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
    
    // バーテックスシェーダのソース
    static constexpr GLchar vsrc[] =
    "#version 150 core\n"
    "in vec4 position;\n"
    "void main(){\n"
    "  gl_Position = position;\n"
    "}";
    
    // フラグメントシェーダのソースプログラム
    static constexpr GLchar fsrc[] =
    "#version 150 core\n"
    "out vec4 fragment;\n"
    "void main(){\n"
    "  fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}";
    
    // プログラムオブジェクトを作成する
    const GLuint program(createProgram(vsrc, fsrc));

    //図形データを作成
    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));
    
    // ウインドウが開いている間繰り返す
    // glfwWindowShouldCloseは、windowを閉じる必要がある時に、Trueになる。
    while(glfwWindowShouldClose(window) == GL_FALSE){
        
        // カラーウインドウを消去（glClearColorで指定した色で塗りつぶす）。
        glClear(GL_COLOR_BUFFER_BIT);
        
        // シェーダプログラムの使用開始
        glUseProgram(program);
        
        // ここで描画処理
        // 図形を描画する
        shape->draw();
        
        // カラーバッファを入れ替える
        glfwSwapBuffers(window);
        
        // イベントを取り出す
        glfwWaitEvents();
    }
}
