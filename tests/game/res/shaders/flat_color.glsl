// Flat Color Shader

#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 uEthan_ViewProjection;
uniform mat4 uEthan_Transform;

void main() {
    gl_Position = uEthan_ViewProjection * uEthan_Transform * vec4(pos, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
    color = u_Color;
}
