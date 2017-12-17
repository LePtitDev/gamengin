LoadAsset("texture:heightmap", "res/heightmap-3.png")
LoadAsset("texture:snow", "res/flocon.png")
CreateHeightTerrain("geometry:heightmap", "res/heightmap-3.png")

-- Prefab de la camera
camera = {}
camera['prefab'] = CreatePrefab("prefab:camera")
-- Tranform de la camera
GameObject.SetPosition(camera['prefab'], 1.0, 1.0, 0.0)
-- Composants de la camera
camera['camera'] = GameObject.AddComponent(camera['prefab'], "Camera")
camera['rts-controller'] = GameObject.AddComponent(camera['prefab'], "RTSCameraController")

-- Prefab du terrain
terrain = {}
terrain['prefab'] = CreatePrefab("prefab:terrain")
-- Geometrie du terrain
terrain['geometry'] = GameObject.AddComponent(terrain['prefab'], "Geometry")
Geometry.Assign(terrain['geometry'], "geometry:heightmap")
-- Materiau du terrain
terrain['material'] = GameObject.AddComponent(terrain['prefab'], "Material")
Material.Assign(terrain['material'], "texture:heightmap")

-- Contenu de la scene
GameObject.Instanciate(camera['prefab'])
GameObject.Instanciate(terrain['prefab'])