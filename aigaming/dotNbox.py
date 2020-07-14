import numpy
import json
import random
botName = '4386_20B_5701-defbot'


def calculate_move(gamestate):

    possibleMvs, specialMvs = getPossibleEdgeIndex(gamestate)
    if len(specialMvs) > 0:
        bestMv, bestScore = minimax(0, gamestate, specialMvs, 1)
        # print([bestMv, bestScore])
        if len(possibleMvs) == 0 or bestScore > 0:
            return gamestate['Grid'][bestMv][:2]

        _, SecbestScore = minimax(0, applyChange(possibleMvs[0], gamestate), specialMvs, 1)
        
        if SecbestScore > bestScore:
            return possibleMvs[0]

        return gamestate['Grid'][bestMv][:2]

    return gamestate['Grid'][possibleMvs[0]][:2]


def getPossibleEdgeIndex(gamestate):
    mvs = [] # refer to set 3 
    specialMvs = [] # refer to set 1
    badMvs = [] # refer to set 2

    grid = gamestate['Grid']

    for i in range(len(grid) - 1, -1, -1):
        if grid[i][2] == -1: # -1 for edge not occupied
            boxes = getBoxIndex(grid[i][:2], gamestate)
            status = max( # take the related squares with most edge 
                [sum(numpy.array(gamestate['Squares'][b][0])[:, 2]) for b in boxes])
            if status > 2:
                specialMvs.append(i)
            elif status > 1:
                badMvs.append(i)
            else:
                mvs.append(i)

    if len(mvs) > 0:
        # refer to rule 1 - "Avoid creating the third boundary"
        return mvs, specialMvs
    
    # refer to rule 2 - "Form the box if available"
    # specialMvs will always be returned
    return badMvs, specialMvs
# %%


def getBoxIndex(e: list, gamestate):
    rs = []

    for i in range(len(gamestate['Squares'])):
        for edge in gamestate['Squares'][i][0]:
            if edge[:2] == e:
                rs.append(i)
                break
    return rs
# %%


def points(id: int, gamestate):
    boxes = getBoxIndex(
        gamestate['Grid'][id][:2], gamestate)

    return sum([sum(numpy.array(gamestate['Squares'][b][0])[:, 2]) == 3
                for b in boxes])


def applyChange(id: int, gamestate):
    e = gamestate['Grid'][id][:2]

    boxes = getBoxIndex(e, gamestate)

    for b in boxes:
        for i in range(4):
            if gamestate['Squares'][b][0][i][:2] == e:
                gamestate['Squares'][b][0][i][2] = True

    gamestate['Grid'][id][2] = 1

def undoChange(id: int, gamestate):
    e = gamestate['Grid'][id][:2]

    boxes = getBoxIndex(e, gamestate)

    for b in boxes:
        for i in range(4):
            if gamestate['Squares'][b][0][i][:2] == e:
                gamestate['Squares'][b][0][i][2] = False

    gamestate['Grid'][id][2] = -1

def minimax(depth, gamestate, legalMoves: list, turns):
    # depth is defined as "counts the number of turn changes", so to allow prediction when player continuously get points.
    bestScore = 0
    bestMv = -1

    if depth == 2: # timeout otherwise
        return bestMv, bestScore

    for mvid in legalMoves:
        # Get the point get by adding the selected edge
        pt = points(mvid, gamestate)
        # Apply changes so to update the remaining possible edge 
        applyChange(mvid, gamestate)
        
        remainingMvs = legalMoves.copy()
        remainingMvs.remove(mvid)

        # Only consider the edge that can get points (will be discussed below)
        # badMvs, remainingMvs = getPossibleEdgeIndex(gamestate)

        # print([depth, turns, bestScore, pt, mvid])

        if pt > 0: # turn continue if user get point
            _, score = minimax(depth, gamestate, remainingMvs, turns)
        else: # switch user when no box is formed
            _, score = minimax(depth + 1, gamestate, remainingMvs, -1 * turns)
       
        # update the score
        score += turns * pt

        if turns == -1:
            # elements will lead you to worst score
            if bestMv == -1 or bestScore > score:
                bestScore = score
                bestMv = mvid
        else:
            if bestMv == -1 or score > bestScore:
                bestScore = score
                bestMv = mvid
                
        remainingMvs.append(mvid)
        undoChange(mvid, gamestate)

    return bestMv, bestScore


# %%
