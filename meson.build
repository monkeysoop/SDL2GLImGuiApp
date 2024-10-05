project(
    'app',
    'cpp',
    default_options: ['cpp_std=c++23'],
    version: '0.1.0',
)

project_source_files = [
    'main.cpp',
]

project_deps = [
    dependency('sdl2', required: true),
    dependency('glew', required: true),
    dependency('opengl', required: true),
    dependency('glu', required: true),
    dependency('imgui', required: true),

    subproject('imgui_bindings', required: true).get_variable('imgui_bindings_dep'),
]

#subdir('src')
#subdir('bindings')

executable(
    meson.project_name(), 
    project_source_files,
    dependencies: project_deps,
    install: true,
)
