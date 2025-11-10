#include "Cube.h"
Cube::Cube(Shader s, Texture1 t) {
    this->setShader(s);
    this->setTexture(t);
    this->build();
}

Cube::Cube(Shader s) {
    this->setShader(s);
    this->build();
}


void Cube::build() {

    float size = .8f;
    float vertices[] = {
        0.0f,  0.0f, 0.0f,   // 0
        0.0f, 0.0f, size, // 1
        0.f, size, 0.f, // 2
        size, 0.0f, 0.0f, //3
        0.0f,  size, size, // 4


        size, size, 0.f, // 5
        size, size, size, // 6
        size, 0.f , size // 7
        
    };
    unsigned int indices[] = {  // note that we start from 0!
        7,6,5,
        7,3,5,

        7,1,4,
        6,7,4,

        0,2,5,
        0,3,5,

        2,4,0,
        1,4,0,

        1,7,3,
        0,1,3,

        2,5,6,
        2,6,4
    };




    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

  

    this->VAO = VAO;
    this->VBO = VBO;
    this->EBO = EBO;



}


void Cube::draw() {
    this->set();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::set() {
    this->s.use();

  
    glBindVertexArray(this->VAO);
}

