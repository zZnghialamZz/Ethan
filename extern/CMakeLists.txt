# ------------------------------------------------------
# Graphics Support
# ------------------------------------------------------
add_subdirectory(glm)       # Math lib support for OpenGL <- To be removed
add_subdirectory(glad)      # OpenGL headers definitions
add_subdirectory(GLFW)      # OpenGL API wrappers
add_subdirectory(freetype)  # Font rendering helpers
add_subdirectory(stb_image) # Images Loader

# ------------------------------------------------------
# Utilities
# ------------------------------------------------------
add_subdirectory(entt)      # Entity Component System lib
add_subdirectory(spdlog)    # Fast logging lib
