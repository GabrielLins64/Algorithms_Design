import numpy as np
import pulp
import time

# FILEPATH = "data/input_A.txt"
FILEPATH = "data/input_B.txt"
# FILEPATH = "data/input_C.txt"
# FILEPATH = "data/input_D.txt"

def read_knapsack_data(filepath=FILEPATH):
  with open(filepath) as f:
    data = f.read().split('\n')
  W = int(data[0])
  items = np.array([x.split(' ') for x in data[1:]]).astype(int).tolist()
  return W, items

def solve_knapsack(input_path=FILEPATH):
  W, items = read_knapsack_data(input_path)
  N = len(items)

  x = pulp.pulp.LpVariable.dicts('item',
                                 range(N),
                                 lowBound=0,
                                 upBound=1,
                                 cat='Integer')

  problem = pulp.LpProblem("Knapsack_Problem", pulp.LpMaximize)

  problem += pulp.lpSum([ x[i] * items[i][0] for i in range(N) ]), "Objective: Maximize profit"
  problem += pulp.lpSum([ x[i] * items[i][1] for i in range(N) ]) <= W, "Constraint: Max capacity"

  start = time.time()
  problem.solve(pulp.PULP_CBC_CMD(msg=0))
  end = time.time()

  used = [int(v.varValue) for v in problem.variables()]

  total_weight = 0.0
  for i in range(N):
    if (x[i].value() == 1):
      total_weight += items[i][1]

  print(f"Solving time: {end - start} s")
  print(f"Optimality: {pulp.LpStatus[problem.status]}")
  print(f"Used items {np.sum(used)}: {used}")
  print(f"Percentage used of the knapsack: {round(100 * total_weight / W, 2)} %")
  print(f"Total value: {pulp.value(problem.objective)}")

def solve_mining_problem():
  problem = pulp.LpProblem("Problema da Mineradora", pulp.LpMaximize)

  ll = pulp.LpVariable("Liga Leve", 0, cat="Integer")
  lr = pulp.LpVariable("Liga Rígida", 0, cat="Integer")
  lf = pulp.LpVariable("Liga Forte", 0, cat="Integer")

  problem += 250*ll + 300*lr + 400*lf # Função objetivo

  # (qtd. de minério que cada liga usa * a qtd. da liga)
  problem += 5*ll + 3*lr + 5*lf <= 100 # Para o minério vermelho
  problem += 3*ll + 5*lr + 5*lf <= 80 # Para o minério preto

  problem.solve()

  print(f"Quantidade de Ligas leves: {ll.varValue}")
  print(f"Quantidade de Ligas rígidas: {lr.varValue}")
  print(f"Quantidade de Ligas fortes: {lf.varValue}")
