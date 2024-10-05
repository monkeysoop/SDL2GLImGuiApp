#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

 


#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>


#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[SDL initialization] Error during the SDL initialization: %s", SDL_GetError());
        return 1;
    }

    std::atexit(SDL_Quit);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    

    SDL_Window* window = SDL_CreateWindow(
        "something",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[Window creation] Error during the SDL initialization: %s", SDL_GetError());
        return 1;
    }


    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[GL context creation] Error during the creation of the GL context: %s", SDL_GetError());
        return 1;
    }
    printf("version: %s\n", glGetString(GL_VERSION));

    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[GLEW] Error during the initialization of glew: %s", glewGetErrorString(glew_status));
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();


    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init();

    //int glVersion[2] = {-1, -1};
    //glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    //glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    //
    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Running OpenGL %d.%d", glVersion[0], glVersion[1]);
    //
    //if (glVersion[0] == -1 && glVersion[1] == -1) {
    //    SDL_GL_DeleteContext(gl_context);
    //    SDL_DestroyWindow(window);
    //
    //    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[GL context creation] Error during the inialization of the GL context! Maybe one of the SDL_GL_SetAttribute(...) calls is erroneous.");
    //
    //    return 1;
    //}
    //printf("version: %s\n", glGetString(GL_VERSION));
    bool running = true;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
                switch (ev.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                        if (ev.key.keysym.sym == SDLK_ESCAPE) {
                            running = false;
                        }
                        break;
                }
            }

        glClearColor(0.125f, 0.25f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
    //if (glGetString(GL_VERSION) == 0) {
    //    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[GLEW] %d.", glGetError());
    //    return 1;
    //}

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);

    return 0;
}