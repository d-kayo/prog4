import random

NUM_GRAPHS = 10
NODES = 50

for g in range(1, NUM_GRAPHS + 1):
    edges = []
    for u in range(NODES):
        num_edges = random.randint(1, 5)  # 1–5 outgoing edges per node
        targets = random.sample(range(NODES), num_edges)
        for v in targets:
            if v == u:
                continue  # avoid self-loop
            w = random.randint(-10, 20)  # random weight
            edges.append((u, v, w))
    
    print(f"Graph {g}:")
    print(f"{NODES} {len(edges)}")
    for u, v, w in edges:
        print(f"{u} {v} {w}")
    source = random.randint(0, NODES-1)
    print(source)  # random source node
    print("\n" + "#"*40 + "\n")
