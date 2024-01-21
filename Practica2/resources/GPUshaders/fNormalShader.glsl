#version 330

in vec3 normal;
out vec4 colorOut;

void main() {
    colorOut = vec4(normalize(normal), 1.0);
}

