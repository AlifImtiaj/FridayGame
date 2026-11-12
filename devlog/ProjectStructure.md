# Project Structure
*Last updated: 2026-11-12*

## Architecture
Friday Engine is a 2D game engine I'm making with C++ and SDL3. I want to keep things simple and organized so I can add new features without making the engine messy.

```
Friday Engine
├── Engine
│   ├── Window
│   ├── Renderer
│   ├── Input
│   └── Time
└── Image
```

*This is the planned high-level structure. The actual organization may change as development continues.*

## Design Goals
- Make the engine easy for other C++ developers to understand and use.
- Keep rendering, audio, animation, and physics as separate systems.
- Avoid unnecessary dependencies between systems.
