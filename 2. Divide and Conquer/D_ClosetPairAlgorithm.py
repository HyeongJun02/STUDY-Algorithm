import math
import time

# 두 좌표 사이의 거리를 계산하는 함수
def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

# 분할 정복을 이용해 최단 거리를 찾는 함수
def closest_pair_recursive(points_sorted_by_x, points_sorted_by_y):
    n = len(points_sorted_by_x)

    # 기저 조건: 점의 개수가 3개 이하일 경우 직접 계산
    if n <= 3:
        min_dist = float('inf')
        for i in range(n):
            for j in range(i + 1, n):
                dist = distance(points_sorted_by_x[i], points_sorted_by_x[j])
                if dist < min_dist:
                    min_dist = dist
        return min_dist

    # 중간 지점을 기준으로 좌우로 나누기
    mid = n // 2
    mid_point = points_sorted_by_x[mid]

    left_by_x = points_sorted_by_x[:mid]
    right_by_x = points_sorted_by_x[mid:]

    left_by_y = list(filter(lambda x: x[0] <= mid_point[0], points_sorted_by_y))
    right_by_y = list(filter(lambda x: x[0] > mid_point[0], points_sorted_by_y))

    # 재귀적으로 좌측과 우측에서 최단 거리를 구함
    dist_left = closest_pair_recursive(left_by_x, left_by_y)
    dist_right = closest_pair_recursive(right_by_x, right_by_y)

    # 두 부분의 최소 거리
    min_dist = min(dist_left, dist_right)

    # 중앙에 걸친 부분에서 최단 거리를 찾음
    strip = [p for p in points_sorted_by_y if abs(p[0] - mid_point[0]) < min_dist]
    min_dist_strip = closest_in_strip(strip, min_dist)

    return min(min_dist, min_dist_strip)

# 중앙에 걸친 부분에서 최단 거리를 찾는 함수
def closest_in_strip(strip, d):
    min_dist = d
    for i in range(len(strip)):
        for j in range(i + 1, min(i + 7, len(strip))):
            dist = distance(strip[i], strip[j])
            if dist < min_dist:
                min_dist = dist
    return min_dist

# Closest Pair 알고리즘을 위한 메인 함수
def closest_pair(points):
    points_sorted_by_x = sorted(points, key=lambda p: p[0])
    points_sorted_by_y = sorted(points, key=lambda p: p[1])
    return closest_pair_recursive(points_sorted_by_x, points_sorted_by_y)

if __name__ == "__main__":
    # 입력 파일로부터 좌표 데이터를 읽어오기
    input_file = "input_closest_pair.txt"
    points = []

    with open(input_file, "r") as file:
        for line in file:
            x, y = map(int, line.split())
            points.append((x, y))

    # 시간 측정 시작
    start_time = time.time()

    # Closest Pair 알고리즘 실행
    min_distance = closest_pair(points)

    # 시간 측정 종료
    end_time = time.time()

    # 최단 거리 출력
    print(f"최단 거리: {min_distance:.6f}")

    # 실행 시간 출력
    print(f"실행 시간: {end_time - start_time:.6f} 초")
