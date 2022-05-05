#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;


float near = 0.1;
float far = 2000.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

float GetFogFactor(float d)
{
    const float FogMax = 20.0;
    const float FogMin = 10.0;

    if (d >= FogMax) return 1;
    if (d <= FogMin) return 0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}

void main()
{
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    //FragColor = vec4((vec3(LinearizeDepth(gl_FragCoord.z), 0.3, LinearizeDepth(gl_FragCoord.z)) / far) * (ourColor - 0.4), 1.0f);
    //FragColor = vec4(ourColor, 1.0);
    //FragColor = texture(texture1, TexCoord) * vec4(ourColor + (vec3(LinearizeDepth(gl_FragCoord.z), LinearizeDepth(gl_FragCoord.z), LinearizeDepth(gl_FragCoord.z)) / 64), 1.0);
    //FragColor = vec4(TexCoord, 0, 1);
    vec3 sky = vec3(0.53f, 0.81f, 0.92f);
    //FragColor = texture(texture1, TexCoord) * vec4(ourColor - (vec3(sky * LinearizeDepth(gl_FragCoord.z)) / 512), 1);
    //FragColor = texture(texture1, TexCoord) * vec4((vec3(LinearizeDepth(gl_FragCoord.z))), 1);
    vec3 fog = (vec3(LinearizeDepth(gl_FragCoord.z)));
    //FragColor = texture(texture1, TexCoord) * vec4(ourColor - sky * fog / 128, 1);

}
