# Kila

Kila is a shading language made for Akel engine. It is based on Lua and is rather simple to learn.

Example of Kila program

```lua
location(0) pos: vec3
location(1) color: vec4

uniform viewData
    view: mat4
    model: mat4
    proj: mat4
end

function Vmain() -> vec4
    pos = vec3(viewData.model * vec4(pos, 1.0))
    return viewData.proj * viewData.view * vec4(pos, 1.0)
end

function Fmain() -> vec4
    return color
end
```
