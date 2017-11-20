#ifndef MYSHADERBILLBOARD_H
#define MYSHADERBILLBOARD_H

#include "tool/programid.h"

class MyShaderBillboard : public ProgramId
{
public:
    MyShaderBillboard();
    ~MyShaderBillboard();

public:
    typedef int attribute;
    typedef int uniform;
public:
    attribute   _pos;
    attribute   _uv;
    uniform     _MVP;
    uniform     _texture;

    /// 初始化函数
    virtual void    initialize();

    /**
    *   使用程序
    */
    virtual void    begin();
    /**
    *   使用完成
    */
    virtual void    end();
};

#endif // MYSHADERBILLBOARD_H
