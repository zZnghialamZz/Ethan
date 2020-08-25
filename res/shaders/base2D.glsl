#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec4 vercolor;

uniform mat4 uEthan_ViewProjection;

out vec2 vtexcoord;
out vec4 vcolor;

void main() {
		vcolor = vercolor;
    vtexcoord = texcoord;
    gl_Position = uEthan_ViewProjection * vec4(position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vtexcoord;
in vec4 vcolor;

void main() {
    color = vcolor;
}
