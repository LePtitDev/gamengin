-- LoadAsset("texture:heightmap", "res/heightmap-3.png")
-- LoadAsset("texture:snow", "res/flocon.png")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/prefabs/camera.prefab")
LoadPrefab("prefab:tower", "assets/prefabs/tower.prefab")
LoadPrefab("prefab:pawn", "assets/prefabs/pawn.prefab")
LoadPrefab("prefab:bishop", "assets/prefabs/bishop.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")
GameObject.Instanciate("prefab:bishop")