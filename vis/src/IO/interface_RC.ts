export class YX {
  y: number;
  x: number;
  constructor(y: number, x: number) {
    this.y = y;
    this.x = x;
  }
  to_key(): string {
    return `${this.y}_${this.x}`;
  }
}

export class Rect {
  public YXs: YX[];
  constructor(
    y1: number,
    x1: number,
    y2: number,
    x2: number,
    y3: number,
    x3: number,
    y4: number,
    x4: number
  ) {
    const yx1 = new YX(y1, x1);
    const yx2 = new YX(y2, x2);
    const yx3 = new YX(y3, x3);
    const yx4 = new YX(y4, x4);
    this.YXs = [yx1, yx2, yx3, yx4];
  }
}
