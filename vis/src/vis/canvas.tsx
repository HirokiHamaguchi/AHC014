import * as React from "react";
import Input from "../IO/input_read";
import Output from "../IO/output_read";
import DefaultCanvas from "./default_canvas";
import ErrorBoundary from "../basis/util/error_boundary";
import VisSVG from "./problem/visSVG";

export default function Canvas(props: { input_data: string; output_data: string }) {
  console.log("Canvas");

  if (props.input_data === "" && props.output_data === "") {
    return <DefaultCanvas />;
  }
  let input: Input, output: Output;
  try {
    input = new Input(props.input_data);
    output = new Output(props.output_data);
  } catch (e) {
    console.log(e);
    return <DefaultCanvas />;
  }

  return (
    <ErrorBoundary>
      <VisSVG input={input} output={output} />
    </ErrorBoundary>
  );
}
