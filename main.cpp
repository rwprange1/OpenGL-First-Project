#include "main.h"
#include <iostream>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


glm::vec3 cameraPos = glm::vec3(2.0, 2.0,2.f);
glm::vec3 lookAtPoint = glm::vec3(.0f, .0f, .0f);
glm::vec3 upPoint = glm::vec3(0.f, 1.f, 0.f);

int main(void){
    std::cout << "Hello\n";
    GLFWwindow* window;

    // configure global opengl state
    // -----------------------------
    
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "GLFW failed to start";
        return -1;
    }
        
    

   
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
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
    glEnable(GL_DEPTH_TEST);
    



    Camera cam = Camera(cameraPos, lookAtPoint, upPoint);
    cam.build_projection(-1.f, 1.f, -1.f, 1.f, 1.0, 10.f);
    Shader shader = Shader("cube.vs", "cube.fs");

    shader.use();
    shader.setMat4("model", glm::mat4(1.f));
    shader.setMat4("view", cam.view);
    shader.setMat4("projection", cam.projection);

    //cam.cameraSetUniforms(shader);
    Cube cube = Cube(shader);
    //Triangle t = Triangle(shader);
    
    
  
   // Model ourModel("C:\\Users\\richw\\Downloads\\CSStuff\\C++\\3D-Models\\sun\\scene.gltf", true);
  
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    float theta = 0.0f;
    float rotSpeed = 2.5f;
 
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   
        // per-frame time logic
         // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        theta += rotSpeed * deltaTime;



        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shader.use();
        
      
        

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f)); // translate it down so it's at the center of the scene
       
        model = glm::rotate(model, theta, glm::vec3(0, 1, .5));
        
        
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
        //shader.setMat4("projection", cam.projection);

     
        shader.setMat4("model", model);
        //ourModel.Draw(shader);
        cube.draw();
        //t.draw();


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        ///return 1;
    }

   // glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    
    
    //glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}






















// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W\n";
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}





