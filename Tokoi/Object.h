#pragma once
#include <array>
#include <GL/glew.h>

// 図形データ
class Object{
    // 頂点配列オブジェクト
    GLuint vao;
    // 頂点バッファオブジェクト
    GLuint vbo;
    
public:
    // 頂点属性
    struct Vertex{
        //位置
        GLfloat position[2];
    };
    
    //コンストラクタ
    Object(GLint size, GLsizei vertexcount, const Vertex *vertex){
        // 【頂点配列オブジェクト】
        //頂点配列オブジェクトの作成
        glGenVertexArrays(1, &vao);
        //頂点配列オブジェクト(VAO)を結合して使用可能にする。
        glBindVertexArray(vao);
        
        // 【頂点バッファオブジェクト】
        //頂点バッファオブジェクト(VBO)を作成。
        glGenBuffers(1, &vbo);
        //頂点バッファオブジェクト(VBO)を結合して使用可能にする。
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //頂点バッファオブジェクトのメモリを確保し、そこにデータ(頂点属性)を転送する。
        glBufferData(GL_ARRAY_BUFFER, vertexcount * sizeof (Vertex), vertex, GL_STATIC_DRAW);
        
        //頂点バッファオブジェクトとattribute変数の関連付け。
        //結合されている頂点バッファオブジェクトをin変数から参照できるようにする
        //描画時にattribute変数が受け取るデータの格納場所と書式を指定する。
        glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }
        
    //デストラクタ
    virtual ~Object(){
        //頂点配列オブジェクト削除
        glDeleteVertexArrays(1, &vao);
        
        //頂点バッファオブジェクト削除
        glDeleteBuffers(1, &vbo);
    }

    
private:
    //コピーコンストラクタによるコピー禁止
    Object(const Object &o);
    
    //代入によるコピー禁止
    Object &operator=(const Object &o);


public:
    //頂点配列オブジェクトの結合
    void bind() const{
        //描画する頂点配列オブジェクトを指定する
        glBindVertexArray(vao);
    }
};
