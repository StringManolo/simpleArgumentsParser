interface Is {
    [key: string]: string | boolean;
}
interface Ic {
    [key: string]: string | boolean;
}
type StringNumberTuple = [string, number];
interface Icli {
    s: Is;
    c: Ic;
    o: StringNumberTuple[];
    p: string | false;
    e: number[];
    noArgs: boolean;
    argc: number;
    color: any;
}
declare const parseCLI: () => Promise<Readonly<Icli>>;
export default parseCLI;
