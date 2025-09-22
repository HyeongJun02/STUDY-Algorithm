tasks = {
    't1': [7, 8],
    't2': [3, 7],
    't3': [1, 5],
    't4': [5, 9],
    't5': [0, 2],
    't6': [6, 8],
    't7': [1, 6]
}

machines = [[] for _ in range(3)]

# 시작 시간으로 정렬
sorted_tasks = sorted(tasks.items(), key=lambda x: x[1][0])
print(sorted_tasks)

for task_name, (start, end) in sorted_tasks:
    for machine in machines:
        # 기계가 비어있음
        # 마지막 작업이 끝났음
        if not machine or machine[-1][2] <= start:
            machine.append((task_name, start, end))
            break

# ===================================================================================
schedule = [[' ' for _ in range(10)] for _ in range(3)]

for i, machine in enumerate(machines):
    for task_name, start, end in machine:
        for t in range(start, end):
            schedule[i][t] = task_name

print("          ", end="")
for t in range(10):
    print(f"{t:>6}", end="")
print()

for i, row in enumerate(schedule):
    print(f"Machine {i + 1:<2}", end="")
    for cell in row:
        print(f"{cell:>6}", end="")
    print()
