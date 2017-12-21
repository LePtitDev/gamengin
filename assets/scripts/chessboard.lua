-- Chess pieces
chess = nil

-- Last update time
lastUpdate = GetTime()

-- Piece movement animation
moveAnim = nil

-- Killed pieces list
killedPieces = nil

-- Init chessboard
function start()
    chess = {
        { i=0, j=0, team=0, piece="Rook", alive=true, pointer=GameObject.Instanciate("prefab:rook-white") },
        { i=0, j=1, team=0, piece="Knight", alive=true, pointer=GameObject.Instanciate("prefab:knight-white") },
        { i=0, j=2, team=0, piece="Bishop", alive=true, pointer=GameObject.Instanciate("prefab:bishop-white") },
        { i=0, j=3, team=0, piece="Queen", alive=true, pointer=GameObject.Instanciate("prefab:queen-white") },
        { i=0, j=4, team=0, piece="King", alive=true, pointer=GameObject.Instanciate("prefab:king-white") },
        { i=0, j=5, team=0, piece="Bishop", alive=true, pointer=GameObject.Instanciate("prefab:bishop-white") },
        { i=0, j=6, team=0, piece="Knight", alive=true, pointer=GameObject.Instanciate("prefab:knight-white") },
        { i=0, j=7, team=0, piece="Rook", alive=true, pointer=GameObject.Instanciate("prefab:rook-white") },

        { i=1, j=0, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=1, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=2, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=3, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=4, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=5, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=6, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=7, team=0, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-white") },
        
        { i=6, j=0, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=1, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=2, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=3, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=4, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=5, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=6, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=7, team=1, piece="Pawn", alive=true, pointer=GameObject.Instanciate("prefab:pawn-black") },
        
        { i=7, j=0, team=1, piece="Rook", alive=true, pointer=GameObject.Instanciate("prefab:rook-black") },
        { i=7, j=1, team=1, piece="Knight", alive=true, pointer=GameObject.Instanciate("prefab:knight-black") },
        { i=7, j=2, team=1, piece="Bishop", alive=true, pointer=GameObject.Instanciate("prefab:bishop-black") },
        { i=7, j=3, team=1, piece="King", alive=true, pointer=GameObject.Instanciate("prefab:king-black") },
        { i=7, j=4, team=1, piece="Queen", alive=true, pointer=GameObject.Instanciate("prefab:queen-black") },
        { i=7, j=5, team=1, piece="Bishop", alive=true, pointer=GameObject.Instanciate("prefab:bishop-black") },
        { i=7, j=6, team=1, piece="Knight", alive=true, pointer=GameObject.Instanciate("prefab:knight-black") },
        { i=7, j=7, team=1, piece="Rook", alive=true, pointer=GameObject.Instanciate("prefab:rook-black") }
    }
    killedPieces = {[0] = {}, [1] = {}}

    for i, p in ipairs(chess) do
        x, y, z = getPosition(p.i, p.j)
        GameObject.SetPosition(p.pointer, x, y, z)
    end
end

-- Update callback
function update()
    currentTime = GetTime()
    elapsedTime = currentTime - lastUpdate
    
    if (moveAnim == nil) then
    else
        alpha = (currentTime - moveAnim.start) / moveAnim.duration
        if (alpha > 1.0) then
            alpha = 1.0
        end
        GameObject.SetPosition(moveAnim.piece.pointer,
                               moveAnim.sx * (1.0 - alpha) + moveAnim.dx * alpha,
                               math.sin(alpha * math.pi) * 3,
                               moveAnim.sz * (1.0 - alpha) + moveAnim.dz * alpha)
        if (alpha >= 1.0) then
            moveAnim.piece.i = moveAnim.di
            moveAnim.piece.j = moveAnim.dj
            moveAnim = nil
        end
    end

    lastUpdate = currentTime
end

-- Get real position in the chessboard
function getPosition(i, j)
    return j * 2 - 7, 0, i * 2 - 7
end

-- Get position by real coordinates
function coordinatesToPosition(x, y, z)
    return math.ceil((z + 7) / 2 - 0.5) .. " " .. math.ceil((x + 7) / 2 - 0.5)
end

-- Get a piece by its position on the board
function getPieceByPos(pi, pj)
    for i, p in ipairs(chess) do
        if (p.alive and p.i == pi and p.j == pj) then
            return p
        end
    end
    return nil
end

-- Create animation for piece moving
function movePiece(si, sj, di, dj)
    if (moveAnim == nil) then else return end
    for i, p in ipairs(chess) do
        if (p.alive and p.i == si and p.j == sj) then
            other = getPieceByPos(di, dj)
            if (other == nil) then
            else
                killPiece(other)
            end
            sx, sy, sz = GameObject.GetPosition(p.pointer)
            dx, dy, dz = getPosition(di, dj)
            moveAnim = {
                sx = sx, sy = sy, sz = sz,
                dx = dx, dy = dy, dz = dz,
                di = di, dj = dj,
                piece = p,
                start = GetTime(),
                duration = 1.0
            }
            break
        end
    end
end

-- Kill a piece
function killPiece(piece)
    piece.alive = false
    count = #(killedPieces[piece.team])
    killedPieces[piece.team][count + 1] = piece
    x, y, z = 0, 0, 0
    if (piece.team == 0) then
        x, y, z = getPosition(9 + math.floor(count / 8), count % 8)
    else
        x, y, z = getPosition(-math.floor(count / 8) - 2, 7 - (count % 8))
    end
    GameObject.SetPosition(piece.pointer, x, y - 0.5, z)
end

-- Get the team and position of a piece
function getPieceDetails(piece)
    for i, p in ipairs(chess) do
        if (p.pointer == piece) then
            return p.team .. " " .. p.i .. " " .. p.j .. " " .. p.piece
        end
    end
    return ""
end