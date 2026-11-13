# Project Structure
*Last updated: 2026-11-13*

## Architecture
Friday Engine is a 2D game engine I'm making with C++ and SDL3. I want to keep things simple and organized so I can add new features without making the engine messy.

```
Friday Engine
│
├── Engine Layer
│   └── Engine
│       ├── Window
│       ├── Renderer
│       ├── Input
│       ├── Time
│       └── LevelManager
│           └── manages -> Level
│                           ├── Level1
│                           └── Level2
│
├── Game Object Layer
│   ├── GameObject (Base Class)
│   │   ├── Position
│   │   ├── Size
│   │   └── Rotation
│   │
│   └── Player (inherits GameObject)
│       └── SpriteRenderer (Reference Texture2D)
│
└── Resource Layer
    └── Texture2D
        └── owns -> SDL_Texture
```

*This is the planned high-level structure. The actual organization may change as development continues.*

## Design Goals
- Make the engine easy for other C++ developers to understand and use.
- Keep rendering, audio, animation, and physics as separate systems.
- Avoid unnecessary dependencies between systems.
