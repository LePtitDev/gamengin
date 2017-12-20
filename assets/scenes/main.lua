-- LoadAsset("texture:heightmap", "res/heightmap-3.png")
-- LoadAsset("texture:snow", "res/flocon.png")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/prefabs/camera.prefab")
LoadPrefab("prefab:pawn", "assets/prefabs/pawn.prefab")
LoadPrefab("prefab:rook", "assets/prefabs/rook.prefab")
LoadPrefab("prefab:knight", "assets/prefabs/knight.prefab")
LoadPrefab("prefab:bishop", "assets/prefabs/bishop.prefab")
LoadPrefab("prefab:queen", "assets/prefabs/queen.prefab")
LoadPrefab("prefab:king", "assets/prefabs/king.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")
GameObject.Instanciate("prefab:queen")