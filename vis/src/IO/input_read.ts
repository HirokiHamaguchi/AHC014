import FileParser from "./parser";

class Point {
  y: number;
  x: number;
  init: boolean;
  constructor(y: number, x: number, init: boolean) {
    this.y = y;
    this.x = x;
    this.init = init;
  }
}

export default class Input {
  public seed: number;
  public N: number;
  public M: number;
  public points: Point[];

  constructor(input_content: string, seed = -1) {
    this.seed = seed;
    const parser = new FileParser("input", input_content);
    this.N = parser.getInt();
    this.M = parser.getInt();
    parser.getNewline();
    this.points = new Array(this.M);
    for (let i = 0; i < this.M; i++) {
      const x = parser.getInt();
      const y = parser.getInt();
      parser.getNewline();
      this.points[i] = new Point(y, x, true);
    }
    console.assert(parser.isEOF());
    if (seed === -1) {
      console.log("[input read] done");
    }
  }
}
