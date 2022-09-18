import FileParser from "./parser";
import { YX, Rect } from "./interface_RC";

export default class Output {
  public K: number;
  public rects: Rect[];

  constructor(output_content: string) {
    const parser = new FileParser("output", output_content);
    this.K = parser.getInt();
    parser.getNewline();
    this.rects = new Array(this.K);
    for (let i = 0; i < this.K; i++) {
      const x1 = parser.getInt();
      const y1 = parser.getInt();
      const x2 = parser.getInt();
      const y2 = parser.getInt();
      const x3 = parser.getInt();
      const y3 = parser.getInt();
      const x4 = parser.getInt();
      const y4 = parser.getInt();
      const rect = new Rect(y1, x1, y2, x2, y3, x3, y4, x4);
      this.rects[i] = rect;
    }
    console.assert(parser.isEOF());
    console.log("[output read] done.");
  }
}
