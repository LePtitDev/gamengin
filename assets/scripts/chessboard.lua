chess = nil

-- Init chessboard
function start()
    chess = {
        { i=0, j=0, piece="Rook", pointer=GameObject.Instanciate("prefab:rook-white") },
        { i=0, j=1, piece="Knight", pointer=GameObject.Instanciate("prefab:knight-white") },
        { i=0, j=2, piece="Bishop", pointer=GameObject.Instanciate("prefab:bishop-white") },
        { i=0, j=3, piece="Queen", pointer=GameObject.Instanciate("prefab:queen-white") },
        { i=0, j=4, piece="King", pointer=GameObject.Instanciate("prefab:king-white") },
        { i=0, j=5, piece="Bishop", pointer=GameObject.Instanciate("prefab:bishop-white") },
        { i=0, j=6, piece="Knight", pointer=GameObject.Instanciate("prefab:knight-white") },
        { i=0, j=7, piece="Rook", pointer=GameObject.Instanciate("prefab:rook-white") },

        { i=1, j=0, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=1, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=2, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=3, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=4, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=5, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=6, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        { i=1, j=7, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-white") },
        
        { i=6, j=0, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=1, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=2, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=3, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=4, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=5, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=6, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        { i=6, j=7, piece="Pawn", pointer=GameObject.Instanciate("prefab:pawn-black") },
        
        { i=7, j=0, piece="Rook", pointer=GameObject.Instanciate("prefab:rook-black") },
        { i=7, j=1, piece="Knight", pointer=GameObject.Instanciate("prefab:knight-black") },
        { i=7, j=2, piece="Bishop", pointer=GameObject.Instanciate("prefab:bishop-black") },
        { i=7, j=3, piece="King", pointer=GameObject.Instanciate("prefab:king-black") },
        { i=7, j=4, piece="Queen", pointer=GameObject.Instanciate("prefab:queen-black") },
        { i=7, j=5, piece="Bishop", pointer=GameObject.Instanciate("prefab:bishop-black") },
        { i=7, j=6, piece="Knight", pointer=GameObject.Instanciate("prefab:knight-black") },
        { i=7, j=7, piece="Rook", pointer=GameObject.Instanciate("prefab:rook-black") }
    }

    for i, p in ipairs(chess) do
        x, y, z = getPosition(p.i, p.j)
        GameObject.SetPosition(p.pointer, x, y, z)
    end
end

function getPosition(i, j)
    return j * 2 - 7, 0, i * 2 - 7
end