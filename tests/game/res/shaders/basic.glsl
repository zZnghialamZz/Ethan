#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texcoord;

uniform mat4 uEthan_ViewProjection;
uniform mat4 uEthan_Transform;

out vec3 vpos;
out vec2 vtexcoord;

void main() {
    vpos = pos;
    vtexcoord = texcoord;
    gl_Position = uEthan_ViewProjection * uEthan_Transform * vec4(pos, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vpos;
in vec2 vtexcoord;
uniform sampler2D u_Texture;

void main() {
    vec4 tex = texture(u_Texture, vtexcoord);
    color = tex;
}
