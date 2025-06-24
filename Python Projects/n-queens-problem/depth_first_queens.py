def check(current, row, col):
  if current.count(row) > 1:
    return False

  diagonal1 = col - current[col]
  for c in range(0, col):
    if c - current[c] == diagonal1:
      return False

  diagonal2 = col + current[col]
  for c in range(0, col):
    if c + current[c] == diagonal2:
      return False

  return True

n = 0

def dfs(initial, col):
  if col > n - 1:
    return None
  curr = initial.copy()
  for row in range(1, n + 1):
    curr[col] = row
    if check(curr, row, col):
      if col == n - 1:
        return(curr)
      result = dfs(curr, col+1)
      if result != None:
        return result


def printboard(board):
    n = len(board)
    for row in range(1, n+1):
        line = ""
        for col in range(n):
            if board[col] == row:
                line += "Q"
            else:
                line += "."
        print("".join(line))


def start(queens):
  global n
  n = queens
  start = [0] * queens
  solution = dfs(start, 0)
  if solution == None:
    print("No solution")
  else:
    printboard(solution)