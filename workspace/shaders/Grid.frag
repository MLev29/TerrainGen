#version 450 core

in vec3 normal;
out vec4 FragColor;
in vec2 uvs;

void main()
{
   //FragColor = vec4(color.xyz, 1.0);
   vec3 upDir = vec3(0.0, 1.0, 0.0);

   float terrainSteepness = abs(dot(upDir, normal));

   if (terrainSteepness < 1.0)
   {
      //FragColor = vec4(vec3(1 - terrainSteepness)* 0.60, 1.0);
      FragColor = vec4(vec3(terrainSteepness), 1.0);
   }
   else
   {
      //vec3 grassColor = vec3(0.33, 0.41, 0.15);
      vec3 snowColor = vec3(0.95, 0.0, 0.0);
      FragColor = vec4(snowColor * terrainSteepness, 1.0);
   }
   FragColor = vec4(uvs + 1.0, 0.000, 1.0)/2.0;
}
