#version 330 core
attribute vec4 a_pos;
attribute vec2 a_texCoord;

uniform mat4 mvpMatrix;

varying vec2 v_texCoord;

void main() {
    gl_Position = mvpMatrix * a_pos;

    v_texCoord = a_texCoord;
}
