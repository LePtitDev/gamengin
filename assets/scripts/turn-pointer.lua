-- Turn
turn = 0

-- Start game
function start()
    turn = 0
    GameObject.SetRotation(this, 0, 180, 0)
end

-- Switch turn
function switch()
    GameObject.SetRotation(this, 0, turn * 180, 0)
    turn = (turn + 1) % 2
end