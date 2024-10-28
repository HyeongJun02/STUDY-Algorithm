def coin_change(amount, coins):
    coin_count = {}
    remain = amount

    for coin in coins:
        count = remain // coin
        remain -= count * coin
        coin_count[coin] = count

    return coin_count

if __name__ == "__main__":
    amount = 2780
    coins = [500, 100, 50, 10]
    coin_count = coin_change(amount, coins) # 함수 실행해서 결과 coin_count에 저장

    # 2780 Won
    output = f"{amount} Won - "
    # 동전들 output에 저장
    output += ", ".join([f"{coin} Won: {count}" for coin, count in coin_count.items() if count > 0])
    print(output)
