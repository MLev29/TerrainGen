#version 450 core

in vec3 normal;
out vec4 FragColor;
in vec2 uvs;

void main()
{
    vec3 upDir = vec3(0.0, 1.0, 0.0);

    float terrainSteepness = abs(dot(upDir, normal));
    FragColor = vec4(vec3((terrainSteepness * 0.75) + 0.25), 1.0);

    //FragColor = vec4(uvs + 1.0, 0.000, 1.0)/2.0;
}
