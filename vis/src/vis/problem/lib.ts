import { YX, Rect } from "../../IO/interface_RC";

// DIR
// →↗↑↖←↙↓↘
export const dirLen = 8;
export const DX = [1, 1, 0, -1, -1, -1, 0, 1];
export const DY = [0, 1, 1, 1, 0, -1, -1, -1];

export function w(y: number, x: number, N: number) {
  const c = (N - 1) / 2;
  return (x - c) * (x - c) + (y - c) * (y - c) + 1;
}

export function deepCopyArray(base: any): any {
  if (!Array.isArray(base)) return base;
  const result = [];
  for (const sub of base) {
    result.push(deepCopyArray(sub));
  }
  return result;
}

export function is_valid(
  y: number,
  x: number,
  dir: number,
  grid: number[][],
  used: boolean[][][]
): [boolean, Rect | undefined] {
  console.assert(!grid[y][x]);
  const dir1 = dir;
  const dir2 = (dir + 2) % dirLen;

  const [ny11, nx11, len1] = getNext(y, x, grid, used, dir1);
  const [ny12, nx12, len2] = getNext(y, x, grid, used, dir2);
  if (ny11 === -1 || ny12 === -1) {
    return [false, undefined];
  }

  const [ny21, nx21] = getNext(ny11, nx11, grid, used, dir2);
  const [ny22, nx22] = getNext(ny12, nx12, grid, used, dir1);

  if (ny21 !== -1 && ny22 !== -1 && ny21 === ny22 && nx21 === nx22 && grid[ny21][nx21]) {
    return [true, new Rect(y, x, ny11, nx11, ny21, nx21, ny12, nx12)];
  }
  return [false, undefined];
}

export function applyRect(used: boolean[][][], rect: Rect) {
  console.log("applyRect");
  for (let i = 0; i < 4; i++) {
    let x = rect.YXs[i].x;
    let y = rect.YXs[i].y;
    const tx = rect.YXs[(i + 1) % 4].x;
    const ty = rect.YXs[(i + 1) % 4].y;
    let dx = Math.sign(tx - x);
    let dy = Math.sign(ty - y);
    let dir = 0;
    for (; dir < 8; dir++) {
      if (dx === DX[dir] && dy === DY[dir]) {
        break;
      }
    }
    while (x != tx || y != ty) {
      used[y][x][dir] = true;
      x += DX[dir];
      y += DY[dir];
      used[y][x][dir ^ 4] = true;
    }
  }
}

export function removeRect(used: boolean[][][], rect: Rect) {
  console.log("removeRect");
  for (let i = 0; i < 4; i++) {
    let x = rect.YXs[i].x;
    let y = rect.YXs[i].y;
    const tx = rect.YXs[(i + 1) % 4].x;
    const ty = rect.YXs[(i + 1) % 4].y;
    let dx = Math.sign(tx - x);
    let dy = Math.sign(ty - y);
    let dir = 0;
    for (; dir < 8; dir++) {
      if (dx === DX[dir] && dy === DY[dir]) {
        break;
      }
    }
    while (x != tx || y != ty) {
      used[y][x][dir] = false;
      x += DX[dir];
      y += DY[dir];
      used[y][x][dir ^ 4] = false;
    }
  }
}

export function printAns(ans: Rect[]) {
  let ret = "";
  ret += `${ans.length}\n`;
  ans.forEach((rect) => {
    ret += rect.toOutput() + "\n";
  });
  console.log(ret);
}

export function getNext(
  y: number,
  x: number,
  grid: number[][],
  used: boolean[][][],
  dir: number
): [number, number, number] {
  if (y == -1 || x == -1) {
    return [-1, -1, -1];
  }
  const N = grid.length;
  let len = 0;
  while (0 < x && x < N - 1 && 0 < y && y < N - 1) {
    if (used[y][x][dir]) {
      return [-1, -1, -1];
    }
    y += DY[dir];
    x += DX[dir];
    len++;
    if (grid[y][x]) {
      return [y, x, len];
    }
  }
  return [-1, -1, -1];
}

export function getNextWithLen(
  y: number,
  x: number,
  grid: number[][],
  used: boolean[][][],
  dir: number,
  len: number
): [number, number] {
  if (y == -1 || x == -1) {
    return [-1, -1];
  }
  const N = grid.length;
  let cnt = 0;
  while (0 < x && x < N - 1 && 0 < y && y < N - 1) {
    if (used[y][x][dir]) {
      return [-1, -1];
    }
    y += DY[dir];
    x += DX[dir];
    cnt++;
    if (grid[y][x] || cnt === len) {
      return [y, x];
    }
  }
  return [-1, -1];
}
