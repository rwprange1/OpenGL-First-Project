#include "Triangle.h"


Triangle::Triangle(Shader s, Texture t) {
	this->setShader(s);
	this->setTexture(t);
	this->build();
}

Triangle::Triangle(Shader s) {
	this->setShader(s);
	this->build();
}


void Triangle::build() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0, // left  
         0.5f, -0.5f, 0.0f, 1.0, // right 
         0.0f,  0.5f, 0.0f, 1.0  // top   
    };

    
   
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    glBindVertexArray(this->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    std::cout << "VAO: ", this->VAO;
}


void Triangle::draw() {
    this->set();
    std::cout << "Drawing triangle\n";
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::set() {
	this->s.use();
    glBindVertexArray(this->VAO);


}

