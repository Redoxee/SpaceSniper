#version 150

uniform mat4 modelViewProjectionMatrix;
uniform mat4 WorldMatrix;
in vec4 position;
uniform samplerBuffer debriPositions;
out vec4 color;


void main(){
    int x = gl_InstanceID*2;
    
    //vec4 pos = vec4(texelFetch(debriPositions, x),texelFetch(debriPositions, x + 1),0,0); 

	gl_Position = modelViewProjectionMatrix * position;
}