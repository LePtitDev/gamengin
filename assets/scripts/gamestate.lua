-- Chessboard informations
chessboard = nil

-- Init game
function start()
    chessboard = {}
    for i = 0, 7 do
        chessboard[i] = {}
        for j = 0, 7 do
            chessboard[i][j] = nil
        end
    end
    for i = 0, 7 do
        chessboard[1][i] = { team=0, piece="Pawn" }
        chessboard[6][i] = { team=1, piece="Pawn" }
    end
    chessboard[0][0] = { team=0, piece="Rook" }
    chessboard[0][1] = { team=0, piece="Knight" }
    chessboard[0][2] = { team=0, piece="Bishop" }
    chessboard[0][3] = { team=0, piece="Queen" }
    chessboard[0][4] = { team=0, piece="King" }
    chessboard[0][5] = { team=0, piece="Bishop" }
    chessboard[0][6] = { team=0, piece="Knight" }
    chessboard[0][7] = { team=0, piece="Rook" }
    chessboard[7][0] = { team=1, piece="Rook" }
    chessboard[7][1] = { team=1, piece="Knight" }
    chessboard[7][2] = { team=1, piece="Bishop" }
    chessboard[7][3] = { team=1, piece="King" }
    chessboard[7][4] = { team=1, piece="Queen" }
    chessboard[7][5] = { team=1, piece="Bishop" }
    chessboard[7][6] = { team=1, piece="Knight" }
    chessboard[7][7] = { team=1, piece="Rook" }
end

-- Get square state
function getState(i, j)
    if (chessboard[i][j] == nil) then
        return ""
    else
        return chessboard[i][j].team .. " " .. chessboard[i][j].piece
    end
end

-- Set piece position
function setState(si, sj, di, dj)
    chessboard[di][dj] = chessboard[si][sj]
    chessboard[si][sj] = nil
    Script.CallFunction(GameObject.GetComponent(GameObject.Find("Chessboard"), "script:chessboard"), "movePiece", si, sj, di, dj)
end