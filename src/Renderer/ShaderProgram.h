#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // ���������� glad ��� ��������� ���� ������������ ������ OpenGL

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // ID - ������������� ���������
    unsigned int ID;

    // ����������� ��������� ������ � ��������� ���������� �������
    Shader(const char* vertexPath, const char* fragmentPath);

    // �������������/��������� �������
    void use();

    // �������� uniform-�������
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;  
};

#endif