-- LoadAsset("texture:heightmap", "res/heightmap-3.png")
-- LoadAsset("texture:snow", "res/flocon.png")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/prefabs/camera.prefab")
LoadPrefab("prefab:cylinder", "assets/prefabs/cylinder.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")
GameObject.Instanciate("prefab:cylinder")