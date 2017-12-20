LoadAsset("texture:heightmap", "res/heightmap-3.png")
LoadAsset("texture:snow", "res/flocon.png")
CreateHeightTerrain("geometry:heightmap", "res/heightmap-3.png")
LoadAsset("script:terrain", "assets/scripts/terrain.lua")
LoadAsset("script:cube", "assets/scripts/box.lua")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/prefabs/camera.prefab")
LoadPrefab("prefab:terrain", "assets/prefabs/terrain.prefab")
LoadPrefab("prefab:snow-particle", "assets/prefabs/snow-particle.prefab")
LoadPrefab("prefab:snow", "assets/prefabs/snow.prefab")
LoadPrefab("prefab:cube", "assets/prefabs/box.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")
GameObject.Instanciate("prefab:terrain")
GameObject.Instanciate("prefab:snow")
GameObject.Instanciate("prefab:cube")