import Input from "./input_read";

interface VariableInfo {
  id: keyof Input;
  description: string;
  value: number;
}

export default function getInputVariables(input?: Input): VariableInfo[] {
  return [
    { id: "N", description: "grid size (odd,31-61)", value: input ? input.N : -1 },
    { id: "M", description: "num of init dots(N≤M≤N^2/12)", value: input ? input.M : -1 },
  ];
}
