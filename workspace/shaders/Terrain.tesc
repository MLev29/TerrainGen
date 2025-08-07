#version 450 core

// Number of control points per patch (size of i/o arrays).
// This value must be the same as the one set for the glPatchParameteri function.
layout (vertices = 4) out;

in vec2 uvs[];
out vec2 uvsCoord[];

// Value set CPU side
layout(location = 0) uniform int divCount;

void main()
{
    /*
    *   Pass vertex attribute data. The shader makes use of a new variable 'gl_InvocationID'
    *   this GLSL variable represents the current index of the vertex within the current patch. 
    */
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    uvsCoord[gl_InvocationID] = uvs[gl_InvocationID];

    // Check for first invocation, the first invocation controls the patch
    if (gl_InvocationID == 0)
    {
        // Number of generated tessellated points.
        gl_TessLevelOuter[0] = divCount;
        gl_TessLevelOuter[1] = divCount;
        gl_TessLevelOuter[2] = divCount;
        gl_TessLevelOuter[3] = divCount;

        gl_TessLevelInner[0] = divCount;
        gl_TessLevelInner[1] = divCount;
    }
}
