# Kila

Kila is a shading language made for Akel engine. It is an oriented object programming language.

Example of Kila program
```Kotlin
@get lstd.kl // To have vec2, vec3, vec4, mat2, mat3, mat4...

// Global part
var pos: vec3 = entry(0); // entry is equivalent to layout in GLSL and "(0)" means "location 0"
var color: vec4 = entry(1);

@entry vert // vertex shader

uniform var view: mat4;
uniform var proj: mat4;
uniform var model: mat4;

fn main()
{
    pos = vec3(model * vec4(pos, 1.0));
    return proj * view * vec4(pos, 1.0);
}

@entry frag // fragment shader

class Light
{
    public:
        fn Light(var pos: vec3, var color: vec3, var radius: float)
        {
            _pos = pos;
            _color = color;
            _radius = radius;
        }

        mtd get_result(): vec3
        {
            /* Some calculations on lights */
            
            return light;
        }
    
    private:
        var _pos: vec3;
        var _color: vec3;
        var _radius: float;
}

fn main()
{
    obj light = Light((0, 10, 5), (255, 255, 255), 15.7);
    var frag_color: vec4 = color * vec4(light.get_result(), 1.0);
    return frag_color;
}
```
