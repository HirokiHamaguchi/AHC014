import { YX } from "./interface_RC";
import FileParser from "./parser";

export default class Input {
  public seed: number;
  public N: number;
  public M: number;
  public points: YX[];

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
      this.points[i] = new YX(y, x);
    }
    console.assert(parser.isEOF());
    if (seed === -1) {
      console.log("[input read] done");
    }
  }
}
