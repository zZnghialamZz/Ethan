#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec4 vercolor;
layout(location = 3) in float texindex;
layout(location = 4) in vec2 tiling;

uniform mat4 uEthan_ViewProjection;

out float vtexindex;
out vec2 vtexcoord;
out vec2 vtiling;
out vec4 vcolor;

void main() {
    vcolor = vercolor;
    vtiling = tiling;
    vtexcoord = texcoord;
    vtexindex = texindex;
    gl_Position = uEthan_ViewProjection * vec4(position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in float vtexindex;
in vec2 vtexcoord;
in vec2 vtiling;
in vec4 vcolor;

uniform sampler2D u_Textures[16];
uniform vec2 u_TilingFactor;

void main() {
    color = texture(u_Textures[int(vtexindex)], vtexcoord * vtiling) * vcolor;
}
