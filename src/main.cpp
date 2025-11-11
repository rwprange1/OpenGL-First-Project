#include "main.h"
#include <iostream>


// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void){
    
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Couldnt load opengl\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL loaded\n";

   
    glClearColor(.75f, .25f, .8f, 1.f);
    glEnable(GL_DEPTH_TEST);
    



    

    camera.defineFrustum(-1.f, 1.f, -1.f, 1.f, 1.0, 100.f);
    Shader shader = Shader("cube.vs", "cube.fs");

    glm::mat4 v = camera.getView();
    std::cout << "View " << glm::to_string(v) << std::endl;

    shader.use();
    shader.setMat4("model", glm::mat4(1.f));
    shader.setMat4("view",v );
    shader.setMat4("projection", camera.projection);

    //cam.cameraSetUniforms(shader);
    Cube cube = Cube(shader);
    //Triangle t = Triangle(shader);
    
    
  
   // Model ourModel("C:\\Users\\richw\\Downloads\\CSStuff\\C++\\3D-Models\\sun\\scene.gltf", true);

    

    float currentFrame;
    
    /* Loop until the user closes the window */

    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> translations;
    for (int i = 0; i < 1000; i++) {
        glm::vec3 color;
        color.x =  static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        color.y = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        color.z = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        colors.push_back(color);
    }

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 20; j++) {
            glm::vec3 trans;
            trans.x = (float)i;
            trans.y = -3;
            trans.z = (float)j;

            translations.push_back(trans);
        }

     }
   
    
    while (!glfwWindowShouldClose(window)) {
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        processInput(window);


        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // activate shader
        shader.use();

        shader.setMat4("projection", camera.projection);
        glm::mat4 view = camera.getView();
        shader.setMat4("view", view);

        
        for (int i = 0; i < colors.size(); i++) {
            
            glm::mat4 model = glm::mat4(1.f);
            
            model = glm::translate(model,translations[i]);
            shader.setMat4("model", model);
            shader.setVec3("uColor", colors[i]);
            
            cube.draw();
        }

        
       
        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    
    //glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}












void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKeyboard(DOWN, deltaTime);
}











// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}









// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    float xoffset, yoffset;
    if (firstMouse)
    {
        xoffset = xpos - lastX;
        yoffset = ypos - lastY;
        firstMouse = false;
    }
    else {
        xoffset = lastX - xpos;
        yoffset = ypos - lastY; // reversed since y-coordinates go from bottom to top
    }

   

    lastX = xpos;
    lastY = ypos;
    

    camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(static_cast<float>(yoffset));
}