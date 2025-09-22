class Node {
  constructor(x, y, g = 0, h = 0, parent = null) {
    this.x = x; // 위치 x
    this.y = y; // 위치 y
    this.g = g; // 시작점 ~ 현재까지 비용
    this.h = h; // 휴리스틱 (현재 ~ 목표)
    this.f = g + h; // 총 비용
    this.parent = parent; // 경로 역추적용
  }
}

// 맨해튼 거리 휴리스틱
function heuristic(a, b) {
  return Math.abs(a.x - b.x) + Math.abs(a.y - b.y);
}

function aStar(grid, start, goal) {
  const openSet = [];
  const closedSet = [];
  const startNode = new Node(start.x, start.y);
  const goalNode = new Node(goal.x, goal.y);

  openSet.push(startNode);

  while (openSet.length > 0) {
    // f 값이 가장 작은 노드를 선택
    openSet.sort((a, b) => a.f - b.f);
    const current = openSet.shift();
    closedSet.push(current);

    // 목표에 도착하면 경로 반환
    if (current.x === goalNode.x && current.y === goalNode.y) {
      const path = [];
      let temp = current;
      while (temp) {
        path.push([temp.x, temp.y]);
        temp = temp.parent;
      }
      return path.reverse();
    }

    // 상하좌우 이웃 탐색
    const directions = [
      [0, -1],
      [0, 1],
      [-1, 0],
      [1, 0],
    ];

    for (let [dx, dy] of directions) {
      const nx = current.x + dx;
      const ny = current.y + dy;

      // 지도 범위 확인
      if (nx < 0 || ny < 0 || nx >= grid.length || ny >= grid[0].length)
        continue;
      if (grid[nx][ny] === 1) continue; // 벽은 패스

      // 이미 탐색한 노드인지 확인
      if (closedSet.some((n) => n.x === nx && n.y === ny)) continue;

      const g = current.g + 1;
      const h = heuristic({ x: nx, y: ny }, goalNode);
      const neighbor = new Node(nx, ny, g, h, current);

      const existing = openSet.find((n) => n.x === nx && n.y === ny);
      if (!existing || g < existing.g) {
        openSet.push(neighbor);
      }
    }
  }

  return []; // 경로 없음
}

// ──────────────── 테스트 ────────────────
const grid = [
  [0, 0, 0, 0, 0],
  [1, 1, 0, 1, 0],
  [0, 0, 0, 1, 0],
  [0, 1, 1, 0, 0],
  [0, 0, 0, 0, 0],
];

const start = { x: 0, y: 0 };
const goal = { x: 4, y: 4 };

const path = aStar(grid, start, goal);
console.log('최단 경로:', path);
