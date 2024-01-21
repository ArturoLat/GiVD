#version 330

// Input data interpolated from the vertex shader
in vec4 vColor;

// Output color
out vec4 fragColor;

void main() {

    fragColor = vColor;
}

