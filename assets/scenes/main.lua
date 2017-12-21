LoadAsset("texture:square-dark", "assets/materials/square-dark.png")
LoadAsset("texture:square-light", "assets/materials/square-light.png")
LoadAsset("texture:white", "assets/materials/white.png")
LoadAsset("texture:black", "assets/materials/black.png")

LoadAsset("script:gamestate", "assets/scripts/gamestate.lua")
LoadAsset("script:chessboard", "assets/scripts/chessboard.lua")

-- Chargement des prefabs
LoadPrefab("prefab:camera", "assets/prefabs/camera.prefab")
LoadPrefab("prefab:square", "assets/prefabs/square.prefab")
LoadPrefab("prefab:chessboard", "assets/prefabs/chessboard.prefab")
LoadPrefab("prefab:pawn", "assets/prefabs/pieces/pawn.prefab")
LoadPrefab("prefab:rook", "assets/prefabs/pieces/rook.prefab")
LoadPrefab("prefab:knight", "assets/prefabs/pieces/knight.prefab")
LoadPrefab("prefab:bishop", "assets/prefabs/pieces/bishop.prefab")
LoadPrefab("prefab:queen", "assets/prefabs/pieces/queen.prefab")
LoadPrefab("prefab:king", "assets/prefabs/pieces/king.prefab")

LoadPrefab("prefab:pawn-white", "assets/prefabs/teams/pawn-white.prefab")
LoadPrefab("prefab:rook-white", "assets/prefabs/teams/rook-white.prefab")
LoadPrefab("prefab:knight-white", "assets/prefabs/teams/knight-white.prefab")
LoadPrefab("prefab:bishop-white", "assets/prefabs/teams/bishop-white.prefab")
LoadPrefab("prefab:queen-white", "assets/prefabs/teams/queen-white.prefab")
LoadPrefab("prefab:king-white", "assets/prefabs/teams/king-white.prefab")
LoadPrefab("prefab:pawn-black", "assets/prefabs/teams/pawn-black.prefab")
LoadPrefab("prefab:rook-black", "assets/prefabs/teams/rook-black.prefab")
LoadPrefab("prefab:knight-black", "assets/prefabs/teams/knight-black.prefab")
LoadPrefab("prefab:bishop-black", "assets/prefabs/teams/bishop-black.prefab")
LoadPrefab("prefab:queen-black", "assets/prefabs/teams/queen-black.prefab")
LoadPrefab("prefab:king-black", "assets/prefabs/teams/king-black.prefab")

LoadPrefab("prefab:gamestate", "assets/prefabs/gamestate.prefab")

-- Contenu de la scene
GameObject.Instanciate("prefab:camera")
GameObject.Instanciate("prefab:gamestate")
GameObject.Instanciate("prefab:chessboard")