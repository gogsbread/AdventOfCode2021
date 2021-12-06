open Common

module part1 =
    let solve (input: List<string>) =
        input
        |> List.pairwise
        |> List.filter (fun (f, l) -> l > f)
        |> List.length

let input = Common.readIn
input |> part1.solve |> Common.writeOut
