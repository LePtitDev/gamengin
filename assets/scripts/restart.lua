-- Indicate if button is outlined
outlined = false

-- Mouse press callback
function mousePress(key, x, y)
    if (key == 1) then
        ox, oy, oz, dx, dy, dz = Camera.GetRay(x, y)
        hits = { Physics.Raycast(ox, oy, oz, dx, dy, dz) }
        if (hits[1] == nil) then
        else
            if (GameObject.GetName(hits[1]) == "RestartButton") then
                Script.CallFunction(GameObject.GetComponent(GameObject.Find("GameState"), "script:gamestate"), "restart")
            end
        end
    end
end

-- Mouse move callback
function mouseMove(x, y)
    outlined = false
    ox, oy, oz, dx, dy, dz = Camera.GetRay(x, y)
    hits = { Physics.Raycast(ox, oy, oz, dx, dy, dz) }
    if (hits[1] == nil) then
    else
        if (GameObject.GetName(hits[1]) == "RestartButton") then
            Material.Assign(GameObject.GetComponent(this, "Material"), "texture:restart-outline")
            outlined = true
        end
    end
    if (not outlined) then
        Material.Assign(GameObject.GetComponent(this, "Material"), "texture:restart")
    end
end