completedMoves = {}

def possibleMoves(currPiles):
  nextMoves = []
  for i in range(0, len(currPiles)):
    remove = 1
    while remove <= currPiles[i]:
      copyPiles = currPiles.copy()
      copyPiles[i] -= remove
      move = "removes " + str(remove) + " sticks from pile number " + str(i+1)
      nextMoves.append((copyPiles, move))
      remove += 1
  return nextMoves

def gameOver(currPiles):
  for p in currPiles:
    if p != 0:
      return False
  return True

def examinePiles(piles):
  reference = 0
  for p in piles:
    reference = (reference ^ p)
  return reference


def minimax(piles, depth, maxPlayer):
  key = (tuple(sorted(piles)), maxPlayer)

  if key in completedMoves:
    return completedMoves[key]

  if depth == 0:
    bits = examinePiles(piles)
    score = 0
    if bits == 0:
      if maxPlayer:
        score = -1
      else:
        score = 1
    else:
      if maxPlayer:
        score = 1
      else:
        score = -1
    return (score, piles, "estimate")

  if gameOver(piles):
    if maxPlayer:
      result = (1, piles, "over")
    else:
      result = (-1, piles, "over")
    completedMoves[key] = result
    return result

  if maxPlayer:
    maxEval = -100
    bestPiles = None
    bestMove = None
    for nextMove in possibleMoves(piles):
      currEval, currPiles, currMove = minimax(nextMove[0], depth - 1, False)
      if currEval > maxEval:
        maxEval = currEval
        bestPiles = nextMove[0]
        bestMove = nextMove[1]
    result = (maxEval, bestPiles, bestMove)
    completedMoves[key] = result
    return result

  else:
    minEval = 100
    bestPiles = None
    bestMove = None
    for nextMove in possibleMoves(piles):
      currEval, currPiles, currMove = minimax(nextMove[0], depth - 1, True)
      if currEval < minEval:
        minEval = currEval
        bestPiles = nextMove[0]
        bestMove = nextMove[1]
    result = (minEval, bestPiles, bestMove)
    completedMoves[key] = result
    return result


def play(startingPiles, maxDepth, opponent = False):
  if not startingPiles:
    print("Number of piles must be at least one")
    return
  moveNumber = 0
  maxPlayer = True
  opponentTurn = True
  if opponent:
    print("Select which piles you would like to take from, and how much to take, in form X X\n")
  while True:
    if opponentTurn:
      if opponent:
        print("Your Turn:")
        print(startingPiles)
        P = 0
        T = 0
        while True:
          userInput = input().split()
          P = int(userInput[0])
          T = int(userInput[1])
          if P < 0 or P > len(startingPiles):
            print("That Pile Was Not Within the Range. Try Again.")
            continue
          if T < 1:
            print("You Must Take At Least One Stick. Try Again.")
            continue
          if T > startingPiles[P-1]:
            print("There Are Not Enough Sticks In That Pile. Try Again.")
            continue
          else:
            break
        startingPiles[P-1] -= T
        print(str("You remove " + str(T) + " sticks from pile number " + str(P)))
        print(startingPiles)
        if gameOver(startingPiles):
          print("You Lose!")
          break;
        opponentTurn = False
      else:
        score, piles, moveTaken = minimax(startingPiles, maxDepth, False)
        print("\nPlayer One Turn:")
        print(startingPiles)
        print("Player One", moveTaken)
        print(piles)
        print("\n")
        if gameOver(piles):
          print("Player Two Wins")
          break
        startingPiles = piles
        opponentTurn = False
    else:
      score, piles, moveTaken = minimax(startingPiles, maxDepth, True)
      moveNumber += 1
      print("\nPlayer Two Turn:")
      print(startingPiles)
      print("Player Two", moveTaken)
      print(piles)
      print("\n")
      if gameOver(piles):
        if opponent:
          print("You Win!")
        else:
          print("Player One Wins")
        break;
      startingPiles = piles
      opponentTurn = True

def start():
  piles = []
  print("Enter Numbers for Each Pile in Form: X1 X2 X3 X4...")
  userNums = input().split()
  for u in userNums:
    piles.append(int(u))
  if not piles or (len(piles) == 1 and piles[0] == 0):
      print("Error: Must Be At Least One Nonzero Pile")
      return
  print("Type 'Play' to Play or 'Auto' To Have The Program Play Itself")
  ans = input()
  ans = ans.lower()
  if ans == "play":
    print("Select Difficulty:\n 1. Easy 2. Medium 3. Impossible")
    dif = int(input())
    maxDepth = 0
    if dif == 1:
      maxDepth = 5
    if dif == 2:
      maxDepth = 10
    if dif == 3:
      maxDepth = 30
    play(piles, maxDepth, True)
  else:
    print("Enter The Maximum Search Depth")
    maxDepth = int(input())
    play(piles, maxDepth, False)