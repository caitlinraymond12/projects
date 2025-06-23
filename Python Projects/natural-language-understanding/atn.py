from copy import copy
import pprint

dictionary_file_name = "vocab.txt"
grammar_file_name = "grammar.txt"

quicktrace = False
trace = False
stepping = False
debug_output = False

dictionary = {}

def read_dictionary():
  global dictionary
  dictionary = {}
  num = 0
  f = open(dictionary_file_name, "r")
  for line in f:
    num += 1
    parts = line.split()
    if len(parts) == 0:
      continue
    if len(parts) < 2:
      print(dictionary_file_name, "line", num, "too short")
      continue
    word = parts[0]
    pos = parts[1]
    if word in dictionary:
      defns = dictionary[word]
    else:
      defns = {}
      dictionary[word] = defns
    if pos in defns:
      print(dictionary_file_name, "line", num, "duplicate entry for", word, "as", pos)
      continue
    defn = {}
    dictionary[word][pos] = defn
    for entry in parts[2:]:
      item = entry.split(":")
      if item[0] in defn:
        print(dictionary_file_name, "line", num, "duplicate entry for", item[0], "in", word, "as", pos)
        continue
      if len(item) == 1:
        vals = { "true" }
      else:
        vals = set(v for v in item[1].split(","))
      defn[item[0]] = vals
  f.close()

def show_dictionary():
  global dictionary
  for word in sorted(dictionary):
    print(word, end = ":\n")
    defs = dictionary[word]
    for pos in defs:
      print("  ", pos, ":", sep = "", end = "")
      ents = defs[pos]
      for key in ents:
        print(" ", key, "=", "/".join(ents[key]), sep = "", end = "")
      print()

def summarise_dictionary():
  global dictionary
  words = sorted(dictionary)
  print(len(words), "different words")
  pos = set()
  for w in words:
    for p in dictionary[w]:
      pos.add(p)
  print(len(pos), "categories:")
  pos = sorted(pos)
  for p in pos:
    ents = {}
    for w in words:
      dw = dictionary[w]
      if p in dw:
        dwp = dw[p]
        for i in dwp:
          if i != "root":
            if i in ents:
              ent = ents[i]
            else:
              ent = set()
              ents[i] = ent
            for v in dwp[i]:
              ent.add(v)
    print("  ", p, ":", sep = "")
    for k in sorted(ents):
      print("    ", k, ": ", ", ".join(ents[k]), sep = "")

grammar = {}
groups = {}
start = None
realstart = None

def read_grammar():
  global grammar, start, realstart, groups
  grammar = {}
  start = None
  realstart = None
  num = 0
  rules = None
  graph = None
  lengthening = False
  received = ""
  f = open(grammar_file_name, "r")
  for line in f:
    num += 1
    line = line.strip()
    if line == "":
      if not lengthening:
        continue
    elif lengthening:
      received = received + " " + line
      lengthening = False
    else:
      received = line
    if received.endswith("\\"):
      received = received[0 : -1]
      lengthening = True
      continue
    if received == "" or received.isspace():
      continue
    if received.startswith("graph"):
      if graph != None:
        if "start" not in nodes:
          print(grammar_file_name, "line", num, "graph", graph, "has no start node")
          raise Exception("bad")
      parts = received.split()
      if len(parts) != 2:
        print(grammar_file_name, "line", num, "wrong format for graph introduction")
        raise Exception("bad")
      graph = parts[1]
      if parts[1] in grammar:
        print(grammar_file_name, "line", num, "redefinition of graph", graph)
        raise Exception("bad")
      nodes = {}
      grammar[graph] = nodes
      node = None
    elif received.startswith("group"):
      parts = received.split()
      if len(parts) < 2:
        print(grammar_file_name, "line", num, "not enough for group definition")
        raise Exception("bad")
      name = parts[1]
      if name in groups:
        print(grammar_file_name, "line", num, "redefinition of group", name)
        raise Exception("bad")
      groups[name] = ("cat", ) + tuple(parts[2:])
    elif received.startswith("start"):
      parts = received.split()
      if len(parts) != 2:
        print(grammar_file_name, "line", num, "wrong format for start definition")
        raise Exception("bad")
      start = parts[1]
      realstart = start
    elif received.startswith("node"):
      if graph == None:
        print(grammar_file_name, "line", num, "node definition outside any graph")
        raise Exception("bad")
      parts = received.split()
      if len(parts) != 2:
        print(grammar_file_name, "line", num, "wrong format for node introduction")
        raise Exception("bad")
      node = parts[1]
      if node in nodes:
        print(grammar_file_name, "line", num, "redefinition of node", node, "in graph", graph)
        raise Exception("bad")
      rules = []
      nodes[node] = rules
    else:
      if node == None:
        print(grammar_file_name, "line", num, "rule outside any node definition")
        raise Exception("bad")
      try:
        rule = eval(received)
      except:
        print(grammar_file_name, "line", num, "badly formatted rule\n")
        raise
      if type(rule) != list or len(rule) != 3:
        print(grammar_file_name, "line", num, "badly formatted rule type", type(rule), "length", len(rule))
        raise Exception("bad")
      rules.append(rule)
  f.close()
  if start == None:
    print(grammar_file_name, "no start graph")
    raise Exception("bad")

def show_grammar():
  global grammar
  for graph in sorted(grammar):
    print(graph, end = ":\n")
    nodes = grammar[graph]
    for node in nodes:
      print("  ", node, end = ":\n")
      arcs = nodes[node]
      for arc in arcs:
        print("     ", arc[a_condition])
        print("        ", arc[a_disposition])
        print("        ", arc[a_action])
    print()

s_graph = 0
s_node = 1
s_inpos = 2
s_arcpos = 3
s_build = 4
s_notes = 5
s_lastcall = 6

a_condition = 0
a_disposition = 1
a_action = 2

typed = None
stack = ()
used = None
successes = 0

phrases = [ "the very big fat orange cat" ]

def clean(s):
  r = bytearray()
  for chr in s:
    ascii = ord(chr)
    if ascii == 8:
      if len(r) > 0:
        del r[-1]
    else:
      r.append(ascii)
  return r.decode()

def make_start_state():
  global start, realstart, typed, phrases, grammar
  start = realstart
  typed = clean(input(" <- ")).split()
  if len(typed) == 1:
    if typed[0].isdecimal():
      n = int(typed[0])
      if n > 0 and n <= len(phrases):
        typed = phrases[n - 1].split()
  if typed[0].startswith("*"):
    start = typed[0][1:]
    typed = typed[1:]
  grammar["**"] = {"start": [["always", ("sub", start), ["receive", ("to", "done")]]],
                   "done": [["end", (), ("accept", "nosolo")]]}
  print(typed, "as", start)
  return ["**", "start", 0, 0, [], {}, ()]

def backtrack():
  global stack
  if stack == ():
    print("\nbacktrack on empty stack\n")
    raise Exception("bad")
  stack = stack[1]

def simple(x):
  if not x:
    return x
  elif type(x) in [str, int, float, bool]:
    return x
  elif type(x) == tuple:
    return tuple(minimal(i) for i in x)
  elif type(x) == list:
    return [minimal(i) for i in x]
  elif type(x) == dict:
    return [",".join(k + ":" + minimal(x[k]) for k in x)]
  else:
    return type(x).__name__

def minimal(x):
  if not x:
    return x
  elif type(x) in [str, int, float, bool]:
    return x
  elif type(x) == tuple or type(x) == list or type(x) == dict:
    return ",".join(almost_nothing(i) for i in x)
  else:
    return type(x).__name__

def almost_nothing(x):
  if not x or type(x) in [str, int, float, bool]:
    return str(x)
  else:
    return type(x).__name__

def print_stack_item(t):
  print(" gr", t[s_graph], "nd", t[s_node], "in", t[s_inpos],
         "ar", t[s_arcpos], "bu", simple(t[s_build]), "nt", simple(t[s_notes]),
         "lc", id(t[s_lastcall]))

def print_stack(max = 999999):
  global stack
  if stack == ():
    print("  stack empty")
    return
  p = stack
  i = 0
  while p != () and i <= max:
    print("  stack ", "top" if i == 0 else str(i).rjust(3), "id", id(p), end = "")
    print_stack_item(p[0])
    p = p[1]
    i += 1

catword = None

def parse():
  global typed, grammar, stack, trace, used, successes, catword
  stack = (make_start_state(), ())
  state = None
  steps = 0
  successes = 0
  while True:
    if stack == ():
      print()
      if successes == 0:
        print("finished, meaningless: no successful parses")
      elif successes == 1:
        print("finished, unambiguous: one successful parse")
      else:
        print("finished, ambiguous:", successes, "successful parses")
      print("************************************************************")
      return

    state = stack[0]
    graphname, nodename, inpos, arcpos, build, notes, lastcall = state
    word = typed[inpos] if inpos < len(typed) else "end"
    graph = grammar[graphname]
    arcs = graph[nodename]
    steps += 1
    if trace:
      print("\n\nstep ", steps, ", word ", word, sep = "")
      print_stack()
      if stepping:
        input("press enter to continue: ")
    elif quicktrace:
      if stack == ():
        print("empty stack")
      else:
        print_stack_item(stack[0])
    used = None
    newstate = None
    catword = None

    if arcpos >= len(arcs):
      if trace:
        print("  no more arcs: backtrack")
      backtrack()
      continue
    arc = arcs[arcpos]

    cond = arc[a_condition]
    if trace:
      print("checking arc", arcpos, "condition", cond)
    p = evaluate(cond, state)
    if p == False:
      state[s_arcpos] += 1
      continue
    elif p != True:
      print("\nnon-boolean result", p, "in condition");
      raise Exception("bad")

    disp = arc[a_disposition]
    if disp == ():
      newstate = state.copy()
      perform(arc[a_action], newstate)
    elif disp == "consume":
      if quicktrace:
        print("  consume", typed[state[s_inpos]])
      newstate = state.copy()
      newstate[s_inpos] += 1
      if newstate[s_inpos] > len(typed):
        print("\nattempt to consume input when none left");
        raise Exception("bad")
      perform(arc[a_action], newstate)
    elif disp[0] == "sub":
      newstate = ([disp[1], "start", state[s_inpos], 0, [], {}, ()])
      stack = (newstate, stack)
      newstate[s_lastcall] = stack
    state[s_arcpos] += 1

def print_parse(item, ind = 0):
  if type(item) == tuple:
    if len(item) == 2:
      print("    " * ind, item[0])
      print_parse(item[1], ind)
    elif len(item) < 2:
      print("    " * ind, "BAD TUPLE", item)
    else:
      print("    " * ind, item[0], '"' + item[1] + '"', item[2:])
  elif type(item) == list:
    for i in item:
      print_parse(i, ind + 1)
  else:
    print("    " * ind, "BAD", type(item), "ITEM", item)

upnotes = None

def evaluate(condition, state):
  global typed, grammar, dictionary, stack, trace, used, upnotes, catword, groups
  printres = True
  r = False

  if state[s_inpos] >= len(typed):
    word = "<end>"
    entries = {}
  else:
    word = typed[state[s_inpos]]
    if word not in dictionary:
      print("\nunknown word", word)
      raise Exception("bad")
    entries = dictionary[word]
  if trace:
    print("  check", condition, end = ": ")
  lenc = len(condition)

  if type(condition) == str:
    if condition == "always":
      r = True
    elif condition == "end":
      r = word == "<end>"
    elif condition == "more":
      r = state[s_inpos] + 1 < len(typed)
    else:
      r = condition

  elif type(condition) == tuple and lenc > 0:
    op = condition[0]

    if op == "cat":
      for pos in condition[1:]:
        r = pos in entries
        if r:
          catword = (pos, word)
          used = (pos, word, None)
          break

    elif op == "word":
      for i in condition[1:]:
        r = condition[i] == word
        if r:
          used = ("word", word, None)
          break

    elif op == "group" and lenc == 2:
      if condition[1] not in groups:
        print("\nuse of undefined group", condition[1])
        raise Exception("bad")
      r = evaluate(groups[condition[1]], state)

    elif op == "noted" and lenc == 2:
      r = condition[1] in state[s_notes] and state[s_notes][condition[1]] != False

    elif op == "noted" and lenc > 2:
      for i in condition[2:]:
        r = condition[1] in state[s_notes] and state[s_notes][condition[1]] == evaluate[i]
        if r:
          break

    elif op == "value" and lenc == 2:
      if condition[1] in state[s_notes]:
        r = state[s_notes][condition[1]]
      else:
        r = False

    elif op == "=" and lenc == 3:
      a = evaluate(condition[1], state)
      b = evaluate(condition[2], state)
      if type(a) == set:
        if type(b) == set:
          r = len(a & b) != 0
        else:
          r = b in a
      elif type(b) == set:
        r = a in b
      else:
        r = a == b

    elif op == "has" and lenc >= 2:
      if catword == None:
        print("\nuse of has without prior successful cat")
        raise Exception("bad")
      entry = dictionary[catword[1]][catword[0]]
      if lenc == 2:
        r = condition[1] in entry and entry[condition[1]] != False
      elif lenc > 2:
        if condition[1] in entry:
          vals = entry[condition[1]]
          for i in condition[2:]:
            r = evaluate(i, state) in vals
            if r:
              break

    elif op == "tag" and lenc == 2:
      if catword == None:
        print("\nuse of has without prior successful cat")
        raise Exception("bad")
      entry = dictionary[catword[1]][catword[0]]
      if condition[1] not in entry:
        r = set()
      else:
        r = entry[condition[1]]

    elif op == "not" and lenc == 2:
      r = evaluate(condition[1], state)
      if type(r) != bool:
        print("\nbad operand for not:", r)
        raise Exception("bad")
      r = not r

    elif op == "or":
      printres = False
      if trace:
        print()
      for part in condition[1:]:
        r = evaluate(part, state)
        if r == True:
          break
        elif r != False:
          print("\nbad operand for and:", r)
          raise Exception("bad")

    else:
      print("\nbad condition", condition)
      raise Exception("bad")

  elif type(condition) == list:
    printres = False
    if trace:
      print()
    for part in condition:
      r = evaluate(part, state)
      if r == False:
        break
      elif r != True:
        print("\nbad operand for implicit and:", r)
        raise Exception("bad")

  else:
    print("\nbad condition", condition)
    raise Exception("bad")
  if trace and printres:
    print(r)
  return r

newbuild = None

def perform(action, state, depth = 0):
  global typed, grammar, dictionary, stack, trace, used, newbuild, successes, upnotes
  if depth == 0:
    newbuild = None
  word = typed[state[s_inpos]] if state[s_inpos] < len(typed) else "<end>"

  if action == "accept":
    action = ("accept", "asis")

  lena = len(action)

  if type(action) == list:
    for a in action:
      perform(a, state, depth + 1)

  elif type(action) == str:
    if trace:
      print("  action", action)

    if action == "build":
      if not newbuild:
        newbuild = state[s_build].copy()
      newbuild.append((used[0], used[1], dictionary[used[1]][used[0]]))
      state[s_build] = newbuild

    elif action == "receive":
      if not newbuild:
        newbuild = state[s_build].copy()
      newbuild.append((used[0], used[1]))
      state[s_build] = newbuild

    elif action == "stay":
      state[s_arcpos] = 0
      stack = (state, stack)

    elif action == "fail":
      backtrack()

    else:
      print("bad action", action, "in graph", state[s_graph])

  elif type(action) == tuple:
    if trace:
      print("  action", action)
    op = action[0]

    if op == "accept" and lena == 2:
      if quicktrace:
        print("  accept", state[s_graph])
      detail = action[1]
      build = state[s_build]
      if detail == "nosolo":
        if len(build) <= 1:
          result = (build[0][0], build[0][1])
        else:
          result = (state[s_graph], build)
      elif detail == "asis":
        result = (state[s_graph], build)
      else:
        result = (evaluate(detail, state), build)

      if trace:
        print("subgraph success for", state[s_graph])
      if state[s_graph] == "**":
        successes += 1
        if trace:
          print("\n")
        print()
        print("***************************************************************************")
        if debug_output:
          print("Exact result:")
          p = pprint.PrettyPrinter(indent = 5, width = 100)
          p.pprint(result)
          print("***************************************************************************")
        print_parse(result)
        if trace:
          print("***************************************************************************\n")
        backtrack()

      else:
        if trace:
          print_parse(result)
        lastcall = state[s_lastcall]
        oldstate = lastcall[1][0].copy()
        if trace or quicktrace:
          print("back to", id(stack), end = " ")
          print_stack_item(oldstate)
        oldgraph = grammar[oldstate[s_graph]]
        oldnode = oldgraph[oldstate[s_node]]
        arc = oldnode[oldstate[s_arcpos] - 1]
        action = arc[a_action]
        oldstate[s_inpos] = state[s_inpos]
        used = result
        upnotes = state[s_notes]
        perform(action, oldstate)

    elif op == "to" and lena == 2:
      state[s_node] = action[1]
      state[s_arcpos] = 0
      stack = (state, stack)

    elif op == "jump" and lena == 2:
      state[s_node] = action[1]
      state[s_arcpos] = 0
      stack = (state, stack[1])

    elif op == "note" and lena == 2:
      state[s_notes][action[1]] = True

    elif op == "note" and lena == 3:
      value = evaluate(action[2], state)
      state[s_notes][action[1]] = value

    elif op == "lift" and lena == 2:
      if type(upnotes) == dict and action[1] in upnotes:
        state[s_notes][action[1]] = upnotes[action[1]]

    else:
      print("bad action", op, "in graph", state[s_graph])
      raise Exception("bad")

  else:
    print("bad action", action, "in graph", state[s_graph])
    raise Exception("bad")

read_dictionary()
summarise_dictionary()
read_grammar()
while True:
  parse()