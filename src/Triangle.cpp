#include "Triangle.h"


Triangle::Triangle(Shader s, Texture1 t) {
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
       -.5f, .25f, 0.0,
       -.25f, .25f, 0.0,
       -0.375f, .5f, 0.0

    };

    unsigned int VBO, VAO;
   
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    this->VAO = VAO;
    this->VBO = VBO;
   
   
}


void Triangle::draw() {
    this->set();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::set() {
	this->s.use();
 
    glBindVertexArray(this->VAO);


}

