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
camera['rts-controller'] = GameObject.AddComponent(camera['prefab'], "CameraRTSController")

-- Prefab du terrain
terrain = {}
terrain['prefab'] = CreatePrefab("prefab:terrain")
-- Geometrie du terrain
terrain['geometry'] = GameObject.AddComponent(terrain['prefab'], "Geometry")
Geometry.Assign(terrain['geometry'], "geometry:heightmap")
-- Materiau du terrain
terrain['material'] = GameObject.AddComponent(terrain['prefab'], "Material")
Material.Assign(terrain['material'], "texture:heightmap")

-- Prefab de la particule de pluie
drop = {}
drop['prefab'] = CreatePrefab("prefab:drop")
-- Tranform de la particule de pluie
GameObject.SetPosition(drop['prefab'], 0.0, 2.0, 0.0)
GameObject.SetScale(drop['prefab'], 0.05, 0.05, 1.0)
-- Geometrie de la particule de pluie
drop['geometry'] = GameObject.AddComponent(drop['prefab'], "Geometry")
Geometry.Assign(drop['geometry'], "geometry:ui-plane")
-- Materiau de la particule de pluie
drop['material'] = GameObject.AddComponent(drop['prefab'], "Material")
Material.Assign(drop['material'], "texture:snow")
-- Controller du camera facing de la particule de pluie
drop['facing-controller'] = GameObject.AddComponent(drop['prefab'], "CameraFacingController")
-- Rididbody de la particule de pluie
drop['rigidbody'] = GameObject.AddComponent(drop['prefab'], "Rigidbody")
Rigidbody.SetGravity(drop['rigidbody'], 0.0, -0.05, 0.0)

-- Prefab de la pluie
rain = {}
rain['prefab'] = CreatePrefab("prefab:rain")
-- Système de particule de la pluie
rain['particle-system'] = GameObject.AddComponent(rain['prefab'], "ParticleSystem")
ParticleSystem.AssignEmitter(rain['particle-system'], "geometry:plane")
ParticleSystem.AssignParticle(rain['particle-system'], "prefab:drop")
ParticleSystem.SetParticleDuration(rain['particle-system'], 2800)
ParticleSystem.SetParticleFrequency(rain['particle-system'], 20)

-- Contenu de la scene
GameObject.Instanciate(camera['prefab'])
GameObject.Instanciate(terrain['prefab'])
GameObject.Instanciate(rain['prefab'])