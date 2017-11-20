#include "myshaderbillboard.h"

MyShaderBillboard::MyShaderBillboard()
{
    _pos    =   -1;
    _uv     =   -1;
    _MVP    =   -1;
    _texture=   -1;
}

MyShaderBillboard::~MyShaderBillboard()
{

}

void MyShaderBillboard::initialize()
{
    const char* vs =
    {
        "uniform    mat4    _MVP;\n\
        attribute   vec3    _pos; \n\
        attribute   vec2    _uv; \n\      
        varying     vec2    _outUV;\n\
        void main()\n\
        {\n\
            vec3  newPos  = _pos ;\n\
            gl_Position =   _MVP * vec4(newPos,1.0); \n\
            _outUV      =   _uv;\n\
        }"
    };
    const char* ps =
    {
        "precision  lowp        float; "
        "uniform    sampler2D   _texture;\n\
        varying     vec2        _outUV;\n\
        void main()\n\
        {\n\
          vec4   color   =   texture2D(_texture,_outUV); \n\
          if(color.a < 0.2) discard;\n\
          gl_FragColor   =   color;\n\
        }"
    };

    bool    res =   createProgram(vs, ps);
    if(res)
    {
        _pos        =   glGetAttribLocation(_programId, "_pos");
        _uv         =   glGetAttribLocation(_programId, "_uv");
        _MVP        =   glGetUniformLocation(_programId, "_MVP");
        _texture    =   glGetUniformLocation(_programId, "_texture");
    }

}

void MyShaderBillboard::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray(_pos);
    glEnableVertexAttribArray(_uv);
}

void MyShaderBillboard::end()
{
    glDisableVertexAttribArray(_pos);
    glDisableVertexAttribArray(_uv);
    glUseProgram(0);
}
