#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float shading;

uniform vec4 unnormalized_color;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model, view, projection;

void main() {
    vec4 p_pos = vec4(aPos, 1);
    gl_Position = projection * view * p_pos;
    TexCoord = aTexCoord;
    ourColor = normalize(aPos * aPos) * shading;
    //ourColor = normalize(model * vec4(1, 1, 1, 1)).xyz * shading;
    //ourColor = vec3(1, 1, 1) * shading;
    //ourColor = normalize(aPos) * shading;
}