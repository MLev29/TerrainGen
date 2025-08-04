#version 450 core

// Number of control points per patch (size of i/o arrays)
layout (vertices = 4) out;

in vec2 uvs[];

out vec2 uvsCoord[];

layout(location = 0) uniform int genCount;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    uvsCoord[gl_InvocationID] = uvs[gl_InvocationID];

    // Check for first invocation, the first invocation controls the patch
    if (gl_InvocationID == 0)
    {
        // Number of generated tessellated points
        gl_TessLevelOuter[0] = genCount;
        gl_TessLevelOuter[1] = genCount;
        gl_TessLevelOuter[2] = genCount;
        gl_TessLevelOuter[3] = genCount;

        gl_TessLevelInner[0] = genCount;
        gl_TessLevelInner[1] = genCount;
    }
}
