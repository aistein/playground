exception List_Too_Small of int;;
let prodOfOtherNums l = 
    let n = List.length l in
    match l with
    (* Error Case *)
    | _ when n <= 1 -> raise (List_Too_Small n)
    (* Corner Cases *)
    | h::t when n == 2 -> (List.hd t)::(h::[])
    | f::(s::t) when n == 3 ->
            let a = s * List.hd t in
            let b = f * List.hd t in
            let c = (f * s)::[] in
            (a::(b::c))
    (* General Case *)
    | _ when n > 3 ->
            (* mult_up: consecutively multiply every element in list,
             * save intermediate products *)
            let rec mult_up m = function
                | [] -> m
                | h::t -> mult_up ((h * List.hd m)::m) t
            in
            (* In OCaml, we have imutable data,
             * so need two M arrays as oppsed to one in imperative languages *)
            let rl = List.rev l in
            let m_right = mult_up [List.hd rl] (List.tl rl) in 
            let m_left = mult_up [List.hd l] (List.tl l) in
            (* Remove last 2 from M-left and first 2 from M-right
             * - instead of using indexing to calc O[i] = M[i-1] * M[i+1]
             * - this allows us to use recursion! *)
            let first = List.hd (List.tl m_right) in
            let last = (List.hd (List.tl m_left))::[] in
            let rec mult_pairs o = function
                | ([],[]) -> List.rev o
                | (h1::t1, h2::t2) -> mult_pairs ((h1 * h2)::o) (t1,t2)
            in
            let cut_two list = List.tl (List.tl list) in
            (* Tricky alignment, example below...
             * - input = [1,2,3,4,5]
             * - m_left =  [120, 24, 6, 2, 1] --truncated--> [6, 2, 1]
             * - m_right = [120,120,60,20, 5] --truncated--> [60,20,5]
             * - desired output = [120] @ [60 * 1, 20 * 2, 5 * 20] @ [24]
             * --> note that to attain the desired output, m_left must be reversed *)
            let middle = mult_pairs [] (List.rev (cut_two m_left), cut_two m_right) in
            (first::middle)@last;;

            
            
(* Test size 0 *)
try 
    List.iter (Printf.printf "%d ") (prodOfOtherNums[]);
    Printf.printf "\n"
with
    List_Too_Small(_) -> Printf.printf "List is too small.\n";;

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

(* Test longer list *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[8;2;4;3;1;5]);;
Printf.printf "\n";;

(* Test List with 1 zero *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[6;2;0;3]);;
Printf.printf "\n";;

(* Test List with 2 zeros *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[4;0;9;1;0]);;
Printf.printf "\n";;

(* Test List with 1 negative number *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[-3;8;4]);;
Printf.printf "\n";;

(* Test List with all negative numbers *)
List.iter (Printf.printf "%d ") (prodOfOtherNums[-7;-1;-4;-2]);;
Printf.printf "\n";;
