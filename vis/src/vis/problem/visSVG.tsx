import * as React from "react";
import Input from "../../IO/input_read";
import Output from "../../IO/output_read";
import INFO from "../../basis/util/load_info";
import DefaultSVG from "../default_svg";
import CanvasVisInfo from "../canvas_vis_info";
// import IgnoreStyle from "../ignore_style";
// import ColorPalette from "../color_palette";
import { YX, Rect } from "../../IO/interface_RC";
import { dirLen, DX, DY, w } from "./lib";

function Title(props: { y: number; x: number; N: number }) {
  const content = `y:${props.y}\nx:${props.x}\nw:${w(props.y, props.x, props.N)}`;
  return <title>{content}</title>;
}

function onCircleEnter(y: number, x: number, setR: React.Dispatch<React.SetStateAction<number>>) {
  setR((r) => r * 2);
}
function onCircleLeave(y: number, x: number, setR: React.Dispatch<React.SetStateAction<number>>) {
  setR((r) => r / 2);
}
function onCircleClick(
  y: number,
  x: number,
  setGrid: React.Dispatch<React.SetStateAction<number[][]>>
) {
  setGrid((grid) => {
    grid[y][x] = 2;
    return grid;
  });
}

function Circle(props: {
  y: number;
  x: number;
  N: number;
  type: number;
  setGrid: React.Dispatch<React.SetStateAction<number[][]>>;
}) {
  const N = props.N;
  const sz = INFO.canvas_size / N;
  const maxW = w(0, 0, N);

  const [r, setR] = React.useState(sz / 5);

  let color: string;
  if (props.type == 0) {
    const c = 30 + (w(props.y, props.x, N) / maxW) * (256 - 30);
    color = `rgb(${c},${c},${c})`;
  } else if (props.type === 1) {
    color = "white";
  } else if (props.type === 1) {
    color = "red";
  } else {
    throw new Error("type is not correct");
  }
  return (
    <>
      <Title y={props.y} x={props.x} N={N} />
      <circle
        cx={sz * (props.x + 0.5)}
        cy={sz * (N - props.y - 0.5)}
        r={r}
        fill={color}
        onMouseEnter={(event) => {
          event.preventDefault();
          onCircleEnter(props.y, props.x, setR);
        }}
        onMouseLeave={(event) => {
          event.preventDefault();
          onCircleLeave(props.y, props.x, setR);
        }}
        onClick={(event) => {
          event.preventDefault();
          onCircleClick(props.y, props.x, props.setGrid);
        }}
      />
    </>
  );
}

// interface CellInfo {
//   r: number;
//   c: number;
//   setStyle: React.Dispatch<React.SetStateAction<string>>;
// }

function getNext(y: number, x: number, grid: number[][], dir: number): [number, number, number] {
  if (y == -1 || x == -1) {
    return [-1, -1, -1];
  }
  const N = grid.length;
  let len = 0;
  while (0 < x && x < N - 1 && 0 < y && y < N - 1) {
    y += DY[dir];
    x += DX[dir];
    len++;
    if (grid[y][x]) {
      return [y, x, len];
    }
  }
  return [-1, -1, -1];
}

function getNextWithLen(
  y: number,
  x: number,
  grid: number[][],
  dir: number,
  len: number
): [number, number] {
  if (y == -1 || x == -1) {
    return [-1, -1];
  }
  const N = grid.length;
  let cnt = 0;
  while (0 < x && x < N - 1 && 0 < y && y < N - 1) {
    y += DY[dir];
    x += DX[dir];
    cnt++;
    if (grid[y][x] || cnt === len) {
      return [y, x];
    }
  }
  return [-1, -1];
}

function getDoubleNext(y: number, x: number, grid: number[][], dir: number) {
  console.assert(grid[y][x]);
  const dir1 = dir;
  const dir2 = (dir + 2) % dirLen;

  const [ny11, nx11, len1] = getNext(y, x, grid, dir1);
  const [ny12, nx12, len2] = getNext(y, x, grid, dir2);
  if (ny11 === -1 || ny12 === -1) {
    return;
  }

  const [ny21, nx21] = getNextWithLen(ny11, nx11, grid, dir2, len2);
  const [ny22, nx22] = getNextWithLen(ny12, nx12, grid, dir1, len1);
  if (ny21 === -1 || ny22 === -1) {
    return;
  }

  if (ny21 === ny22 && nx21 === nx22 && !grid[ny21][nx21]) {
    return new Rect(y, x, ny11, nx11, ny21, nx21, ny12, nx12);
  }
}

function RectSVG(props: { rect: Rect; N: number; is_entity: boolean }) {
  const sz = INFO.canvas_size / props.N;
  const str = props.rect.YXs.reduce(
    (prev, cur) => prev + `${sz * (cur.x + 0.5)},${sz * (props.N - cur.y - 0.5)} `,
    ""
  );
  return <polygon points={str} fill="none" stroke="blue" />;
}

function drawRects(grid: number[][]) {
  const N = grid.length;
  const rects: JSX.Element[] = [];
  for (let y = 0; y < N; y++) {
    for (let x = 0; x < N; x++) {
      if (grid[y][x]) {
        for (let dir = 0; dir < 8; dir++) {
          const rect = getDoubleNext(y, x, grid, dir);
          if (rect === undefined) continue;
          rects.push(
            <g key={`${y}-${x}_${dir}`}>
              <RectSVG rect={rect} N={N} is_entity={false} />
            </g>
          );
        }
      }
    }
  }
  console.log(rects);

  return rects;
}

function SubVisSVG(props: {
  input: Input;
  output: Output;
  grid: number[][];
  setGrid: React.Dispatch<React.SetStateAction<number[][]>>;
  used: boolean[][][];
  setUsed: React.Dispatch<React.SetStateAction<boolean[][][]>>;
}) {
  const N = props.input.N;
  const M = props.input.M;

  props.output.rects.forEach((elem) => {
    console.assert(false); // not implemented yet
    let new_yx: YX | undefined;
    elem.YXs.forEach((yx) => {
      if (props.grid[yx.y][yx.x]) {
        console.assert(new_yx === undefined);
        new_yx = yx;
      }
    });
    if (new_yx === undefined) {
      throw new Error("rect dosen't have new point");
    }
    props.setGrid((grid) => {
      grid[new_yx!.y][new_yx!.x] = 2;
      return grid;
    });
  });

  const points: JSX.Element[] = [];
  let S = 0;
  let sumW = 0;
  for (let y = 0; y < N; y++) {
    for (let x = 0; x < N; x++) {
      S += w(y, x, N);
      let point_type = 0;
      if (props.grid[y][x] === 1) {
        sumW += w(y, x, N);
        point_type = 1;
      }
      if (props.grid[y][x] === 2) {
        sumW += w(y, x, N);
        point_type = 2;
      }
      points.push(
        <g key={`${y}-${x}`}>
          <Circle y={y} x={x} N={N} type={point_type} setGrid={props.setGrid} />
        </g>
      );
    }
  }

  const rects: JSX.Element[] = drawRects(props.grid);

  return (
    <>
      <CanvasVisInfo score={Math.round(1e6 * ((N * N) / M) * (sumW / S))} input={props.input} />
      <DefaultSVG>
        <>
          {points}
          {rects}
        </>
      </DefaultSVG>
    </>
  );
}

export default function VisSVG(props: { input: Input; output: Output }) {
  const N = props.input.N;

  const _grid: number[][] = [...Array(N)].map((_) => Array(N).fill(0));
  const _used: boolean[][][] = [...Array(N)].map((_) =>
    [...Array(N)].map((_) => Array(dirLen).fill(false))
  );

  props.input.points.forEach((elem) => {
    _grid[elem.y][elem.x] = 1;
  });

  const [grid, setGrid] = React.useState(_grid);
  const [used, setUsed] = React.useState(_used);

  return (
    <SubVisSVG
      input={props.input}
      output={props.output}
      grid={grid}
      setGrid={setGrid}
      used={used}
      setUsed={setUsed}
    />
  );
}
