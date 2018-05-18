exception List_Too_Small of int;;
let prodOfOtherNums l = 
    let n = List.length l in
    match l with
    | _ when n <= 1 -> raise (List_Too_Small n)
    | h::t when n == 2 -> (List.hd t)::(h::[])
    | f::(s::t) when n == 3 ->
            let a = s * List.hd t in
            let b = f * List.hd t in
            let c = (f * s)::[] in
            (a::(b::c))
    | _ when n > 3 ->
            let rec mult_up m = function
                | [] -> m
                | h::t -> mult_up ((h * List.hd m)::(List.tl m)) t
            in
            let rl = List.rev l in
            mult_up [List.hd rl] (List.tl rl) ;;





(* Test size 1 *)
try 
    List.iter (Printf.printf "%d ") (prodOfOtherNums[1]);
    Printf.printf "\n"
with
    List_Too_Small(_) -> Printf.printf "List is too small.\n";;

(* Test size 2 *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[1;2]);;
Printf.printf "\n";;

(* Test size 3 *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[1;2;3]);;
Printf.printf "\n";;

(* Test size 5 *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[1;2;3;4;5]);;
Printf.printf "\n";;

