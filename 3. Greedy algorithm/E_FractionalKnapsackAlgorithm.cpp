#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Goods {
    char name;
    double weight, value;
    double vpw; // vpw = value per weight
};

// 정렬을 위해 비교 함수 작성
bool compareGoods(const Goods& a, const Goods& b) {
    return a.vpw > b.vpw; // 단위 무게 당 가치가 높은 순서대로 정렬
}

void print(const vector<Goods>& goods, double total_weight, double total_value) {
    printf("Goods\tWeight of goods in knapsack\tValue of goods in knapsack\n");
    for (const auto& item : goods) {
        printf("%c\t%.lf\t\t\t\t%.lf\n", item.name, item.weight, item.value);
    }
    printf("Sum\t%.lf\t\t\t\t%.lf\n", total_weight, total_value);
}

int main() {
    double total_weight = 0, total_value = 0;
    double max_weight = 40; // 배낭의 최대 무게

    // 데이터 하드코딩해서 넣기 (A: 백금, B: 금, C: 은, D: 주석)
    vector<Goods> goodsSet = {
        { 'A', 10, 600000, 0 },  // 백금
        { 'B', 15, 750000, 0 },  // 금
        { 'C', 25, 100000, 0 },  // 은
        { 'D', 50, 50000, 0 }    // 주석
    };

    // 단위 무게 당 가치 구하기 (value per weight)
    for (auto& item : goodsSet) {
        item.vpw = item.value / item.weight;
    }

    // 단위 무게 당 가치가 큰 순서대로 정렬
    sort(goodsSet.begin(), goodsSet.end(), compareGoods);

    // 단위 무게 당 가치가 가장 큰 물건을 먼저 가져오기
    vector<Goods> goodsList = {
        { 'A', 0, 0, 0 },
        { 'B', 0, 0, 0 },
        { 'C', 0, 0, 0 },
        { 'D', 0, 0, 0 }
    };

    int i = 0;
    while (i < goodsSet.size() && (total_weight + goodsSet[i].weight) <= max_weight) {
        total_weight += goodsSet[i].weight;
        total_value += goodsSet[i].value;
        goodsList[i].weight = goodsSet[i].weight;
        goodsList[i].value = goodsSet[i].value;
        i++;
    }

    // 남은 무게가 있다면 다음 물건의 일부를 가져오기
    if (i < goodsSet.size() && (max_weight - total_weight) > 0) {
        double remain_weight = max_weight - total_weight;
        double gain_per = remain_weight / goodsSet[i].weight;
        goodsList[i].weight = goodsSet[i].weight * gain_per;
        goodsList[i].value = goodsSet[i].value * gain_per;
        total_weight += goodsSet[i].weight * gain_per;
        total_value += goodsSet[i].value * gain_per;
    }

    print(goodsList, total_weight, total_value);

    return 0;
}
