# Kila

<p align="center">
    <img src="https://github.com/SpinWaves/Akel/blob/main/Resources/assets/kila_logo.png" alt="drawing" width="500"/>
</p>

Kila is a shading language made for Akel engine. It is based on Lua and Rust and is rather simple to learn.

Example of Kila program

```
![spatial_shader]

external
    tex : sampler2D
end

function Vmain() -> vec4
     return ![vertex].projection * ![vertex].view * ![vertex].model * vec4(![vertex].pos, 1.0)
end

function Fmain() -> vec4
    return vec4(![fragment].color * texture(tex, ![fragment].tex_coord), 1.0)
end
```
