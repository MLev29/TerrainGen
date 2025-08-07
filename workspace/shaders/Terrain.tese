#version 450 core

// define patch type, point spacing and winding order ccw (counter clock wise)
layout (quads, fractional_odd_spacing, ccw) in;

// Take in tex coords from previous stage
in vec2 uvsCoord[];

// Send tex-cord & normal data to the next stage (fragment shader) 
out vec2 uvs;
out vec3 normal;

uniform mat4 view;
uniform mat4 projection;

uniform float scale = 0.05;         // Controls frequency of terrain features
uniform float heightScale = 25.0;   // Controls vertical exaggeration

// Return random number between 0 - 1
float Hash(vec2 p) 
{
    return fract(sin(dot(p ,vec2(127.1,311.7))) * 43758.5453123);
}

float PerlinNoise2D(vec2 point) 
{
    vec2 floorVal = floor(point);
    vec2 posInCell = fract(point);

    float llCorner = Hash(floorVal);                  // Lower left corner
    float lrCorner = Hash(floorVal + vec2(1.0, 0.0)); // Lower right corner
    float ulCroner = Hash(floorVal + vec2(0.0, 1.0)); // Upper left corner
    float urCorner = Hash(floorVal + vec2(1.0, 1.0)); // Upper right corner

    // Smoothstep
    vec2 val = posInCell * posInCell * (3.0 - 2.0 * posInCell); 

    // Return height value
    return mix(llCorner, lrCorner, val.x) +
           (ulCroner - llCorner)* val.y * (1.0 - val.x) +
           (urCorner - lrCorner) * val.x * val.y;
}

float FractalPerlinNoise(vec2 pos) 
{
    float total = 0.0;
    float frequency = 1.0;
    float amplitude = 1.0;
    float persistence = 0.5; // Controls amplitude decay
    int octaves = 5;

    // Loop the perlin noise function multiple times to create layered perlin noise
    for (int i = 0; i < octaves; i++) {
        total += PerlinNoise2D(vec2(pos) * frequency) * amplitude;
        frequency *= 2.0;
        amplitude *= persistence;
    }

    // Return the vertex's height
    return total;
}

void main() {
    // Get the 4 vertices
    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    vec3 p2 = gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz;

    // Texture coordinate components
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // Applying bilinear interpolation on point
    vec3 leftPos = mix(p3, p0, v);
    vec3 rightPos = mix(p2, p1, v);
    vec3 pos = mix(leftPos, rightPos, u);

    // Calculate normals
    vec4 uVec = vec4(p1 - p0, 1.0);
    vec4 vVec = vec4(p2 - p0, 1.0);
    normal = normalize( vec4(cross(vVec.xyz, uVec.xyz), 0).xyz );

    // Apply noise to Y-axis (height)
    //pos.y = PerlinNoise2D(pos.xz * scale) * heightScale; // Standard perlin noise
    pos.y = FractalPerlinNoise(pos.xz * scale) * heightScale; // Fractal perlin noise

    // Set position
    gl_Position = projection * view * vec4(pos, 1.0);

    // Recalculate new UV coordinate for new points
    vec2 uv0 = uvsCoord[0];
    vec2 uv1 = uvsCoord[1];
    vec2 uv2 = uvsCoord[2];
    vec2 uv3 = uvsCoord[3];

    vec2 leftUV = mix(uv3, uv0, v);
    vec2 rightUV = mix(uv2, uv1, v);
    vec2 texCoord = mix(leftUV, rightUV, u);

    uvs = texCoord;
}
