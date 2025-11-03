#include "Shader.h"

Shader::Shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    std::vector<unsigned int> modules;

    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));


    unsigned int shader = glCreateProgram();

    for (const auto val : modules) {
        glAttachShader(shader, val);
    }
    glLinkProgram(shader);


    int success;
    glGetShaderiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        std::cout << "Shader Module Linking Error:\n" << errorLog << "\n";
    }
    else {
        std::cout << "Shader Linking Successfull:\n";
    }

    for (const auto val : modules) {
        glDeleteShader(val);
    }

    this->ID = shader;

}



unsigned int Shader::make_module(const std::string& filepath, unsigned int module_type) {
    std::string shader_source = getShaderContent(filepath);

    const char* shader_src = shader_source.c_str();

    unsigned int shader_module = glCreateShader(module_type);
    glShaderSource(shader_module, 1, &shader_src, NULL);
    glCompileShader(shader_module);

    int success;
    glGetShaderiv(shader_module, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shader_module, sizeof(errorLog), NULL, errorLog);
        std::cout << "Shader Module Compilation Error:\n" << "Failed to compile FILE: " << filepath << " with error msg:\n" << errorLog << "\n";
    }
    else {
        std::cout << "Shader Compilation Successfull:\n";
    }

    return shader_module;
}


std::string Shader::getShaderContent(const std::string& filepath) {
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filepath);

        while (std::getline(file, line)) {
            bufferedLines << line << "\n";
        }
        file.close();
    }


    catch (std::ifstream::failure e) { 
        if (!file.eof()) {
            std::cout << "ERROR::SHADER::" << filepath << " FILE_NOT_SUCCESFULLY_READ " << e.what() << std::endl;
        }
        
    }


   
    std::string to_ret = bufferedLines.str();
    bufferedLines.str("");
    return to_ret;


}

void Shader::use() {
    glUseProgram(this->ID);
}


void Shader::setBool(const std::string& name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}