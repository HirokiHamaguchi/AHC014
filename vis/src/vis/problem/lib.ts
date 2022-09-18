// DIR
// →↗↑↖←↙↓↘
export const dirLen = 8;
export const DX = [1, 1, 0, -1, -1, -1, 0, 1];
export const DY = [0, 1, 1, 1, 0, -1, -1, -1];

export function w(y: number, x: number, N: number) {
  const c = (N - 1) / 2;
  return (x - c) * (x - c) + (y - c) * (y - c) + 1;
}
