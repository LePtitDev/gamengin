LoadAsset("texture:heightmap", "res/heightmap-3.png")
LoadAsset("texture:snow", "res/flocon.png")
CreateHeightTerrain("geometry:heightmap", "res/heightmap-3.png")
LoadAsset("script:terrain", "assets/exemples/heightmap/scripts/terrain.lua")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/exemples/heightmap/prefabs/camera.prefab")
LoadPrefab("prefab:terrain", "assets/exemples/heightmap/prefabs/terrain.prefab")
LoadPrefab("prefab:snow-particle", "assets/exemples/heightmap/prefabs/snow-particle.prefab")
LoadPrefab("prefab:snow", "assets/exemples/heightmap/prefabs/snow.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")
GameObject.Instanciate("prefab:terrain")
GameObject.Instanciate("prefab:snow")