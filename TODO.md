
Things to do, in no particular order:

## Test to ensure VBO rendering works

## Implement MRenderer::Model

- Model loader
  - Binary storage
- Blender exporter
- Static model with no animations
- Materials

## Implement MRenderer::Camera3D and MRenderer::Camera2D

- Dynamic switching between cameras

## Implement MRenderer::Material

- Texture loading
- Material definition loading
  - Material definition format
- Move shader program into materials
- Remove shader programs from VBOs

## Sound playback

- OpenAL (should look into loaders, libogg/libvorbis are possibilities)
- Music playback

## Gamestate

- Menu
- Game
  - Paused
