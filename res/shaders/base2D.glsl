#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texcoord;

uniform mat4 uEthan_ViewProjection;
uniform mat4 uEthan_Transform;

out vec2 vtexcoord;

void main() {
    vtexcoord = texcoord;
    gl_Position = uEthan_ViewProjection * uEthan_Transform * vec4(pos, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vtexcoord;
uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main() {
    color = texture(u_Texture, vtexcoord) * u_Color;
}
