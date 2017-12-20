-- LoadAsset("texture:heightmap", "res/heightmap-3.png")
-- LoadAsset("texture:snow", "res/flocon.png")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/prefabs/camera.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")