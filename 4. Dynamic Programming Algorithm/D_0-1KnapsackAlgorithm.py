def knapsack(n):
    C = 11  # 배낭의 용량 (0인 경우 포함)
    N = 5   # 물건의 개수

    # 물건의 리스트 (weight, value, size 리스트)
    items = [
        {'weight': 0, 'value': 0, 'size': [0] * C},
        {'weight': 5, 'value': 10, 'size': [0] * C},
        {'weight': 4, 'value': 40, 'size': [0] * C},
        {'weight': 6, 'value': 30, 'size': [0] * C},
        {'weight': 3, 'value': 50, 'size': [0] * C},
    ]

    # 초기화
    for i in range(N):
        items[i]['size'][0] = 0
    for w in range(C):
        items[0]['size'][w] = 0

    # 동적 계획법을 이용한 배낭 문제 해결
    for i in range(1, n):
        # print("----------------------------------------")
        # print(f"{i}번째 물건")
        # print("----------------------------------------")
        for w in range(C):
            # print(f"w: {w}")
            # print(f"items[i]['weight']: {items[i]['weight']}")
            if items[i]['weight'] > w:
                # print("items[i]['weight'] > w")
                # print(f"items[i - 1]['size'][w]: {items[i - 1]['size'][w]}")
                items[i]['size'][w] = items[i - 1]['size'][w]
            else:
                # print("items[i]['weight'] <= w")
                # print(f"items[i - 1]['size'][w]: {items[i - 1]['size'][w]}")
                # print(f"items[i - 1]['size'][w - items[i]['weight']]: {items[i - 1]['size'][w - items[i]['weight']]}")
                items[i]['size'][w] = max(
                    items[i - 1]['size'][w],
                    items[i - 1]['size'][w - items[i]['weight']] + items[i]['value']
                )
            # print("----------------------------------------")

    # 결과 출력
    print("  -   ", end="")
    print("  -   ", end="")
    print("  -   ", end="")
    print(" | ", end="")
    for i in range(C):
        print(f"{i:2d}  ", end="")
    print()
    for i in range(N):
        if i == 0:
            print("----------------------------------------------------------------")
            print(" 물건 ", end="")
            print(" 가치 ", end="")
            print(" 무게 ", end="")
            print(" | ", end="")
        else:
            print(f"{i:4d}  ", end="")
            print(f"{items[i]['value']:4d}  ", end="")
            print(f"{items[i]['weight']:4d}  ", end="")
            print(" | ", end="")
        for j in range(C):
            print(f"{items[i]['size'][j]:2d}  ", end="")
        print()
        if i == 0:
            print("----------------------------------------------------------------")


if __name__ == "__main__":
    knapsack(5)
