#include "program_p2_c4.h"

PROGRAM_P2_C4::PROGRAM_P2_C4()
{
    _position   =   -1;
    _normal     =   -1;
    _uv         =   -1;
    _color      =   -1;
    _colorOffset=   -1;
    _MVP        =   -1;
    _lightDir   =   -1;
    _texture    =   -1;
    _texture1   =   -1;
}

bool PROGRAM_P2_C4::initialize()
{
    //!1\使用（varying），是表示需要在（vs）和（ps）之间进行传递的变量，
    //!  把需要传递的变量在（vs）中赋值，并在（ps）中重复使用（varying）语句即可
    //!2\知识点，光线和法线的点积产生的值与光线的颜色相乘就是打在屏幕上的亮度，
    //! 一般选择光线的颜色是白色的，而光源由eye发出
    //! 颜色是顶点shader的特征，在顶点shader中定义并传递(顶点shader三大特征：顶点坐标，uv和颜色)
    const char* vs  =
    {
        "uniform    mat4    _MVP;"
        "uniform    vec3    _lightDir;"
        "uniform    vec3    _color;"
        "uniform    vec3    _colorOffset;"
        "attribute  vec3    _position;"
        "attribute  vec3    _normal;"
        "attribute  vec2    _uv;"
        "varying    vec4    _outColor;"
        "varying    vec2    _outUV;"

        "void main()"
        "{"
        "   _outUV      =   _uv;"
        "   float NDotL =   max(dot(_normal, _lightDir), 0.0);"
        "   _outColor   =   vec4(_color*NDotL+_colorOffset,1);"
        "   vec4    pos =   vec4(_position,1);"
        "   gl_Position =   _MVP * pos;"
        "}"
    };
    const char* ps  =
    {
        "precision  lowp        float; "
        "uniform    sampler2D   _texture;"
        "uniform    sampler2D   _texture1;"
        "varying    vec4        _outColor;"
        "varying    vec2        _outUV;"
        "void main()"
        "{"
        "   vec4 color      =   texture2D(_texture,_outUV);"
        "   vec4 color1     =   texture2D(_texture1,_outUV);"
        "   vec4 dstColor   =   (1.0-color1.a)*color + color1.a*color1;"
        "   gl_FragColor    =   _outColor * dstColor ;"
        "}"
    };
    //!注意：在shader中，（1-color.a）一定要写成（1.0-color.a）,不然会报看不懂的错误。
    //!上面的if语句，表示如果颜色中的alpha值<0.2,那么就不绘制（discard）出来。
    //!在上面的（"gl_FragColor=tcolor0 + tcolor1;"）中，用（+）图像变亮；用（*）图像变暗。
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        //!~需要注意变量的类型
        _position   =   glGetAttribLocation(_programId,"_position");
        _normal     =   glGetAttribLocation(_programId,"_normal");
        _uv         =   glGetAttribLocation(_programId,"_uv");
        _color      =   glGetUniformLocation(_programId,"_color");
        _colorOffset=   glGetUniformLocation(_programId,"_colorOffset");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
        _lightDir   =   glGetUniformLocation(_programId,"_lightDir");
        _texture    =   glGetUniformLocation(_programId,"_texture");
        _texture1   =   glGetUniformLocation(_programId,"_texture1");
    }
    return  res;
}

void PROGRAM_P2_C4::begin()
{
    glUseProgram(_programId);
    //!在显卡里面使用的局部变量，在使用时是需要进行使能和关闭的
    glEnableVertexAttribArray(_position);       
    glEnableVertexAttribArray(_normal);
    glEnableVertexAttribArray(_uv);
}

void PROGRAM_P2_C4::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_normal);
    glDisableVertexAttribArray(_uv);
    glUseProgram(0);
}
