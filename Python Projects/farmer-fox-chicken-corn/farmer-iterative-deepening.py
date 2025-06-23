class queue:
    def __init__(self):
      self.beg = 0
      self.end = -1
      self.capacity = 50
      self.count = 0
      self.arr = [None] * 50

    def empty(self):
      if self.count == 0:
        return True
      return False

    def add(self, state):
      self.end += 1
      if self.end == self.capacity:
        self.end = 0
      self.arr[self.end] = state
      self.count += 1
      if self.count == self.capacity:
        self.grow(self.capacity * 2)

    def grow(self, newcapacity):
      self.newarr = [None] * newcapacity
      i = 0
      while self.count != 0:
        self.newarr[i] = self.pop()
        i += 1
      self.beg = 0
      self.end = self.capacity - 1
      self.count = self.capacity
      self.arr = self.newarr
      self.capacity = newcapacity

    def pop(self):
      if self.count == 0:
        return None
      save = self.arr[self.beg]
      self.count -= 1
      self.beg += 1
      if self.beg == self.capacity:
        self.beg = 0
      return save

    def print(self):
      print(self.arr[0])

class path:
  def __init__(self, states, prev):
    self.states = states
    self.path = prev

  def print(self):
    for p in self.path:
      print(p)



puzzle = dict()
opposite = {"west" : "east" , "east" : "west"}

def start(user):
  global puzzle
  puzzle = user
  initial = Initial(user)
  initialPath = []
  buildStr = ""
  for k in initial.keys():
    buildStr += str(k + ", ")
  buildStr += "all begin on the west."
  initialPath.append(buildStr)
  userPath = path(initial, initialPath)
  final = findShortest(userPath)
  if final == None:
    print("No solution.")
  else:
    final.print()

def Initial(user):
  initial = dict()
  initial["farmer"] = "west"
  for k in user.keys():
    initial[k] = "west"
  return initial

def success(states):
  for s in states.values():
    if s == "west":
      return False
  return True

def safe(state):
  global puzzle
  for s in state.keys():
    if state["farmer"] != state[s]:
      if puzzle[s] == {}:
        continue
      for prey in puzzle[s]:
        if state[s] == state[prey]:
          return False
  return True

def switchSides(stateClass, object):
  global opposite
  newstates = stateClass.states.copy()
  newpath = stateClass.path.copy()
  if object == "farmer":
    newstates["farmer"] = opposite[stateClass.states["farmer"]]
    newpath.append(str("Move farmer from " + stateClass.states["farmer"] + " to " + opposite[stateClass.states["farmer"]]))
    return path(newstates, newpath)
  if stateClass.states["farmer"] != stateClass.states[object]:
    return None
  newstates["farmer"] = opposite[stateClass.states["farmer"]]
  newstates[object] = opposite[stateClass.states[object]]
  newpath.append(str("Move farmer and " + object + " from " + stateClass.states["farmer"] + " to " + opposite[stateClass.states["farmer"]]))
  return path(newstates, newpath)


def findShortest(initial):
  maxDepth = 1
  currDepth = 1
  stack = []
  keys = list(puzzle.keys())
  keys.append("farmer")
  while True:
    stack.append((initial, 1))
    while stack:
      currState, currDepth = stack.pop()
      if success(currState.states):
        return currState
      if currDepth < maxDepth:
        for k in keys:
          newState = switchSides(currState, k)
          if newState:
            if safe(newState.states):
              stack.append((newState, currDepth + 1))
    if currDepth < maxDepth:
      return None
    maxDepth += 1