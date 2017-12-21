-- Indicate if button is outlined
started = true

-- Mouse press callback
function mousePress(key, x, y)
    if (key == 1) then
        ox, oy, oz, dx, dy, dz = Camera.GetRay(x, y)
        hits = { Physics.Raycast(ox, oy, oz, dx, dy, dz) }
        if (hits[1] == nil) then
        else
            if (GameObject.GetName(hits[1]) == "MuteButton") then
                if started then
                    Sound.Stop()
                    started = false
                    Material.Assign(GameObject.GetComponent(this, "Material"), "texture:mute")
                else
                    Sound.Play("sound:main")
                    started = true
                    Material.Assign(GameObject.GetComponent(this, "Material"), "texture:sound")
                end
            end
        end
    end
end