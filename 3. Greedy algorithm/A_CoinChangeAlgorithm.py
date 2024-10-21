# 잔돈 반환하는 함수
def coin_change(amount, coins):
    coin_count = {}
    remain = amount # 남은 돈

    for coin in coins: # 큰 동전부터
        count = remain // coin # 몫을 count에 저장
        remain -= count * coin # 남은 돈의 값 조정
        coin_count[coin] = count

    return coin_count

# 메인 함수
if __name__ == "__main__":
    amount = 2780                       # 거스름돈
    coins = [500, 100, 50, 10]          # 동전들
    coin_count = coin_change(amount, coins) # 함수 실행해서 결과 coin_count에 저장

    # 2780 Won
    output = f"{amount} Won - "
    # 동전들 output에 저장
    output += ", ".join([f"{coin} Won: {count}" for coin, count in coin_count.items() if count > 0])
    print(output)
