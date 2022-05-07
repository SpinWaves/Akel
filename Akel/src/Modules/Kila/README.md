# Kila

Kila is a shading language made for Akel engine. It is based on LUA and is rather simple to learn.

Example of Kila program

```lua
local pos: vec3 = location(0)
local color: vec4 = location(1)

uniform(0) viewData
    view: mat4
    model: mat4
    proj: mat4
end

function Vmain() -> vec4
    pos = vec3(vewData.model * vec4(pos, 1.0))
    return vewData.proj * vewData.view * vec4(pos, 1.0)
end

function Fmain() -> vec4
    return color
end
```
