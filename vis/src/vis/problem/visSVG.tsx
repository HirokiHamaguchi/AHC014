import * as React from "react";
import Input from "../../IO/input_read";
import Output from "../../IO/output_read";
import INFO from "../../basis/util/load_info";
import DefaultSVG from "../default_svg";
import CanvasVisInfo from "../canvas_vis_info";
import IgnoreStyle from "../ignore_style";
// import ColorPalette from "../color_palette";

import { YX, Rect } from "../../IO/interface_RC";
import {
  dirLen,
  DX,
  DY,
  w,
  deepCopyArray,
  is_valid,
  applyRect,
  removeRect,
  printAns,
  getNext,
  getNextWithLen,
} from "./lib";

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
  grid: number[][],
  used: boolean[][][],
  candIdx: number,
  setGrid: React.Dispatch<React.SetStateAction<number[][]>>,
  setUsed: React.Dispatch<React.SetStateAction<boolean[][][]>>
): Rect[] {
  const results: Rect[] = [];

  if (grid[y][x]) {
    return [];
  }

  for (let dir = 0; dir < dirLen; dir++) {
    const [ok, rect] = is_valid(y, x, dir, grid, used);
    if (ok) {
      results.push(rect!);
    }
  }

  if (results.length !== 0) {
    const final_rect = results[(candIdx + 1) % results.length];
    setGrid((grid) => {
      const new_grid = deepCopyArray(grid);
      new_grid[y][x] = 2;
      return new_grid;
    });
    setUsed((used) => {
      const new_used = deepCopyArray(used);
      applyRect(new_used, final_rect);
      return new_used;
    });
  }

  return results;
}

function Circle(props: {
  y: number;
  x: number;
  N: number;
  type: number;
  grid: number[][];
  used: boolean[][][];
  setGrid: React.Dispatch<React.SetStateAction<number[][]>>;
  setUsed: React.Dispatch<React.SetStateAction<boolean[][][]>>;
  setAns: React.Dispatch<React.SetStateAction<Rect[]>>;
}) {
  const N = props.N;
  const sz = INFO.canvas_size / N;
  const maxW = w(0, 0, N);

  const [r, setR] = React.useState(sz / 5);
  const [candIdx, setCandIdx] = React.useState(-1);
  const [lastRect, setlastRect] = React.useState(new Rect(-1, -1, -1, -1, -1, -1, -1, -1));

  let color: string;
  if (props.type == 0) {
    const c = 10 + (w(props.y, props.x, N) / maxW) * (256 - 10);
    color = `rgb(${c},${c},${c})`;
  } else if (props.type === 1) {
    color = "white";
  } else if (props.type === 2) {
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
          console.log(candIdx);
          const results = onCircleClick(
            props.y,
            props.x,
            props.grid,
            props.used,
            candIdx,
            props.setGrid,
            props.setUsed
          );
          if (results.length) {
            const newCandIdx = (candIdx + 1) % results.length;
            setlastRect(results[newCandIdx]);
            props.setAns((ans) => [...ans, results[newCandIdx]]);
            setCandIdx(newCandIdx);
          }
        }}
      />
    </>
  );
}

function getDoubleNext(y: number, x: number, grid: number[][], used: boolean[][][], dir: number) {
  console.assert(grid[y][x]);
  const dir1 = dir;
  const dir2 = (dir + 2) % dirLen;

  const [ny11, nx11, len1] = getNext(y, x, grid, used, dir1);
  const [ny12, nx12, len2] = getNext(y, x, grid, used, dir2);
  if (ny11 === -1 || ny12 === -1) {
    return;
  }

  const [ny21, nx21] = getNextWithLen(ny11, nx11, grid, used, dir2, len2);
  const [ny22, nx22] = getNextWithLen(ny12, nx12, grid, used, dir1, len1);

  if (ny21 === -1 || ny22 === -1) {
    return;
  }

  if (ny21 === ny22 && nx21 === nx22 && !grid[ny21][nx21]) {
    return new Rect(ny21, nx21, ny11, nx11, y, x, ny12, nx12);
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

function drawRects(grid: number[][], used: boolean[][][]) {
  console.log("drawRects");
  const N = grid.length;
  const sz = INFO.canvas_size / N;
  const JSXrects: JSX.Element[] = [];
  const JSXgoodpoints: JSX.Element[] = [];
  for (let y = 0; y < N; y++) {
    for (let x = 0; x < N; x++) {
      for (let dir = 0; dir < 8; dir++) {
        if (dir < dirLen / 2 && used[y][x][dir]) {
          JSXrects.push(
            <line
              key={`${y}_${x}_${dir}_line`}
              x1={(x + 0.5) * sz}
              x2={(x + DX[dir] + 0.5) * sz}
              y1={(N - y - 0.5) * sz}
              y2={(N - y - DY[dir] - 0.5) * sz}
              stroke="yellow"
            />
          );
        }
        if (grid[y][x]) {
          const rect = getDoubleNext(y, x, grid, used, dir);
          if (rect === undefined) continue;
          JSXrects.push(
            <g key={`${y}-${x}_${dir}`}>
              <RectSVG rect={rect} N={N} is_entity={false} />
            </g>
          );
          JSXgoodpoints.push(
            <circle
              style={IgnoreStyle}
              key={`${rect.YXs[0].y}_${rect.YXs[0].x}_${dir}_goodpoint`}
              cx={sz * (rect.YXs[0].x + 0.5)}
              cy={sz * (N - rect.YXs[0].y - 0.5)}
              r={sz / 5}
              fill="orange"
            />
          );
        }
      }
    }
  }
  return [JSXrects, JSXgoodpoints];
}

function SubVisSVG(props: {
  input: Input;
  output: Output;
  grid: number[][];
  used: boolean[][][];
  ans: Rect[];
  setGrid: React.Dispatch<React.SetStateAction<number[][]>>;
  setUsed: React.Dispatch<React.SetStateAction<boolean[][][]>>;
  setAns: React.Dispatch<React.SetStateAction<Rect[]>>;
}) {
  console.log("subVisSVG");

  const N = props.input.N;
  const M = props.input.M;

  props.output.rects.forEach((elem) => {
    console.assert(false); // not implemented yet
    // let new_yx: YX | undefined;
    // elem.YXs.forEach((yx) => {
    //   if (props.grid[yx.y][yx.x]) {
    //     console.assert(new_yx === undefined);
    //     new_yx = yx;
    //   }
    // });
    // if (new_yx === undefined) {
    //   throw new Error("rect dosen't have new point");
    // }
    // props.setGrid((grid) => {
    //   grid[new_yx!.y][new_yx!.x] = 2;
    //   return grid;
    // });
  });

  const JSXpoints: JSX.Element[] = [];
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
      JSXpoints.push(
        <g key={`${y}-${x}`}>
          <Circle
            y={y}
            x={x}
            N={N}
            type={point_type}
            grid={props.grid}
            used={props.used}
            setGrid={props.setGrid}
            setUsed={props.setUsed}
            setAns={props.setAns}
          />
        </g>
      );
    }
  }

  const [JSXrects, JSXgoodpoints] = drawRects(props.grid, props.used);

  printAns(props.ans);

  return (
    <>
      <CanvasVisInfo score={Math.round(1e6 * ((N * N) / M) * (sumW / S))} input={props.input} />
      <DefaultSVG>
        <>
          {JSXrects}
          {JSXpoints}
          {JSXgoodpoints}
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
  const [ans, setAns] = React.useState(new Array());

  return (
    <SubVisSVG
      input={props.input}
      output={props.output}
      grid={grid}
      used={used}
      ans={ans}
      setGrid={setGrid}
      setUsed={setUsed}
      setAns={setAns}
    />
  );
}
