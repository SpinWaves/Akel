# Kila

Kila is a shading language made for Akel engine. It is an oriented object programming language.

Example of Kila program
```kotlin
var pos: vec3 = location(0); // location is equivalent to layout in GLSL
var color: vec4 = location(1);

uniform(0) 
{
    var view: mat4;
    var proj: mat4;
    var model: mat4;
} viewData;

@entry vert // entry function of the vertex shader
fn main() -> vec4 // return value is the position of the pixel
{
    pos = vec3(viewData.model * vec4(pos, 1.0));
    return viewData.proj * viewData.view * vec4(pos, 1.0);
}

class Light
{
    // "fn" are static functions and "mtd" are object methods

    pub fn Light(var pos: vec3, var color: vec3, var radius: float) -> Light
    {
        _pos = pos;
        _color = color;
        _radius = radius;
    }

    pub mtd get_result() -> vec3
    {
        /* Some light calculations */
        
        return light;
    }
    
    var _pos: vec3;
    var _color: vec3;
    var _radius: float;
}

@entry frag // entry function of the fragment shader
fn main() -> vec4 // return value is the color of the pixel
{
    obj light = Light(vec3(0, 10, 5), vec3(255, 255, 255), 15.7);
    var frag_color: vec4 = color * vec4(light.get_result(), 1.0);
    return frag_color;
}
```
