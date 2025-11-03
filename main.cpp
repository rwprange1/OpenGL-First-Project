#include "main.h"





int main(void){

    GLFWwindow* window;



    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "GLFW failed to start";
        return -1;
    }
        

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        std::cout << "GLFW failed to create a window";
        glfwTerminate();
        return -1;
    }

    std::cout << "GLFW started and created a window\n";
    glfwMakeContextCurrent(window);

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Couldnt load opengl\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL loaded\n";

   
    glClearColor(.75f, .25f, .8f, 1.f);

    Shader shader = Shader("vertexShader.txt", "fragmentShader.txt");
    //Texture texture1 = Texture("container.jpg", false, 0, false);
    //Texture texture2 = Texture("awesomeface.png", true, 1, true);
    Camera camera = Camera(glm::vec3(3.f, 3.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    camera.build_projection(-1.f, 1.f, -1.f, 1.f, 1.f, 1000.f);

    unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
    //unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
   
    
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
   
    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
  
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));

   
    
    unsigned int VBO, VAO, EBO;
    build_axis(VBO, VAO, EBO);

    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   
        processInput(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        
    
        

        //glActiveTexture(texture1.position);
        //glBindTexture(GL_TEXTURE_2D, texture1.ID);
        
        //glActiveTexture(texture2.position);
        //glBindTexture(GL_TEXTURE_2D, texture2.ID);

        // render container
    
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES,0,6);


        /**
     
            THIS GENERATES TWO DISJOINT TRIANGLES NEED TO UNCOMMENT ABOVE MATERIAL
             glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // then we draw the second triangle using the data from the second VAO
        
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        */
       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

   // glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    
    
    //glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}


void build_axis(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO) {
    float axisLength = 100.f;

    float points[] = {
         0.0, 0.0, 0.0, 1.0,         1.0, 0.0, 0.0, 1.0,
         axisLength, 0.0, 0.0, 1.0,  1.0, 0.0, 0.0, 1.0,

         0.0, 0.0, 0.0, 1.0,         0.0, 0.0, 1.0, 1.0,
         0.0, axisLength, 0.0, 1.0,  0.0, 0.0, 1.0, 1.0,

         0.0, 0.0, 0.0, 1.0,         1.0, 1.0, 0.0,1.0,
         0.0, 0.0, axisLength, 1.0,  1.0, 1.0, 0.0,1.0, 

         axisLength, 0.0, 0.0, 1.0,  1.0, 0.0, 1.0,1.0,
         axisLength, 0.0, 0.0, 1.0,  1.0, 0.0, 1.0,1.0,
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);

     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (4 * sizeof(float)));
     glEnableVertexAttribArray(1);
}



void buildTexturedTriangle(unsigned int& VBO, unsigned int& VAO, unsigned int &EBO) {
   
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
       0, 1, 3, // first triangle
       1, 2, 3  // second triangle
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	//vPos
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float))); //vColor
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // vText
    glEnableVertexAttribArray(2);


}





void buildColorTriangle(unsigned int &VBO, unsigned int &VAO) {
    float firstTriangle[] = {
        0.9f, 0.5f, 0.0f,    // left
        0.0f, 0.5f, 0.0f, // right blue
        0.45f, 0.5f, 0.0f// top 
    };

   

   
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);

   // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    std::cout << "VBO: " << VBO << " VAO: " << VAO << "\n";
}
    



/**
    This function just displays 2 disjoint triangles
*/
void buildTwoTriangles(unsigned int(&VBOs)[2], unsigned int(&VAOs)[2]) {

    float firstTriangle[] = {
       -0.9f, -0.5f, 0.0f,  // left 
       -0.0f, -0.5f, 0.0f,  // right
       -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

        
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);


}





// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



void make_triangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
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
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    

}


void make_square() {
    float vertices[] = {
        -.5f, .5f, 0.f,
        -.5f, -.5f, 0.f,
         .5f, -.5f, 0.f,
    
         .5f, -.5f, 0.f,
         .5f, .5f, 0.f,
         -.5f, .5f, 0.f,



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
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    

}

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
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

    return shader;
}






unsigned int make_module(const std::string& filepath, unsigned int module_type) {
    std::string shader_source = get_shader_content(filepath);

    const char* shader_src = shader_source.c_str();

    unsigned int shader_module = glCreateShader(module_type);
    glShaderSource(shader_module, 1, &shader_src, NULL);
    glCompileShader(shader_module);

    int success;
    glGetShaderiv(shader_module, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shader_module, sizeof(errorLog), NULL, errorLog);
        std::cout << "Shader Module Compilation Error:\n" << errorLog << "\n";
    }
    else {
        std::cout << "Shader Compilation Successfull:\n";
    }

    return shader_module;
}


std::string get_shader_content(const std::string& filepath) {
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);

    while (std::getline(file, line)) {
        bufferedLines << line << "\n";
    }
    file.close();

    std::string to_ret = bufferedLines.str();
    bufferedLines.str("");
    return to_ret;


 }
