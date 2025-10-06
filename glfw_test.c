#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>


const char *const vertex_source = 
"#version 330 core\n"

"layout (location = 0) in vec3 aPos;\n"

"uniform float u_time;\n"

"out float scale;\n"
"out vec3 position;\n"

"void main() {\n"
"    position = aPos;\n"
"    scale = (2 + sin(u_time)) / 4.0;\n"
"    gl_Position = vec4(scale * aPos.xy, aPos.z, 1.0);\n"
"}\n";

const char *const fragment_source =
"#version 330 core\n"

"out vec4 FragColor;\n"

"in float scale;\n"
"in vec3 position;\n"

"void main() {\n" 
"    FragColor = vec4((position.xy + vec2(1.0)) / 2.0 * scale, 0.0, 1.0);\n"
"}\n";



unsigned int get_file_size(FILE *f_p);


void framebuffer_size_callback(GLFWwindow *window, int width, int height);


int main() {
    float vertices[] = {
        -1, 1, 0.0,
        1, 1, 0.0,
        -1, -1, 0.0,
        1, -1, 0.0,
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3,
    };


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    

    GLFWwindow *window = glfwCreateWindow(1280, 720, "glfw_test", NULL, NULL);
    if (window == NULL) {
        printf("Couldn't open window.");
        glfwTerminate();
        return -1;
    } 

    glfwMakeContextCurrent(window);

   
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Couldn't load OpenGL functions.\n");
        return -1;
    }
 

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   


    //char *vertex_source = NULL;
    //{
    //    FILE *f_p = fopen("./vertex.glsl", "r");
    //    unsigned int file_size = get_file_size(f_p);
    //   
    //    vertex_source = malloc(file_size);
    //    fwrite(vertex_source, sizeof(char), file_size, f_p);

    //    fclose(f_p);
    //}
 
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    //free(vertex_source);


    //char *fragment_source = NULL;
    //{
    //    FILE *f_p = fopen("./fragment.glsl", "r");
    //    unsigned int file_size = get_file_size(f_p);
    //    
    //    fragment_source = malloc(file_size);
    //    fwrite(fragment_source, sizeof(char), file_size, f_p);

    //    fclose(f_p);
    //}
 
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    //free(fragment_source);


    
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);



    unsigned VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);


        int time_location = glGetUniformLocation(shader_program, "u_time");
        glUseProgram(shader_program);
        glUniform1f(time_location, glfwGetTime());


        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);


    glfwTerminate();
    return 0;
}



unsigned int get_file_size(FILE *f_p) {
    fseek(f_p, 0, SEEK_END);
    unsigned int file_size = ftell(f_p);
    rewind(f_p);

    return file_size;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

