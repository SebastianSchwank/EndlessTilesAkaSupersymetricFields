#ifdef GL_ES
// Set default precision to high
precision highp int;
precision highp float;
#endif

//RT2DShader

varying vec2 v_texcoord;

uniform sampler2D Particles;
uniform int numParticles;
uniform int numParametersP;

uniform sampler2D renderedImage;
uniform int width;
uniform int height;

uniform int mirroredX;
uniform int mirroredY;

const float pi = 3.14159265359;

uniform float zOOm;
uniform int shaderMode;

// Unpacking a [0-1] float value from a 4D vector where each component was a 8-bits integer
float unpack(const vec4 value)
{
   const vec4 bitSh = vec4(1.0 / (256.0 * 256.0 * 256.0), 1.0 / (256.0 * 256.0), 1.0 / 256.0, 1.0);
   return(dot(value, bitSh));
}
//synthesizing TexelFetch
vec4 texelFetch(sampler2D tex,const vec2 coord, const ivec2 size){
    vec2 fCoord = vec2((2.0*coord.x + 1.0)/(2.0*float(size.x)),(2.0*coord.y + 1.0)/(2.0*float(size.y)));
    return texture2D(tex,fCoord);
}

void main()
{
    vec4 renderedImagePixel = texture2D(renderedImage,(v_texcoord-vec2(0.5,0.5))*zOOm);

    if(shaderMode == 1){
        vec4 pixelColor = vec4(0.0,0.0,0.0,0.0);

        vec2 pos = vec2(v_texcoord.x,v_texcoord.y) ;
        float dist = 0;

        for(int i = 0; i < numParticles; i++){
            float xP = unpack(texelFetch(Particles,vec2(float(i),3.0),ivec2(numParticles,numParametersP)));
            float yP = unpack(texelFetch(Particles,vec2(float(i),2.0),ivec2(numParticles,numParametersP)));
            float brightness = unpack(texelFetch(Particles,vec2(float(i),1.0),ivec2(numParticles,numParametersP)));

            for(int x = -mirroredX/2; x < mirroredX/2; x++){
                for(int y = -mirroredY/2; y < mirroredY/2; y++){
                    vec4  color = vec4(((x+xP)-pos.x),((y+yP)-pos.y),0.0,0.0);
                    //float dist = length(color);
                    float d = length(color);
                    color = color / (d*d*d);

                    pixelColor += color;
                }
            }
        }

        renderedImagePixel = 0.5*(normalize(pixelColor)+vec4(1.0,1.0,0.0,1.0));
    }


    gl_FragColor = renderedImagePixel;

}

