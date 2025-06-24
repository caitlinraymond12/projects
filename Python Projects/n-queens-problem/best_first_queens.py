import heapq
import random

class problem:
    def __init__(self, n, c = 0, b = [0], copy = False):
      self.n = n
      if copy == False:
        self.board = [0] * n
        self.size = n
        for i in range(0, n):
          self.board[i] = random.randint(1, n)
        self.conflicts = self.countConflictsInitial(self.board, n)
      else:
        self.board = b
        self.conflicts = c

    def print(self):
      print("board: " , self.board)
      print("conflicts: ",  self.conflicts)

    def countConflictsInitial(self, board, n):
      conflicts = 0
      for col in range(0, n):
        row = board[col]
        if board.count(row) > 1:
          conflicts += board.count(row) - 1
        diagonal1 = col - row
        diagonal2 = col + row
        for j in range(0 , n):
          if j == col:
            continue
          if j - board[j] == diagonal1:
            conflicts += 1
          if j + board[j] == diagonal2:
            conflicts += 1
      return conflicts / 2

    def countConflictsColumn(self, board, col, n):
      conflicts = 0
      row = board[col]
      conflicts += board.count(row) - 1
      diagonal1 = col - row
      diagonal2 = col + row
      for j in range(0, n):
        if j == col:
          continue
        if j - board[j] == diagonal1:
          conflicts += 1
        if j + board[j] == diagonal2:
          conflicts += 1
      return conflicts

    def add(self, col, row):
      newboard = self.board.copy()
      newboard[col] = row
      conflictsRemoved = self.countConflictsColumn(self.board, col, self.n)
      conflictsAdded = self.countConflictsColumn(newboard, col, self.n)
      newconflicts = self.conflicts + conflictsAdded - conflictsRemoved
      return problem(n = self.n, c = newconflicts, b = newboard, copy = True)

    def getHash(self):
      hv = 169
      for i in range(0, self.n):
        hv = hv * 169 + i + self.board[i]
      return hv



def best_first(first, n):
  pq = []
  tiebreaker = 0
  heapq.heappush(pq, (first.conflicts, tiebreaker, first))
  visited = set()
  while pq:
    priority, dontcare, initial = heapq.heappop(pq)
    if priority == 0:
      return initial
    for col in range(0, n):
      initialRow = initial.board[col]
      for row in range(1, n + 1):
        if row == initialRow:
          continue
        curr = initial.add(col, row)
        if curr.conflicts <= initial.conflicts and curr.getHash() not in visited:
          visited.add(curr.getHash())
          tiebreaker += 1
          heapq.heappush(pq, (curr.conflicts, tiebreaker, curr))
  return None


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

def start(n):
  start = problem(n)
  final = best_first(start, n)
  if final:
    printboard(final.board)
  if final == None:
    print("final was none")