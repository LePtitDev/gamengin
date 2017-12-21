-- Chessboard script
chessboard = nil

-- Selected piece details
selected = nil

-- Init script
function start()
    chessboard = GameObject.GetComponent(GameObject.Find("Chessboard"), "script:chessboard")
end

-- Mouse press callback
function mousePress(button, x, y)
    if (button == 1) then
        ox, oy, oz, dx, dy, dz = Camera.GetRay(x, y)
        hits = { Physics.Raycast(ox, oy, oz, dx, dy, dz) }
        if (hits[1] == nil) then
        else
            details = { split(Script.CallFunction(chessboard, "getPieceDetails", hits[1])) }
            --if (details[1] == "0") then
                selected = { piece = hits[1], i = tonumber(details[2]), j = tonumber(details[3]), type = details[4] }
            --end
        end
    end
end

-- Mouse release callback
function mouseRelease(button, x, y)
    if (selected == nil) then
    else
        if (button == 1) then
            ox, oy, oz, dx, dy, dz = Camera.GetRay(x, y)
            hits = { Physics.Raycast(ox, oy, oz, dx, dy, dz) }
            for i = 1, #hits, 4 do
                if (GameObject.GetName(hits[i]) == "Chessboard") then
                    posi, posj = split(Script.CallFunction(chessboard, "coordinatesToPosition", hits[i + 1], hits[i + 2], hits[i + 3]))
                    if (tonumber(posi) == selected.i) and (tonumber(posj) == selected.j) then
                    else
                        Script.CallFunction(GameObject.GetComponent(GameObject.Find("GameState"), "script:gamestate"), "setState", selected.i, selected.j, tonumber(posi), tonumber(posj))
                    end
                end
            end
            selected = nil
        end
    end
end